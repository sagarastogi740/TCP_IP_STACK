#ifndef __ARP_ENTRY_H__
#define __ARP_ENTRY_H__

#include "../lib/net.h"
#include "../lib/interface.h"
#include "../lib/glthread.h"

typedef struct arp_entry_
{
    ipv4_t ip;
    mac_t mac;
    interface_t *oif;
    glthread_t arp_glue;
} arp_entry_t;

arp_entry_t *
arp_entry_create(ipv4_t *ip, mac_t *mac, interface_t *interface);

arp_entry_t *
arp_entry_glue_to_entry(glthread_t *arp_glue);

ipv4_t *
arp_entry_get_ip(arp_entry_t *arp_entry);

mac_t *
arp_entry_get_mac(arp_entry_t *arp_entry);

interface_t *
arp_entry_get_interface(arp_entry_t *arp_entry);

glthread_t *
arp_entry_get_glue(arp_entry_t *arp_entry);

void arp_entry_set_ip(arp_entry_t *arp_entry, ipv4_t *ip);

void arp_entry_set_mac(arp_entry_t *arp_entry, mac_t *mac);

void arp_entry_set_interface(arp_entry_t *arp_entry, interface_t *oif);

bool arp_entry_lookup(arp_entry_t *arp_entry, ipv4_t *ip);

#endif /* __ARP_ENTRY_H__ */