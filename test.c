#include "lib/graph.h"

graph_t *build_topology()
{
    graph_t *topo = create_graph("First topology");

    node_t *R0 = create_graph_node(topo);
    node_t *R1 = create_graph_node(topo);
    node_t *R2 = create_graph_node(topo);
    node_t *R3 = create_graph_node(topo);
    node_t *R4 = create_graph_node(topo);
    node_t *R5 = create_graph_node(topo);

    insert_link_between_two_nodes(R0, R1, 3);
    insert_link_between_two_nodes(R1, R2, 1);
    insert_link_between_two_nodes(R2, R0, 2);
    insert_link_between_two_nodes(R2, R3, 3);
    insert_link_between_two_nodes(R3, R4, 2);
    insert_link_between_two_nodes(R4, R5, 1);
    insert_link_between_two_nodes(R5, R3, 5);

    return topo;
}

int main()
{
    graph_t *topo = build_topology();
    dump_graph(topo);
    return 0;
}