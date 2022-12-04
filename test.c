#include "lib/graph.h"

graph_t *build_topology()
{
    graph_t *topo = graph_create("First topology");
    node_t *R0 = graph_create_node(topo, "10.0.0.1");
    node_t *R1 = graph_create_node(topo, "10.0.0.2");
    node_t *R2 = graph_create_node(topo, "10.0.0.3");

    graph_insert_link_between_two_nodes(R0, R1, "192.168.0.1", "192.168.0.2", 24, 24, 3);
    graph_insert_link_between_two_nodes(R1, R2, "192.168.1.1", "192.168.1.2", 24, 24, 1);
    graph_insert_link_between_two_nodes(R2, R0, "192.168.2.1", "192.168.2.2", 24, 24, 2);

    return topo;
}

int main()
{
    graph_t *graph = build_topology();
    graph_dump(graph);
    return 0;
}