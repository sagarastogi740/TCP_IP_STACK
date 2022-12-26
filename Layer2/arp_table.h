#ifndef __ARP_TABLE_H__
#define __ARP_TABLE_H__

#include "../lib/glthread.h"
#include "../lib/net.h"
#include "../lib/interface.h"

typedef struct arp_table_
{
    glthread_t arp_entries;
} arp_table_t;

arp_table_t *
arp_table_create();

interface_t *
arp_table_lookup(arp_table_t *arp_table, ipv4_t *ip);

void arp_table_clear(arp_table_t *arp_table);

void arp_table_delete_entry(arp_table_t *arp_table, ipv4_t *ip);

void arp_table_entry_add(arp_table_t *arp_table, ipv4_t *ip, mac_t *mac, interface_t *oif);

void arp_table_dump(arp_table_t *arp_table);

#endif /* __ARP_TABLE_H__ */
