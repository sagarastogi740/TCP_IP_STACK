#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdint.h>
#include "glthread.h"

#define TOPOLOGY_NAME_SIZE 64

typedef struct node_ node_t;

typedef struct graph_
{
    uint32_t no_of_nodes;
    char topology_name[TOPOLOGY_NAME_SIZE];
    glthread_t graph_node_list;
} graph_t;

graph_t *
create_graph(const char *topology_name);

node_t *
create_graph_node(graph_t *graph);

void insert_link_between_two_nodes(node_t *node1, node_t *node2, uint64_t cost);

void dump_graph(graph_t *graph);

#endif /*_DS_GRAPH_*/
