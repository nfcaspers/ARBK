/*
 * task2.c
 *
 * LED bar animation: Run a light from left to right and vice versa with increasing speed
 *
 * Created: 18.07.2024 15:53:14
 * Author : Fachbereich 5 - FH Aachen
 */
#include "tasks.h"
#include "ledBar.h"
#include "button.h"
#include "util.h"

//! Forward declarations
void task2_init();
void task2_barAnimation();

/*!
 * Main task that starts and ends a game
 */
void task2()
{
	// Init ports
	task2_init();
	
	while (1) { task2_barAnimation(); }
}

/*!
 * Initializes PORTs
 */
void task2_init()
{
	ledBar_init();
	button_init();
}

/*!
 * Animation of the LED bar
 */
void task2_barAnimation()
{
	// Current state of the LED bar
	uint16_t led_status = 0x01;
	
	// LED shift direction
	direction_t direction = DIR_LEFT;
	
	// Shift delay of game level 0 in ms
	uint16_t delay_ms = DELAY_INITIAL_MS;
	
	// Start: wait for button press and release
	while(gbi(PINC, 5) == 1) {
		//Taster noch nicht gedrückt
	}
	while(gbi(PINC, 5) == 0) {
		//Taster gedrückt
	}
	
	while (true)
	{
		//uint16_t ledBar = gbi(PINC, PINC5) ? 0x00 : 0x3FF;
		//ledBar_set(ledBar);
		if(direction == DIR_LEFT) {
			led_status = led_status << 1;
		} else if(direction == DIR_RIGHT) {
			led_status = led_status >> 1;
		}
		ledBar_set(led_status);
		for(int x=0; x < delay_ms; x++) {
			_delay_ms(1);
		}
		if(gbi(led_status, 9) == 1) {
			direction = DIR_RIGHT;
			delay_ms *= DELAY_DECREMENT_FACTOR;
		} else if(gbi(led_status, 0)) {
			direction = DIR_LEFT;
			delay_ms *= DELAY_DECREMENT_FACTOR;
		}
		if(delay_ms < 2) {
			ledBar_set(0x3FF);
			break;
		}
	}
}