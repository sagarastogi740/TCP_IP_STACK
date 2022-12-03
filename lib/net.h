#ifndef __NET_H__
#define __NET_H__

#include <stdint.h>

typedef struct ipv4_
{
    uint8_t addr[4];
} ipv4_t;

typedef uint8_t netmask_t;

typedef struct mac_
{
    uint8_t addr[6];
} mac_t;

uint32_t
net_get_ipv4(ipv4_t *ipv4);

void net_set_ipv4(ipv4_t *ipv4, uint32_t addr);

uint8_t
net_get_ipv4_octate(ipv4_t *ipv4, uint8_t octate_no);

uint64_t
net_get_mac(mac_t *mac);

void net_set_mac(mac_t *mac, uint64_t val);

uint8_t
net_get_mac_octate(mac_t *mac, uint8_t octate_no);

void net_set_mac_octate(mac_t *dest_mac, mac_t *src_mac);

void net_set_ipv4_octate(ipv4_t *dest_ipv4, ipv4_t *src_ipv4);

uint64_t
net_generate_random_mac(uint32_t seed);

#endif /* __NET_H__ */