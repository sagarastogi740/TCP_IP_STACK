#include "DS/graph.h"

graph_t *build_topology()
{
    graph_t *topo = create_graph("First topology");

    node_t *R0 = create_graph_node(topo);
    node_t *R1 = create_graph_node(topo);
    node_t *R2 = create_graph_node(topo);

    insert_link_between_two_nodes(R0, R1, 1);
    insert_link_between_two_nodes(R1, R2, 2);
    insert_link_between_two_nodes(R2, R0, 3);

    return topo;
}

int main()
{
    graph_t *topo = build_topology();
    dump_graph(topo);
    return 0;
}