/*
 * USART_LIB.h
 *
 * Created: 5/27/2011 10:23:38 AM
 *  Author: Stephen Christie
 *  Originally Copied from http://winavr.scienceprog.com/avr-gcc-tutorial/avr-usart-explained.html
 */ 

#ifndef USART_LIB_H_
#define USART_LIB_H_

uint8_t	copy;

void USART_Init(unsigned long baudrate);
void USART_SendByte(uint8_t u8Data);
void USART_SendChangingByte(uint8_t u8Data);
uint8_t USART_ReceiveByte();

#endif /* USART_LIB_H_ */