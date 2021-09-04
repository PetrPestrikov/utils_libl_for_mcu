#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "filo.h"

/**
 * main.c

 */
uint8_t Mas[10];
uint8_t ReadMas[10];
uint8_t WriteMas[10];

Filo <uint8_t> myfilo(10, Mas);

int main(void)
{
    for(uint8_t i = 0; i<10; i++)
    {
        WriteMas[i] = i;
        myfilo.write(&WriteMas[i]);
    }

    if(myfilo.isFull())
    {
        uint8_t i =0;
        while(!myfilo.isEmpty())
        {
            ReadMas[i] =  *myfilo.read();
            i++;
        }
    }




    while(1)
    {

    }

	return 0;
}
