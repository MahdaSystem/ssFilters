/**
 **********************************************************************************
 * @file   MovingAverage.c
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief
 *         Functionalities of the this file:
 *          + Getting Moving Average filtered data
 **********************************************************************************
 **/

// Private Includes -------------------------------------------------------------- //
#include "MovingAverage.h"

// Others ------------------------------------------------------------------------ //
#ifdef MovingAverage_Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

// Public Functions -------------------------------------------------------------- //

void ssf_MA_Init(MovingAverage_t *MA_ControlBlock, uint16_t windowSize, MovingAverage_DatatypeUsed *buffer)
{
    if (MA_ControlBlock && buffer)
    {
        MA_ControlBlock->Count = 0;
        MA_ControlBlock->Window = windowSize ? windowSize : 1;
        MA_ControlBlock->Sum = 0;
        MA_ControlBlock->divideCounter = 0;
        MA_ControlBlock->Buffer = buffer;
        memset(buffer, 0, windowSize * sizeof(MovingAverage_DatatypeUsed));
    }
}

MovingAverage_DatatypeUsed
ssf_MA_GetData(MovingAverage_t *MA_ControlBlock, MovingAverage_DatatypeUsed value)
{
    if (MA_ControlBlock)
    {
        MA_ControlBlock->Sum += value - MA_ControlBlock->Buffer[MA_ControlBlock->Count];
        MA_ControlBlock->Buffer[MA_ControlBlock->Count] = value;
        if (MA_ControlBlock->Count < (MA_ControlBlock->Window - 1))
            MA_ControlBlock->Count++;
        else
            MA_ControlBlock->Count = 0;
        if (MA_ControlBlock->divideCounter < MA_ControlBlock->Window)
        {
            MA_ControlBlock->divideCounter++;
            return MA_ControlBlock->Sum / MA_ControlBlock->divideCounter;
        }
        else
            return MA_ControlBlock->Sum / MA_ControlBlock->Window;
    }
    return 0;
}
