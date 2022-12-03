#include <memory.h>
#include <stdlib.h>
#include "net.h"

inline uint64_t
net_generate_random_mac(uint32_t seed)
{
    uint64_t rn = 0;
    srand(seed);
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
net_set_ipv4_octate(ipv4_t *dest_ipv4, ipv4_t *src_ipv4)
{
    memcpy(dest_ipv4, src_ipv4, sizeof(ipv4_t));
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
net_set_mac_octate(mac_t *dest_mac, mac_t *src_mac)
{
    memcpy(dest_mac, src_mac, sizeof(mac_t));
}
