/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "main.h"

// #include "btstack_run_loop.h"
// #include "btstack_event.h"
// #include "btstack.h"

// // #include "pico/stdlib.h"
// #include "pico/stdio_usb.h"
// // #include "picow_bt_example_common.h"

// // #include "hardware/watchdog.h"
// #include "pico/bootrom.h"
// #include "pico/cyw43_arch.h"




#define RFCOMM_SERVER_CHANNEL 1

static btstack_packet_callback_registration_t hci_event_callback_registration;
static uint16_t rfcomm_channel_id;
static uint8_t  spp_service_buffer[150];
uint16_t BT_Nb_To_Send = 0;


/* @section SPP Service Setup 
 *s
 * @text To provide an SPP service, the L2CAP, RFCOMM, and SDP protocol layers 
 * are required. After setting up an RFCOMM service with channel nubmer
 * RFCOMM_SERVER_CHANNEL, an SDP record is created and registered with the SDP server.
 * Example code for SPP service setup is
 * provided in Listing SPPSetup. The SDP record created by function
 * spp_create_sdp_record consists of a basic SPP definition that uses the provided
 * RFCOMM channel ID and service name. For more details, please have a look at it
 * in \path{src/sdp_util.c}. 
 * The SDP record is created on the fly in RAM and is deterministic.
 * To preserve valuable RAM, the result could be stored as constant data inside the ROM.   
 */

/* LISTING_START(SPPSetup): SPP service setup */ 
// void spp_service_setup(void){

//     // register for HCI events  : deja fait avant
//     // hci_event_callback_registration.callback = &BT_packet_handler;
//     // hci_add_event_handler(&hci_event_callback_registration);

//     l2cap_init();


//     rfcomm_init();
//     rfcomm_register_service(BT_packet_handler, RFCOMM_SERVER_CHANNEL, 0xffff);  // reserved channel, mtu limited by l2cap

//     // init SDP, create record for SPP and register with SDP
//     sdp_init();
//     memset(spp_service_buffer, 0, sizeof(spp_service_buffer));
//     spp_create_sdp_record(spp_service_buffer, 0x10001, RFCOMM_SERVER_CHANNEL, "SPP Counter");
//     sdp_register_service(spp_service_buffer);
//     printf("SDP service record size: %u\n", de_get_len(spp_service_buffer));
// }



/* @section Bluetooth Logic 
 * @text The Bluetooth logic is implemented within the 
 * packet handler, see Listing SppServerPacketHandler. In this example, 
 * the following events are passed sequentially: 
 * - BTSTACK_EVENT_STATE,
 * - HCI_EVENT_PIN_CODE_REQUEST (Standard pairing) or 
 * - HCI_EVENT_USER_CONFIRMATION_REQUEST (Secure Simple Pairing),
 * - RFCOMM_EVENT_INCOMING_CONNECTION,
 * - RFCOMM_EVENT_CHANNEL_OPENED, 
* - RFCOMM_EVETN_CAN_SEND_NOW, and
 * - RFCOMM_EVENT_CHANNEL_CLOSED
 */

/* @text Upon receiving HCI_EVENT_PIN_CODE_REQUEST event, we need to handle
 * authentication. Here, we use a fixed PIN code "0000".
 *
 * When HCI_EVENT_USER_CONFIRMATION_REQUEST is received, the user will be 
 * asked to accept the pairing request. If the IO capability is set to 
 * SSP_IO_CAPABILITY_DISPLAY_YES_NO, the request will be automatically accepted.
 *
 * The RFCOMM_EVENT_INCOMING_CONNECTION event indicates an incoming connection.
 * Here, the connection is accepted. More logic is need, if you want to handle connections
 * from multiple clients. The incoming RFCOMM connection event contains the RFCOMM
 * channel number used during the SPP setup phase and the newly assigned RFCOMM
 * channel ID that is used by all BTstack commands and events.
 *
 * If RFCOMM_EVENT_CHANNEL_OPENED event returns status greater then 0,
 * then the channel establishment has failed (rare case, e.g., client crashes).
 * On successful connection, the RFCOMM channel ID and MTU for this
 * channel are made available to the heartbeat counter. After opening the RFCOMM channel, 
 * the communication between client and the application
 * takes place. In this example, the timer handler increases the real counter every
 * second. 
 *
 * RFCOMM_EVENT_CAN_SEND_NOW indicates that it's possible to send an RFCOMM packet
 * on the rfcomm_cid that is include

 */ 

/* LISTING_START(SppServerPacketHandler): SPP Server - Heartbeat Counter over RFCOMM */
void BT_packet_handler (uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size){
    UNUSED(channel);

/* LISTING_PAUSE */ 
    bd_addr_t event_addr;
    bd_addr_t local_addr;
    uint8_t   rfcomm_channel_nr;
    uint16_t  mtu;
    int i;

    switch (packet_type) {
        case HCI_EVENT_PACKET:
            switch (hci_event_packet_get_type(packet)) {
                // ajout from other packet handler :
                case BTSTACK_EVENT_STATE:
                    if (btstack_event_state_get_state(packet) != HCI_STATE_WORKING) return;
                    gap_local_bd_addr(local_addr);
                    printf("BTstack up and running on %s.\n", bd_addr_to_str(local_addr));
                    break;

                    
                case HCI_EVENT_PIN_CODE_REQUEST:
                    // inform about pin code request
                    printf("Pin code request - using '0000'\n");
                    hci_event_pin_code_request_get_bd_addr(packet, event_addr);
                    gap_pin_code_response(event_addr, "0000");
                    break;

                case HCI_EVENT_USER_CONFIRMATION_REQUEST:
                    // ssp: inform about user confirmation request
                    printf("SSP User Confirmation Request with numeric value %06u\n", little_endian_read_32(packet, 8));
                    printf("SSP User Confirmation Auto accept\n");
                    break;

                case RFCOMM_EVENT_INCOMING_CONNECTION:
                    rfcomm_event_incoming_connection_get_bd_addr(packet, event_addr);
                    rfcomm_channel_nr = rfcomm_event_incoming_connection_get_server_channel(packet);
                    rfcomm_channel_id = rfcomm_event_incoming_connection_get_rfcomm_cid(packet);
                    printf("RFCOMM channel %u requested for %s\n", rfcomm_channel_nr, bd_addr_to_str(event_addr));
                    rfcomm_accept_connection(rfcomm_channel_id);
                    break;
               
                case RFCOMM_EVENT_CHANNEL_OPENED:
                    if (rfcomm_event_channel_opened_get_status(packet)) {
                        printf("RFCOMM channel open failed, status 0x%02x\n", rfcomm_event_channel_opened_get_status(packet));
                    } else {
                        rfcomm_channel_id = rfcomm_event_channel_opened_get_rfcomm_cid(packet);
                        mtu = rfcomm_event_channel_opened_get_max_frame_size(packet);
                        printf("RFCOMM channel open succeeded. New RFCOMM Channel ID %u, max frame size %u\n", rfcomm_channel_id, mtu);
                    }
                    break;
                case RFCOMM_EVENT_CAN_SEND_NOW:
                    if (BT_Nb_To_Send > 200) {
                        BT_Nb_To_Send = 200;
                    }
                    if (BT_Nb_To_Send) {
                        rfcomm_send(rfcomm_channel_id, stdio_bt_get_stdout_ptr(), BT_Nb_To_Send);
                        stdio_bt_advance_stdout(BT_Nb_To_Send);
                    }
                    BT_Nb_To_Send = 0;
                    break;

/* LISTING_PAUSE */                 
                case RFCOMM_EVENT_CHANNEL_CLOSED:
                    printf("RFCOMM channel closed\n");
                    rfcomm_channel_id = 0;
                    break;
                
                default:
                    break;
            }
            break;

        case RFCOMM_DATA_PACKET:
            for (i=0; i<size; i++) {
                stdio_bt_add_stdin(packet[i]);
            }
            break;

        default:
            break;
    }
/* LISTING_RESUME */ 
}
/* LISTING_END */




void BT_Init(void)
{
    // inform about BTstack state
    hci_event_callback_registration.callback = &BT_packet_handler;
    hci_add_event_handler(&hci_event_callback_registration);
    
    // spp_service_setup();
    // /* LISTING_START(SPPSetup): SPP service setup */ 
    // void spp_service_setup(void){

    // register for HCI events  : deja fait avant
    // hci_event_callback_registration.callback = &BT_packet_handler;
    // hci_add_event_handler(&hci_event_callback_registration);

    l2cap_init();


    rfcomm_init();
    rfcomm_register_service(BT_packet_handler, RFCOMM_SERVER_CHANNEL, 0xffff);  // reserved channel, mtu limited by l2cap

    // init SDP, create record for SPP and register with SDP
    sdp_init();
    memset(spp_service_buffer, 0, sizeof(spp_service_buffer));
    spp_create_sdp_record(spp_service_buffer, 0x10001, RFCOMM_SERVER_CHANNEL, "Plateau CDFRJ");
    sdp_register_service(spp_service_buffer);
    printf("SDP service record size: %u\n", de_get_len(spp_service_buffer));
// }


    gap_discoverable_control(1);
    gap_ssp_set_io_capability(SSP_IO_CAPABILITY_DISPLAY_YES_NO);
    gap_set_local_name("Plateau CDFRJ 00:00:00:00:00:00");

    // turn on!
    hci_power_control(HCI_POWER_ON);


    BT_StdIO_Init();

}

uint32_t Last_BT_Timer_Poll = 0;
void BT_Loop(void)
{
    if (Timer_ms1 != Last_BT_Timer_Poll) {
        Last_BT_Timer_Poll = Timer_ms1;

        cyw43_arch_poll();
        BT_Nb_To_Send = stdio_bt_get_nb_in_stdout();

        if (rfcomm_channel_id && BT_Nb_To_Send){
            rfcomm_request_can_send_now_event(rfcomm_channel_id);
        }
    }
}