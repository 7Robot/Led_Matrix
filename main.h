#ifndef __MAIN_H
#define	__MAIN_H


#include <stdio.h>
#include <stdlib.h>
#include "pico/stdio_usb.h"
#include "pico/stdio/driver.h"

#include "pico/stdlib.h"

#include <stdint.h>
#include <string.h>
#include <math.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

#define Abs_Ternaire(a)   ((a<0)?-a:a)
#define Min_Ternaire(a,b) ((a<b)?a:b)
#define Max_Ternaire(a,b) ((a>b)?a:b)
#define sizetab(a) sizeof(a)/sizeof(a[0])


#include "hardware/adc.h"
#include "hardware/flash.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/watchdog.h"
#include "hardware/pio.h"
#include "hardware/dma.h"

#include "pico/binary_info.h"
#include "pico/bootrom.h"
#include "pico/cyw43_arch.h"

#include "hardware/structs/ssi.h"
#include "hardware/structs/ioqspi.h"
#include "hardware/sync.h"

#include "ADC.h"
#include "Hex_Decodeur.h"
#include "Interpreteur.h"
#include "Leds_RGB.h"
#include "Leds_RGB_Anim.h"
#include "Test_Funcs.h"
#include "user.h"


#include "BT/BT.h"
#include "BT/BT_Stdio.h"
#include "btstack_run_loop.h"
#include "btstack_event.h"
#include "btstack.h"


#include "Flash/Flash.h"
#include "Flash/Flash_Mem_Orga.h"
#include "Flash/Log_File.h"
#include "Flash/Setup_File.h"


#include "BT.h"



extern uint32_t Timer_ms1;

#define Timer_us1  timer_hw->timelr


#define RGB1_PIN 3
#define RGB2_PIN 7
#define RGB3_PIN 11
#define RGB4_PIN 15



#endif	/* MAIN_H */
