/**
 **********************************************************************************
 * @file   MovingAverageConfig.h
 * @author Ali Moallem (https://github.com/AliMoal)
 * @brief  
 *         Functionalities of the this file:
 *          + Adjust Configurations of Moving Average Library
 **********************************************************************************
 **/

// Define to prevent recursive inclusion ----------------------------------------- //
#ifndef __MOVING_AVERAGE_CONFIG_H__
#define __MOVING_AVERAGE_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

// User Configurations and Notes ------------------------------------------------- //
#define MovingAverage_Debug_Enable   // comment if you want to disable debug (depends on printf in stdio.h)
#define MovingAverage_UsingFloat     // comment if you want to use Double datatype, otherwise Float datatype will be used


#ifdef __cplusplus
}
#endif

#endif