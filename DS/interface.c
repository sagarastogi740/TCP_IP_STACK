#include <stdlib.h>
#include <stdint.h>
#include "interface.h"

inline interface_t *create_interface(uint32_t interface_id)
{
    interface_t *interface = (interface_t *)calloc(1, sizeof(interface_t));
    interface->interface_id = interface_id;
    return interface;
}

inline void delete_interface(interface_t *interface)
{
    free(interface);
}

inline node_t *get_interface_parent(interface_t *interface)
{
    return interface->parent_node;
}

inline link_t *get_interface_link(interface_t *interface)
{
    return interface->link;
}

inline uint32_t get_interface_id(interface_t *interface)
{
    return interface->interface_id;
}

inline void set_interface_parent(interface_t *interface, node_t *node)
{
    interface->parent_node = node;
}

inline void set_interface_link(interface_t *interface, link_t *link)
{
    interface->link = link;
}

inline void set_interface_id(interface_t *interface, uint32_t interface_id)
{
    interface->interface_id = interface_id;
}