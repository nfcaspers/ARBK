/*
 * task4.c
 *
 * ADC: Convert a voltage and display it on the seven segment and on the LED bar
 *
 * Created: 19.07.2024 15:03:03
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "tasks.h"
#include "adc.h"
#include "sevenSeg.h"
#include "ledBar.h"

/*!
 * Display poti value on led-bar and 7-segments
 */
void task4()
{
	ledBar_init();
	adc_init();
	sevenSeg_init();
	
	while (1)
	{
		uint16_t adc_value = adc_getValue();
		float val = (adc_value / 1023.0) * 5.0;
		int num_leds = (adc_value * 10 + 511) / 1023; //511 = 1023/2 -> Ganzzahlendivision rundet ab, verschiebung um hälfte ermöglicht aufrunden (wenn Zahl größer als die Hälfte war)
		//uint8_t num_leds = (uint8_t)round((adc_value / 1023) * 10);
		uint16_t leds_bin = 0;
		for (uint8_t i = 0; i < num_leds; i++) {
			leds_bin |= (1 << i); // Setze das i-te Bit auf 1
		}
		ledBar_set(leds_bin);
		sevenSeg_displayFloat(val);
		_delay_ms(100);
	}
}