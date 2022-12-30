#ifndef __NET_H__
#define __NET_H__

#include <stdint.h>
#include <stdbool.h>

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

void net_set_mac_octate(mac_t *dest_mac, uint8_t octate_no, uint8_t value);

void net_set_ipv4_octate(ipv4_t *dest_ipv4, uint8_t octate_no, uint8_t val);

uint64_t
net_generate_random_mac();

bool net_are_mac_equal(mac_t *mac_1, mac_t *mac_2);

bool net_is_mac_broadcast(mac_t *mac);

bool net_are_ip_equal(ipv4_t *ip_1, ipv4_t *ip_2);

void net_dump_ipv4_addr(ipv4_t *ipv4, uint8_t mask);

void net_dump_mac_addr(mac_t *mac);

void net_copy_ipv4(ipv4_t *dest, ipv4_t *src);

void net_copy_mac(mac_t *dest, mac_t *src);

uint32_t
net_ip_string_to_uin32(const char *ip);

ipv4_t
net_ip_string_to_ipv4(const char *ip);

void net_set_broadcast_mac(mac_t *mac);

bool net_ipv4_subnet_are_same(ipv4_t *ip_1, ipv4_t *ip_2, uint8_t mask_1, uint8_t mask_2);

#endif /* __NET_H__ */