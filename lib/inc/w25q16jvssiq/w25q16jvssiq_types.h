/*
* File: w25q16jvssiq_types.h
* Created On: 2026-11-24 at 13:05
* Author: Andrea Rantin
* @brief: //TODO
*/

#ifndef W25Q16JVSSIQ_TYPES_H
#define W25Q16JVSSIQ_TYPES_H

#include <stdint.h>
#include <stdbool.h>

/**
* @brief Status code returned by all functions from the library.
*   A value of 0 corresponds to success while any other value must be considered as an error or warning
* 
*/
typedef enum {
    W25Q16JVSSIQ_OK = 0,
    W25Q16JVSSIQ_ERROR_NULL_NULL_CS_FUN,
    W25Q16JVSSIQ_ERROR_NULL_TX_FUN,
    W25Q16JVSSIQ_ERROR_NULL_RX_FUN,
    W25Q16JVSSIQ_ERROR_NULL_DELAY_FUN,
    W25Q16JVSSIQ_ERROR_NULL_SPI_CFG_STRUCT,
}W25Q16JVSSIQ_Status;

/**
* @brief Status code used for SPI operations. This is used to "adapt" and uniform all kinds of
*   HAL status codes from different vendors(For example instead of having to manage HAL_Status from STM32 or esp_err_t from
*   ESP32, this single enum must be returned from all SPI function "adapters" provided by the user(So for example instead of returning
*   HAL_Error when STM32 SPI transmit goes in error, they will return W25Q16JVSSIQ_SPI_ERROR)) 
* 
*/
typedef enum {
    W25Q16JVSSIQ_SPI_OK = 0,
    W25Q16JVSSIQ_SPI_ERROR,
    W25Q16JVSSIQ_SPI_BUSY,
    W25Q16JVSSIQ_SPI_TIMEOUT,
}W25Q16JVSSIQ_SpiStatus;

/**
* @brief Pointer to the function that controls the chip select pin for the flash. Note that as this flash is active LOW,
*   a value of true for selected means that the CS Pin will being pulled LOW, and a value of false means that the CS Pin will be
*   pulled high 
* @param selected: If true pulls the CS pin LOW, otherwise pulls it HIGH
* 
*/
typedef void (*ChipSelect_Fun)(bool selected);

/**
* @brief Pointer to the function that transmits via SPI.
* @param txData: Pointer to the data to transmit
* @param length: Number of bytes to transmit
*
* @return Returns a @ref W25Q16JVSSIQ_SpiStatus depending on how the user implements this. Note that this is the users responsibility
* to make sure that the transmit was successful before returning a successful status(If possible)
*/
typedef W25Q16JVSSIQ_SpiStatus (*SpiTransmit_Fun)(uint8_t* txData, uint16_t length);

/**
* @brief Pointer to the function that receives via SPI.
* @param rxData: Pointer to the data to receive
* @param length: Number of bytes to receive
* 
* @return Returns a @ref W25Q16JVSSIQ_SpiStatus depending on how the user implements this. Note that this is the users responsibility
* to make sure that the transmit was successful before returning a successful status(If possible)
*/
typedef W25Q16JVSSIQ_SpiStatus (*SpiReceive_Fun)(uint8_t* rxData, uint16_t length);

/**
* @brief Pointer to a function that delays execution of the code.
* @param delay: Delay in milliseconds
*/
typedef void (*DelayFun)(uint32_t delay);

/**
* @brief Structure that contains all the function pointers needed by the library to work
* 
*/
typedef struct {
    ChipSelect_Fun chipSelect_Fun; /*!< Pointer to the function that controls the chip select pin for the flash.*/
    SpiTransmit_Fun spiTransmit_Fun; /*< Pointer to the function that transmits via SPI.*/
    SpiReceive_Fun spiReceive_Fun; /*< Pointer to the function that receives via SPI.*/
    DelayFun delay_Fun; /*< Pointer to a function that delays execution of the code.*/
}W25Q16JVSSIQ_SpiConfig_Struct;

#endif /* W25Q16JVSSIQ_TYPES_H */
