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

link_t *create_link();
void delete_link(link_t *link);
interface_t *get_link_interface1(link_t *link);
interface_t *get_link_interface2(link_t *link);
uint64_t get_link_cost(link_t *link);
void set_link_interface1(link_t *link, interface_t *interface);
void set_link_interface2(link_t *link, interface_t *interface);
void set_link_cost(link_t *link, uint64_t cost);

#endif /* __LINK_H__ */