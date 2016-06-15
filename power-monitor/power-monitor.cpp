/*
 * power_monitor.cpp
 *
 * Created: 6/1/2016 9:18:30 PM
 *  Author: Abhishek
 */ 
#define F_CPU 8000000UL
#define SAMPLES 400
#define CURRENT_MULTIPLIER 0.00488 //CT turn ratio 1000:01:00
#define VOLT_MULTIPLIER 132.5
#define DEBUG 0
#include <math.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"
#include "UART.h"

int voltageSamples[SAMPLES]={0},
	currentSamples[SAMPLES]={0};

long double averageVolt=0,
		averageCurrent=0,
		actualVolt=0,
		actualCurrent=0,
		Vrms=0,
		Irms=0,
		voltSquaredSum=0,
		currentSquaredSum=0,
		realPower=0;
		
LCD lcd('B','C',0,1,2);

int analogRead(unsigned char);
void readVoltageCurrent();
double calculatePowerFactor();
void printSamples();
void adcInit();



int main(void)
{
    //TODO:: Please write your application code 
	DDRB = 0xff;
	DDRC = 0x0f;
	lcd.begin();
	Serial.begin(9600);
	Serial.print("hello world\n");
	lcd.Print("Power Monitoring",0,0);
	lcd.Print("System",4,1);
	_delay_ms(4000);
	adcInit();
	double data = calculatePowerFactor();
	//printSamples();
	lcd.clear();
	while(1){	
		if(DEBUG){
			char buffer[20];
			sprintf(buffer,"V: %d , I: %d",analogRead(1),analogRead(2));
			Serial.println(buffer);
		}else{
			lcd.Print("Vrms:",0,0);
			lcd.Print((unsigned int)Vrms,5,0);
			lcd.Print("Irms:",0,1);
			lcd.Print(Irms,5,1);
			lcd.Print("S:",10,0);
			lcd.Print((unsigned int)(Vrms*Irms),12,0);
			lcd.Print((long double)calculatePowerFactor(),11,1);
		}
		_delay_ms(100);	
	}
}


void adcInit()
{
	ADCSRA |= 1<<ADEN; //ADC enable. ADC doesn't consume power when ADEN is cleared
	//ADCSRA |=(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); // prescaler=128 means X_cpu/128=7.8125KHz
	ADCSRA |=(1<<ADPS2); //prescaler = 16
	ADMUX |= 1<<REFS0; //Reference: AVCC (AVCC must be connected with VCC)
}

int analogRead(uint8_t channel)
{
	int adc_value = 0;
	//ADMUX |= (ADMUX&0b11100000)|(channel&0b00011111); // First five bits of ADMUX for selecting channel
	ADMUX = (ADMUX&0xf0)|(channel&0x0f);
	ADCSRA |=1<<ADSC; //Conversion will start writing this bit to one.
	while(!(ADCSRA&(1<<ADIF))); //ADIF will set when conversion complete and loop breaks.
	ADCSRA|= 1<<ADIF; //ADIF must be cleared(1) to trigger a new conversion next time
	adc_value = ADCW;
	return(adc_value);
	
}

void readVoltageCurrent(){
	for (int i=0;i<SAMPLES;i++){
		voltageSamples[i] = analogRead(1);
		_delay_us(100);
		currentSamples[i] = analogRead(2);
		_delay_us(100);
	}
}

void printSamples(){
	for (int i=0;i<SAMPLES;i++){
		char buffer[20];
		sprintf(buffer,"V: %d , I: %d",voltageSamples[i],currentSamples[i]);
		Serial.println(buffer);
	}
}

double calculatePowerFactor(){
	//Serial.println("start...");
	readVoltageCurrent();
	//Serial.println("Stop..");
	averageVolt=0;
	averageCurrent=0;
	actualVolt=0;
	actualCurrent=0;
	Vrms=0;
	Irms=0;
	voltSquaredSum=0;
	currentSquaredSum=0;
	realPower=0;
	/*char buffer[20];
	sprintf(buffer,"AvgVolt Before Sum : %d",averageVolt);
	Serial.println(buffer);*/
	//calculating the average 
	for(int i=0;i<SAMPLES;i++){
		averageVolt+=((double)voltageSamples[i]*CURRENT_MULTIPLIER);
		averageCurrent+=((double)currentSamples[i]*CURRENT_MULTIPLIER);
		/*char buffer[30];
		sprintf(buffer,"%d - %d : %d",i,(int)voltageSamples[i],(int)averageVolt);
		Serial.println(buffer);*/
		/*char buffer[30];
		sprintf(buffer,"%d - %d : %d",i,(int)((double)currentSamples[i]*CURRENT_MULTIPLIER),(int)averageCurrent);
		Serial.println(buffer);*/
	}
	averageVolt = averageVolt/SAMPLES;
	averageCurrent = averageCurrent/SAMPLES;
	
	//calculating actual voltage
	for(int i=0;i<SAMPLES;i++){
		actualVolt			 = ((double)voltageSamples[i]*CURRENT_MULTIPLIER-averageVolt)*VOLT_MULTIPLIER;
		/*char buffer[30];
		sprintf(buffer,"%d - %d : %d",(int)((double)voltageSamples[i]*CURRENT_MULTIPLIER),(int)averageVolt,(int)actualVolt);
		Serial.println(buffer);*/
		actualCurrent		 = ((double)currentSamples[i]*CURRENT_MULTIPLIER-averageCurrent);
		/*char buffer[30];
		sprintf(buffer,"%d - %d : %d",currentSamples[i],(int)averageCurrent,(int)actualCurrent);
		Serial.println(buffer);*/
		voltSquaredSum		+= pow(actualVolt,2);
		currentSquaredSum	+= pow(actualCurrent,2);
		realPower			+= actualVolt * actualCurrent ;
	}
	
	Vrms		= sqrt(voltSquaredSum/SAMPLES);
	Irms		= sqrt(currentSquaredSum/SAMPLES);
	realPower	= realPower/SAMPLES;
	char buffer[30];
	sprintf(buffer,"Irms : %d",(int)Irms);
	Serial.println(buffer);
	return realPower/(Vrms*Irms);
}