#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "ethernet.h"
#include "arp.h"
#include "../lib/net.h"

ethernet_t *
ethernet_create(mac_t *dest_mac, mac_t *src_mac, uint16_t type, void *payload, uint16_t payload_size, uint32_t CRC)
{
    ethernet_t *frame = (ethernet_t *)calloc(1, sizeof(ethernet_t));
    net_copy_mac(&frame->dest_mac, dest_mac);
    net_copy_mac(&frame->src_mac, src_mac);
    frame->type = type;
    frame->length = ETHERNET_FRAME_SIZE_WITHOUT_PAYLOAD + payload_size;
    frame->CRC = CRC;
    memset(&frame->payload, 0, sizeof(frame->payload));
    memcpy(&frame->payload, payload, payload_size);
    return frame;
}

ethernet_t *
ethernet_create_broadcast(mac_t *src_mac, uint16_t type, void *payload, uint16_t payload_size, uint32_t CRC)
{
    ethernet_t *frame = (ethernet_t *)calloc(1, sizeof(ethernet_t));
    net_set_broadcast_mac(&frame->dest_mac);
    net_copy_mac(&frame->src_mac, src_mac);
    frame->type = type;
    frame->length = ETHERNET_FRAME_SIZE_WITHOUT_PAYLOAD + payload_size;
    frame->CRC = CRC;
    memset(&frame->payload, 0, sizeof(frame->payload));
    memcpy(&frame->payload, payload, payload_size);
    return frame;
}

void ethernet_dump(ethernet_t *frame)
{
    net_dump_mac_addr(&frame->dest_mac);
    printf("\n");
    net_dump_mac_addr(&frame->src_mac);
    printf("\n");
    printf("%u\n", frame->type);
    printf("%u\n", frame->length);
    printf("%u\n", frame->CRC);
    arp_t arp;
    memcpy(&arp, &frame->payload, frame->length - ETHERNET_FRAME_SIZE_WITHOUT_PAYLOAD);
    printf("ARP START\n");
    arp_dump(&arp);
}
