#ifndef __LAYER2_H__
#define __LAYER2_H__

#include "../lib/interface.h"
#include "../lib/node.h"

void layer2_frame_recv(node_t *node, interface_t *interface, void *frame, uint32_t frame_size);

#endif /* __LAYER2_H__ */