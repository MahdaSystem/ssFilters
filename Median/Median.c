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
 ** ==================================================================================
 **                           ##### Public Functions #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Initializes The Library
 * @note   Must be called at first and once
 * @param  M_ControlBlock:   Pointer Of Library Handler
 * @param  windowSize:       Window Size        
 * @param  buffer:           Pointer Of window buffer | Number of Element: At least windowSize
 * @param  tempBuffer:       Pointer Of window temp buffer | Number of Element: At least windowSize
 * @param  SortFuncMAXtoMIN  Pointer Of sorting function (From MAX[0] to MIN[NumOfEl - 1] | Descending order)
 *         @param ArrToSort: Pointer of array to sort
 *         @param LowIDX:    The lowest index to sort
 *         @param HighIDX:   The highest index to sort
 *         @note  You can pass it as NULL to use default function (QuickSort)
 * @retval None
 */
void
ssf_M_Init(Median_t *M_ControlBlock, uint16_t windowSize, DatatypeUsed *buffer, DatatypeUsed *tempBuffer, void (* SortFuncMAXtoMIN)(DatatypeUsed *ArrToSort, const int16_t LowIDX, const int16_t HighIDX))
{
    if (M_ControlBlock && buffer && tempBuffer && SortFuncMAXtoMIN)
    {
        M_ControlBlock->Count = 0;
        M_ControlBlock->FirstCounter = 0;
        M_ControlBlock->Window = windowSize ? windowSize : 1;
        M_ControlBlock->Buffer = buffer;
        M_ControlBlock->TempBuffer = tempBuffer;
        M_ControlBlock->SortMAXtoMIN = SortFuncMAXtoMIN;
        if (windowSize % 2 == 0)
            M_ControlBlock->isEven = true;
        else 
            M_ControlBlock->isEven = false;
        memset(buffer, 0, windowSize * sizeof(DatatypeUsed));
        memset(tempBuffer, 0, windowSize * sizeof(DatatypeUsed));
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
        M_ControlBlock->SortMAXtoMIN(M_ControlBlock->TempBuffer, 0, M_ControlBlock->Window - 1);

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

/**
 * @brief  Sorts data from Maximum to Minimum (Quick Sort: Descending order) - Recommended
 * @note   You can use it as sort function. For more Information see http://www.liangshunet.com/en/202007/153509174.htm
 * @param  arr:   Pointer Of array to sort
 * @param  left:  The lowest index to sort
 * @param  right: The highest index to sort
 * @retval None
 */
void 
QuickSort(float *arr, int16_t left, int16_t right)
{
    int16_t i = left;
    int16_t j = right;
    float temp = arr[i];

    if (left < right)
    {
        while (i < j)
        {
            while (arr[j] <= temp && i < j)
                j--;
            arr[i] = arr[j];

            while (arr[i] >= temp && i < j)
                i++;
            arr[j] = arr[i];

        }
        arr[i] = temp;

        QuickSort(arr, left, i - 1);
        QuickSort(arr, j + 1, right);
    }
}
