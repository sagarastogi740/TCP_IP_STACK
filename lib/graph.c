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

static inline uint32_t
ip_string_to_uin32(const char *ip)
{
    uint32_t sum = 0;
    uint8_t num = 0;
    size_t len = strlen(ip);
    for (size_t i = 0; i <= len; i++)
    {
        switch (ip[i])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            num *= 10;
            num += ((uint8_t)ip[i] - (uint8_t)'0');
            break;
        case '.':
            sum *= 256;
            sum += num;
            num = 0;
            break;
        case '\0':
            sum *= 256;
            sum += num;
            break;
        default:
            printf("Unknown charactor in ip address string configured in topology.\n");
            exit(0);
        }
    }
    return sum;
}

static inline void
dump_ipv4_addr(ipv4_t *ipv4, uint8_t mask)
{
    printf("%u.%u.%u.%u/%u",
           net_get_ipv4_octate(ipv4, 3),
           net_get_ipv4_octate(ipv4, 2),
           net_get_ipv4_octate(ipv4, 1),
           net_get_ipv4_octate(ipv4, 0),
           mask);
}

static inline void
dump_mac_addr(mac_t *mac)
{
    printf("%u:%u:%u:%u:%u:%u",
           net_get_mac_octate(mac, 5),
           net_get_mac_octate(mac, 4),
           net_get_mac_octate(mac, 3),
           net_get_mac_octate(mac, 2),
           net_get_mac_octate(mac, 1),
           net_get_mac_octate(mac, 0));
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
graph_create_node(graph_t *graph, const char *loopback)
{
    node_t *node = node_create();
    node_set_id(node, graph->no_of_nodes++);
    node_set_loopback(node, ip_string_to_uin32(loopback));
    node_init_glue(node);
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
    interface_t *intf_1 = node_add_interface(node_1, ip_string_to_uin32(ip_1), mask_1);
    interface_t *intf_2 = node_add_interface(node_2, ip_string_to_uin32(ip_2), mask_2);
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
            printf(", ");
            dump_mac_addr(interface_get_mac_octate(interface));

            printf("    ");
            printf("Neighbour Node : ");
            dump_ipv4_addr(node_get_loopback(interface_get_parent(get_neighbour_interface(interface))), 32);

            printf("    ");
            printf("Neighbour Interface : ");
            dump_ipv4_addr(interface_get_ip_octate(get_neighbour_interface(interface)), interface_get_mask(get_neighbour_interface(interface)));
            printf(", ");
            dump_mac_addr(interface_get_mac_octate(get_neighbour_interface(interface)));

            printf("    ");
            printf("Cost = %ld", link_get_cost(interface_get_link(interface)));
            printf("\n");
        }
        NODE_ITERATE_OVER_INTF_END();
    }
}
