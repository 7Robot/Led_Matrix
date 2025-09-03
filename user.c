
#include "main.h"


void Init_All(void) {
    
    // initialize all things    
	stdio_init_all();
    ADC_Init();

    RGB_Init();
    Flash_LogFile_Init();
    Setup_File_Init();


    cyw43_arch_init();
    BT_Init();

    // "purge" du buffer USB RX ?
	getchar_timeout_us(0);

}

uint8_t Reboot_Func(void) {
    watchdog_hw->ctrl = WATCHDOG_CTRL_TRIGGER_BITS;
    return 0;
}

uint8_t Reboot_USB_Func(void) {
    
    reset_usb_boot(0,0);
    return 0;
} 

uint8_t Print_Version_Func(void) {
    printf("version,PKit_Plateau_RP2040_Software\n");
    printf("Compiled_on,");
    printf(__DATE__);
    printf(" @ ");
    printf(__TIME__);
    printf("\n");
    return 0;
}


uint32_t time_ms_32(void) {

    // Read the lower 32 bits
    uint64_t lo = timer_hw->timelr;
    // Now read the upper 32 bits 
    uint64_t hi = timer_hw->timehr;

    uint64_t loc_time_us = (hi << 32) + lo;
    loc_time_us = loc_time_us / 1000;
    return loc_time_us;
}
