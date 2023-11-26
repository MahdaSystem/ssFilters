/**
 **********************************************************************************
 * @file   MovingAverage.h
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief  
 *         Functionalities of the this file:
 *          + Getting Moving Average filtered data
 **********************************************************************************
 **/

// Define to prevent recursive inclusion ----------------------------------------- //
#ifndef __MOVING_AVERAGE_H__
#define __MOVING_AVERAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

// Includes ---------------------------------------------------------------------- //
#include <stdint.h>
#include <string.h>
#include "MovingAverageConfig.h" 

// DO NOT USE OR EDIT THIS BLOCK ------------------------------------------------- //
#ifdef MovingAverage_UsingFloat
#define MovingAverage_DatatypeUsed    float
#else
#define MovingAverage_DatatypeUsed    double
#endif

// Public Typedefs --------------------------------------------------------------- //
/**
 * @brief  Handling Library
 * @note   DO NOT USE OR EDIT THIS, This struct will be handled by library 
 */
typedef struct
MovingAverage_s
{
    MovingAverage_DatatypeUsed *Buffer;
    MovingAverage_DatatypeUsed Sum;
    uint16_t Count;
    uint16_t Window;
    uint16_t divideCounter;
} MovingAverage_t;

// Public Functions --------------------------------------------------------------- //
/**
 * @brief  Initializes The Library
 * @note   Must be called at first and once
 * @param  MA_ControlBlock: Pointer Of Library Handler
 * @param  windowSize:      Window Size        
 * @param  buffer:          Pointer Of window buffer | Number of Element: At least windowSize
 * @retval None
 */
void
ssf_MA_Init(MovingAverage_t *MA_ControlBlock, uint16_t windowSize, MovingAverage_DatatypeUsed *buffer);

/**
 * @brief  Gets The Moving Average filtered data
 * @note   This works as Streaming
 * @param  MA_ControlBlock: Pointer Of Library Handler
 * @param  value:           Next data value to be added
 * @retval Moving Average filtered data
 */
MovingAverage_DatatypeUsed
ssf_MA_GetData(MovingAverage_t *MA_ControlBlock, MovingAverage_DatatypeUsed value);

#ifdef __cplusplus
}
#endif

#endif
