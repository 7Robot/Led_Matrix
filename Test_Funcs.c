
#include "main.h"

#include "hardware/clocks.h"

// temporaire, durant le dev du bootloader
// bloc qui lit "toute" la flash

uint8_t Must_Read_All_Flash;
uint32_t Flash_Rd_Addr;



void Test_Loop(void)
{
  
}

u8 Test_Func (void)
{
 


    return 0;
}

#define FLASH_OFFSET 0x10000000
//2*1024*1024   // 2Mo
// => 256 ko
//#define FLASH_READ_MAX_SIZE  256*1024
#define FLASH_READ_MAX_SIZE 0x00200000

void All_Flash_Read_Loop(void)
{
    if (Must_Read_All_Flash) {
        printf("0x%08X : ", Flash_Rd_Addr);
        int i;
        for (i = 0; i< 16; i++) {
            uint8_t* Data_ptr = (uint8_t*)(0x10000000 + Flash_Rd_Addr);
            printf("%02X ", *Data_ptr);
            Flash_Rd_Addr ++;
        }
        printf("\n");
        if (Flash_Rd_Addr >= FLASH_READ_MAX_SIZE) {
            Must_Read_All_Flash = 0;
            printf("\n");
        }
    }
}

u8  Ping_Func (void)
{
    printf("Pong\n");
    return 0;
}

uint8_t Timer_Func(void)
{
    printf("%lu\n", Timer_ms1);
    return 0;
}

uint8_t Debug_En = 0;

uint8_t Debug_En_Func(void)
{
    u32 val32;
    if (Get_Param_u32(&val32)) {    // si y a param, on le prend, sinon on inverse l'etat actuel
        val32 = !Debug_En;
    }
    
    Debug_En = (val32 != 0);
    
    return 0;
}


