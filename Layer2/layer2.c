#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "layer2.h"
#include "ethernet.h"
#include "arp.h"
#include "../lib/interface.h"
#include "../lib/node.h"
#include "../lib/net.h"

#define _GET_ARP_OF_ETHERNET(ethernet_frame_ptr) ((arp_t *)(((ethernet_t *)(ethernet_frame_ptr))->payload))
#define _GET_ETHERNET(frame_ptr) ((ethernet_t *)frame_ptr)

static inline bool
_layer2_frame_recv_qualify_on_intf(ethernet_t *frame, interface_t *intf)
{
    if (net_are_mac_equal(&frame->dest_mac, &intf->mac) || net_is_mac_broadcast(&frame->dest_mac))
    {
        return true;
    }
    return false;
}

static inline void
_layer2_process_arp_broadcast_message(node_t *node, interface_t *interface, arp_t *arp_hdr)
{
    arp_table_entry_add(&node->arp_table,
                        &arp_hdr->src_ip,
                        &arp_hdr->src_mac,
                        interface);

    arp_t *arp = arp_create_reply(&interface->mac,
                                  &arp_hdr->src_mac,
                                  &interface->ip,
                                  &arp_hdr->src_ip);

    ethernet_t *eth_frame = ethernet_create(&arp_hdr->src_mac,
                                            &interface->mac,
                                            ARP_MSG,
                                            (void *)arp,
                                            sizeof(arp_t),
                                            0);

    free(arp);

    node_send_arp_reply_msg(node, interface, eth_frame);

    free(eth_frame);
}

static inline void
_layer2_process_arp_reply_message(node_t *node, interface_t *interface, arp_t *arp_hdr)
{
    arp_table_entry_add(&node->arp_table,
                        &arp_hdr->src_ip,
                        &arp_hdr->src_mac,
                        interface);
}

static inline void
_handle_ARP_message(node_t *node, interface_t *interface, arp_t *arp_hdr)
{
    switch (arp_hdr->opcode)
    {
    case ARP_BROAD_REQ:
        _layer2_process_arp_broadcast_message(node, interface, arp_hdr);
        break;
    case ARP_REPLY:
        _layer2_process_arp_reply_message(node, interface, arp_hdr);
        break;
    default:
    }
}

void layer2_frame_recv(node_t *node, interface_t *interface, void *frame, uint32_t frame_size)
{
    if (_layer2_frame_recv_qualify_on_intf((ethernet_t *)frame, interface))
    {
        switch (_GET_ETHERNET(frame)->type)
        {
        case ARP_MSG:
            _handle_ARP_message(node, interface, _GET_ARP_OF_ETHERNET(frame));
            break;
        default:
        }
    }
}