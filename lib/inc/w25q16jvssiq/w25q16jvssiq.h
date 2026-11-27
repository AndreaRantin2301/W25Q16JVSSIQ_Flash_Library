/*
* File: w25q16jvssiq.h
* Created On: 2026-11-24 at 11:29
* Author: Andrea Rantin
* @brief: //TODO
*/

#ifndef W25Q16JVSSIQ_H
#define W25Q16JVSSIQ_H

#include "w25q16jvssiq_types.h"
#include <w25q16jvssiq/w25q16jvssiq_types.h>

/**
* @brief Sets all the SPI functions needed by the library from the provided structure.
*
* @param spiCfgStruct Structure containing the pointers to all SPI functions. This function MUST be called before
* any other function from this library to ensure a correct behaviour
* @return W25Q16JVSSIQ_Status This function can return the following values:
*   - W25Q16JVSSIQ_ERROR_NULL_SPI_CFG_STRUCT If the provided spiCfgStruct is NULL
*   - W25Q16JVSSIQ_ERROR_NULL_NULL_CS_FUN If the provided chipSelect_Fun from the structure is NULL
*   - W25Q16JVSSIQ_ERROR_NULL_TX_FUN If the provided spiTransmit_Fun from the structure is NULL
*   - W25Q16JVSSIQ_ERROR_NULL_RX_FUN If the provided spiReceive_Fun from the structure is NULL
*   - W25Q16JVSSIQ_ERROR_NULL_DELAY_FUN If the provided delay_Fun from the structure is NULL
*   - W25Q16JVSSIQ_OK If everything was successful
* @note It is the user's responsibility to make sure that the functions that he passes with the struct are correct for
* controlling the CS and Writing/Reading to/from the SPI, the library can only check the return code of those functions(Wich is of 
* type @ref W25Q16JVSSIQ_SpiStatus) to check if the function completed correctly.
*/
W25Q16JVSSIQ_Status W25Q16JVSSIQ_Config_SpiFunctions(const W25Q16JVSSIQ_SpiConfig_Struct * spiCfgStruct);

/**
* @brief Reads the manufacturer(Jedec) and device identification id from the flash
* 
* @param deviceIdentificationStruct Pointer to a @ref W25Q16JVSSIQ_DeviceIdentification structure that will be filled with the
* read data
* @return W25Q16JVSSIQ_Status This function can return the following values:
*   - W25Q16JVSSIQ_ERROR_NULL_IDENTIFICATION_STRUCT If the provided pointer to the structure is NULL
*   - W25Q16JVSSIQ_ERROR_WRITE_INSTRUCTION If there was a SPI error while writing to the flash
*   - W25Q16JVSSIQ_ERROR_READ_JEDEC_ID If there was a SPI error while reading from the flash
*   - W25Q16JVSSIQ_OK If everything completed successfully
*/
W25Q16JVSSIQ_Status W25Q16JVSSIQ_Read_DeviceIdentification(W25Q16JVSSIQ_DeviceIdentification *deviceIdentificationStruct);

/**
* @brief Reads the device unique id from the flash
* 
* @param uidStruct Pointer to a @ref W25Q16JVSSIQ_UniqueId structure that will be filled with the read uid
* @return W25Q16JVSSIQ_Status This function can return the following values:
*   - W25Q16JVSSIQ_ERROR_NULL_UID_STRUCT If the provided pointer to the structure is NULL
*   - W25Q16JVSSIQ_ERROR_READ_UID If there was a SPI error while reading the uid
*   - W25Q16JVSSIQ_OK If everything completed successfully
*/
W25Q16JVSSIQ_Status W25Q16JVSSIQ_Read_UniqueId(W25Q16JVSSIQ_UniqueId *uidStruct);

/**
* @brief Performs a software reset of the flash chip
*
* @note That a software reset requires the flash to not be BUSY or SUSPENDED before invoking the reset operation.
* this functions checks for that, but it's always advised to make sure that the reset operation is not invoked during writes/erases
* or other operations
* 
* @return W25Q16JVSSIQ_Status This function can return the following values_
*   - W25Q16JVSSIQ_ERROR_NULL_READ_VALUE If there was a problem while reading the status register(This error should never actually happen)
*   - W25Q16JVSSIQ_ERROR_WRITE_INSTRUCTION If there was a problem while sending the ENABLE_RESET or RESET instruction
*   - W25Q16JVSSIQ_ERROR_READ_REGISTER8 If there was a problem while reading the status register
*   - W25Q16JVSSIQ_ERROR_STATUS_REG1_TIMEOUT If the flash was either BUSY or SUSPENDED
*   - W25Q16JVSSIQ_OK If everything completed correctly
*/
W25Q16JVSSIQ_Status W25Q16JVSSIQ_ResetChip(void);

#endif /* W25Q16JVSSIQ_H */
