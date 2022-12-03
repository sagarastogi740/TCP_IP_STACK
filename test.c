#include "lib/graph.h"

graph_t *build_topology()
{
    graph_t *topo = graph_create("First topology");
    ipv4_t ip;
    ip.addr[0] = 10;
    ip.addr[1] = 0;
    ip.addr[2] = 0;
    ip.addr[3] = 1;
    node_t *R0 = graph_create_node(topo, &ip);
    ip.addr[0] = 10;
    ip.addr[1] = 0;
    ip.addr[2] = 0;
    ip.addr[3] = 2;
    node_t *R1 = graph_create_node(topo, &ip);
    ip.addr[0] = 10;
    ip.addr[1] = 0;
    ip.addr[2] = 0;
    ip.addr[3] = 3;
    node_t *R2 = graph_create_node(topo, &ip);

    ipv4_t ip_1, ip_2;

    ip_1.addr[0] = 192;
    ip_1.addr[1] = 168;
    ip_1.addr[2] = 0;
    ip_1.addr[3] = 1;
    ip_2.addr[0] = 192;
    ip_2.addr[1] = 168;
    ip_2.addr[2] = 0;
    ip_2.addr[3] = 2;
    graph_insert_link_between_two_nodes(R0, R1, &ip_1, &ip_2, 24, 24, 3);

    ip_1.addr[0] = 192;
    ip_1.addr[1] = 168;
    ip_1.addr[2] = 1;
    ip_1.addr[3] = 1;
    ip_2.addr[0] = 192;
    ip_2.addr[1] = 168;
    ip_2.addr[2] = 1;
    ip_2.addr[3] = 2;
    graph_insert_link_between_two_nodes(R1, R2, &ip_1, &ip_2, 24, 24, 1);

    ip_1.addr[0] = 192;
    ip_1.addr[1] = 168;
    ip_1.addr[2] = 0;
    ip_1.addr[3] = 2;
    ip_2.addr[0] = 192;
    ip_2.addr[1] = 168;
    ip_2.addr[2] = 2;
    ip_2.addr[3] = 2;
    graph_insert_link_between_two_nodes(R2, R0, &ip_1, &ip_2, 24, 24, 2);

    return topo;
}

int main()
{
    graph_t *graph = build_topology();
    graph_dump(graph);
    return 0;
}