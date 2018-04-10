#include "morse.h"

int main(void)
{
	int menu = 0;		//
	int btn = 0;		// enc button state toggle (entering option)
	int menuEnc = 0;	// selecting option in menu

	initializeSetup();

	while(1)
	{
	readEncoderCounter();

	if(btn == 0)		//enc button not pressed
	{
		if(encoderCount < 0) encoderCount = 0;	//reaching the end
		if(encoderCount > 3) encoderCount = 3;	// of the menu
		menuEnc = encoderCount;
	}

	if(menu == 0)		//"home page"
	{
		LCD_Home();
		LCD_WriteText("Opcje:  ");
		LCD_GoTo(0,1);
		LCD_WriteText("Nadaj   ");
		menu=1;
	}
	else if(menu ==1)	//scrolling through menu options
	{
		switch (menuEnc)
		{
		case 0:				//BROADCAST OPTION
			if(btn == 0)	
			{				
			LCD_GoTo(0,1);
			LCD_WriteText("nadaj   ");

				if(isButton())	//enc button push at this option
				{
					btn = 1;	//enc button toggle on - dial
					LCD_Clear();
					encoderCount=0;
					delay_ms(800);
					LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
				}
			}
				if(btn == 1)	// enc button was pushed - option 
				{				// was selected
					if(dial())	// doing dial function
					{
					btn = 0;
					menu = 0;
					}
				}
		break;

		case 1:			//DISPLAY OPTION
		if(btn == 0)
		{
		LCD_GoTo(0,1);
		LCD_WriteText("wyswietl");

			if(isButton())
			{
			btn = 2;			//enc button toggle on - display
			delay_ms(1000);
			messageDisplay();
			LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
			}
		}
		if(btn == 2)
		{
		LCD_moveMode();

			if(isButton())		// enc button push to exit display
			{
			delay_ms(500);
			btn = 0;
			menu = 0;
			}
		}
		break;

			case 2:			//DECODE OPTION
			if(btn == 0)
			{
			LCD_GoTo(0,1);
			LCD_WriteText("rozszyf.");

				if(isButton())
				{
				btn = 3;			//enc button toggle on - decode
				LCD_Clear();
				delay_ms(600);
				encoderCount = 0;
				}
			}
			if(btn == 3)
			{
				//messageDecrypt();
				/*if()
				{
					while(!(isButton()))
					{
						LCD_moveMode();
					}
				delay_ms(500);
				btn = 0;
				menu = 0;*/
				//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
				//}
			}

		break;
			case 3:			//SET SPEED OPTION
			if(btn == 0)
			{
			LCD_GoTo(0,1);
			LCD_WriteText("predkosc");

				if(isButton())
				{
				btn = 4;			//enc button toggle on - decode
				LCD_Clear();
				delay_ms(600);
				encoderCount = 0;
				}
			}
			if(btn == 4)
			{
				if(setWpmSpeed())	// doing speed set function
				{
				btn = 0;
				menu = 0;
				}
			}

		break;

			default:
		LCD_GoTo(0,1);
		LCD_WriteText("sw_err");
		menuEnc = 0;
		break;
		}
	}
	}
}


