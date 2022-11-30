#include <stdlib.h>
#include "link.h"

inline link_t *create_link()
{
    return (link_t *)calloc(1, sizeof(link_t));
}

inline void delete_link(link_t *link)
{
    free(link);
}

inline interface_t *get_link_interface1(link_t *link)
{
    return link->interface1;
}

inline interface_t *get_link_interface2(link_t *link)
{
    return link->interface2;
}

inline uint64_t get_link_cost(link_t *link)
{
    return link->cost;
}

inline void set_link_interface1(link_t *link, interface_t *interface)
{
    link->interface1 = interface;
}

inline void set_link_interface2(link_t *link, interface_t *interface)
{
    link->interface2 = interface;
}

inline void set_link_cost(link_t *link, uint64_t cost)
{
    link->cost = cost;
}
