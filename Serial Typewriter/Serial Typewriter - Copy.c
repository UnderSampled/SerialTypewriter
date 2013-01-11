/*
 * Serial_Genesis_Controller.c
 *
 * Created: 5/25/2011 3:23:44 AM
 *  Author: Stephen Christie
 */ 
#include "Global_DEFs.h"

#include <avr/io.h>

#include "USART_LIB.h"

#define CORRECT 'C'
#define WORDERASER 'W'
#define MARGIN 'M'
#define CODE '^'
#define RIGHTSHIFT 'R'
#define RETURN 'E'
#define FRACTION 'F'
#define BACKSPACE 'B'
#define TABS 'S'
#define TAB 'T'
#define LOCK 'K'
#define LEFTSHIFT 'L'

uint8_t ScanValue;
uint8_t Key;
uint8_t LastKey;

uint8_t y;
uint8_t x;

uint8_t KeyMap[]={
	CORRECT,	WORDERASER,	' ',		MARGIN,	CODE,	'/',	RIGHTSHIFT,
	'.',		',',		'm',		'\'',	';',	'l',	'k',
	'j',		RETURN,		FRACTION,	'p',	'o',	'i',	'u',
	BACKSPACE,	'=',		'-',		'0',	'9',	'8',	'7',
	'6',		'5',		'4',		'3',	'2',	'1',	TABS,
	'y',		't',		'r',		'e',	'w',	'q',	TAB,
	'h',		'g',		'f',		'd',	's',	'a',	LOCK,
	'n',		'b',		'v',		'c',	'x',	'z',	LEFTSHIFT
};

int main(void)
{
	PORTA = 0xFF; //Set all Port A pulled up
	
	DDRC = 0xFF; //Set all Port C to output
	PORTC = 0xFF; //Set all Port C to high
	
	USART_Init(38400);

	LastKey = 0;
	while(1)
    {
		for(y = 0; y < 8; y++)
		{
			PORTC = ~(1<<y);
			ScanValue = PINA;
			
			if (~ScanValue)
			{
				for(x = 0; x < 7; x++)
				{
					if ((1<<x) & ~ScanValue)
						Key = KeyMap[x+y*7];
				}
			}
		}
		
		if (LastKey != Key)
		USART_SendByte(Key);
		
		LastKey = Key;
		Key = 0;
	}	
	return 0;
}

//uint8_t getSpreadPinD()
//{
	//return ((PINA & 0x80)>>7)|((PINB & 0x80)>>6)|((PIND & 0xFC)); // Last bit of PINA and PINB shifted and ORed with the last 6 bits of PIND
//}
//
//int main(void)
//{
	//DDRA &= 0x7F; 
	//DDRB &= 0x7F; //Set Distant input pins
	//
	////PORTA |= 0x80;
	////PORTB = 0xFF;
	////PORTD = 0xFF; //Set pull ups
	//
	//USART_Init(38400);
	//
	//while(1)
	//{
		//x = PINB;
		//y = getSpreadPinD();
		//
		//USART_SendByte(x);
		//USART_SendByte(y);
	//}
	//return 0;	
//}

/*
int main(void)
{
	PORTA = 0x7F; //Set Port A pull ups
	
	USART_Init(38400);
	
	while(1)
	{
		x = PINA;
		y = PINC;
		
		USART_SendByte(x);
		USART_SendByte(y);
	}
	return 0;
}
*/