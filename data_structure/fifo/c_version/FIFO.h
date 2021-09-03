/*
 * ComFIFO.h
 *
 * Created: 30.07.2020 8:46:12
 *  Author: PestrikovPetr
 */ 


#ifndef FIFO_H_
#define FIFO_H_

/*====================
	   Includes
 *====================*/

#include "stdint.h"
#include <stdbool.h>
#include "stddef.h"

/**********************
 *      TYPEDEFS
 **********************/

typedef  void(*setCritFunc_t)(void);		//a pointer to a function that sets the critical section
typedef  void(*relCritFunc_t)(void);		//a pointer to a function that releases the critical section

/*****************************************************
 * Describing a generic FIFO ring buffer
 * use a separate bit to track the case of data loopback.
 *************************************************** */
typedef struct fifo_t{
	uint16_t size;				// buffer size
	uint16_t fifoReadIndex;			//points to the element to be read next (where the fresh data is) a pointer to the beginning of the data
	uint16_t fifoWriteIndex;		//Indicates the item that was last written
    uint8_t	 msb;				//bit that determines whether the buffer has been overwritten
    void *   masHeadptr;			//pointer to the first element of the array
	uint8_t  dataTypeLen;			//Length of the data field in one FIFO cell in bytes
	setCritFunc_t setCritFoo;		//a pointer to a function that sets the critical section
	relCritFunc_t relCritFoo;		//a pointer to a function that releases the critical section
}fifo_t;

/**************************************************
 *	functions for working with FIFO
 *************************************************/
void createFifo(fifo_t *fifo, uint16_t ArrSize, void * Headptr, uint8_t DataTypeLen);	//create buffer
void writeFifo (fifo_t *fifo, void * data);						//writing to the buffer by reference
void  * readFifo (fifo_t *fifo);							//reading
void flushFifo(fifo_t *fifo);								//buffer erase
bool isEmptyFifo(fifo_t *fifo);								//returns true if the buffer is empty
bool isFullFifo(fifo_t *fifo);								//returns true if the buffer is full
uint16_t getBufferCount(fifo_t *fifo);							// the current number of elements written in the buffer




#endif /* FIFO_H_ */
