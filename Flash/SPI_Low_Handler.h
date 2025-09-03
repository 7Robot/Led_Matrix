
#ifndef __SPI_LOW_HANDLER_H
#define __SPI_LOW_HANDLER_H





#define MAX_SPI_TRANSAC 10

#define SPI_WIZ_CONFIG 0x01


typedef struct {
    u8 Config;
    u16 NB_Transferts;
	u8 *ptr_to_send;
	u8 *ptr_to_get;
	u8 *ptr_on_done;
} SPI_Transaction;



void Add_SPI_Transtion (u8 Config, u16 NB_Transferts, u8 *ptr_to_send, u8 *ptr_to_get, u8 *ptr_on_done);

void SPI_Low_Handler_Init (void);

void SPI_Low_Handler_Loop (void);

void Param_SPI_Transac (u8 Config);
void Start_End_SPI_Transac (u8 Config, u8 CS_Val);


#endif
