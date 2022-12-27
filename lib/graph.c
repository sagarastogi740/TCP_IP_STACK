#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "link.h"
#include "node.h"
#include "interface.h"
#include "net.h"
#include "comm.h"

inline graph_t *
graph_create(const char *topology_name)
{
    graph_t *graph = (graph_t *)calloc(1, sizeof(graph_t));
    strncpy(graph->topology_name, topology_name, TOPOLOGY_NAME_SIZE);
    init_glthread(&graph->graph_node_list);
    return graph;
}

inline node_t *
graph_create_node(graph_t *graph, const char *loopback)
{
    node_t *node = node_create();
    node_set_id(node, graph->no_of_nodes++);
    node_set_loopback(node, net_ip_string_to_uin32(loopback));
    glthread_add_next(&graph->graph_node_list, node_get_glue(node));
    return node;
}

void graph_insert_link_between_two_nodes(node_t *node_1,
                                         node_t *node_2,
                                         const char *ip_1,
                                         const char *ip_2,
                                         uint8_t mask_1,
                                         uint8_t mask_2,
                                         uint64_t link_cost)
{
    link_t *link = (link_t *)calloc(1, sizeof(link_t));
    interface_t *intf_1 = node_add_interface(node_1, net_ip_string_to_uin32(ip_1), mask_1);
    interface_t *intf_2 = node_add_interface(node_2, net_ip_string_to_uin32(ip_2), mask_2);
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
        net_dump_ipv4_addr(node_get_loopback(node), 32);
        printf("\n");
        interface_t *interface = NULL;
        NODE_ITERATE_OVER_INTF_START(node, interface)
        {
            interface_t *nbr_interface = link_get_other_interface(interface);

            printf(" ");
            printf("Local Interface : ");
            net_dump_ipv4_addr(interface_get_ip_octate(interface), interface_get_mask(interface));
            printf(", ");
            net_dump_mac_addr(interface_get_mac_octate(interface));

            printf("    ");
            printf("Neighbour Node : ");
            net_dump_ipv4_addr(node_get_loopback(interface_get_parent(nbr_interface)), 32);

            printf("    ");
            printf("Neighbour Interface : ");
            net_dump_ipv4_addr(interface_get_ip_octate(nbr_interface),
                               interface_get_mask(nbr_interface));
            printf(", ");
            net_dump_mac_addr(interface_get_mac_octate(nbr_interface));

            printf("    ");
            printf("Cost = %ld", link_get_cost(interface_get_link(interface)));
            printf("\n");
        }
        NODE_ITERATE_OVER_INTF_END();
    }
}

inline node_t *
graph_glue_to_node(glthread_t *glthread)
{
    return GLTHREAD_TO_PARENT_NODE_ADDR(node_t, glthread, glue);
}

inline node_t *
graph_get_node_by_id(graph_t *graph, uint32_t node_id)
{
    glthread_t *itr = NULL;
    ITERATE_OVER_GLTHREAD(&graph->graph_node_list, itr)
    {
        node_t *node = graph_glue_to_node(itr);
        if (node_get_id(node) == node_id)
        {
            return node;
        }
    }
    return NULL;
}