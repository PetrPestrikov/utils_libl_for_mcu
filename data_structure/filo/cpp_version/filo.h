/*
 * filo.h
 *
 *  Created on: 4 сент. 2021 г.
 *      Author: user
 */

#ifndef FILO_H_
#define FILO_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef  void(*setCritFunc_t)(void);        //a pointer to a function that sets the critical section
typedef  void(*relCritFunc_t)(void);        //a pointer to a function that releases the critical section

template <typename  T>
class Filo
{
public:
    Filo(uint16_t size, T *Headptr);
    bool write(T *data);
    T  *read();
    void flush();               //buffer erase
    bool isEmpty();             //returns true if the buffer is empty
    bool isFull();              //returns true if the buffer is full
    uint16_t getCount();
    setCritFunc_t setCritFoo;   //a pointer to a function that sets the critical section
    relCritFunc_t relCritFoo;   //a pointer to a function that releases the critical section

private:
    uint16_t size;              // buffer size
    uint16_t filoRWIndex;       //indicates the cell where the next item can be written. You can read from the previous cell
    T *masHeadptr;              //pointer to the first element of the array
};

/***********************************************************************************
 *       filo initialization
 * Size      - the size of the array in which the data is stored
 * *headptr     - pointer to the beginning of the array
 **********************************************************************************/
template <typename T> Filo <T> :: Filo(uint16_t size, T *Headptr)
{
    masHeadptr = Headptr;
    filoRWIndex = 0;
    this->size = size;
    setCritFoo = NULL;
    relCritFoo = NULL;

}
/*******************************************************************************
*                        Is the buffer Empty
* returns true if the buffer is empty
******************************************************************************/
template <typename T> bool Filo <T> :: isEmpty()
{
   return( filoRWIndex  == 0 ? true : false);
}
/*******************************************************************************
*                        Is the buffer full
* returns true if the buffer is full
******************************************************************************/
template <typename T> bool Filo <T> :: isFull()
{
   return( filoRWIndex  == size ? true : false);
}

/**********************************************************
 *      record in the filo of the data by reference
 * *data - a pointer to an instance of data to be placed in the filo
 * return - true if write well done
 ******************************************************** */
template <typename T> bool Filo <T> :: write(T *data)
{
    if(isFull())
    {
        return false;
    }

    masHeadptr[filoRWIndex] = *data;

    filoRWIndex++;

    return true;
}
/*************************************************************************
*      returns a pointer to the read data
* return - NULL if read from empty bufer
*************************************************************************/
template <typename T> T* Filo <T> :: read ()
{
    T *returnvalue;

    if(isEmpty())
    {
        returnvalue = NULL;
    }
    else
    {
       returnvalue = &masHeadptr[filoRWIndex - 1];
       filoRWIndex--;
    }

    return returnvalue;
}



#endif /* FILO_H_ */
