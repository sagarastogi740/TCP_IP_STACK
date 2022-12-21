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

    return topo;
}

int main()
{
    char msg[] = "Hello topo";
    graph_t *graph = build_topology();
    comm_send(graph, 0, 0, msg, sizeof(msg));
    comm_send(graph, 0, 1, msg, sizeof(msg));
    sleep(1);
    graph_dump(graph);
    return 0;
}