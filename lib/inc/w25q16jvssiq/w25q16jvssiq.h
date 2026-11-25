/*
* File: w25q16jvssiq.h
* Created On: 2026-11-24 at 11:29
* Author: Andrea Rantin
* @brief: //TODO
*/

#ifndef W25Q16JVSSIQ_H
#define W25Q16JVSSIQ_H

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

#endif /* W25Q16JVSSIQ_H */
