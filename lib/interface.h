#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <stdint.h>
#include "net.h"

typedef struct link_ link_t;
typedef struct node_ node_t;

typedef struct interface_
{
    uint32_t interface_id;
    node_t *parent_node;
    link_t *link;
    mac_t mac;
    ipv4_t ip;
    netmask_t mask;
} interface_t;

interface_t *
interface_create(void);

void interface_delete(interface_t *interface);

node_t *
interface_get_parent(interface_t *interface);

link_t *
interface_get_link(interface_t *interface);

uint32_t
interface_get_id(interface_t *interface);

void interface_set_parent(interface_t *interface, node_t *node);

void interface_set_link(interface_t *interface, link_t *link);

void interface_set_id(interface_t *interface, uint32_t interface_id);

uint64_t
interface_get_mac(interface_t *interface);

void interface_set_mac(interface_t *interface, uint64_t mac);

void interface_set_mac_octet(interface_t *interface, mac_t *mac);

uint32_t
interface_get_ip(interface_t *interface);

void interface_set_ip(interface_t *interface, uint32_t ip);

void interface_set_ip_octate(interface_t *interface, uint8_t octate_no, uint8_t val);

uint8_t
interface_get_mask(interface_t *interface);

void interface_set_mask(interface_t *interface, uint8_t mask);

ipv4_t *
interface_get_ip_octate(interface_t *interface);

mac_t *
interface_get_mac_octate(interface_t *interface);

#endif /* __INTERFACE_H__ */