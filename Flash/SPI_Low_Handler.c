

#include "main.h"

SPI_Transaction SPI_Transaction_Tab[MAX_SPI_TRANSAC];

u16 SPI_Transaction_Tab_TODO = 0, SPI_Transaction_Tab_DONE = 0;
u16 SPI_Low_Handler_State = 0;

volatile u16 SPI_Tx_Count = 0;
volatile u16 SPI_Rx_Count = 0;

volatile SPI_Transaction Current_SPI_Transaction;


void Add_SPI_Transtion (u8 Config, u16 NB_Transferts, u8 *ptr_to_send, u8 *ptr_to_get, u8 *ptr_on_done)
{
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].Config = Config;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].NB_Transferts = NB_Transferts;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].ptr_to_send = ptr_to_send;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].ptr_to_get = ptr_to_get;
	SPI_Transaction_Tab[SPI_Transaction_Tab_TODO].ptr_on_done = ptr_on_done;
	
	SPI_Transaction_Tab_TODO ++;
	if (SPI_Transaction_Tab_TODO >= MAX_SPI_TRANSAC)
		SPI_Transaction_Tab_TODO = 0;
    
}

void SPI_Low_Handler_Init(void)
{
	SPI_Low_Handler_State = 0;
	SPI_Transaction_Tab_TODO = 0;
	SPI_Transaction_Tab_DONE = 0;


    spi_init(WIZ_SPI, 100 * 1000);
    gpio_set_function(WIZ_MOSI_PIN, GPIO_FUNC_SPI);
    gpio_set_function(WIZ_MISO_PIN, GPIO_FUNC_SPI);
    gpio_set_function(WIZ_SCLK_PIN, GPIO_FUNC_SPI);
    gpio_init(WIZ_CS_PIN);
    gpio_put(WIZ_CS_PIN, 1);
    gpio_set_dir(WIZ_CS_PIN, GPIO_OUT);

}



void SPI_Low_Handler_Loop(void)
{
	
	switch (SPI_Low_Handler_State) {
		case 0:
			if (SPI_Transaction_Tab_DONE != SPI_Transaction_Tab_TODO) {
                SPI_Low_Handler_State ++;
            }
			break;
		case 1:
			SPI_Tx_Count = 0;
			SPI_Rx_Count = 0;
			Current_SPI_Transaction = SPI_Transaction_Tab[SPI_Transaction_Tab_DONE];
			SPI_Transaction_Tab_DONE ++;
			if (SPI_Transaction_Tab_DONE >= MAX_SPI_TRANSAC)
				SPI_Transaction_Tab_DONE = 0;
			Param_SPI_Transac(Current_SPI_Transaction.Config);
			SPI_Low_Handler_State ++;
            break;
		case 2:
            Start_End_SPI_Transac(Current_SPI_Transaction.Config, 0);
            SPI_Low_Handler_State ++;
            break;
        case 3:
            while(WIZ_SPI_hw->sr & SPI_SSPSR_RNE_BITS) {  // si qqchose � recevoir
                Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count] = WIZ_SPI_hw->dr;
                //printf("G : %02X\n", Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count]);
                SPI_Rx_Count ++;
                // si on a tout recu, on sort, sinon on envoit l'octet suivant
                if (SPI_Rx_Count == Current_SPI_Transaction.NB_Transferts) {
                    SPI_Low_Handler_State ++;
                }
            }
            // s'il me reste à envoyer, et qu'il reste de la place
            if (SPI_Tx_Count < Current_SPI_Transaction.NB_Transferts) {
                if (WIZ_SPI_hw->sr & SPI_SSPSR_TFE_BITS) {
                    WIZ_SPI_hw->dr = Current_SPI_Transaction.ptr_to_send[SPI_Tx_Count];
                    SPI_Tx_Count ++;
                }
            }

            /*if (SPI1STATbits.SPIRBF) {
				Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count] = SPI1BUF;
                //printf("G : %02X\n", Current_SPI_Transaction.ptr_to_get[SPI_Rx_Count]);
				SPI_Rx_Count ++;
                // si on a tout recu, on sort, sinon on envoit l'octet suivant
				if (SPI_Rx_Count == Current_SPI_Transaction.NB_Transferts) {
					SPI_Low_Handler_State ++;
                } else {
                    SPI1BUF = Current_SPI_Transaction.ptr_to_send[SPI_Tx_Count];
                    //printf("S : %02X\n", Current_SPI_Transaction.ptr_to_send[SPI_Tx_Count]);
                    SPI_Tx_Count ++;
                }
			}*/
			break;
		case 4:
			Start_End_SPI_Transac(Current_SPI_Transaction.Config, 1);
			*(Current_SPI_Transaction.ptr_on_done) = 1;
			SPI_Low_Handler_State = 0;
            //SPI_EIO1_Test_Func();
            break;
		default:
			break;
	}
}




/*
 * help from pic :
 * CKE: SPIx Clock Edge Select bit
 * 1 = Serial output data changes on transition from active clock state to Idle clock state (see bit 6)
 * 0 = Serial output data changes on transition from Idle clock state to active clock state (see bit 6)
 * bit 6 CKP: Clock Polarity Select bit    
 * 1 = Idle state for clock is a high level; active state is a low level
 * 0 = Idle state for clock is a low level; active state is a high level
 *
 * CKE = not CPHA
 * CKP = CPOL
*/

void Param_SPI_Transac (u8 Config)
{
	switch (Config) {
		case SPI_WIZ_CONFIG:

			// config SPI + Pins pour WIZ
            
//          //Modes PIN WIZ = 00 ou 11
//          // choix 00
            
            
            if (1) {
                uint8_t Poubelle;
                while(WIZ_SPI_hw->sr & SPI_SSPSR_RNE_BITS) {  // si qqchose � recevoir
                    Poubelle = WIZ_SPI_hw->dr;
                }
            }

			break;

		default :
			break;
	}
    
}

void Start_End_SPI_Transac (u8 Config, u8 CS_Val)
{
	switch (Config) {
		case SPI_WIZ_CONFIG:
            gpio_put(WIZ_CS_PIN, CS_Val);
			break;
		default :
			break;
	}
}

