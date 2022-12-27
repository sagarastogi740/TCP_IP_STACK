#ifndef __LAYER2_H__
#define __LAYER2_H__

#include "../lib/interface.h"
#include "../lib/node.h"
#include "../lib/net.h"

#define PAYLOAD_SIZE 248 /* Maximum allowed is 1500 */

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