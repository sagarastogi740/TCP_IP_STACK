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

// graph_t *build_topology()
// {
//     graph_t *topo = graph_create("First topology");
//     node_t *R0 = graph_create_node(topo, "10.0.0.1");
//     node_t *R1 = graph_create_node(topo, "10.0.0.2");
//     node_t *R2 = graph_create_node(topo, "10.0.0.3");

//     comm_start_receiver_thread(topo);

//     graph_insert_link_between_two_nodes(R0, R1, "192.168.0.1", "192.168.0.2", 24, 24, 0);
//     graph_insert_link_between_two_nodes(R1, R2, "192.168.1.1", "192.168.1.2", 24, 24, 1);
//     graph_insert_link_between_two_nodes(R2, R0, "192.168.2.1", "192.168.2.2", 24, 24, 2);

//     return topo;
// }

int main()
{
    // char msg[13] = "Hello topo";
    // graph_t *graph = build_topology();
    // comm_send(graph, 0, 1, msg, sizeof(msg));
    // comm_send(graph, 0, 1, msg, sizeof(msg));
    // while (1)
    //     ;
    // graph_dump(graph);
    ipv4_t ip;
    mac_t mac;
    interface_t *intf;
    net_set_ipv4_octate(&ip, 0, 1);
    net_set_ipv4_octate(&ip, 1, 0);
    net_set_ipv4_octate(&ip, 2, 0);
    net_set_ipv4_octate(&ip, 3, 10);
    net_set_mac_octate(&mac, 0, 1);
    net_set_mac_octate(&mac, 1, 2);
    net_set_mac_octate(&mac, 2, 3);
    net_set_mac_octate(&mac, 3, 4);
    net_set_mac_octate(&mac, 4, 5);
    net_set_mac_octate(&mac, 5, 6);

    intf = interface_create();
    arp_table_t *t = arp_table_create();
    arp_table_entry_add(t, &ip, &mac, intf);
    arp_table_entry_add(t, &ip, &mac, intf);
    arp_table_entry_add(t, &ip, &mac, intf);
    arp_table_entry_add(t, &ip, &mac, intf);
    arp_table_entry_add(t, &ip, &mac, intf);
    arp_table_entry_add(t, &ip, &mac, intf);
    arp_table_entry_add(t, &ip, &mac, intf);
    arp_table_dump(t);
    return 0;
}