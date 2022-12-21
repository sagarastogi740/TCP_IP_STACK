#ifndef __LINK_H__
#define __LINK_H__

#include <stdint.h>

typedef struct interface_ interface_t;

typedef struct link_
{
    interface_t *interface1;
    interface_t *interface2;
    uint64_t cost;
} link_t;

link_t *
link_create();

void link_delete(link_t *link);

interface_t *
link_get_interface1(link_t *link);

interface_t *
link_get_interface2(link_t *link);

uint64_t
link_get_cost(link_t *link);

void link_set_interface1(link_t *link, interface_t *interface);

void link_set_interface2(link_t *link, interface_t *interface);

void link_set_cost(link_t *link, uint64_t cost);

interface_t *
link_get_other_interface(interface_t *interface);

#endif /* __LINK_H__ */