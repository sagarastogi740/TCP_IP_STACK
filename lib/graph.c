#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "link.h"
#include "node.h"
#include "interface.h"
#include "net.h"

static inline interface_t *
get_neighbour_interface(interface_t *interface)
{
    link_t *link = interface_get_link(interface);
    interface_t *intf_1 = link_get_interface1(link);
    interface_t *intf_2 = link_get_interface2(link);
    if (interface == intf_1)
    {
        return intf_2;
    }
    else
    {
        return intf_1;
    }
}

static inline void
dump_ipv4_addr(ipv4_t *ipv4, uint8_t mask)
{
    printf("%u.%u.%u.%u/%u", net_get_ipv4_octate(ipv4, 0), net_get_ipv4_octate(ipv4, 1), net_get_ipv4_octate(ipv4, 2), net_get_ipv4_octate(ipv4, 3), mask);
}

inline graph_t *
graph_create(const char *topology_name)
{
    graph_t *graph = (graph_t *)calloc(1, sizeof(graph_t));
    strncpy(graph->topology_name, topology_name, TOPOLOGY_NAME_SIZE);
    init_glthread(&graph->graph_node_list);
    return graph;
}

inline node_t *
graph_create_node(graph_t *graph, ipv4_t *loopback)
{
    node_t *node = node_create();
    node_set_id(node, graph->no_of_nodes++);
    node_set_loopback(node, loopback);
    node_init_glue(node);
    glthread_add_next(&graph->graph_node_list, node_get_glue(node));
    return node;
}

void graph_insert_link_between_two_nodes(node_t *node_1, node_t *node_2, ipv4_t *ip_1, ipv4_t *ip_2, uint8_t mask_1, uint8_t mask_2, uint64_t link_cost)
{
    link_t *link = (link_t *)calloc(1, sizeof(link_t));
    interface_t *intf_1 = node_add_interface(node_1, ip_1, mask_1);
    interface_t *intf_2 = node_add_interface(node_2, ip_2, mask_2);
    link_set_interface1(link, intf_1);
    link_set_interface2(link, intf_2);
    link_set_cost(link, link_cost);
    interface_set_link(intf_1, link);
    interface_set_link(intf_2, link);
}

void graph_dump(graph_t *graph)
{
    glthread_t *glthread_itr;
    printf("Topology Name = %s\n", graph->topology_name);
    ITERATE_OVER_GLTHREAD(&graph->graph_node_list, glthread_itr)
    {
        node_t *node = GLTHREAD_TO_PARENT_NODE_ADDR(node_t, glthread_itr, glue);
        printf("Node ");
        dump_ipv4_addr(node_get_loopback(node), 32);
        printf("\n");
        interface_t *interface = NULL;
        NODE_ITERATE_OVER_INTF_START(node, interface)
        {
            printf(" ");
            printf("Local Interface : ");
            dump_ipv4_addr(interface_get_ip_octate(interface), interface_get_mask(interface));

            printf("    ");
            printf("Neighbour Node : ");
            dump_ipv4_addr(node_get_loopback(interface_get_parent(get_neighbour_interface(interface))), 32);

            printf("    ");
            printf("Neighbour Interface : ");
            dump_ipv4_addr(interface_get_ip_octate(get_neighbour_interface(interface)), interface_get_mask(get_neighbour_interface(interface)));

            printf("    ");
            printf("Cost = %ld", link_get_cost(interface_get_link(interface)));
            printf("\n");
        }
        NODE_ITERATE_OVER_INTF_END();
    }
}
