/**
 **********************************************************************************
 * @file   Median.c
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief  
 *         Functionalities of the this file:
 *          + Getting Median filter
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
#include "Median.h"

//* Others ------------------------------------------------------------------------ //
#ifdef Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

/**
 *! ==================================================================================
 *!                           ##### Private Functions #####                               
 *! ==================================================================================
 **/

int
ssf_M_QSortFunction (const void *FirstParam,const void *SecondParam)
{
    if ((*(DatatypeUsed*)FirstParam) > (*(DatatypeUsed *)SecondParam)) return 1; // Bigger to lower
    else return -1;
}

/**
 ** ==================================================================================
 **                           ##### Public Functions #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Initializes The Library
 * @note   Must be called at first and once
 * @param  M_ControlBlock: Pointer Of Library Handler
 * @param  windowSize:     Window Size
 * @param  buffer:         Pointer Of window buffer | Number of Element: At least windowSize
 * @param  tempBuffer:     Pointer Of window temp buffer | Number of Element: At least windowSize
 * @retval None
 */
void
ssf_M_Init(Median_t *M_ControlBlock, uint16_t windowSize, DatatypeUsed *buffer, DatatypeUsed *tempBuffer)
{
    if (M_ControlBlock && buffer && tempBuffer)
    {
        M_ControlBlock->Count = 0;
        M_ControlBlock->FirstCounter = 0;
        M_ControlBlock->Window = windowSize;
        M_ControlBlock->Buffer = buffer;
        M_ControlBlock->TempBuffer = tempBuffer;
        if (windowSize % 2 == 0)
            M_ControlBlock->isEven = true;
        else 
            M_ControlBlock->isEven = false;
        memset(buffer, 0, windowSize);
        memset(tempBuffer, 0, windowSize);
    }
}

/**
 * @brief  Gets The Median filtered data
 * @note   This works as Streaming
 * @param  M_ControlBlock: Pointer Of Library Handler
 * @param  value:          Next data value to be added
 * @retval Median filtered data
 */
DatatypeUsed
ssf_M_GetData(Median_t *M_ControlBlock, DatatypeUsed value)
{
    if (M_ControlBlock)
    {
        M_ControlBlock->Buffer[M_ControlBlock->Count] = value;
        memcpy(M_ControlBlock->TempBuffer, M_ControlBlock->Buffer, M_ControlBlock->Window * sizeof(DatatypeUsed));
        qsort(M_ControlBlock->TempBuffer, M_ControlBlock->Window, sizeof(DatatypeUsed), ssf_M_QSortFunction);

        if(M_ControlBlock->Count < (M_ControlBlock->Window - 1))
            M_ControlBlock->Count++;
        else
            M_ControlBlock->Count = 0;

        if (M_ControlBlock->FirstCounter < M_ControlBlock->Window)
        {
            M_ControlBlock->FirstCounter++;
            if(M_ControlBlock->FirstCounter % 2 == 0)
                return ((M_ControlBlock->TempBuffer[M_ControlBlock->FirstCounter / 2 - 1] + M_ControlBlock->TempBuffer[M_ControlBlock->FirstCounter / 2]) / 2);
            else
                return M_ControlBlock->TempBuffer[M_ControlBlock->FirstCounter / 2];
        }
        else
        {
            if(M_ControlBlock->isEven)
                return ((M_ControlBlock->TempBuffer[M_ControlBlock->Window / 2 - 1] + M_ControlBlock->TempBuffer[M_ControlBlock->Window / 2]) / 2);
            else
                return M_ControlBlock->TempBuffer[M_ControlBlock->Window / 2];
        }
    }
    return 0;
}

