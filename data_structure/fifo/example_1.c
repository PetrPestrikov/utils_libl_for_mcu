/*
 * Fifo_C.c
 *
 * Created: 29.08.2021 9:57:33
 * Author : Pestrikov Petr
 */ 

#include "FIFO.h"

/******************************************************************
Shows an example of using the basic functions of working with fifo. 
Installation and removal of the critical section is not performed.
This example creates 2 arrays and 1 fifo buffer. 
The fifo buffer is filled with data from the data [] array, 
after which its contents are read into the readData [] array.
*******************************************************************/

#define MAS_LENGHT 10


int example_1(void)
{
	uint16_t mas[MAS_LENGHT];
	uint16_t data[MAS_LENGHT];
	uint16_t readData[MAS_LENGHT];
	
   	fifo_t fifo;		
	createFifo(&fifo, MAS_LENGHT, mas, sizeof(uint16_t));
	
	for(uint8_t i; i < MAS_LENGHT; i++)
	{
		data[i] = i;
		writeFifo (&fifo, (void *)(&data[i]));
	}
	
	if(isFullFifo(&fifo))
	{
		uint8_t i = 0;
		while(!isEmptyFifo(&fifo))
		{
			readData[i] =  *(uint16_t *)readFifo (&fifo);
			i++;
		}
	}
	
	
}

