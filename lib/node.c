#include <stdlib.h>
#include "node.h"
#include "interface.h"

inline interface_t *
node_add_interface(node_t *node, uint32_t ip_addr, uint8_t net_mask)
{
    interface_t *interface = interface_create();
    interface_set_id(interface, node->no_of_interfaces);
    interface_set_parent(interface, node);
    interface_set_mac(interface, net_generate_random_mac());
    interface_set_ip(interface, ip_addr);
    interface_set_mask(interface, net_mask);
    node->intf[node->no_of_interfaces] = interface;
    node->no_of_interfaces++;
    return interface;
}

inline node_t *
node_create(void)
{
    return (node_t *)calloc(1, sizeof(node_t));
}

inline void
node_delete(node_t *node)
{
    free(node);
}

inline uint32_t
node_get_id(node_t *node)
{
    return node->node_id;
}

inline void
node_set_id(node_t *node, uint32_t node_id)
{
    node->node_id = node_id;
}

inline uint32_t
node_get_no_of_interfaces(node_t *node)
{
    return node->no_of_interfaces;
}

inline glthread_t *
node_get_glue(node_t *node)
{
    return &node->glue;
}

inline void
node_init_glue(node_t *node)
{
    init_glthread(&node->glue);
}

inline void
node_set_loopback(node_t *node, uint32_t loopback)
{
    net_set_ipv4(&node->loopback, loopback);
}

inline ipv4_t *
node_get_loopback(node_t *node)
{
    return &node->loopback;
}

inline uint32_t
node_get_udp_port_number(node_t *node)
{
    return node->udp_port_number;
}

inline int
node_get_udp_sock_fd(node_t *node)
{
    return node->udp_sock_fd;
}

inline void
node_set_udp_port_number(node_t *node, uint32_t udp_port_number)
{
    node->udp_port_number = udp_port_number;
}

inline void
node_set_udp_sock_fd(node_t *node, int udp_sock_fd)
{
    node->udp_sock_fd = udp_sock_fd;
}

inline interface_t *
node_get_interface_by_id(node_t *node, uint32_t interface_id)
{
    return node->intf[interface_id];
}