#ifndef __ETHERNET_H__
#define __ETHERNET_H__

#include "../lib/net.h"

#define MAX_PAYLOAD_SIZE 1500 /* Maximum allowed is 1500 and minimum is 46 */

#define ARP_MSG 806

#pragma pack(push, 1)
typedef struct ethernet_
{
    mac_t dest_mac;
    mac_t src_mac;
    uint16_t type;
    uint16_t length;
    uint32_t CRC;
    uint8_t payload[MAX_PAYLOAD_SIZE];
} ethernet_t;
#pragma pack(pop)

#define ETHERNET_FRAME_SIZE_WITHOUT_PAYLOAD (sizeof(ethernet_t) - MAX_PAYLOAD_SIZE)

ethernet_t *
ethernet_create(mac_t *dest_mac, mac_t *src_mac, uint16_t type, void *payload, uint16_t payload_size, uint32_t CRC);

ethernet_t *
ethernet_create_broadcast(mac_t *src_mac, uint16_t type, void *payload, uint16_t payload_size, uint32_t CRC);

void ethernet_dump(ethernet_t *frame);

#endif /* __ETHERNET_H__ */
