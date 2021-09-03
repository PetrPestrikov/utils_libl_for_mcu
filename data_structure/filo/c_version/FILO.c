/*
 * FIFO.c
 *
 * Created: 30.07.2015 
 *  Author: Pestrikov Petr
 */ 

#include "FILO.h"


/***********************************************************************************
 *		 filo initialization
 *	*filo		- a pointer to the filo to be initialized
 * arrSize		- the size of the array in which the data is stored
 * *headptr		- pointer to the beginning of the array
 * dataTypeLen  - size in bytes of one data instance in the array
 * 
 **********************************************************************************/
void createFilo(filo_t *filo, uint16_t arrSize, void *headptr, uint8_t dataTypeLen)
{
	filo->size = arrSize;
	filo->masHeadptr = headptr;

	filo->filoRWIndex = 0;

	filo->dataTypeLen = dataTypeLen; 
	
	filo->setCritFoo = NULL;
	filo->relCritFoo = NULL;
}
/**********************************************************
 *		record in the filo of the data by reference
 * *filo - a pointer to the filo to be initialized
 * *data - a pointer to an instance of data to be placed in the filo
 * return - true if write well done
 * the function performs a byte write of data from the * data pointer, taking into account the size in bytes of one data field
 ******************************************************** */
bool writeFilo(filo_t *filo, void *data)
 {
	if(isFullFilo(filo))
    {
		return false;
    }
	
	uint8_t * firstPlace = &((uint8_t *)filo->masHeadptr)[filo->filoRWIndex * filo->dataTypeLen];

	for(uint8_t i = 0; i < filo->dataTypeLen; i++)
	{
		(firstPlace)[i] = ((uint8_t*)data)[i];
	}
	
	filo->filoRWIndex++;
	
	return true;
}
 /*************************************************************************
 *		returns a pointer to the read data
 *  *filo - a pointer to the filo to be initialized
 * return - NULL if read from empty bufer
 *************************************************************************/
void  *readFilo (filo_t *filo)
 {
	 void *returnvalue;
	 
	 if(isEmptyFilo(filo))
	 {
		 returnvalue = NULL;
	 }
	 else
	 {
		returnvalue = (void *)(&((uint8_t *)filo->masHeadptr)[(filo->filoRWIndex - 1) * filo->dataTypeLen]);
		filo->filoRWIndex--;		 
	 }

	 return returnvalue;
 }
 /**************************************************************************
 *	buffer erase
 *	The content of the buffer is not deleted, but all pointers are cleared
 **************************************************************************/
 void  flushFifo(filo_t *filo)
 {
	 filo->filoRWIndex = 0;
 }
 /*******************************************************************************
 *                        Is the buffer Empty
 * *filo - a pointer to the filo to be initialized
 * returns true if the buffer is empty
 ******************************************************************************/
 bool  isEmptyFilo(filo_t *filo)
 {
	return( (filo->filoRWIndex  == 0) ? true : false);
 }
 /*******************************************************************************
 *                        Is the buffer full
 * *filo - a pointer to the filo to be initialized
 * returns true if the buffer is full
 ******************************************************************************/
 bool isFullFilo(filo_t *filo)
 {
    return( (filo->filoRWIndex  == filo->size) ? true : false);
 }
/*******************************************************************************
*   *filo - a pointer to the filo to be initialized
*   returns current number of elements written in the buffer
********************************************************************************/
uint16_t getFiloCount(filo_t *filo)
{
   return filo->filoRWIndex;
}


