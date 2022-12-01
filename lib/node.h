#ifndef __NODE_H__
#define __NODE_H__

#include <stdint.h>
#include "glthread.h"

#define MAX_INTF_PER_NODE 64

#define NODE_ITERATE_OVER_INTF_START(node_ptr, interface)                 \
    for (uint32_t intf_itr = 0; intf_itr < MAX_INTF_PER_NODE; intf_itr++) \
    {                                                                     \
        if (node_ptr->intf[intf_itr] == NULL)                             \
        {                                                                 \
            break;                                                        \
        }                                                                 \
        interface = node_ptr->intf[intf_itr];
#define NODE_ITERATE_OVER_INTF_END() }

typedef struct interface_ interface_t;

typedef struct node_
{
    uint32_t node_id;
    uint32_t no_of_interfaces;
    interface_t *intf[MAX_INTF_PER_NODE];
    glthread_t glue;
} node_t;

interface_t *
node_add_interface(node_t *node);

node_t *
create_node(uint32_t node_id);

void delete_node(node_t *node);

uint32_t
get_node_id(node_t *node);

void set_node_id(node_t *node, uint32_t node_id);

uint32_t
get_node_no_of_interfaces(node_t *node);

interface_t *
get_node_interface_by_id(node_t *node, uint32_t interface_id);

glthread_t *
get_node_glue(node_t *node);

void node_init_glue(node_t *node);

#endif /* __NODE_H__ */