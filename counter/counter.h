/*
 * counter.h
 *
 *  Created on: 2 мар. 2023 г.
 *      Author: 79141
 */

#ifndef UTILS_COUNTER_H_
#define UTILS_COUNTER_H_

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
typedef enum CounterMode{
    CYCLIC,
    ONE_CYCLE
}CounterMode;

typedef enum CounterDir{
    UP,
    DOWN
}CounterDir;


/*****************************************************
 * Describing the Counter class
 *************************************************** */

template <typename  T>
class Counter
{
public:
    Counter();
    Counter(T maxVal, T minVal, T defVal, T ittVal, CounterMode mode);

    void SetValue (T value);
    void SetMaxValue (T value);
    void SetMinValue (T value);
    void SetItterationValue (T value);
    void SetDefValue (T value);

    T GetValue(void);
    void Count(CounterDir dir);

    void Reset(void);
    bool CheckOvf(void);
    void ClearOvf(void);


private:
    T  counter;               //bit that determines whether the buffer has been overwritten
    T minVal;         //points to the element to be read next (where the fresh data is) a pointer to the beginning of the data
    T maxVal;        //Indicates the item that was last written
    T defVal;
    T ittVal;
    CounterMode mode;
    bool OVF;       //counter overflow

};

template <typename T> Counter <T> :: Counter(T maxVal, T minVal, T defVal, T ittVal, CounterMode mode)
{
    counter = defVal;
    this->defVal = defVal;
    this->minVal = minVal;
    this->maxVal = maxVal;
    this->ittVal = ittVal;
    this->mode = mode;
    OVF = false;
}

template <typename T> Counter <T> :: Counter()
{
    counter = 0;
    this->defVal = 0;
    this->minVal = 0;
    this->maxVal = 10;
    this->ittVal = 1;
    this->mode = CYCLIC;
    OVF = false;
}

template <typename T> void Counter <T> :: SetValue (T value)
{
    counter = value;
}

template <typename T> void Counter <T> :: SetMaxValue (T value)
{
    this->maxVal = value;
}

template <typename T> void Counter <T> :: SetMinValue (T value)
{
    this->minVal = value;
}

template <typename T> void Counter <T> ::  SetItterationValue (T value)
{
    this->ittVal = value;
}

template <typename T> void Counter <T> ::  SetDefValue (T value)
{
    this->defVal = value;
}

template <typename T> T Counter <T> ::  GetValue (void)
{
    return this->counter;
}

template <typename T> void Counter <T> ::  Count(CounterDir dir)
{
    T upBalance = maxVal - counter;
    T downBalance = counter - minVal;

    if(dir == UP)
    {
        if(upBalance >= ittVal)  counter = counter + ittVal;
        else
        {
            OVF = true;
            if(mode == CYCLIC) counter = minVal;
            else counter = maxVal;
        }
    }
    else
    {
        if(downBalance >= ittVal)  counter = counter - ittVal;
        else
        {
            OVF = true;
            if(mode == CYCLIC) counter = maxVal;
            else counter = minVal;
        }
    }
}

template <typename T> void Counter <T> ::  Reset(void)
{
    counter = defVal;
}

template <typename T> bool Counter <T> ::  CheckOvf(void)
{
    return OVF;
}

template <typename T> void Counter <T> ::  ClearOvf(void)
{
    OVF = false;
}





#endif /* UTILS_COUNTER_H_ */
