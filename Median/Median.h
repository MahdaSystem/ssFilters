/**
 **********************************************************************************
 * @file   Median.h
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

//* Define to prevent recursive inclusion ----------------------------------------- //
#ifndef MEDIAN_H
#define MEDIAN_H

#ifdef __cplusplus
extern "C" {
#endif

//* Includes ---------------------------------------------------------------------- //
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//? User Configurations and Notes ------------------------------------------------- //
#define Debug_Enable   // Uncomment if you want to use (depends on printf in stdio.h)
#define UsingFloat     // Uncomment if you want to use Float datatype, otherwise Double datatype will be used
//? ------------------------------------------------------------------------------- //

//! DO NOT USE OR EDIT THIS BLOCK ------------------------------------------------- //
#ifdef UsingFloat
#define DatatypeUsed    float
#else
#define DatatypeUsed    double
#endif
//! ------------------------------------------------------------------------------- //

/**
 ** ==================================================================================
 **                               ##### Structs #####                               
 ** ==================================================================================
 **/

/**
 * @brief  Handling Library
 * @note   DO NOT USE OR EDIT THIS, This struct will be handled by library 
 */
typedef struct
Median_s
{
    DatatypeUsed *Buffer;
    DatatypeUsed *TempBuffer;
    uint16_t Count;
    uint16_t Window;
    uint16_t FirstCounter;
    bool isEven;
} Median_t;

/**
 ** ==================================================================================
 **                          ##### Public Functions #####                               
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
ssf_M_Init(Median_t *M_ControlBlock, uint16_t windowSize, DatatypeUsed *buffer, DatatypeUsed *tempBuffer);

/**
 * @brief  Gets The Median filtered data
 * @note   This works as Streaming
 * @param  M_ControlBlock: Pointer Of Library Handler
 * @param  value:          Next data value to be added
 * @retval Median filtered data
 */
DatatypeUsed
ssf_M_GetData(Median_t *M_ControlBlock, DatatypeUsed value);

#ifdef __cplusplus
}
#endif

#endif
