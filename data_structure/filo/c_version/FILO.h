/*
 * ComFIFO.h
 *
 * Created: 30.07.2020 8:46:12
 *  Author: PestrikovPetr
 */ 


#ifndef FILO_H_
#define FILO_H_

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
 * Describing a generic FILO ring buffer
 *************************************************** */
typedef struct filo_t{
	uint16_t size;				// buffer size
	uint16_t filoRWIndex;		//indicates the cell where the next item can be written. You can read from the previous cell
    void *masHeadptr;			//pointer to the first element of the array
	uint8_t  dataTypeLen;		//Length of the data field in one FIFO cell in bytes
	setCritFunc_t setCritFoo;	//a pointer to a function that sets the critical section
	relCritFunc_t relCritFoo;	//a pointer to a function that releases the critical section
}filo_t;

/**************************************************
 *	functions for working with FILO
 *************************************************/
void createFilo(filo_t *filo, uint16_t ArrSize, void * Headptr, uint8_t DataTypeLen);	//create buffer
bool writeFilo(filo_t *filo, void *data);					//writing to the buffer by reference
void  * readFilo (filo_t *filo);							//reading
void flushFilo(filo_t *filo);								//buffer erase
bool isEmptyFilo(filo_t *filo);								//returns true if the buffer is empty
bool isFullFilo(filo_t *filo);								//returns true if the buffer is full
uint16_t getFiloCount(filo_t *filo);						// the current number of elements written in the buffer




#endif /* FILO_H_ */
