#ifndef __BT_H
#define __BT_H


// void BT_packet_handler (uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size);
// void spp_service_setup(void);


void BT_Init(void);
void BT_Loop(void);


#endif // __BT_H