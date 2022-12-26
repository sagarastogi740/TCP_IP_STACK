#ifndef __LAYER2_H__
#define __LAYER2_H__

#include "../lib/interface.h"
#include "../lib/node.h"
#include "../lib/net.h"

#define PAYLOAD_SIZE 248 /* Maximum allowed is 1500 */

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

#pragma pack(push, 1)
typedef struct ethernet_frame_
{
    mac_t dest_mac;
    mac_t src_mac;
    uint16_t length;
    uint8_t payload[PAYLOAD_SIZE];
    uint32_t CRC;
} ethernet_frame_t;
#pragma pack(pop)

void layer2_frame_recv(node_t *node, interface_t *interface, void *frame, uint32_t frame_size);

#endif /* __LAYER2_H__ */