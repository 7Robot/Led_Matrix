
#include "main.h"

uint16_t ADC2_Val = 0;
uint16_t Temp_Val = 0;

float Vin;
float Temp;

uint8_t ADC_Loop_State = 0;
uint32_t ADC_Loop_Timer = 0;


void ADC_Init(void)
{
	adc_init();
    //adc_gpio_init(28);  // ADC2 = Vin_Sense = Vin / 11;
    adc_set_temp_sensor_enabled(true);
}


void ADC_Loop(void)
{
    if ((Timer_ms1 - ADC_Loop_Timer) > 5) {
        ADC_Loop_Timer = Timer_ms1;
        switch (ADC_Loop_State) {
            case 0:
                //adc_select_input(2);
                ADC_Loop_State ++;
                break;
            case 1:
                //ADC2_Val = adc_read();
                Vin = ADC2_Val * 3.3 * 11.0 / 4096;
                ADC_Loop_State ++;
                break;
            case 2:
                adc_select_input(4);
                ADC_Loop_State ++;
                break;
            case 3:
                Temp_Val = adc_read();
                Temp =  (0.997*Temp) + 0.003* (27 - ((Temp_Val * 3.3/4096) - 0.706) / 0.001721);
                //ADC3_Val * 3.3 * 6.1 / 4096;
                ADC_Loop_State = 0;
                break;
        }
    }
}

uint8_t ADC_Rd_Func(void)
{
	printf("2 : 0x%04X   : %.3f\n", ADC2_Val, Vin);
	printf("T : 0x%04X   : %.3f\n", Temp_Val, Temp);
	
	return 0;
}

float Get_Temp(void)
{
    return Temp;
}