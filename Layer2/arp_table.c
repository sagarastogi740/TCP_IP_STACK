#include <stdlib.h>
#include <stdio.h>
#include "arp_table.h"
#include "arp_entry.h"
#include "../lib/glthread.h"
#include "../lib/net.h"

arp_table_t *arp_table_create()
{
    return (arp_table_t *)calloc(1, sizeof(arp_table_t));
}

interface_t *arp_table_lookup(arp_table_t *arp_table, ipv4_t *ip)
{
    glthread_t *itr;
    ITERATE_OVER_GLTHREAD(&arp_table->arp_entries, itr)
    {
        arp_entry_t *arp_entry = arp_entry_glue_to_entry(itr);
        if (arp_entry_lookup(arp_entry, ip))
        {
            return arp_entry_get_interface(arp_entry);
        }
    }
    return NULL;
}

void arp_table_clear(arp_table_t *arp_table)
{
    glthread_t *itr;
    ITERATE_OVER_GLTHREAD(&arp_table->arp_entries, itr)
    {
        arp_entry_t *arp_entry = arp_entry_glue_to_entry(itr);
        free(arp_entry);
    }
}

void arp_table_delete_entry(arp_table_t *arp_table, ipv4_t *ip)
{
    glthread_t *itr;
    ITERATE_OVER_GLTHREAD(&arp_table->arp_entries, itr)
    {
        arp_entry_t *arp_entry = arp_entry_glue_to_entry(itr);
        if (net_are_ip_equal(&arp_entry->ip, ip))
        {
            glthread_remove(itr);
            free(arp_entry);
            return;
        }
    }
}

void arp_table_entry_add(arp_table_t *arp_table, ipv4_t *ip, mac_t *mac, interface_t *oif)
{
    arp_entry_t *arp_entry = arp_entry_create(ip, mac, oif);
    glthread_add_next(&arp_table->arp_entries, arp_entry_get_glue(arp_entry));
}

void arp_table_dump(arp_table_t *arp_table)
{
    glthread_t *itr;
    ITERATE_OVER_GLTHREAD(&arp_table->arp_entries, itr)
    {
        arp_entry_t *arp_entry = arp_entry_glue_to_entry(itr);
        arp_entry_dump(arp_entry);
        printf("\n");
    }
}