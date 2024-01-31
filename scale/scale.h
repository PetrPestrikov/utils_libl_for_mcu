/*
 * uHisterisis.h
 *
 *  Created on: 13 мар. 2023 г.
 *      Author: 79141
 */

#ifndef UTILS_SCALE_H_
#define UTILS_SCALE_H_


/*====================
       Includes
 *====================*/

#include "stdint.h"
#include <stdbool.h>
#include "stddef.h"
#include "commBufer.h"

/*****************************************************
 * Describing the scale class
 *************************************************** */

template <typename  T>
class Scale
{
public:
    Scale();
    Scale(T maxVal, T minVal, T step, T histeresis);

    T GetValue (T value);

private:
    T  value;        //bit that determines whether the buffer has been overwritten
    T minVal;        //points to the element to be read next (where the fresh data is) a pointer to the beginning of the data
    T maxVal;        //Indicates the item that was last written
    T step;
    T histeresis;
};


template <typename T> Scale <T> :: Scale(T maxVal, T minVal, T step, T histeresis)
{
    this->value = minVal;
    this->minVal = minVal;
    this->maxVal = maxVal;
    this->step = step;
    this->histeresis = histeresis;
}

template <typename T> Scale <T> :: Scale()
{
    this->value = 0;
    this->minVal = 0;
    this->maxVal = 100;
    this->step = 10;
    this->histeresis = 3;
}

template <typename T> T Scale <T> :: GetValue (T value)
{
    T div = abs(value - this->value);

    if(div >= histeresis)
    {
        this->value = (value/this->step);
        this->value = this->value * this->step;

        if(this->value > maxVal) this->value = maxVal;
        if(this->value < minVal) this->value = minVal;
    }

    return this->value;
}


#endif /* UTILS_SCALE_H_ */
