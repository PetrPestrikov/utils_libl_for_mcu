/*
 * fifo.h
 *
 *  Created on: 26 дек. 2022 г.
 *      Author: 79141
 */

#ifndef UTILS_FIFO_H_
#define UTILS_FIFO_H_

/*====================
       Includes
 *====================*/

#include "stdint.h"
#include <stdbool.h>
#include "stddef.h"
#include "commBufer.h"

/**********************
 *      TYPEDEFS
 **********************/

typedef  void(*setCritFunc_t)(void);        //a pointer to a function that sets the critical section
typedef  void(*relCritFunc_t)(void);        //a pointer to a function that releases the critical section

/*****************************************************
 * Describing a generic FIFO ring buffer
 * use a separate bit to track the case of data loopback.
 *************************************************** */

template <typename  T>
class Fifo
{
public:
    Fifo();
    Fifo(uint32_t size, T *Headptr);
    uint32_t size;              // buffer size

    T *masHeadptr;                     //pointer to the first element of the array
    setCritFunc_t setCritFoo;       //a pointer to a function that sets the critical section
    relCritFunc_t relCritFoo;       //a pointer to a function that releases the critical section

    //void createFifo(fifo_t *fifo, uint16_t ArrSize, void * Headptr, uint8_t DataTypeLen);   //create buffer
    void writeFifo (T * data);                     //writing to the buffer by reference
    T  * readFifo ();                            //reading
    void flushFifo();                               //buffer erase
    bool isEmptyFifo();                             //returns true if the buffer is empty
    bool isFullFifo();                              //returns true if the buffer is full
    uint16_t getBufferCount();                          // the current number of elements written in the buffer

private:
    uint8_t  msb;               //bit that determines whether the buffer has been overwritten
    uint16_t fifoReadIndex;         //points to the element to be read next (where the fresh data is) a pointer to the beginning of the data
    uint16_t fifoWriteIndex;        //Indicates the item that was last written
    void increment(uint16_t *index);


};

template <typename T> Fifo <T> :: Fifo(uint32_t size, T *Headptr)
{
    masHeadptr = Headptr;
    this->size = size;
}

template <typename T> Fifo <T> :: Fifo()
{
    masHeadptr = NULL;
    this->size = 0;
}

template <typename T> void Fifo <T> ::increment(uint16_t *index)
{
    *index = *index + 1;
     if( *index == size )
      {
          *index = 0;
          msb ^= 1;
      }
}

/**************************************************************************
*  buffer erase
*  The content of the buffer is not deleted, but all pointers are cleared
**************************************************************************/
template <typename T> void Fifo <T> :: flushFifo()
{
    fifoReadIndex = 0;
    fifoWriteIndex = 0;
    msb = 0;
}
/*******************************************************************************
*                        Is the buffer Empty
* *fifo - a pointer to the fifo to be initialized
* returns true if the buffer is empty
******************************************************************************/
 template <typename T> bool Fifo <T> :: isEmptyFifo()
{
   return( ((fifoWriteIndex  == fifoReadIndex) && (msb == 0)) ? true : false);
}
/*******************************************************************************
*                        Is the buffer full
* *fifo - a pointer to the fifo to be initialized
* returns true if the buffer is full
******************************************************************************/
 template <typename T> bool Fifo <T> :: isFullFifo()
{
   return( ((fifoWriteIndex  == fifoReadIndex) && (msb != 0)) ? true : false);
}



/**********************************************************
 *      record in the fifo of the data by reference
 * *fifo - a pointer to the fifo to be initialized
 * *data - a pointer to an instance of data to be placed in the fifo
 * the function performs a byte write of data from the * data pointer, taking into account the size in bytes of one data field
 ******************************************************** */
template <typename T> void Fifo <T> :: writeFifo (T * data)
 {
    if( isFullFifo() )
    {
        increment(&fifoReadIndex);
    }

    masHeadptr[fifoWriteIndex] = *data;


    increment( &fifoWriteIndex );

}

/*************************************************************************
*      returns a pointer to the read data
*  *fifo - a pointer to the fifo to be initialized
*************************************************************************/
template <typename T> T * Fifo <T> ::  readFifo ()
{
    T *returnvalue;

    returnvalue = &masHeadptr[fifoReadIndex];

    increment(&fifoReadIndex);

    return returnvalue;
}

/*************************************************************************
*      returns a pointer to the read data
*  *fifo - a pointer to the fifo to be initialized
*************************************************************************/
template <typename T> uint16_t Fifo <T> ::   getBufferCount ()
{
    uint16_t returnvalue;

    returnvalue = masHeadptr[fifoReadIndex];

    if(msb == 0)
    {
        returnvalue = fifoWriteIndex - fifoReadIndex;
    }
    else
    {
        returnvalue = size - (fifoReadIndex - fifoWriteIndex);
    }

    return returnvalue;
}


#endif /* UTILS_FIFO_H_ */
