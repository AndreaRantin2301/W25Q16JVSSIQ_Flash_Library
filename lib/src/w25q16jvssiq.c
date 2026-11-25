/*
* File: w25q16jvssiq.c
* Created On: 2026-11-24 at 11:30
* Author: Andrea Rantin
* @brief: Implementation file for w25q16jvssiq.h
*/

#include <w25q16jvssiq/w25q16jvssiq.h>
#include <stddef.h>

/**
* @brief Structure of type @ref W25Q16JVSSIQ_SpiConfig_Struct that contains all the needed
* SPI function pointers. This is filled in W25Q16JVSSIQ_Config_SpiFunctions.
* 
*/
static W25Q16JVSSIQ_SpiConfig_Struct spiConfig = {0};

W25Q16JVSSIQ_Status W25Q16JVSSIQ_Config_SpiFunctions(const W25Q16JVSSIQ_SpiConfig_Struct * spiCfgStruct) {

    if(spiCfgStruct == NULL) return  W25Q16JVSSIQ_ERROR_NULL_SPI_CFG_STRUCT;

    if(spiCfgStruct->chipSelect_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_NULL_CS_FUN;
    if(spiCfgStruct->spiTransmit_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_TX_FUN;
    if(spiCfgStruct->spiReceive_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_RX_FUN;
    if(spiCfgStruct->delay_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_DELAY_FUN;

    spiConfig.chipSelect_Fun = spiCfgStruct->chipSelect_Fun;
    spiConfig.spiTransmit_Fun = spiCfgStruct->spiTransmit_Fun;
    spiConfig.spiReceive_Fun = spiCfgStruct->spiReceive_Fun;
    spiConfig.delay_Fun = spiCfgStruct->delay_Fun;

    return W25Q16JVSSIQ_OK;
}