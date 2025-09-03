
#include "main.h"

#include "ws2812.pio.h"

uint8_t WS2812_Right_Strip_SM = 0;
uint8_t WS2812_Right_Strip_DMA = 0;

uint8_t WS2812_Left_Strip_SM = 0;
uint8_t WS2812_Left_Strip_DMA = 0;

uint8_t WS2812_Matrix_SM = 0;
uint8_t WS2812_Matrix_DMA = 0;


uint32_t RGB_Send_Timer = 0;
uint8_t RGB_Send_State = 0;

uint32_t Right_Strip_GRB_Pix[RGB_STRIP_LENGTH];
uint32_t Left_Strip_GRB_Pix[RGB_STRIP_LENGTH];
uint32_t Matrix_Strip_GRB_Pix[RGB_MATRIX_H*RGB_MATRIX_L];

uint32_t Matrix_RGB_Pix[RGB_MATRIX_H][RGB_MATRIX_L];
// matrice :   (TBC)
//  - ligne 0 en haut, 7 en bas
//  - colonne 0 a gauche, 31 a droite



void RGB_Init(void)
{
    uint8_t Dma_Req_from_pio_sm;
    dma_channel_config Dma_Conf;

    // on charge une seule fois le programme, toutes les SM doivent pouvoir tourner sur le meme
	uint32_t offset = pio_add_program(pio0, &ws2812_program);


    // Prog PIO
	WS2812_Right_Strip_SM = pio_claim_unused_sm(pio0, true);
    ws2812_program_init(pio0, WS2812_Right_Strip_SM, offset, RIGHT_RGB_STRIP_PIN, 800000, false);

    // Prog DMA
    WS2812_Right_Strip_DMA = dma_claim_unused_channel(true);
    Dma_Conf = dma_channel_get_default_config(WS2812_Right_Strip_DMA);
    channel_config_set_transfer_data_size(&Dma_Conf, DMA_SIZE_32);
    channel_config_set_read_increment(&Dma_Conf, true);
    channel_config_set_write_increment(&Dma_Conf, false);
    
    // voir "hardware/regs/dreq.h"
    // mais les TX du pio0, et les data_request DMA c'est la meme chose
    Dma_Req_from_pio_sm = WS2812_Right_Strip_SM;
    channel_config_set_dreq(&Dma_Conf, Dma_Req_from_pio_sm);

    dma_channel_configure(
        WS2812_Right_Strip_DMA,// Channel to be configured
        &Dma_Conf,                 // The configuration we just created
        &(pio0->txf[WS2812_Right_Strip_SM]),                // The initial write address
        &Right_Strip_GRB_Pix[0],     // The initial read address
        RGB_STRIP_LENGTH,        // Number of transfers; in this case each is 1 byte.
        false               // Start immediately.
    );


    // Prog PIO
	WS2812_Left_Strip_SM = pio_claim_unused_sm(pio0, true);
    ws2812_program_init(pio0, WS2812_Left_Strip_SM,  offset, LEFT_RGB_STRIP_PIN, 800000, false);

    // Prog DMA
    WS2812_Left_Strip_DMA = dma_claim_unused_channel(true);
    Dma_Conf = dma_channel_get_default_config(WS2812_Left_Strip_DMA);
    channel_config_set_transfer_data_size(&Dma_Conf, DMA_SIZE_32);
    channel_config_set_read_increment(&Dma_Conf, true);
    channel_config_set_write_increment(&Dma_Conf, false);
    
    // voir "hardware/regs/dreq.h"
    // mais les TX du pio0, et les data_request DMA c'est la meme chose
    Dma_Req_from_pio_sm = WS2812_Left_Strip_SM;
    channel_config_set_dreq(&Dma_Conf, Dma_Req_from_pio_sm);

    dma_channel_configure(
        WS2812_Left_Strip_DMA,// Channel to be configured
        &Dma_Conf,                 // The configuration we just created
        &(pio0->txf[WS2812_Left_Strip_SM]),                // The initial write address
        &Left_Strip_GRB_Pix[0],     // The initial read address
        RGB_STRIP_LENGTH,        // Number of transfers; in this case each is 1 byte.
        false               // Start immediately.
    );

    // Prog PIO
	WS2812_Matrix_SM = pio_claim_unused_sm(pio0, true);
    ws2812_program_init(pio0, WS2812_Matrix_SM,      offset, MATRIX_RGB_STRIP_PIN, 800000, false);

    // Prog DMA
    WS2812_Matrix_DMA = dma_claim_unused_channel(true);
    Dma_Conf = dma_channel_get_default_config(WS2812_Matrix_DMA);
    channel_config_set_transfer_data_size(&Dma_Conf, DMA_SIZE_32);
    channel_config_set_read_increment(&Dma_Conf, true);
    channel_config_set_write_increment(&Dma_Conf, false);
    
    // voir "hardware/regs/dreq.h"
    // mais les TX du pio0, et les data_request DMA c'est la meme chose
    Dma_Req_from_pio_sm = WS2812_Matrix_SM;
    channel_config_set_dreq(&Dma_Conf, Dma_Req_from_pio_sm);

    dma_channel_configure(
        WS2812_Matrix_DMA,// Channel to be configured
        &Dma_Conf,                 // The configuration we just created
        &(pio0->txf[WS2812_Matrix_SM]),                // The initial write address
        &Matrix_Strip_GRB_Pix[0],     // The initial read address
        RGB_MATRIX_H*RGB_MATRIX_L,        // Number of transfers; in this case each is 1 byte.
        false               // Start immediately.
    );
}

void RGB_Loop(void)
{
    switch (RGB_Send_State) {
        case 0:
            if ((Timer_ms1 - RGB_Send_Timer) > 10) {
                RGB_Send_Timer = Timer_ms1;
                RGB_Anim_Loop();
                RGB_Send_State ++;
            }
            break;
        case 1:
            for (uint16_t i = 0; i < RGB_STRIP_LENGTH; i++) {    // shift avant envoi
                Right_Strip_GRB_Pix[i] = Right_Strip_GRB_Pix[i] << 8;
                Left_Strip_GRB_Pix[i]  = Left_Strip_GRB_Pix[i]  << 8;
            }
            uint16_t Line = 0, Col = 0;
            for (uint16_t i = 0; i < RGB_MATRIX_H*RGB_MATRIX_L; i++) {    // creation du "rubanc" a partir de la matrice
                Matrix_Strip_GRB_Pix[i] = Matrix_RGB_Pix[Line][Col] << 8;
                // il faut se balader en serpentin
                if (!(Col & 1)) {   // si on est sur colonne paire
                    if (Line == (RGB_MATRIX_H - 1)) {   // arrive en bas : decal sur le cote
                        Col ++;
                    } else {                            // sinon descend
                        Line ++;
                    }
                } else {    // colonne impaire
                    if (Line == 0) {                    // arrive en haut : decal cote
                        Col ++;
                    } else {
                        Line --;                        // sinon remonte
                    }
                }
            }

            RGB_Send_State ++;
            break;
        case 2:
            //dma_channel_start(DMA_Chan_For_WS2812);
            dma_channel_transfer_from_buffer_now(WS2812_Right_Strip_DMA, &Right_Strip_GRB_Pix[0], RGB_STRIP_LENGTH);
            dma_channel_transfer_from_buffer_now(WS2812_Left_Strip_DMA,  &Left_Strip_GRB_Pix[0],  RGB_STRIP_LENGTH);
            dma_channel_transfer_from_buffer_now(WS2812_Matrix_DMA,      &Matrix_Strip_GRB_Pix[0],  RGB_MATRIX_H*RGB_MATRIX_L);

            RGB_Send_State ++;
            break;
        case 3:
            // attente que les DMA soient finis :
            if (    (!dma_channel_is_busy(WS2812_Right_Strip_DMA))  &&    
                    (!dma_channel_is_busy(WS2812_Left_Strip_DMA))   &&    
                    (!dma_channel_is_busy(WS2812_Matrix_DMA))           ) {
                RGB_Send_State ++;
            }
            break;
        case 4:
            for (uint16_t i = 0; i < RGB_STRIP_LENGTH; i++) {    // deshift apres (pour pouvoir jouer plus facilement)
                Right_Strip_GRB_Pix[i] = Right_Strip_GRB_Pix[i] >> 8;
                Left_Strip_GRB_Pix[i]  = Left_Strip_GRB_Pix[i]  >> 8;
            }
            RGB_Send_State = 0;
            break;
    }
}

