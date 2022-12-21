#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdint.h>
#include "glthread.h"
#include "net.h"

#define TOPOLOGY_NAME_SIZE 64

typedef struct node_ node_t;

typedef struct graph_
{
    uint32_t no_of_nodes;
    char topology_name[TOPOLOGY_NAME_SIZE];
    glthread_t graph_node_list;
} graph_t;

graph_t *
graph_create(const char *topology_name);

node_t *
graph_create_node(graph_t *graph, const char *loopback);

void graph_insert_link_between_two_nodes(node_t *node_1,
                                         node_t *node_2,
                                         const char *ip_1,
                                         const char *ip_2,
                                         uint8_t mask_1,
                                         uint8_t mask_2,
                                         uint64_t link_cost);

void graph_dump(graph_t *graph);

node_t *
graph_glue_to_node(glthread_t *glthread);

node_t *
graph_get_node_by_id(graph_t *graph, uint32_t node_id);

#endif /*_DS_GRAPH_*/
