/*
 * commBufer.h
 *
 *  Created on: 11 но€б. 2022 г.
 *      Author: 79141
 */

#ifndef UTILS_COMMBUFER_H_
#define UTILS_COMMBUFER_H_


#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>


template <typename  T>
class Bufer
{
public:
    Bufer();
    Bufer(uint32_t size, T *Headptr);
    uint32_t size;              // buffer size
    T *ptr;                     //pointer to the first element of the array
};

/***********************************************************************************
 *       Bufer initialization
 * Size      - the size of the array in which the data is stored
 * *headptr     - pointer to the beginning of the array
 **********************************************************************************/
template <typename T> Bufer <T> :: Bufer(uint32_t size, T *Headptr)
{
    ptr = Headptr;
    this->size = size;
}

template <typename T> Bufer <T> :: Bufer()
{
    ptr = NULL;
    this->size = 0;
}



#endif /* UTILS_COMMBUFER_H_ */
