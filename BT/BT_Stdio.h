#ifndef __BT_STDIO_H
#define __BT_STDIO_H


#define BT_COMM_BUFF_SIZE 1000

void BT_StdIO_Init(void);

void stdio_bt_add_stdin(char c);

uint16_t stdio_bt_get_nb_in_stdout(void);
void stdio_bt_advance_stdout(uint16_t nb_sent);
uint8_t* stdio_bt_get_stdout_ptr(void);


#endif // __BT_STDIO_H