#include <stdlib.h>
#include <stdio.h>
#include "../lib/net.h"
#include "arp.h"

arp_t *arp_create_broadcast(mac_t *src_mac, ipv4_t *src_ip, ipv4_t *dest_ip)
{
    arp_t *arp_bcast = (arp_t *)calloc(1, sizeof(arp_t));
    arp_bcast->hw_type = 1;
    arp_bcast->proto_type = 0x0800;
    arp_bcast->hw_addr_len = sizeof(mac_t);
    arp_bcast->proto_addr_len = sizeof(ipv4_t);

    arp_bcast->opcode = ARP_BROAD_REQ;
    net_copy_mac(&arp_bcast->src_mac, src_mac);
    net_copy_ipv4(&arp_bcast->src_ip, src_ip);
    net_set_mac(&arp_bcast->dest_mac, 0);
    net_copy_ipv4(&arp_bcast->dest_ip, dest_ip);
    return arp_bcast;
}

arp_t *arp_create_reply(mac_t *src_mac, mac_t *dest_mac, ipv4_t *src_ip, ipv4_t *dest_ip)
{
    arp_t *arp_reply = (arp_t *)calloc(1, sizeof(arp_t));
    arp_reply->hw_type = 1;
    arp_reply->proto_type = 0x0800;
    arp_reply->hw_addr_len = sizeof(mac_t);
    arp_reply->proto_addr_len = sizeof(ipv4_t);

    arp_reply->opcode = ARP_REPLY;
    net_copy_mac(&arp_reply->src_mac, src_mac);
    net_copy_ipv4(&arp_reply->src_ip, src_ip);
    net_copy_mac(&arp_reply->dest_mac, dest_mac);
    net_copy_ipv4(&arp_reply->dest_ip, dest_ip);
    return arp_reply;
}

void arp_dump(arp_t *arp)
{
    printf("%u\n", arp->hw_type);
    printf("%u\n", arp->proto_type);
    printf("%u\n", arp->hw_addr_len);
    printf("%u\n", arp->proto_addr_len);
    printf("%u\n", arp->opcode);
    net_dump_mac_addr(&arp->src_mac);
    printf("\n");
    net_dump_ipv4_addr(&arp->src_ip, 0);
    printf("\n");
    net_dump_mac_addr(&arp->dest_mac);
    printf("\n");
    net_dump_ipv4_addr(&arp->dest_ip, 0);
    printf("\n");
}