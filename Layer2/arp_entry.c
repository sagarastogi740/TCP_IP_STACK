#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <stdbool.h>
#include "arp_entry.h"
#include "../lib/net.h"

arp_entry_t *
arp_entry_create(ipv4_t *ip, mac_t *mac, interface_t *interface)
{
    arp_entry_t *entry = (arp_entry_t *)calloc(1, sizeof(arp_entry_t));
    net_copy_ipv4(&entry->ip, ip);
    net_copy_mac(&entry->mac, mac);
    entry->oif = interface;
    init_glthread(&entry->arp_glue);
    return entry;
}

arp_entry_t *arp_entry_glue_to_entry(glthread_t *arp_glue_addr)
{
    return GLTHREAD_TO_PARENT_NODE_ADDR(arp_entry_t, arp_glue_addr, arp_glue);
}

ipv4_t *
arp_entry_get_ip(arp_entry_t *arp_entry)
{
    return &arp_entry->ip;
}

mac_t *arp_entry_get_mac(arp_entry_t *arp_entry)
{
    return &arp_entry->mac;
}

interface_t *
arp_entry_get_interface(arp_entry_t *arp_entry)
{
    return arp_entry->oif;
}

glthread_t *arp_entry_get_glue(arp_entry_t *arp_entry)
{
    return &arp_entry->arp_glue;
}

void arp_entry_set_ip(arp_entry_t *arp_entry, ipv4_t *ip)
{
    memcpy(&arp_entry->ip, ip, sizeof(ip));
}

void arp_entry_set_mac(arp_entry_t *arp_entry, mac_t *mac)
{
    memcpy(&arp_entry->mac, mac, sizeof(mac));
}

void arp_entry_set_interface(arp_entry_t *arp_entry, interface_t *oif)
{
    arp_entry->oif = oif;
}

bool arp_entry_lookup(arp_entry_t *arp_entry, ipv4_t *ip)
{
    return net_are_ip_equal(&arp_entry->ip, ip);
}

void arp_entry_dump(arp_entry_t *entry)
{
    net_dump_ipv4_addr(&entry->ip, 0);
    printf("    ");
    net_dump_mac_addr(&entry->mac);
    printf("    ");
    printf("%u", interface_get_id(entry->oif));
}