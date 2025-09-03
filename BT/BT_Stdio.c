

#include "main.h"


uint8_t BT_TX_Buff[BT_COMM_BUFF_SIZE];
uint16_t BT_TX_Buff_TODO = 0, BT_TX_Buff_DONE = 0;
uint8_t BT_RX_Buff[BT_COMM_BUFF_SIZE];
uint16_t BT_RX_Buff_TODO = 0, BT_RX_Buff_DONE = 0;


int stdio_bt_in_chars(char *buf, int length);
void stdio_bt_out_chars(const char *buf, int length);

stdio_driver_t stdio_BT = {
    .out_chars = stdio_bt_out_chars,
    .in_chars = stdio_bt_in_chars,
    .out_flush = NULL,
    .set_chars_available_callback = NULL,
#if PICO_STDIO_ENABLE_CRLF_SUPPORT
    //.crlf_enabled = PICO_STDIO_DEFAULT_CRLF
    .crlf_enabled = 0
#endif
};


void BT_StdIO_Init(void)
{
	stdio_set_driver_enabled(&stdio_BT, true);
}

// getchar
int stdio_bt_in_chars(char *buf, int length) {
    if ((length > 0) && (BT_RX_Buff_TODO != BT_RX_Buff_DONE)) {
        buf[0] = BT_RX_Buff[BT_RX_Buff_DONE];
        BT_RX_Buff_DONE ++;
        if (BT_RX_Buff_DONE >= BT_COMM_BUFF_SIZE) {
            BT_RX_Buff_DONE = 0;
        }
        return 1;
    } else {
        return 0;
    }
}

void stdio_bt_add_stdin(char c) {
    BT_RX_Buff[BT_RX_Buff_TODO] = c;
    BT_RX_Buff_TODO ++;
    if (BT_RX_Buff_TODO >= BT_COMM_BUFF_SIZE) {
        BT_RX_Buff_TODO = 0;
    }
}

void stdio_bt_out_chars(const char *buf, int length) {
    int i;
    for (i = 0; i < length; i++) {
        BT_TX_Buff[BT_TX_Buff_TODO] = buf[i];
        BT_TX_Buff_TODO ++;
        if (BT_TX_Buff_TODO >= BT_COMM_BUFF_SIZE) {
            BT_TX_Buff_TODO = 0;
        }
    }
}

uint16_t stdio_bt_get_nb_in_stdout(void) {
    if (BT_TX_Buff_TODO >= BT_TX_Buff_DONE) {
        return BT_TX_Buff_TODO - BT_TX_Buff_DONE;
    } else {    // gestion du tour complet
        return BT_COMM_BUFF_SIZE - BT_TX_Buff_DONE;
    }
}

void stdio_bt_advance_stdout(uint16_t nb_sent) {
    BT_TX_Buff_DONE += nb_sent;
    if (BT_TX_Buff_DONE >= BT_COMM_BUFF_SIZE) {
        BT_TX_Buff_DONE = 0;
    }
}

uint8_t* stdio_bt_get_stdout_ptr(void) {
    return &BT_TX_Buff[BT_TX_Buff_DONE];
}
