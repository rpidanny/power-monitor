/*
 * UART.h
 *
 * Created: 6/1/2016 9:23:46 PM
 *  Author: Abhishek
 */ 


#ifndef UART_H_
#define UART_H_

#ifndef F_CPU
# warning "F_CPU not defined for <util/delay.h>"
# define F_CPU 8000000UL
#endif

#define value (((F_CPU / (baud * 16UL))) - 1)
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>

class UART{	
	int baud;
	public:
	UART():baud(0){}
	
	void begin(int x)
	{   
		baud=x;
	
		UCSRB |= (1 << RXEN)|(1 << TXEN);   
		UCSRC |= (1 << URSEL) | (0<<USBS) | (1 << UCSZ0) | (1 << UCSZ1); 
		UBRRL = value; 
	}

	uint8_t read()
	{   
		//while ((UCSRA & (1 << RXC)) == 0); 
		
			return UDR;
		
		
		
	}
	
	void send(char datam)
	{
		 while(!(UCSRA & (1 << UDRE)));   
		 UDR = datam; 
	 }
 	
	void print(const char *str)
	{
			unsigned int i=0;
			while(str[i]!='\0')
			  {
				send(str[i]);
				i++;
			  }
	}
	
	void println(const char *str)
	{
			unsigned int i=0;
			while(str[i]!='\0')
			  {
				send(str[i]);
				i++;
			  }
			send('\r');
			send('\n');
	}
	
	int available()
	{
		if ((UCSRA & (1 << RXC)) == 0)
		{
			return 0;
		}
		else{
			return 1;
		}
		
	}

}Serial;



#endif /* UART_H_ */