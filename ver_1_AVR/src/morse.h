<<<<<<< HEAD
#ifndef MORSE_H_
#define MORSE_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include "HD44780.h"
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define ENC_BUTTON (1<<PC3)
//------------------------------------------------------//

/*		ENCODER			*/
//#define ENC_PIN_A (1<<PD4)		//first encoder pin
//#define ENC_PIN_B (1<<PD5)		//second encoder pin
//#define ENC_PIN_BTN (1<<PB1)	//encoder button pin

/*		SIGNAL LED		*/
//#define LED_BROADCAST (1<<PB0)	//broadcast led pin

//------------------------------------------------------//

	extern int encoderCount;	//encoder turns
	extern uint8_t val;			//encoder actual gray code reading
	extern int asciiNum;		//ascii value of currently displayed character
	extern char userInput[];
	extern volatile uint16_t Timer1, Timer2;
	extern int flag;

	void delay_ms( int ms);
	uint8_t readEncoder(void);
	void initializeSetup (void);
	void readEncoderCounter ();
	void broadcast(int period,int length);
	void LCD_clearLine(int nr);
	int dial();
	void messageDisplay();
	int isButton();
	void LCD_move(char dir);
	void LCD_moveMode();
	void blinkLed(int on, int off);
	int messageDecrypt();

	/*typedef struct {
		volatile uint8_t *pin;
		uint8_t keyMask;
		uint8_t waitTime;
		uint8_t flag;
		int isPressed(void);
	}BUTTON;*/

#endif /* MORSE_H_ */
=======
#ifndef MORSE_H_
#define MORSE_H_

#define F_CPU 1000000UL
#include <avr/io.h>
#include "HD44780.h"
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#define ENC_BUTTON (1<<PC3)
//------------------------------------------------------//

/*		ENCODER			*/
//#define ENC_PIN_A (1<<PD4)		//first encoder pin
//#define ENC_PIN_B (1<<PD5)		//second encoder pin
//#define ENC_PIN_BTN (1<<PB1)	//encoder button pin

/*		SIGNAL LED		*/
//#define LED_BROADCAST (1<<PB0)	//broadcast led pin

//------------------------------------------------------//

	extern int encoderCount;	//encoder turns
	extern uint8_t val;			//encoder actual gray code reading
	extern int asciiNum;		//ascii value of currently displayed character
	extern char userInput[];
	extern volatile uint16_t Timer1, Timer2;
	extern int flag;

	void delay_ms( int ms);
	uint8_t readEncoder(void);
	void initializeSetup (void);
	void readEncoderCounter ();
	void broadcast(int period,int length);
	void LCD_clearLine(int nr);
	int dial();
	void messageDisplay();
	int isButton();
	void LCD_move(char dir);
	void LCD_moveMode();
	void blinkLed(int on, int off);
	int messageDecrypt();

	/*typedef struct {
		volatile uint8_t *pin;
		uint8_t keyMask;
		uint8_t waitTime;
		uint8_t flag;
		int isPressed(void);
	}BUTTON;*/

#endif /* MORSE_H_ */
>>>>>>> eb475db957139794f7261a2861e291a52ab8c330
