#include <stdint.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include "comm.h"
#include "node.h"
#include "graph.h"
#include "glthread.h"
#include "interface.h"
#include "link.h"
#include "../Layer2/layer2.h"

static uint32_t udp_port_number = 40000;

static uint8_t send_buffer[MAX_PACKET_BUFFER_SIZE];
static uint8_t recv_buffer[MAX_PACKET_BUFFER_SIZE];

typedef struct packet_
{
    uint32_t interface_id;
    uint32_t data_size;
    uint8_t data[MAX_PACKET_BUFFER_SIZE - sizeof(uint32_t)];
} packet_t;

static void _pkt_receive(node_t *receiving_node,
                         uint8_t *pkt_with_aux_data,
                         uint32_t pkt_size)
{
    packet_t pkt;
    memset(&pkt, 0, sizeof(pkt));
    memcpy(&pkt, pkt_with_aux_data, pkt_size);

    interface_t *interface = node_get_interface_by_id(receiving_node, pkt.interface_id);

    comm_receive(receiving_node, interface, pkt.data, pkt.data_size);
}

static uint32_t
_get_next_udp_port_number()
{
    return udp_port_number++;
}

static int
_send_pkt_out(int sock_fd, void *data, uint32_t data_size, uint32_t dst_port_no)
{
    int rc = 0;
    struct sockaddr_in dest_addr;

    struct hostent *host = (struct hostent *)gethostbyname("127.0.0.1");

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = dst_port_no;
    dest_addr.sin_addr = *((struct in_addr *)host->h_addr);

    rc = sendto(sock_fd, data, data_size, 0, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
    return rc;
}

static void *
_comm_start_pkt_receiver_thread(void *args)
{
    graph_t *graph = (graph_t *)args;
    node_t *node;
    glthread_t *curr;

    fd_set active_sock_fd_set, backup_sock_fd_set;

    int sock_max_fd = 0;
    int bytes_recvd = 0;

    int addr_len = sizeof(struct sockaddr);

    FD_ZERO(&active_sock_fd_set);
    FD_ZERO(&backup_sock_fd_set);

    struct sockaddr_in sender_addr;

    ITERATE_OVER_GLTHREAD(&graph->graph_node_list, curr)
    {
        node = graph_glue_to_node(curr);
        if (node_get_udp_sock_fd(node) > sock_max_fd)
        {
            sock_max_fd = node_get_udp_sock_fd(node);
        }
        FD_SET(node_get_udp_sock_fd(node), &backup_sock_fd_set);
    }
    while (1)
    {
        memcpy(&active_sock_fd_set, &backup_sock_fd_set, sizeof(fd_set));
        select(sock_max_fd + 1, &active_sock_fd_set, NULL, NULL, NULL);

        ITERATE_OVER_GLTHREAD(&graph->graph_node_list, curr)
        {
            node = graph_glue_to_node(curr);
            if (FD_ISSET(node_get_udp_sock_fd(node), &active_sock_fd_set))
            {
                memset(recv_buffer, 0, MAX_PACKET_BUFFER_SIZE);
                bytes_recvd = recvfrom(node_get_udp_sock_fd(node),
                                       recv_buffer,
                                       MAX_PACKET_BUFFER_SIZE, 0,
                                       (struct sockaddr *)&sender_addr,
                                       &addr_len);
                _pkt_receive(node, recv_buffer, bytes_recvd);
            }
        }
    }
}

static int
comm_send_pkt_out(uint8_t *pkt, uint32_t pkt_size, interface_t *interface)
{
    int rc = 0;
    packet_t packet;

    interface_t *nbr_interface = link_get_other_interface(interface);

    node_t *parent_node = interface_get_parent(interface);
    node_t *nbr_node = interface_get_parent(nbr_interface);

    uint32_t dst_port_no = node_get_udp_port_number(nbr_node);

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0)
    {
        printf("ERROR: Sending socket creation failed, errno = %d\n", errno);
        return -1;
    }

    memset(send_buffer, 0, MAX_PACKET_BUFFER_SIZE);
    packet.interface_id = interface_get_id(nbr_interface);
    packet.data_size = pkt_size;
    memcpy(packet.data, pkt, pkt_size);

    memcpy(send_buffer, &packet, MAX_PACKET_BUFFER_SIZE);

    rc = _send_pkt_out(sock, &packet, sizeof(packet), dst_port_no);

    close(sock);
    return rc;
}

void comm_start_receiver_thread(graph_t *graph)
{
    pthread_attr_t attr;
    pthread_t recv_pkt_thread;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&recv_pkt_thread,
                   &attr,
                   _comm_start_pkt_receiver_thread,
                   (void *)graph);
}

void comm_init_udp_socket(node_t *node)
{
    node_set_udp_port_number(node, _get_next_udp_port_number());

    int udp_sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in node_addr;
    node_addr.sin_family = AF_INET;
    node_addr.sin_port = node_get_udp_port_number(node);
    node_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(udp_sock_fd, (struct sockaddr *)&node_addr, sizeof(struct sockaddr)) == -1)
    {
        printf("Error : socket bind failed for Node %u\n", node_get_id(node));
        return;
    }
    node_set_udp_sock_fd(node, udp_sock_fd);
}

int comm_receive(node_t *recv_node, interface_t *recv_interface, void *data, uint32_t size)
{
    layer2_frame_recv(recv_node, recv_interface, data, size);
    return 0;
}

void comm_send(graph_t *graph, uint32_t node_id, uint32_t interface_id, void *msg, uint32_t msg_size)
{
    node_t *node = graph_get_node_by_id(graph, node_id);
    interface_t *intf = node_get_interface_by_id(node, interface_id);
    comm_send_pkt_out(msg, msg_size, intf);
}

void comm_send_flood(graph_t *graph, uint32_t node_id, uint32_t exempted_intf_id, void *msg, uint32_t msg_size)
{
    node_t *node = graph_get_node_by_id(graph, node_id);
    interface_t *intf = NULL;
    NODE_ITERATE_OVER_INTF_START(node, intf)
    {
        if (interface_get_id(intf) != exempted_intf_id)
        {
            comm_send_pkt_out(msg, msg_size, intf);
        }
    }
    NODE_ITERATE_OVER_INTF_END()
}