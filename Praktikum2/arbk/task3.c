/*
 * task3.c
 *
 * LED bar game: Run a light from left to right and vice versa with increasing speed,
 * the player has to press the button in time to change direction. Pressing is allowed
 * while the two outermost LEDs are on
 *
 * Created: 19.07.2024 14:09:26
 * Author : Fachbereich 5 - FH Aachen
 */ 
#include "tasks.h"
#include "ledBar.h"
#include "button.h"
#include "sevenSeg.h"

//! Game level
uint8_t level;

//! Forward declarations
void task3_init();
gameover_t task3_game();

/*!
 * Main task that starts and ends a game
 */
void task3()
{
	// Init ports
	task3_init();
	
	while (1)
	{
		// Play game
		gameover_t result = task3_game();
		
		// Game over animation
		gameOverAnimation(result);
		
		// Show reached level (display level / 2)
		showScore(level);
	}
}

/*!
 * Initializes PORTs
 */
void task3_init()
{
	ledBar_init();
	button_init();
	sevenSeg_init();
}

/*!
 * Game logic
 */
gameover_t task3_game()
{
	// Current state of the LED bar
	uint16_t led_status = 0x01;
	
	// LED shift direction
	direction_t direction = DIR_LEFT;
	
	// Shift delay of game level 0 in ms
	uint16_t delay_ms = DELAY_INITIAL_MS;
	
	// Reset game level
	level = 0;
	
	// Start: wait for button press and release
	while(gbi(PINC, 5) == 1) {
		//Taster noch nicht gedrückt
	}
	while(gbi(PINC, 5) == 0) {
		//Taster gedrückt
		ledBar_set(led_status);
	}
	
	while (1)
	{
		
		if(direction == DIR_LEFT) {
			led_status = led_status << 1;
		} else if(direction == DIR_RIGHT) {
			led_status = led_status >> 1;
		}
		
		ledBar_set(led_status);
		
		bool button_press = button_waitForPressRelease(delay_ms);
		
		if(button_press && (led_status & LED_BAR_INNER)) {
			return GAME_OVER_TOO_EARLY;
		} else if(button_press && (led_status & LED_BAR_OUTER)) {
			if(direction == DIR_LEFT) {
				level++;
				delay_ms *= DELAY_DECREMENT_FACTOR;
				direction = DIR_RIGHT;
			} else {
				level++;
				delay_ms *= DELAY_DECREMENT_FACTOR;
				direction = DIR_LEFT;
			}
		}

        //0b1111111111 => 0b0000000000 i.e. alle validen bits in led_status werden 0, wenn die led sich im invaliden Bereich befindet
		//ist der Wert =/= 0, wenn led im validen Bereich ist der Wert immer 0
		//rechts out of bounds wird erkannt, wenn led_status 0 (logischerweise) 
        if((led_status & ~(LED_BAR_OUTER | LED_BAR_INNER)) || led_status == 0) {
			return GAME_OVER_OUT_OF_BOUNDS;
        }
		
		sevenSeg_displayDecimal(level);
	}	
}