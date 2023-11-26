/**
 **********************************************************************************
 * @file   Median.c
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief
 *         Functionalities of the this file:
 *          + Getting Median filtered data
 **********************************************************************************
 **/

// Private Includes -------------------------------------------------------------- //
#include "Median.h"

// Others ------------------------------------------------------------------------ //
#ifdef Median_Debug_Enable
#include <stdio.h> // for debug
#define PROGRAMLOG(arg...) printf(arg)
#else
#define PROGRAMLOG(arg...)
#endif

// Public Functions -------------------------------------------------------------- //

void ssf_M_Init(Median_t *M_ControlBlock, uint16_t windowSize, Median_DatatypeUsed *buffer, Median_DatatypeUsed *tempBuffer, void (*SortFuncMAXtoMIN)(Median_DatatypeUsed *ArrToSort, const int16_t LowIDX, const int16_t HighIDX))
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
        memset(buffer, 0, windowSize * sizeof(Median_DatatypeUsed));
        memset(tempBuffer, 0, windowSize * sizeof(Median_DatatypeUsed));
    }
}

Median_DatatypeUsed
ssf_M_GetData(Median_t *M_ControlBlock, Median_DatatypeUsed value)
{
    if (M_ControlBlock)
    {
        M_ControlBlock->Buffer[M_ControlBlock->Count] = value;
        memcpy(M_ControlBlock->TempBuffer, M_ControlBlock->Buffer, M_ControlBlock->Window * sizeof(Median_DatatypeUsed));
        M_ControlBlock->SortMAXtoMIN(M_ControlBlock->TempBuffer, 0, M_ControlBlock->FirstCounter);

        if (M_ControlBlock->Count < (M_ControlBlock->Window - 1))
            M_ControlBlock->Count++;
        else
            M_ControlBlock->Count = 0;

        if (M_ControlBlock->FirstCounter < M_ControlBlock->Window)
        {
            M_ControlBlock->FirstCounter++;
            if (M_ControlBlock->FirstCounter % 2 == 0)
                return ((M_ControlBlock->TempBuffer[M_ControlBlock->FirstCounter / 2 - 1] + M_ControlBlock->TempBuffer[M_ControlBlock->FirstCounter / 2]) / 2);
            else
                return M_ControlBlock->TempBuffer[M_ControlBlock->FirstCounter / 2];
        }
        else
        {
            if (M_ControlBlock->isEven)
                return ((M_ControlBlock->TempBuffer[M_ControlBlock->Window / 2 - 1] + M_ControlBlock->TempBuffer[M_ControlBlock->Window / 2]) / 2);
            else
                return M_ControlBlock->TempBuffer[M_ControlBlock->Window / 2];
        }
    }
    return 0;
}

void QuickSort(float *arr, int16_t left, int16_t right)
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
