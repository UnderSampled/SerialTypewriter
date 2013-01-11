/*
 * USART_LIB.c
 *
 * Created: 5/27/2011 10:29:10 AM
 *  Author: Stephen Christie
 *  Originally Copied from http://winavr.scienceprog.com/avr-gcc-tutorial/avr-usart-explained.html
 */ 
#include "Global_DEFs.h"

#include <avr/io.h>

#include "USART_LIB.h"

#define CALC_BAUD(baudrate) ((F_CPU/(baudrate<<4))-1)

void USART_Init(unsigned long baudrate)
{
	// Set baud rate

	UBRR0H = (uint8_t)(CALC_BAUD(baudrate)>>8);

	UBRR0L = (uint8_t)CALC_BAUD(baudrate);


	// Set frame format to 8 data bits, no parity, 1 stop bit

	UCSR0C = (0<<USBS0)|(1<<UCSZ01)|(1<<UCSZ00);


	// Enable receiver and transmitter

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
}


void USART_SendByte(uint8_t u8Data)
{
	// Wait if a byte is being transmitted

	while((UCSR0A&(1<<UDRE0)) == 0);

	// Transmit data

	UDR0 = u8Data;
}

void USART_SendChangingByte(uint8_t u8Data)
{
	//keep a copy of the data
	copy = u8Data;
	
	// Wait if a byte is being transmitted

	while((UCSR0A&(1<<UDRE0)) == 0);

	// Transmit data

	UDR0 = copy;
}


uint8_t USART_ReceiveByte()
{
	// Wait until a byte has been received

	while((UCSR0A&(1<<RXC0)) == 0);

	// Return received data

	return UDR0;
}

void USART_SendStr(char Data[])
{
	for (char *ch = &Data[0] ; *ch ; ch++)
	{
		USART_SendByte((uint8_t)*ch);
	}
}