#ifndef __LEDS_RGB_H_
#define __LEDS_RGB_H_


#define RGB_STRIP_LENGTH 300
#define RGB_MATRIX_H    8
#define RGB_MATRIX_L    32


#define RIGHT_RGB_STRIP_PIN  RGB2_PIN
#define LEFT_RGB_STRIP_PIN   RGB4_PIN
#define MATRIX_RGB_STRIP_PIN RGB1_PIN



void RGB_Init(void);
void RGB_Loop(void);



#endif // __LEDS_RGB_H_
