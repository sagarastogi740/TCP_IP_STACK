#include <stdbool.h>
#include <stdio.h>
#include "layer2.h"
#include "../lib/interface.h"
#include "../lib/node.h"
#include "../lib/net.h"

static inline bool
l2_frame_recv_qualify_on_intf(ethernet_frame_t *frame, interface_t *intf)
{
    if (net_are_mac_equal(&frame->dest_mac, &intf->mac) || net_is_mac_broadcast(&frame->dest_mac))
    {
        return true;
    }
    return false;
}

void layer2_frame_recv(node_t *node, interface_t *interface, void *frame, uint32_t frame_size)
{
    uint8_t *msg = frame;
    printf("msg = %s, on node = %u, interface = %u\n", msg, node_get_id(node), interface_get_id(interface));
    printf("%d\n", frame_size);
}