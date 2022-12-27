#ifndef __ARP_H__
#define __ARP_H__

#include <stdint.h>
#include "../lib/net.h"

#define ARP_BROAD_REQ 1
#define ARP_REPLY 2
#define ARP_MSG 806

#pragma pack(push, 1)
typedef struct arp_
{
    uint16_t hw_type;
    uint16_t proto_type;
    uint8_t hw_addr_len;
    uint8_t proto_addr_len;
    uint16_t opcode;
    mac_t src_mac;
    ipv4_t src_ip;
    mac_t dest_mac;
    ipv4_t dest_ip;
} arp_t;
#pragma pack(pop)

#endif /* __ARP_H__ */