#ifndef __NODE_H__
#define __NODE_H__

#include <stdint.h>
#include "glthread.h"
#include "net.h"

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
    ipv4_t loopback;
    glthread_t glue;
} node_t;

interface_t *
node_add_interface(node_t *node, uint32_t ip_addr, uint8_t net_mask);

node_t *
node_create(void);

void node_delete(node_t *node);

uint32_t
node_get_id(node_t *node);

void node_set_id(node_t *node, uint32_t node_id);

uint32_t
node_get_no_of_interfaces(node_t *node);

glthread_t *
node_get_glue(node_t *node);

void node_init_glue(node_t *node);

void node_set_loopback(node_t *node, uint32_t loopback);

ipv4_t *
node_get_loopback(node_t *node);

#endif /* __NODE_H__ */