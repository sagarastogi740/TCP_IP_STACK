#include <stdlib.h>
#include "node.h"
#include "interface.h"

inline interface_t *
node_add_interface(node_t *node)
{
    interface_t *interface = create_interface(node->no_of_interfaces);
    set_interface_parent(interface, node);
    node->intf[node->no_of_interfaces++] = interface;
    return interface;
}

inline node_t *
create_node(uint32_t node_id)
{
    node_t *node = (node_t *)calloc(1, sizeof(node_t));
    node->node_id = node_id;
    return node;
}

inline void
delete_node(node_t *node)
{
    free(node);
}

inline uint32_t
get_node_id(node_t *node)
{
    return node->node_id;
}

inline void
set_node_id(node_t *node, uint32_t node_id)
{
    node->node_id = node_id;
}

inline uint32_t
get_node_no_of_interfaces(node_t *node)
{
    return node->no_of_interfaces;
}

inline glthread_t *
get_node_glue(node_t *node)
{
    return &node->glue;
}

inline void
node_init_glue(node_t *node)
{
    init_glthread(&node->glue);
}