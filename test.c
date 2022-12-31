/*
 * +--------+               +--------+
 * |        |               |        |
 * |        +---------------+        |
 * |   R0   |0             0|   R1   |
 * |        |               |        |
 * +---+----+               +---+----+
 *     | 1                      |1
 *     |                        |
 *     |                        |
 *     |        +--------+      |
 *     |        |        |      |
 *     |       1|        |0     |
 *     +--------+   R2   +------+
 *              |        |
 *              +--------+
 */

#include <stdio.h>
#include <unistd.h>
#include "lib/graph.h"
#include "lib/node.h"
#include "lib/interface.h"
#include "lib/comm.h"
#include "Layer2/arp_entry.h"
#include "Layer2/arp_table.h"
#include "Layer2/arp.h"
#include "Layer2/ethernet.h"

graph_t *build_topology()
{
    graph_t *topo = graph_create("First topology");
    node_t *R0 = graph_create_node(topo, "10.0.0.1");
    node_t *R1 = graph_create_node(topo, "10.0.0.2");
    node_t *R2 = graph_create_node(topo, "10.0.0.3");

    comm_start_receiver_thread(topo);

    graph_insert_link_between_two_nodes(R0, R1, "192.168.0.1", "192.168.0.2", 24, 24, 0);
    graph_insert_link_between_two_nodes(R1, R2, "192.168.1.1", "192.168.1.2", 24, 24, 1);
    graph_insert_link_between_two_nodes(R2, R0, "192.168.2.1", "192.168.2.2", 24, 24, 2);
    ipv4_t ip = net_ip_string_to_ipv4("192.168.1.2");
    node_send_arp_broadcast_request(R1, &ip, 24);
    ip = net_ip_string_to_ipv4("192.168.0.1");
    node_send_arp_broadcast_request(R1, &ip, 24);
    ip = net_ip_string_to_ipv4("192.168.2.2");
    node_send_arp_broadcast_request(R2, &ip, 24);
    ip = net_ip_string_to_ipv4("192.168.1.1");
    node_send_arp_broadcast_request(R2, &ip, 24);
    ip = net_ip_string_to_ipv4("192.168.0.2");
    node_send_arp_broadcast_request(R0, &ip, 24);
    ip = net_ip_string_to_ipv4("192.168.2.1");
    node_send_arp_broadcast_request(R0, &ip, 24);
    sleep(1);
    printf("-------------------For node R0-----------------\n\n");
    node_dump_arp_table(R0);
    printf("\n\n\n");
    printf("-------------------For node R1-----------------\n\n");
    node_dump_arp_table(R1);
    printf("\n\n\n");
    printf("-------------------For node R2-----------------\n\n");
    node_dump_arp_table(R2);
    printf("\n\n\n");
    return topo;
}

int main()
{
    char msg[13] = "Hello topo";
    graph_t *graph = build_topology();
    // comm_send(graph, 0, 1, msg, sizeof(msg));
    // comm_send(graph, 0, 1, msg, sizeof(msg));
    // graph_dump(graph);
    // while (1);
    //     ;
    // ipv4_t ip = net_ip_string_to_ipv4("10.1.1.1");
    // ipv4_t ip2 = net_ip_string_to_ipv4("10.1.0.2");
    // mac_t mac;
    // printf("%d\n", net_ipv4_subnet_are_same(&ip, &ip2, 24, 24));
    // interface_t *intf;
    // net_set_ipv4_octate(&ip, 0, 1);
    // net_set_ipv4_octate(&ip, 1, 0);
    // net_set_ipv4_octate(&ip, 2, 0);
    // net_set_ipv4_octate(&ip, 3, 10);
    // net_set_mac_octate(&mac, 0, 1);
    // net_set_mac_octate(&mac, 1, 2);
    // net_set_mac_octate(&mac, 2, 3);
    // net_set_mac_octate(&mac, 3, 4);
    // net_set_mac_octate(&mac, 4, 5);
    // net_set_mac_octate(&mac, 5, 6);

    // arp_t *arp = arp_create_broadcast(&mac, &ip, &ip);
    // // // arp_dump(arp);
    // // printf("Size = %lu\n", sizeof(arp_t));
    // ethernet_t *eth = ethernet_create(&mac, &mac, 802, arp, sizeof(arp_t), 4982);
    // ethernet_dump(eth);
    // intf = interface_create();
    // arp_table_t *t = arp_table_create();
    // arp_table_entry_add(t, &ip, &mac, intf);
    // arp_table_entry_add(t, &ip, &mac, intf);
    // arp_table_entry_add(t, &ip, &mac, intf);
    // arp_table_entry_add(t, &ip, &mac, intf);
    // arp_table_entry_add(t, &ip, &mac, intf);
    // arp_table_entry_add(t, &ip, &mac, intf);
    // arp_table_entry_add(t, &ip, &mac, intf);
    // arp_table_dump(t);
    // net_dump_ipv4_addr(&ip, 10);
    return 0;
}