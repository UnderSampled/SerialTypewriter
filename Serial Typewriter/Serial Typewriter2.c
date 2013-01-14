/*
 * Serial_Genesis_Controller.c
 *
 * Created: 5/25/2011 3:23:44 AM
 *  Author: Stephen Christie
 */ 
#include "Global_DEFs.h"

#include <avr/io.h>
#include <util/delay.h>

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

uint8_t KeyMap[]={
	'.',		',',		'm',		'\'',	';',	'l',	'k',
	'j',		RETURN,		FRACTION,	'p',	'o',	'i',	'u',
	BACKSPACE,	'=',		'-',		'0',	'9',	'8',	'7',
	'6',		'5',		'4',		'3',	'2',	'1',	TABS,
	'y',		't',		'r',		'e',	'w',	'q',	TAB,
	'h',		'g',		'f',		'd',	's',	'a',	LOCK,
	'n',		'b',		'v',		'c',	'x',	'z',	LEFTSHIFT,
	CORRECT,	WORDERASER,	' ',		MARGIN,	CODE,	'/',	RIGHTSHIFT
};

uint8_t CharMap[]={
	255,	255,	255,	255,	255,	255,	255,	255,
	14,		34,		132,	255,	255,	8,		255,	255,
	255,	255,	255,	255,	255,	255,	255,	255,
	255,	255,	255,	255,	255,	255,	255,	255,
	51,		82,		59,		80,		79,		78,		76,		3,
	74,		73,		75,		71,		1,		16,		0,		54,
	17,		26,		25,		24,		23,		22,		21,		20,
	19,		18,		4,		60,		255,	15,		255,	110,
	81,		96,		99,		101,	94,		87,		93,		92,
	91,		68,		63,		62,		61,		58,		98,		67,
	66,		89,		86,		95,		85,		69,		100,	88,
	102,	84,		103,	125,	255,	124,	145,	72,
	142,	40,		43,		45,		38,		31,		37,		36,
	35,		12,		7,		6,		5,		2,		42,		11,
	10,		33,		30,		39,		29,		13,		44,		32,
	46,		28,		47,		255,	255,	255,	140,	49
};

void pressKey(uint8_t key)
{
	DDRB = 0x00;
	PORTB = 0x00;
	
	int x = key%7;
	int y = key/7;
	
	USART_SendStr("Start: ");
	
	DDRB = (1 << (x+1));// | 0x80;
	int i;
	if (x < y)
	{
		while(1)
		{
			PORTB = (PINC & (1 << y)) >> (y-(x+1));// | (PINC & 0x80);
		}
	} else {
		while(1)
		{
			PORTB = (PINC & (1 << y)) << ((x+1)-y);// | (PINC & 0x80);
		}
	}
	PORTB = 0x00;
	DDRB = 0x00;
	
	USART_SendStr("Done. ");
	return;
}

void pressKey2(uint8_t key)
{
	if (key < 56)
	{
		uint8_t outPin = 1 << ((key%7)+1);
		uint8_t inPin = 1 << (key/7);
	}
	
	DDRB = outPin;
	
	for(int i = 7 ; i ; i--)
	{
		PORTB = 0; //Ground outPin, leave others floating
		while (!(PINC & inPin));
		PORTB = outPin; //Raise outPin, leave others floating
		while (PINC & inPin);
	}
	
	PORTB = 0; //Float all
	DDRB = 0; //Float all
	
	_delay_ms(100);
}

void TypeStr(char Data[])
{
	for (char *ch = &Data[0] ; *ch ; ch++)
	{
		pressKey2(CharMap[*ch]);
	}
}

int main(void)
{
	USART_Init(38400);
	DDRC = 0x00;
	
	TypeStr("hello world.");
	
	return 0;
}

//int main(void)
//{
	//USART_Init(38400);
	//
	//DDRA = 0x00; //7 inputs from keyboard
	//PORTA = 0x7F; //Pulled up
	//
	////DDRC = 0xFF; //8 outputs to keyboard
	////PORTC = 0x00; //Low
	//
	//DDRC = 0xFF; //8 outputs
	//PORTC = 0x00; //Low
//
	//Key = 0;
	//LastKey = 0;
	//
	////uint8_t ScanValue;
	//
	//while(1)
    //{					
		//if (~PINA) {
			//for(x=0 ; x<7 ; x++) {
				//if (~PINA & (1<<x)) {
					//for(y=0 ; y<8 ; y++) {
						//PORTC = (1<<y);
						//if (PINA & (1<<x)) {
							//USART_SendByte(KeyMap[x+y*7]);
						//}
					//}	
				//}							
			//}
		//}
		//
		////for(x=0 ; x<8 ; x++)
		////{
			////DDRC = (1<<x);
			////if (~(PINA) & 0x7F) {
				////for(y=0 ; y<7 ; y++)
				////{
					////////Key = KeyMap[x+y*7];
					//////Key |=(1<<y);
					//////USART_SendChangingByte(KeyMap[y+x*7]);
					//////USART_SendByte(x);
					//////USART_SendByte(y);
					//////if((~PINA) & (1<<y))
						////USART_SendByte(KeyMap[y+x*7]);
				////}
				////USART_SendChangingByte(~(PINA) & 0x7F);
			////}
		////}
		//
		////for(x=0 ; x<8 ; x++)
		////{
			////DDRC = (1<<x);
			//////if (~(PINA) & 0x7F)
				////for(y=0 ; y<7 ; y++)
					////if((~PINA) & (1<<y))
						////USART_SendByte(KeyMap[y+x*7]);
		////}
		//
		////for(x=0 ; x<7 ; x++)
			//////if ((~PINA) & (x<<1))
				////for(y=0 ; y<8 ; y++)
				////{
					////DDRC = (1<<x);
					//////if((~PINA) & (1<<x))
						////USART_SendByte(KeyMap[x+y*7]);
				////}
				//
		////for(y = 0; y < 8; y++)
		////{
			////PORTC = ~(1<<y);
			////ScanValue = PINA;
			////
			////if (~ScanValue)
			////{
				////for(x = 0; x < 7; x++)
				////{
					////if ((1<<x) & ~ScanValue)
						////Key = KeyMap[x+y*7];
				////}
			////}
		////}
		//
		////if(LastKey != Key)
		////{
			////if(Key)
				////USART_SendByte(Key);
			////LastKey = Key;
		////}
		//
		//Key = 0;		
	//}	
	//return 0;
//}

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