#include "morse.h"

extern int encoderCount = 0;
extern uint8_t val=0;
extern int asciiNum = 0;
extern char userInput[30] = {};	//array with message
int morseInput[30] ={};
int morseDecode[30] = {};
char encodedMessage[30] = {};
extern volatile uint16_t Timer1=0, Timer2=0;
int lcdPos = 0;		//lcd cursor position
//extern int flag = 0;

const uint8_t waitTime = 2;
int btnFlag = 0;
int encoderTmp = 0;

const int morseTable[37][7] = {
  {0, 1, 2},//a
  {1, 0, 0, 0, 2},//b
  {1, 0, 1, 0, 2},//c
  {1, 0, 0, 2},//d
  {0, 2},//e
  {0, 0, 1, 0, 2},//f
  {1, 0, 0, 2},//g
  {0, 0, 0, 0, 2},//h
  {0, 0, 2},//i
  {0, 1, 1, 1, 2},//j
  {1, 0, 1, 2},//k
  {0, 1, 0, 0, 2},//l
  {1, 1, 2},//m
  {1, 0, 2},//n
  {1, 1, 1, 2},//o
  {0, 1, 1, 0, 2},//p
  {1, 1, 0, 1, 2},//q
  {0, 1, 0, 2},//r
  {0, 0, 0, 2},//s
  {1, 2},//t
  {0, 0, 1, 2},//u
  {0, 1, 1, 2},//w
  {0, 0, 0, 1, 2},//v
  {1, 0, 0, 1, 2},//x
  {1, 0, 1, 2},//y
  {1, 1, 0, 0, 2},//z
  {0, 1, 1, 1, 1, 2},//1
  {0, 0, 1, 1, 1, 2},//2
  {0, 0, 0, 1, 1, 2},//3
  {0, 0, 0, 0, 1, 2},//4
  {0, 0, 0, 0, 0, 2},//5
  {1, 0, 0, 0, 0, 2},//6
  {1, 1, 0, 0, 0, 2},//7
  {1, 1, 1, 0, 0, 2},//8
  {1, 1, 1, 1, 0, 2},//9
  {1, 1, 1, 1, 1, 2}//0
  //0 - dot, 1 - dash, 2 - end
};

void initializeSetup (void)		//initializing registers//
{
	 MCUCSR = (1<<JTD);		//disabling JTAG
	 MCUCSR = (1<<JTD);

	TCCR2 |= (1<<WGM21);		//work mode CTC
	TCCR2 |= (1<<CS22)|(1<<CS21)|(1<<CS20);	//prescaler = 1024
	OCR2  = 4;				//comparison interrupt every 10ms (100Hz)
	TIMSK = (1<<OCIE2);			//interrupt unlock CompareMatch

	/*DDRD &=~ (1 << PD4);
	DDRD &=~ (1 << PD5);	// encoder pins as input
	PORTD |= (1 << PD5)		// with pull-up enabled
			|(1 << PD4);*/

		DDRA &=~ (1 << PA1);
		DDRA &=~ (1 << PA2);	// encoder pins as input
		PORTA |= (1 << PA2)		// with pull-up enabled
				|(1 << PA1);

	//DDRA |= (1<<PA0);			//signal LED as output
		DDRC |= (1<<PC4);
	//DDRB |= (0<<PB1); 			//encoder button pin as input
		DDRA |= (0<<PA3);
	//DDRB |= (0<<PB2);	//sw 1 in
	//DDRB |= (0<<PB3);	//sw 2 in
		DDRC |= (0<<PC1);	//sw 1 in
		DDRC |= (0<<PC2);	//sw 2 in

	LCD_Initalize();
	val = readEncoder();
	sei();
}

int dial()
{
	asciiNum = encoderCount+97;
	if(asciiNum < 97) 	encoderCount = 0;
	if(asciiNum > 122)	encoderCount = 25;

	LCD_GoTo(lcdPos,0);
	LCD_WriteData(asciiNum);	//wybor litery
	LCD_GoTo(lcdPos,1);
	LCD_WriteData(94);			//strzalka

	/*if(encoderCount != encoderTmp)
	{
		//LCD_WriteData(asciiNum);
		LCD_GoTo(lcdPos,0);
		//LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT);
		//LCD_WriteCommand(HD44780_SHIFT_CURSOR);
		//LCD_WriteCommand(HD44780_SHIFT_LEFT);
		encoderTmp=encoderCount;
	}*/
	if(!(PINC & 0x02) && !(PINC & 0x04))
	{
		LCD_Clear();
		return 1;
	}

	if (!(PINA & 0x08) && btnFlag == 0)		//encoder button push
	{
		Timer1 = (waitTime*1000)/10;
		btnFlag = 1;
	}
	else if((PINA & 0x08) && btnFlag == 1)	//encoder button release
	{
		userInput[lcdPos] = asciiNum;
		//LCD_WriteData(asciiNum);
		lcdPos++;
		delay_ms(100);
		encoderCount = 0;
		LCD_clearLine(1);
		//encoderTmp = 0;

		btnFlag = 0;
		Timer1 = 0;
	}
	else if(!(PINA & 0x08) && btnFlag == 1 && !Timer1)	//encoder button long press
	{
		userInput[lcdPos] = 'E';
		for(int i=0;i<lcdPos;i++)	//message display on scnd line
		{
			LCD_GoTo(i,1);
			LCD_WriteData(userInput[i]);
		}
		//messageDisplay();

		LCD_WriteData(lcdPos+48);	//message length display

		LCD_clearLine(0);
		btnFlag = 0;
		delay_ms(1000);
		broadcast(500,lcdPos);
		lcdPos=0;
		delay_ms(700);
		return 1;
	}
return 0;
}

void broadcast(int period,int length)
{
	int symbolSpace = period/3;
	int letterSpace = period;
	//int wordSpace 	= 2*period;

	//LCD_Clear();
	int pos=0;
	//int L = (sizeof userInput)/(sizeof userInput[0]);
	for(int i=0;i<length;i++)
	{
		int j=0;
		while(morseTable[userInput[i]-97][j] != 2)
		{
			LCD_GoTo(pos,0);
			if(morseTable[userInput[i]-97][j] == 0)	//dot
			{

				LCD_WriteData('1');
				morseInput[pos] = 1;
				blinkLed(period,symbolSpace);
			}
			else if(morseTable[userInput[i]-97][j] == 1)	//dash
			{
				LCD_WriteData('0');
				morseInput[pos] = 0;
				blinkLed(period*3,symbolSpace);
			}
			j++;
			pos++;
		}
		delay_ms(letterSpace);
	}
	morseInput[pos] = 2;
	//LCD_Clear();

}

int messageDecrypt()
{
	LCD_GoTo(lcdPos,1);
	LCD_WriteData(94);			//strzalka

	if(!(PINC & 0x02))			//dash
	{
	LCD_clearLine(1);
	delay_ms(400);
	LCD_GoTo(lcdPos,0);
	LCD_WriteData(45);	// "-"
	morseDecode[lcdPos] = 0;
	lcdPos++;
	}
	if(!(PINC & 0x04))			//dot
	{
	LCD_clearLine(1);
	delay_ms(400);
	LCD_GoTo(lcdPos,0);
	LCD_WriteData(46);	// "."
	morseDecode[lcdPos] = 1;
	lcdPos++;
	}

	if(!(PINC & 0x04) && !(PINC & 0x02)) 	//powrot do menu
	{
	delay_ms(500);
	morseDecode[lcdPos] = 2;
	lcdPos = 0;
	LCD_Clear();
	return 1;
	}

	if (!(PINA & 0x08))			//encoder push - decode message
	{
	delay_ms(500);
	lcdPos = 0;
	/*
		int k=0;
		int l=0;
		int m=0;
		//while(morseDecode[k] != 2)
		//{
			if(morseTable[l][k] != morseDecode[k])
				l++;
			else
			{
				k++;
				if(morseTable[l][k] == 2)
				{
					encodedMessage[m] = 97+l;
					m++;
					k=0;
				}


			//}



			for(int i=0;i<37;i++)
			{
				int j=0;
				while(morseTable[i][j] != 2)
				{
					if(morseTable[i][j] != morseDecode[j])
					break;
					else
					{

					}
					j++;
				}
				/*for(int j=0;j<7;j++)
				{
					if(morseTable[i][j] == morseDecode[])
				}*/

			//}

		//}
	}
return 0;}

void messageDisplay()
{
	LCD_clearLine(0);
	LCD_clearLine(1);
	/*for(int i=0;i<15;i++)	//message display on scnd line
	{
		LCD_GoTo(i,1);
		LCD_WriteData(userInput[i]);
	}*/
	if(userInput[0] < 97 || userInput[0] > 122)
	{
		LCD_Home();
		LCD_WriteText("brak");
		LCD_GoTo(0,1);
		LCD_WriteText("danych");
		return;
	}

	int j = 0;
	while(morseInput[j] != 2)
	{
		LCD_GoTo(j,0);
		LCD_WriteData(morseInput[j]+48);
		j++;
	}
	int k = 0;
	while(userInput[k] != 'E')
	{
		LCD_GoTo(k,1);
		LCD_WriteData(userInput[k]);
		k++;
	}
	/*for(int i=0;i<15;i++)	//message display on scnd line
	{
		LCD_GoTo(i,0);
		LCD_WriteData(morseInput[i]+48);
	}*/
}

void LCD_move(char dir)
{
	//LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT);
	//LCD_WriteCommand(HD44780_SHIFT_CURSOR);
	if(dir =='L')
	{
		LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT|HD44780_SHIFT_DISPLAY|HD44780_SHIFT_RIGHT);
		LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
		delay_ms(20);
	}
	else if(dir =='R')
	{
		LCD_WriteCommand(HD44780_DISPLAY_CURSOR_SHIFT|HD44780_SHIFT_DISPLAY|HD44780_SHIFT_LEFT);
		LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK);
		delay_ms(20);
	}
}

void LCD_moveMode()
{
	if (!(PINC & 0x02))		//1 button push
		{
			delay_ms(100);
			//LCD_WriteText("pierwszy");
			LCD_move('L');
		}

		if (!(PINC & 0x04))		//2 button push
		{
			delay_ms(100);
			//LCD_WriteText("drugi");
			LCD_move('R');
		}
}

void blinkLed(int on, int off)
{
	PORTC |= (1<<PC4);
	delay_ms(on);
	PORTC &= ~(1<<PC4);
	delay_ms(off);
}

void delay_ms( int ms)
{
	volatile long unsigned int i;
	for(i=0;i<ms;i++)
		_delay_ms(1);
}

void LCD_clearLine(int nr)
{
		LCD_GoTo(0,nr);
		LCD_WriteText("        ");
}

int isButton()
{
	if(!(PINA & 0x08))
		return 1;
	else
		return 0;
}

uint8_t readEncoder(void)
{
 uint8_t val=0;

  if(!bit_is_clear(PINA, PA2))
	val |= (1<<1);

  if(!bit_is_clear(PINA, PA1))
	val |= (1<<0);

  return val;
}

void readEncoderCounter ()	//monitoring increase
{												//or decrease //
	uint8_t val_tmp = 0;						//returning 1 if +
	val_tmp = readEncoder();			//			0 if -

	if(val != val_tmp)
	{
		if((val==3 && val_tmp==1) //||
		//(val==0 && val_tmp==2)
		)
			{
			encoderCount ++;	//clockwise turn
			}
		else if((val==2 && val_tmp==0) //||
		//(val==1 && val_tmp==3)
		)
			{
			encoderCount --;	//counter-clockwise turn
			}
		val = val_tmp;
		}

	delay_ms(1);
}

ISR(TIMER2_COMP_vect)
{
	uint16_t n;

	n = Timer1;		//100Hz Timer1
	if (n) Timer1 = --n;
	n = Timer2;		//100Hz Timer2
	if (n) Timer2 = --n;
}
