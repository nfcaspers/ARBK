/*
 * adc.c
 *
 * Created: 19.07.2024 14:46:29
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "adc.h"
#include "util.h"
#include <avr/io.h>

/*!
 * This method initializes the necessary registers for using the ADC module.
 * Reference voltage:    internal
 * Input channel:        PORTA7
 * Conversion frequency: 125kHz
 */
void adc_init()
{
	ADCSRA |= 1 << ADEN; //enable bit
	ADMUX |= (0 << REFS1) | (1 << REFS0); //01 für ADMUX REFS1/0 ist AVcc with external capacitor at AREF pin
	ADMUX |= (0 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0); //0111 wählt ADC7 als Kanal aus
	ADCSRA |= (1 << ADATE); //Freerunning mode
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (0 << ADPS0); //110 ADPS -> prescaler x128
	ADCSRA |= (1 << ADSC); //Konvertierung starten
}

/*!
 * Returns the ADC value of the last conversion
 * \return The converted voltage (0 = 0V, 1023 = AVCC)
 */
uint16_t adc_getValue()
{
	while (!(ADCSRA & (1 << ADIF))) {
		//Wenn 1 in ADIF von ADCSRA steht, wurde umwandlung durchgeführt
	}
	
	uint8_t adc_low = ADCL;  // ADCL muss zuerst gelesen werden; ADC data register wird erst geupdatet wenn ADCH gelesen wird -> wir brauchen alle 10 bits
	uint8_t adc_high = ADCH; // 

	uint16_t adc_value = (adc_high << 8) | adc_low; // 10-Bit-Wert
	return adc_value;
}