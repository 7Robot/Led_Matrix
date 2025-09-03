

#include "main.h"

uint32_t Timer_ms1 = 0;

uint32_t Last_Led_Timer = 0;

uint8_t Led_Val = 0;
 
int main() {

	bi_decl(bi_program_description("Pepino's PKit Software"));

	Init_All();
	sleep_ms(1000);
	

	Print_Version_Func();


	while (1) {

		Timer_ms1 = time_ms_32();

		int c = getchar_timeout_us(0);
		if (c != -1) {
			Interp(c);
		}
		uint8_t c_Setup;
		if (Setup_File_Get(&c_Setup)) {
			Interp(c_Setup);
		}

		Print_All_Cmd_Loop();
		All_Flash_Read_Loop();

		ADC_Loop();
		Flash_LogFile_Loop();
		Log_Print_Save_Loop();
		Setup_File_Loop();

		Test_Loop();
		BT_Loop();
		RGB_Loop();
		//RGB_Anim_Loop();

		if ((Timer_ms1 - Last_Led_Timer) > 500) {
			Last_Led_Timer += 500;
			//gpio_put(LED_PIN, !gpio_get_out_level(LED_PIN));
			Led_Val = !Led_Val;
			cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, Led_Val);
			//uart0_hw->dr = 'l';
		}
	}
}

