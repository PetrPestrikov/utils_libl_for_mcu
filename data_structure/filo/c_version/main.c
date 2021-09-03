/*
 * FILO_C.c
 *
 * Created: 01.09.2021 20:41:45
 * Author : Рабочий
 */ 

#include <avr/io.h>
#include "FILO.h"

#define MAX_NUMBER 7

uint16_t mas[MAX_NUMBER];
uint16_t writeBuf[MAX_NUMBER];
uint16_t readBuf[MAX_NUMBER];
filo_t filo;

int main(void)
{
	
	createFilo(&filo, MAX_NUMBER, mas, sizeof(uint16_t));
	
	for(uint8_t i=0; i<MAX_NUMBER;i++)
	{
		writeBuf[i] = i;
		writeFilo(&filo, (void *)&writeBuf[i]);					//writing to the buffer by reference
	}
	
	if(isFullFilo(&filo))
	{
		uint8_t i=0;
		while(!isEmptyFilo(&filo))
		{
			readBuf[i]= *(uint16_t *)readFilo (&filo);
			i++;
		}
	}
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

