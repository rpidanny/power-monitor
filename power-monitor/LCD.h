/*
 * LCD.h
 *
 * Created: 6/1/2016 9:22:44 PM
 *  Author: Abhishek
 */ 


#ifndef LCD_H_
#define LCD_H_


class LCD{
	char LCD_DATA ;
	char ctrl ;
	int en;		
	int rw;		
	int rs;	
	public:
	
	LCD(char DATA,char Control,int enable,int readwrite,int reset);
	void cmd(unsigned char cmd);
	void begin(void);
	void write(unsigned char data);
	void Print(const char*,int=0,int=0);
	void Print(unsigned int,int=0,int=0);
	void print(unsigned int,int=0,int=0);
	void Print(long double number,int x,int y);
	void clear();
};


#endif /* LCD_H_ */