/*
 * Serial Typewriter.c
 *
 * Created: 5/25/2011 3:23:44 AM
 *  Author: Stephen Christie
 */ 
#include "Global_DEFs.h"

#include <avr/io.h>
#include <util/delay.h>

#include "USART_LIB.h"

#define META 0x80
#define SHIFT 0x80
#define CODE 0x20

/*uint8_t KeyMap[]={
	'.',		',',		'm',		'\'',	';',	'l',	'k',
	'j',		RETURN,		FRACTION,	'p',	'o',	'i',	'u',
	BACKSPACE,	'=',		'-',		'0',	'9',	'8',	'7',
	'6',		'5',		'4',		'3',	'2',	'1',	TABS,
	'y',		't',		'r',		'e',	'w',	'q',	TAB,
	'h',		'g',		'f',		'd',	's',	'a',	LOCK,
	'n',		'b',		'v',		'c',	'x',	'z',	LEFTSHIFT,
	CORRECT,	WORDERASER,	' ',		MARGIN,	CODE,	'/',	RIGHTSHIFT
};*/

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

/*void pressKey(uint8_t key)
{
	uint8_t outPin;
	uint8_t inPin;
	uint8_t metaOutPin;
	
	uint8_t lastPINC;
	
	outPin = 1 << ((key%7)+1);
	inPin = (1 << (key/7));
		
	if (key < 56)
	{
		metaOutPin = 0;
	}
	else if (key < 112)
	{
		metaOutPin = SHIFT;
	}
	else if (key < 168)
	{
		metaOutPin = CODE;
	}
	else
	{
		return;
	}
	
	USART_SendByte(key);

	PORTB = 0;
	DDRB = outPin;// | metaOutPin;
	
	for(int i = 20 ; i ; i--)
	{
		lastPINC = PINC;
		//USART_SendByte(lastPINC);
		if (!lastPINC)
			PORTB = 0; //Ground
		//if (lastPINC & META)
		//	PORTB = metaOutPin; //Raise metaOutPin
		if (lastPINC & inPin)
			PORTB = outPin; //Raise outPin
		while (lastPINC & PINC);
	}
	
	PORTB = 0; //Float all
	DDRB = 0; //Float all
	
	_delay_ms(100);
}*/

void pressKey2(uint8_t key)
{
	//uint8_t outPin = 1 << ((key%7)+1);
	//uint8_t inPin = 1 << (key/7);
	
	//uint8_t lastPINC;
	
	uint8_t out[8] = {0};
	out[key/7]= 1 << ((key%7)+1);
	//out[7] |= SHIFT;
	
	//uint8_t* j = &out[1];
	//uint8_t nextOut = out[0];
	//uint8_t scanPin = 1;
	
	uint8_t out0 = out[0];
	uint8_t out1 = out[1];
	uint8_t out2 = out[2];
	uint8_t out3 = 0x40;
	uint8_t out4 = out[4];
	uint8_t out5 = out[5];
	uint8_t out6 = out[6];
	uint8_t out7 = out[7];
	
	PORTB = 0;
	DDRB = 0xFF;
	
	while(1)
	{	while (!(PINC & 1));
		PORTB = out0;
		while (!(PINC & 2));
		PORTB = out1;
		while (!(PINC & 4));
		PORTB = out2;
		while (!(PINC & 8));
		PORTB = out3;
		while (!(PINC & 16));
		PORTB = out4;
		while (!(PINC & 32));
		PORTB = out5;
		while (!(PINC & 64));
		PORTB = out6;
		while (!(PINC & 128));
		PORTB = out7;
		
		/*do
		{
			while (!(PINC & scanPin));
			PORTB = nextOut;
			nextOut = *j++;
		} while (scanPin << 1);
	
		j = &out[1];
		nextOut = out[0];
		scanPin = 1;*/
		
		//PORTB = 0; //Ground outPin, leave others floating
		//while (!(PINC & inPin));
		//PORTB = outPin; //Raise outPin, leave others floating
		//while (PINC & inPin);
	}
	
	PORTB = 0; //Float all
	DDRB = 0; //Float all
	
	_delay_ms(100);
}

void TypeStr(char Data[])
{
	for (char *ch = &Data[0] ; *ch ; ch++)
	{
		pressKey2(CharMap[(int)*ch]);
	}
}

int main(void)
{
	USART_Init(38400);
	DDRC = 0x00;
	
	TypeStr("hello world.");
	
	return 0;
}