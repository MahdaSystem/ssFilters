/**
 **********************************************************************************
 * @file   MovingAverage.c
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief  
 *         Functionalities of the this file:
 *          + Getting Moving Average filter
 **********************************************************************************
 *
 *! Copyright (c) 2021 Mahda Embedded System (MIT License)
 *!
 *! Permission is hereby granted, free of charge, to any person obtaining a copy
 *! of this software and associated documentation files (the "Software"), to deal
 *! in the Software without restriction, including without limitation the rights
 *! to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *! copies of the Software, and to permit persons to whom the Software is
 *! furnished to do so, subject to the following conditions:
 *!
 *! The above copyright notice and this permission notice shall be included in all
 *! copies or substantial portions of the Software.
 *!
 *! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *! FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *! AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *! LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *! OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *! SOFTWARE.
 *!
 **********************************************************************************
 **/

//* Private Includes -------------------------------------------------------------- //
#include "MovingAverage.h"

//* Others ------------------------------------------------------------------------ //
#ifdef Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

/**
 ** ==================================================================================
 **                           ##### Public Functions #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Initializes The Library
 * @note   Must be called at first and once
 * @param  MA_ControlBlock: Pointer Of Library Handler
 * @param  windowSize:      Window Size
 * @param  buffer:          Pointer Of window buffer | Number of Element: At least windowSize
 * @retval None
 */
void
ssf_MA_Init(MovingAverage_t *MA_ControlBlock, uint16_t windowSize, DatatypeUsed *buffer)
{
    if (MA_ControlBlock && buffer)
    {
        MA_ControlBlock->Count = 0;
        MA_ControlBlock->Window = windowSize;
        MA_ControlBlock->Sum = 0;
        MA_ControlBlock->divideCounter = 0;
        MA_ControlBlock->Buffer = buffer;
        memset(buffer, 0, windowSize);
    }
}

/**
 * @brief  Gets The Moving Average filtered data
 * @note   This works as Streaming
 * @param  MA_ControlBlock: Pointer Of Library Handler
 * @param  value:           Next data value to be added
 * @retval Moving Average filtered data
 */
DatatypeUsed
ssf_MA_GetData(MovingAverage_t *MA_ControlBlock, DatatypeUsed value)
{
    if (MA_ControlBlock)
    {
        MA_ControlBlock->Sum += value - MA_ControlBlock->Buffer[MA_ControlBlock->Count];
        MA_ControlBlock->Buffer[MA_ControlBlock->Count] = value;
        if(MA_ControlBlock->Count < (MA_ControlBlock->Window - 1))
            MA_ControlBlock->Count++;
        else
            MA_ControlBlock->Count = 0;
        if(MA_ControlBlock->divideCounter < MA_ControlBlock->Window)
        {
            MA_ControlBlock->divideCounter++;
            return MA_ControlBlock->Sum / MA_ControlBlock->divideCounter;
        }
        else
            return MA_ControlBlock->Sum / MA_ControlBlock->Window;
    }
    return 0;
}

