#include <stdlib.h>
#include <stdint.h>
#include "interface.h"
#include "net.h"

inline interface_t *
interface_create(void)
{
    return (interface_t *)calloc(1, sizeof(interface_t));
}

inline void
interface_delete(interface_t *interface)
{
    free(interface);
}

inline node_t *
interface_get_parent(interface_t *interface)
{
    return interface->parent_node;
}

inline link_t *
interface_get_link(interface_t *interface)
{
    return interface->link;
}

inline uint32_t
interface_get_id(interface_t *interface)
{
    return interface->interface_id;
}

inline void
interface_set_parent(interface_t *interface, node_t *node)
{
    interface->parent_node = node;
}

inline void
interface_set_link(interface_t *interface, link_t *link)
{
    interface->link = link;
}

inline void
interface_set_id(interface_t *interface, uint32_t interface_id)
{
    interface->interface_id = interface_id;
}

inline uint64_t
interface_get_mac(interface_t *interface)
{
    return net_get_mac(&interface->mac);
}

inline void
interface_set_mac(interface_t *interface, uint64_t mac)
{
    net_set_mac(&interface->mac, mac);
}

inline void
interface_set_mac_octet(interface_t *interface, uint8_t octate_no, uint8_t value)
{
    net_set_mac_octate(&interface->mac, octate_no, value);
}

inline uint32_t
interface_get_ip(interface_t *interface)
{
    return net_get_ipv4(&interface->ip);
}

inline void
interface_set_ip(interface_t *interface, uint32_t ip)
{
    net_set_ipv4(&interface->ip, ip);
}

inline void
interface_set_ip_octate(interface_t *interface, uint8_t octate_no, uint8_t val)
{
    net_set_ipv4_octate(&interface->ip, octate_no, val);
}

inline uint8_t
interface_get_mask(interface_t *interface)
{
    return interface->mask;
}

inline void
interface_set_mask(interface_t *interface, uint8_t mask)
{
    interface->mask = mask;
}

inline ipv4_t *
interface_get_ip_octate(interface_t *interface)
{
    return &interface->ip;
}

inline mac_t *
interface_get_mac_octate(interface_t *interface)
{
    return &interface->mac;
}