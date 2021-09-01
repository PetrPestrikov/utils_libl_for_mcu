/*
 * FIFO.c
 *
 * Created: 30.07.2015 
 *  Author: Pestrikov Petr
 */ 

#include "FIFO.h"


/***************************************************************
*
* The helper function for incrementing index-pointers to the beginning and end of the data in the buffer
*
************************************************************* */
static  void increment(fifo_t *fifo, uint16_t *index)
{
  *index = *index + 1;
   if( *index == fifo->size )
	{
		*index = 0;
  		fifo->msb ^= 1;
    }
}
/***********************************************************************************
 *		 fifo initialization
 *	*fifo		- a pointer to the fifo to be initialized
 * ArrSize		- the size of the array in which the data is stored
 * *Headptr		- pointer to the beginning of the array
 * dataTypeLen  - size in bytes of one data instance in the array
 * 
 **********************************************************************************/
void createFifo(fifo_t *fifo, uint16_t arrSize, void *headptr, uint8_t dataTypeLen)
{
	fifo->size = arrSize;
	fifo->masHeadptr = headptr;

	fifo->fifoReadIndex = 0;
	fifo->fifoWriteIndex = 0;

	fifo->msb = 0;
	
	fifo->dataTypeLen = dataTypeLen; 
	
	fifo->setCritFoo = NULL;
	fifo->relCritFoo = NULL;
}
/**********************************************************
 *		record in the fifo of the data by reference
 * *fifo - a pointer to the fifo to be initialized
 * *data - a pointer to an instance of data to be placed in the fifo
 * the function performs a byte write of data from the * data pointer, taking into account the size in bytes of one data field
 ******************************************************** */
void writeFifo (fifo_t *fifo, void *data)
 {
	if(isFullFifo(fifo))
    {
		increment(fifo,&(fifo->fifoReadIndex));
    }
	uint8_t * firstPlace = &((uint8_t *)fifo->masHeadptr)[fifo->fifoWriteIndex * fifo->dataTypeLen];

	for(uint8_t i = 0; i < fifo->dataTypeLen; i++)
	{
		(firstPlace)[i] = ((uint8_t*)data)[i];
	}

    increment(fifo,&(fifo->fifoWriteIndex));
	
}
 /*************************************************************************
 *		returns a pointer to the read data
 *  *fifo - a pointer to the fifo to be initialized
 *************************************************************************/
void  *readFifo (fifo_t *fifo)
 {
	 void *returnvalue;

	 returnvalue = (void *)(&((uint8_t *)fifo->masHeadptr)[fifo->fifoReadIndex * fifo->dataTypeLen]);
	 increment(fifo,&(fifo->fifoReadIndex));

	 return returnvalue;
 }
 /**************************************************************************
 *	buffer erase
 *	The content of the buffer is not deleted, but all pointers are cleared
 **************************************************************************/
 void  flushFifo(fifo_t *fifo)
 {
	 fifo->fifoReadIndex = 0;
	 fifo->fifoWriteIndex = 0;
	 fifo->msb = 0;
 }
 /*******************************************************************************
 *                        Is the buffer Empty
 * *fifo - a pointer to the fifo to be initialized
 * returns true if the buffer is empty
 ******************************************************************************/
 bool  isEmptyFifo(fifo_t *fifo)
 {
	return( ((fifo->fifoWriteIndex  == fifo->fifoReadIndex) && (fifo->msb == 0)) ? true : false);
 }
 /*******************************************************************************
 *                        Is the buffer full
 * *fifo - a pointer to the fifo to be initialized
 * returns true if the buffer is full
 ******************************************************************************/
 bool isFullFifo(fifo_t *fifo)
 {
    return( ((fifo->fifoWriteIndex  == fifo->fifoReadIndex) && (fifo->msb != 0)) ? true : false);
 }


