#ifndef __INTERFACE_H__
#define __INTERFACE_H__

typedef struct link_ link_t;
typedef struct node_ node_t;

typedef struct interface_
{
    uint32_t interface_id;
    node_t *parent_node;
    link_t *link;
} interface_t;

interface_t *create_interface(uint32_t interface_id);
node_t *get_interface_parent(interface_t *interface);
link_t *get_interface_link(interface_t *interface);
uint32_t get_interface_id(interface_t *interface);
void set_interface_parent(interface_t *interface, node_t *node);
void set_interface_link(interface_t *interface, link_t *link);
void set_interface_id(interface_t *interface, uint32_t if_id);
void delete_interface(interface_t *interface);

#endif /* __INTERFACE_H__ */