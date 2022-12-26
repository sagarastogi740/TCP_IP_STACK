#ifndef __COMM_H__
#define __COMM_H__

#include "node.h"
#include "graph.h"

#define MAX_PACKET_BUFFER_SIZE 2048

void comm_init_udp_socket(node_t *node);
void comm_start_receiver_thread(graph_t *graph);
void comm_send(graph_t *graph, uint32_t node_id, uint32_t interface_id, void *msg, uint32_t msg_size);
void comm_send_flood(graph_t *graph, uint32_t node_id, uint32_t exempted_intf_id, void *msg, uint32_t msg_size);
int comm_receive(node_t *recv_node, interface_t *recv_interface, void *data, uint32_t size);

#endif /**/