/**
 **********************************************************************************
 * @file   Median.h
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief  
 *         Functionalities of the this file:
 *          + Getting Median filtered data
 **********************************************************************************
 **/

// Define to prevent recursive inclusion ----------------------------------------- //
#ifndef __MEDIAN_H_
#define __MEDIAN_H_

#ifdef __cplusplus
extern "C" {
#endif

// Includes ---------------------------------------------------------------------- //
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "MedianConfig.h"

// DO NOT USE OR EDIT THIS BLOCK ------------------------------------------------- //
#ifdef Median_UsingFloat
#define Median_DatatypeUsed    float
#else
#define Median_DatatypeUsed    double
#endif
// ------------------------------------------------------------------------------- //

// Public Typedefs --------------------------------------------------------------- //
/**
 * @brief  Handling Library
 * @note   DO NOT USE OR EDIT THIS, This struct will be handled by library 
 */
typedef struct
Median_s
{
    Median_DatatypeUsed *Buffer;
    Median_DatatypeUsed *TempBuffer;
    uint16_t Count;
    uint16_t Window;
    uint16_t FirstCounter;
    bool isEven;
    void (* SortMAXtoMIN)(Median_DatatypeUsed *, const int16_t, const int16_t);
} Median_t;

// Public Functions --------------------------------------------------------------- //
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
ssf_M_Init(Median_t *M_ControlBlock, uint16_t windowSize, Median_DatatypeUsed *buffer, Median_DatatypeUsed *tempBuffer, void (* SortFuncMAXtoMIN)(Median_DatatypeUsed *ArrToSort, const int16_t LowIDX, const int16_t HighIDX));

/**
 * @brief  Gets The Median filtered data
 * @note   This works as Streaming
 * @param  M_ControlBlock: Pointer Of Library Handler
 * @param  value:          Next data value to be added
 * @retval Median filtered data
 */
Median_DatatypeUsed
ssf_M_GetData(Median_t *M_ControlBlock, Median_DatatypeUsed value);

/**
 * @brief  Sorts data from Maximum to Minimum (Quick Sort: Descending order) - Recommended
 * @note   You can use it as sort function. For more Information see http://www.liangshunet.com/en/202007/153509174.htm
 * @param  arr:   Pointer Of array to sort
 * @param  left:  The lowest index to sort
 * @param  right: The highest index to sort
 * @retval None
 */
void 
QuickSort(float *arr, int16_t left, int16_t right);

#ifdef __cplusplus
}
#endif

#endif
