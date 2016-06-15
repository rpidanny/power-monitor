/*
 * LCD.cpp
 *
 * Created: 6/1/2016 9:22:29 PM
 *  Author: Abhishek
 */ 

#include "LCD.h"
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>

LCD::LCD(char DATA,char Control,int enable,int readwrite,int reset){
		LCD_DATA =DATA;
		ctrl =Control;
		en =enable;		
		rw =readwrite;		
		rs=reset;
		PORTC=0xff;
		_delay_ms(100);
		PORTC=0x00;
	}
	
	
void LCD::cmd(unsigned char cmd)
	{
		if(LCD_DATA=='A'){
			PORTA=cmd;
			if(ctrl=='B'){
			PORTB =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTB =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='C'){
			PORTC =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTC =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='D'){
			PORTD =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTD =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
		}
		else if(LCD_DATA=='B'){
			PORTB=cmd;
			if(ctrl=='A'){
			PORTA =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTA =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='C'){
			PORTC =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTC =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='D'){
			PORTD =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTD =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
		}
		else if(LCD_DATA==67){
			PORTC=cmd;
			if(ctrl==66){
			PORTB =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTB =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='A'){
			PORTA =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTA =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='D'){
			PORTD =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTD =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
		}
		else if(LCD_DATA=='D'){
			PORTD=cmd;
			if(ctrl=='B'){
			PORTB =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTB =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='C'){
			PORTC =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTC =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
			else if(ctrl=='A'){
			PORTA =(0<<rs)|(0<<rw)|(1<<en);	// RS and RW as LOW and EN as HIGH
			_delay_ms(1);
			PORTA =(0<<rs)|(0<<rw)|(0<<en);	// RS, RW , LOW and EN as LOW
			_delay_ms(50);
			return;
			}
		}
		
	}


void LCD::begin(void)
	{
		cmd(0x38);		// initialization of 16X2 LCD in 8bit mode
		_delay_ms(1);
	 
		cmd(0x01);		// clear LCD
		_delay_ms(1);
	 
		cmd(0x0E);		// cursor ON
		_delay_ms(1);
	 
		cmd(0x80);		// ---8 go to first line and --0 is for 0th position
		_delay_ms(1);
		return;
	}
	 

void LCD::write(unsigned char data)
	{
			
			
		if(LCD_DATA=='A'){
			PORTA= data;
			if(ctrl=='B'){
				PORTB = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTB = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='C'){
				PORTC = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTC = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='D'){
				PORTD = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTD = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
		
		}
		else if(LCD_DATA=='B'){
			PORTB= data;
			if(ctrl=='A'){
				PORTA = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTA = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='C'){
				PORTC = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTC = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='D'){
				PORTD = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTD = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
		
		}
		else if(LCD_DATA=='C'){
			PORTC= data;
			if(ctrl=='B'){
				PORTB = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTB = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='A'){
				PORTA = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTA = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='D'){
				PORTD = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTD = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
		
		}
		else if(LCD_DATA=='D'){
			PORTD= data;
			if(ctrl=='B'){
				PORTB = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTB = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='C'){
				PORTC = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTC = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
			else if(ctrl=='A'){
				PORTA = (1<<rs)|(0<<rw)|(1<<en);	// RW as LOW and RS, EN as HIGH
				_delay_ms(1);
				PORTA = (1<<rs)|(0<<rw)|(0<<en);	// EN and RW as LOW and RS HIGH
				_delay_ms(1);			// delay to get things executed
				return ;
			}
		
		}
		
	}
	
void LCD::clear(){
	Print("                ",0,0);
	Print("                ",0,1);
}
void LCD::Print(const char *string,int x,int y) //String, x position, y position
{
	if(x<40)
	 {
		  if(y) x|=0b01000000;
		  x|=0b10000000;
		  cmd(x);
	  }
	while (*string)
	write(*string++);
}
	 
void LCD::Print(unsigned int i,int x,int y) //integer value, x position, y position
{
	if(x<40)
	{
		if(y) x|=0b01000000;
		x|=0b10000000;
		cmd(x);
	}
	write((i/1000)+48);
	write(((i/100)%10)+48);
	write(((i/10)%10)+48);
	write((i%10)+48);
}

void LCD::print(unsigned int i,int x,int y) //integer value, x position, y position
{
	if(x<40)
	{
		if(y) x|=0b01000000;
		x|=0b10000000;
		cmd(x);
	}
	write((i%10)+48);
}

void LCD::Print(long double number,int x,int y) 
{ 
	if(x<40)
	{
		if(y) x|=0b01000000;
		x|=0b10000000;
		cmd(x);
	}
  
  if (isnan(number)) Print("nan",x,y);
  if (isinf(number)) Print("inf",x,y);
  if (number > 4294967040.0) Print ("ovf",x,y);  // constant determined empirically
  if (number <-4294967040.0) Print ("ovf",x,y);  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
	 Print("-",x,y);
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<2; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  print((unsigned int)int_part,x,y);

  // Print the decimal point, but only if there are digits beyond
  if (2 > 0) {
    Print(".",x+1,y+2); 
  }

  // Extract digits from the remainder one at a time
  for (int i=0;i<2;i++)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    print((unsigned int)toPrint,x+2+i,y);
    remainder -= toPrint; 
  } 
  
}