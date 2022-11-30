#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "link.h"
#include "node.h"
#include "interface.h"

static inline interface_t *
graph_get_neighbour_interface(interface_t *interface)
{
    link_t *link = get_interface_link(interface);
    interface_t *intf_1 = get_link_interface1(link);
    interface_t *intf_2 = get_link_interface2(link);
    if (interface == intf_1)
    {
        return intf_2;
    }
    else
    {
        return intf_1;
    }
}

inline graph_t *create_graph(const char *topology_name)
{
    graph_t *graph = (graph_t *)calloc(1, sizeof(graph_t));
    strncpy(graph->topology_name, topology_name, TOPOLOGY_NAME_SIZE);
    init_glthread(&graph->graph_node_list);
    return graph;
}

inline node_t *create_graph_node(graph_t *graph)
{
    node_t *node = create_node(graph->no_of_nodes++);
    node_init_glue(node);
    glthread_add_next(&graph->graph_node_list, get_node_glue(node));
    return node;
}

void insert_link_between_two_nodes(node_t *node_1, node_t *node_2, uint64_t cost)
{
    link_t *link = (link_t *)calloc(1, sizeof(link_t));
    interface_t *intf_1 = node_add_interface(node_1);
    interface_t *intf_2 = node_add_interface(node_2);
    set_link_interface1(link, intf_1);
    set_link_interface2(link, intf_2);
    set_link_cost(link, cost);
    set_interface_link(intf_1, link);
    set_interface_link(intf_2, link);
}

void dump_graph(graph_t *graph)
{
    glthread_t *glthread_itr;
    printf("Topology Name = %s\n", graph->topology_name);
    ITERATE_OVER_GLTHREAD(&graph->graph_node_list, glthread_itr)
    {
        node_t *node = GLTHREAD_TO_PARENT_NODE_ADDR(node_t, glthread_itr, glue);
        printf("Node ID = %d :\n", get_node_id(node));
        interface_t *interface = NULL;
        NODE_ITERATE_OVER_INTF_START(node, interface)
        {
            printf("  ");
            printf("Local Node : %d,", get_node_id(node));
            printf("    ");
            printf("Neighbour Node : %d,", get_node_id(get_interface_parent(graph_get_neighbour_interface(interface))));
            printf("    ");
            printf("Cost = %ld", get_link_cost(get_interface_link(interface)));
            printf("\n");
        }
        NODE_ITERATE_OVER_INTF_END();
    }
}
