#define F_CPU 1000000 /*1MHz*/

#include "display.h"
#include <avr/io.h>
#include <util/delay.h>

Display::Display()
{
	m_DigitValues[0] = '-';
	m_DigitValues[1] = '-';
	m_DigitValues[2] = '-';
	m_DigitValues[3] = '-';
}

void Display::SetDigit(Position position, uint8_t value)
{
	switch(position)
	{
		case Position::POSITION_1:
		PORTB &= ~(1<<0);
		break;

		case Position::POSITION_2:
		PORTB &= ~(1<<1);
		break;

		case Position::POSITION_3:
		PORTB &= ~(1<<2);
		break;

		case Position::POSITION_4:
		PORTB &= ~(1<<3);
		break;
	}

	switch(value)
	{
		/*Hex codes for common anode 7-segment display setup*/
		case 0:
		PORTA = 0xC0;
		break;

		case 1:
		PORTA = 0xF9;
		break;

		case 2:
		PORTA = 0xA4;
		break;

		case 3:
		PORTA = 0xB0;
		break;

		case 4:
		PORTA = 0x99;
		break;

		case 5:
		PORTA = 0x92;
		break;

		case 6:
		PORTA = 0x82;
		break;
		
		case 7:
		PORTA = 0xF8;
		break;

		case 8:
		PORTA = 0x80;
		break;

		case 9:
		PORTA = 0x90;
		break;
		
		case '-':		// display '-'
		PORTA = 0xBF;
		break;
		
		case '.':		// display '.'
		PORTA = 0x7F;
		break;
		
		case 13:
		PORTA = 0x3F;	// display '-' and '.' simultaneously
		break;
		
		case 14:
		PORTA = 0x8C;	// letter P
		break;
		
		case 15:
		PORTA = 0x86;	// letter E
		break;
		
		case 16:
		PORTA = 0xAB;	// letter n
		break;
		
		case 17:
		PORTA = 0x83;	// letter b
		break;
				
		case 18:
		PORTA = 0x88;	// letter A
		break;
		
		case 19:
		PORTA = 0xA1;	// letter d
		break;
		
		case 20:
		PORTA = 0xFF;	//display nothing
		break;
	}
	
	_delay_us(600);
	Clear();
}

void Display::SetAllDigitsToValue(uint8_t value)
{
	for(int i=0; i < 4; i++)
	{
		m_DigitValues[i] = value;
	}
}

void Display::MultiplexDigits()
{
	SetDigit(Position::POSITION_1, m_DigitValues[0]);
	SetDigit(Position::POSITION_2, m_DigitValues[1]);
	SetDigit(Position::POSITION_3, m_DigitValues[2]);
	SetDigit(Position::POSITION_4, m_DigitValues[3]);
}

void Display::SetDigitValue(uint8_t position, DigitValue digitValue)
{
	//switch(position)
	//{
	//case Position::POSITION_1:
	//m_DigitValues[0] = value;
	//break;
	//
	//case Position::POSITION_2:
	//m_DigitValues[1] = value;
	//break;
	//
	//case Position::POSITION_3:
	//m_DigitValues[2] = value;
	//break;
	//
	//case Position::POSITION_4:
	//m_DigitValues[3] = value;
	//break;
	//}
	
	m_DigitValues[position - 1] = static_cast<uint8_t>(digitValue);
}

void Display::Clear()
{
	PORTA = 255;
	PORTB = 255;
}