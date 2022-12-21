#include <stdlib.h>
#include "link.h"
#include "interface.h"

inline link_t *
link_create()
{
    return (link_t *)calloc(1, sizeof(link_t));
}

inline void
link_delete(link_t *link)
{
    free(link);
}

inline interface_t *
link_get_interface1(link_t *link)
{
    return link->interface1;
}

inline interface_t *
link_get_interface2(link_t *link)
{
    return link->interface2;
}

inline uint64_t
link_get_cost(link_t *link)
{
    return link->cost;
}

inline void
link_set_interface1(link_t *link, interface_t *interface)
{
    link->interface1 = interface;
}

inline void
link_set_interface2(link_t *link, interface_t *interface)
{
    link->interface2 = interface;
}

inline void
link_set_cost(link_t *link, uint64_t cost)
{
    link->cost = cost;
}

inline interface_t *
link_get_other_interface(interface_t *interface)
{
    link_t *link = interface_get_link(interface);
    interface_t *intf_1 = link_get_interface1(link);
    interface_t *intf_2 = link_get_interface2(link);
    if (interface == intf_1)
    {
        return intf_2;
    }
    else
    {
        return intf_1;
    }
}