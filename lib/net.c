#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <stdbool.h>
#include "net.h"

inline uint64_t
net_generate_random_mac()
{
    uint64_t rn = 0;
    rn |= rand();
    rn <<= 32;
    rn |= rand();
    return rn;
}

inline uint32_t
net_get_ipv4(ipv4_t *ipv4)
{
    uint32_t addr;
    memcpy(&addr, ipv4->addr, sizeof(ipv4->addr));
    return addr;
}

inline void
net_set_ipv4(ipv4_t *ipv4, uint32_t addr)
{
    memcpy(ipv4->addr, &addr, sizeof(ipv4->addr));
}

inline uint8_t
net_get_ipv4_octate(ipv4_t *ipv4, uint8_t octate_no)
{
    return ipv4->addr[octate_no];
}

inline void
net_set_ipv4_octate(ipv4_t *ipv4, uint8_t octate_no, uint8_t val)
{
    ipv4->addr[octate_no] = val;
}

inline uint64_t
net_get_mac(mac_t *mac)
{
    uint64_t addr = 0;
    memcpy(&addr, mac->addr, sizeof(mac->addr));
    return addr;
}

inline void
net_set_mac(mac_t *mac, uint64_t val)
{
    memcpy(mac->addr, &val, sizeof(mac->addr));
}

inline uint8_t
net_get_mac_octate(mac_t *mac, uint8_t octate_no)
{
    return mac->addr[octate_no];
}

inline void
net_set_mac_octate(mac_t *dest_mac, uint8_t octate_no, uint8_t value)
{
    dest_mac->addr[octate_no] = value;
}

inline bool
net_are_mac_equal(mac_t *mac_1, mac_t *mac_2)
{
    return ((mac_1->addr[0] == mac_2->addr[0]) &&
            (mac_1->addr[1] == mac_2->addr[1]) &&
            (mac_1->addr[2] == mac_2->addr[2]) &&
            (mac_1->addr[3] == mac_2->addr[3]) &&
            (mac_1->addr[4] == mac_2->addr[4]) &&
            (mac_1->addr[5] == mac_2->addr[5]));
}

inline bool
net_is_mac_broadcast(mac_t *mac)
{
    return ((mac->addr[0] == 255) &&
            (mac->addr[1] == 255) &&
            (mac->addr[2] == 255) &&
            (mac->addr[3] == 255) &&
            (mac->addr[4] == 255) &&
            (mac->addr[5] == 255));
}

bool net_are_ip_equal(ipv4_t *ip_1, ipv4_t *ip_2)
{
    return ((ip_1->addr[0] == ip_2->addr[0]) &&
            (ip_1->addr[1] == ip_2->addr[1]) &&
            (ip_1->addr[2] == ip_2->addr[2]) &&
            (ip_1->addr[3] == ip_2->addr[3]));
}

void net_dump_ipv4_addr(ipv4_t *ipv4, uint8_t mask)
{
    printf("%u.%u.%u.%u/%u",
           net_get_ipv4_octate(ipv4, 3),
           net_get_ipv4_octate(ipv4, 2),
           net_get_ipv4_octate(ipv4, 1),
           net_get_ipv4_octate(ipv4, 0),
           mask);
}

void net_dump_mac_addr(mac_t *mac)
{
    printf("%u:%u:%u:%u:%u:%u",
           net_get_mac_octate(mac, 5),
           net_get_mac_octate(mac, 4),
           net_get_mac_octate(mac, 3),
           net_get_mac_octate(mac, 2),
           net_get_mac_octate(mac, 1),
           net_get_mac_octate(mac, 0));
}

void net_copy_ipv4(ipv4_t *dest, ipv4_t *src)
{
    memcpy(dest, src, sizeof(ipv4_t));
}

void net_copy_mac(mac_t *dest, mac_t *src)
{
    memcpy(dest, src, sizeof(mac_t));
}