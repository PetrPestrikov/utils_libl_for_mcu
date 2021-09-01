/*
 * Fifo_C.c
 *
 * Created: 29.08.2021 9:57:33
 * Author : Pestrikov Petr
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "FIFO.h"


/******************************************************************
Shown is an example of installing and removing a critical section when 
working in parallel with a FIFO from the main body of the program and interrupt.
This example creates 1 array and 1 FIFO buffer.
The FIFO is filled with ADC data,
after which its contents are read into the readData [] array.
*******************************************************************/

#define MAS_LENGHT 10

//turn off the interrupts of the hardware timer selected for counting the system time
void SetCriticalSection(void)
{
	
}

//turn on the interrupts of the hardware timer selected for counting the system time
void ReleaseCriticalSection(void)
{
	
}


void setupADC (void){
   // ADC setup
   
   DDRA &= ~(1<<PA4);	//Set the PA4 leg to the entrance
   
   ADMUX |= (1<<MUX2);	//Configuring the multiplexer
   
   ADMUX |= (1<<REFS0);	//Choosing a voltage reference
   
   ADCSRA |=(1<<ADATE);							//Setting up a cyclical mode of operation
   SFIOR &= ~((1<<ADTS0)|(1<<ADTS1)|(1<<ADTS2));
   
   ADCSRA |= (1<<ADPS2)|(1<<ADPS0);//adjust the conversion frequency
   
   ADCSRA |= (1<<ADIE); //allow interruption at the end
   
   ADCSRA |= (1<<ADEN); //we allow work
   
   ADCSRA |= (1<<ADSC); //first start
}

uint16_t ADCVal = 0;

uint16_t mas[MAS_LENGHT];
uint16_t readData[MAS_LENGHT];
fifo_t fifo;

int main(void)
{
	setupADC();
	sei();
		
	createFifo(&fifo, MAS_LENGHT, mas, sizeof(uint16_t));
	fifo.setCritFoo = SetCriticalSection;
	fifo.relCritFoo = ReleaseCriticalSection;
	
	while(1)
	{
		if(isFullFifo(&fifo))
		{
			uint8_t i = 0;
			while(!isEmptyFifo(&fifo))
			{
				fifo.setCritFoo();		//install the critical section
				readData[i] =  *(uint16_t *)readFifo (&fifo);
				fifo.relCritFoo();		//remove the critical section
				i++;
			}
		}	
	}
}

ISR(ADC_vect)
{
	uint8_t Low = ADCL;
	uint8_t Hi = ADCH;
	
	ADCVal = (Hi<<8) | Low;
	
	writeFifo (&fifo, (void *)(&ADCVal));
	
}

