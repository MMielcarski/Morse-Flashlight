<<<<<<< HEAD
#include "morse.h"
// git test 2
int main(void)
{
	int menu = 0;
	int btn = 0;
	int menuEnc = 0;

	initializeSetup();

	while(1)
	{
	readEncoderCounter();

	if(btn == 0)
	{
		/*if(menuEnc < 0) menuEnc = 0;
		else if(menuEnc > 2) menuEnc = 2;
		else
			menuEnc = encoderCount;*/
		if(encoderCount < 0) encoderCount = 0;
		if(encoderCount > 2) encoderCount = 2;
		menuEnc = encoderCount;
	}

	if(menu == 0)
	{
		LCD_Home();
		LCD_WriteText("Opcje:  ");
		LCD_GoTo(0,1);
		LCD_WriteText("Nadaj   ");
		menu=1;
	}
	else if(menu ==1)
	{
		switch (menuEnc)
		{
		case 0:
		if(btn == 0)
		{
		LCD_GoTo(0,1);
		LCD_WriteText("nadaj   ");

			if(isButton())
			{
				btn = 1;
				LCD_Clear();
				encoderCount=0;
				delay_ms(800);
				LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
			}
		}
			if(btn == 1)
			{
				if(dial())
				{
				btn = 0;
				menu = 0;
				}
			}
		break;

		case 1:
		if(btn == 0)
		{
		LCD_GoTo(0,1);
		LCD_WriteText("wyswietl");

			if(isButton())
			{
			btn = 2;
			delay_ms(1000);
			messageDisplay();
			LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
			}
		}
		if(btn == 2)
		{
		LCD_moveMode();

			if(isButton())
			{
			delay_ms(500);
			btn = 0;
			menu = 0;
			//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
			}
		}
		break;

			case 2:
			if(btn == 0)
			{
			LCD_GoTo(0,1);
			LCD_WriteText("rozszyf.");

				if(isButton())
				{
				btn = 3;
				LCD_Clear();
				delay_ms(1000);
				//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
				}
			}
			if(btn == 3)
			{
				if(messageDecrypt())
				{
				delay_ms(500);
				btn = 0;
				menu = 0;
				//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
				}
			}

		break;

			default:
		//LCD_GoTo(0,1);
		//LCD_WriteText("nadaj   ");
		//menuEnc = 0;
		break;
		}
	}


	//if(countDisplay == 123) encoderCount = 0;
	//if(countDisplay == 96) encoderCount = 0;
	}
}
/*if(isButton() && menu <3)
{
	delay_ms(500);
	if(btn==0)
	btn = 1;
	else btn = 0;
}*/

=======
#include "morse.h"

int main(void)
{
	int menu = 0;
	int btn = 0;
	int menuEnc = 0;

	initializeSetup();

	while(1)
	{
	readEncoderCounter();

	if(btn == 0)
	{
		/*if(menuEnc < 0) menuEnc = 0;
		else if(menuEnc > 2) menuEnc = 2;
		else
			menuEnc = encoderCount;*/
		if(encoderCount < 0) encoderCount = 0;
		if(encoderCount > 2) encoderCount = 2;
		menuEnc = encoderCount;
	}

	if(menu == 0)
	{
		LCD_Home();
		LCD_WriteText("Opcje:  ");
		LCD_GoTo(0,1);
		LCD_WriteText("Nadaj   ");
		menu=1;
	}
	else if(menu ==1)
	{
		switch (menuEnc)
		{
		case 0:
		if(btn == 0)
		{
		LCD_GoTo(0,1);
		LCD_WriteText("nadaj   ");

			if(isButton())
			{
				btn = 1;
				LCD_Clear();
				encoderCount=0;
				delay_ms(800);
				LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
			}
		}
			if(btn == 1)
			{
				if(dial())
				{
				btn = 0;
				menu = 0;
				}
			}
		break;

		case 1:
		if(btn == 0)
		{
		LCD_GoTo(0,1);
		LCD_WriteText("wyswietl");

			if(isButton())
			{
			btn = 2;
			delay_ms(1000);
			messageDisplay();
			LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
			}
		}
		if(btn == 2)
		{
		LCD_moveMode();

			if(isButton())
			{
			delay_ms(500);
			btn = 0;
			menu = 0;
			//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
			}
		}
		break;

			case 2:
			if(btn == 0)
			{
			LCD_GoTo(0,1);
			LCD_WriteText("rozszyf.");

				if(isButton())
				{
				btn = 3;
				LCD_Clear();
				delay_ms(1000);
				//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
				}
			}
			if(btn == 3)
			{
				if(messageDecrypt())
				{
				delay_ms(500);
				btn = 0;
				menu = 0;
				//LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
				}
			}

		break;

			default:
		//LCD_GoTo(0,1);
		//LCD_WriteText("nadaj   ");
		//menuEnc = 0;
		break;
		}
	}


	//if(countDisplay == 123) encoderCount = 0;
	//if(countDisplay == 96) encoderCount = 0;
	}
}
/*if(isButton() && menu <3)
{
	delay_ms(500);
	if(btn==0)
	btn = 1;
	else btn = 0;
}*/

>>>>>>> eb475db957139794f7261a2861e291a52ab8c330
