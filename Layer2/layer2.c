#include <stdbool.h>
#include <stdio.h>
#include "layer2.h"
#include "ethernet.h"
#include "../lib/interface.h"
#include "../lib/node.h"
#include "../lib/net.h"

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
_layer2_send_arp_reply_message()
{
}

void layer2_frame_recv(node_t *node, interface_t *interface, void *frame, uint32_t frame_size)
{
    if (_layer2_frame_recv_qualify_on_intf((ethernet_t *)frame, interface))
    {
        switch (((ethernet_t *)frame)->type)
        {
        case ARP_MSG:
            _layer2_send_arp_reply_message();
            break;
        default:
        }
        ethernet_dump(frame);
    }
}