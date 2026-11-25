/*
* File: example.c
* Created On: 2026-11-25 at 12:14
* Author: Andrea Rantin
* @brief: //TODO
*/
#include "spi.h"
#include "gpio.h"
#include <w25q16jvssiq/w25q16jvssiq.h>

//TODO
static void SPI_MoveFlashCS(bool selected) {
    if(selected) {
        HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_RESET);
    }else {
        HAL_GPIO_WritePin(FLASH_CS_GPIO_Port,FLASH_CS_Pin,GPIO_PIN_SET);
    }
}

//TODO
static W25Q16JVSSIQ_SpiStatus SPI_WriteToFlash(uint8_t *txBuf, uint16_t len) {

    if(txBuf == NULL) return W25Q16JVSSIQ_SPI_ERROR; 

    HAL_StatusTypeDef checkError = HAL_SPI_Transmit(&hspi2,txBuf,len,0xFF);

    switch(checkError) {
        case HAL_OK:
            return W25Q16JVSSIQ_SPI_OK;
        case HAL_BUSY:
            return W25Q16JVSSIQ_SPI_BUSY;
        case HAL_TIMEOUT:
            return W25Q16JVSSIQ_SPI_TIMEOUT;
        default:
            return W25Q16JVSSIQ_SPI_ERROR;
    }

    return W25Q16JVSSIQ_SPI_ERROR;
}

//TODO
static W25Q16JVSSIQ_SpiStatus SPI_ReadFromFlash(uint8_t *rxBuf, uint16_t len) {

    if(rxBuf == NULL)  return W25Q16JVSSIQ_SPI_ERROR;

    HAL_StatusTypeDef checkError = HAL_SPI_Receive(&hspi2,rxBuf,len,0xFF);

        switch(checkError) {
        case HAL_OK:
            return W25Q16JVSSIQ_SPI_OK;
        case HAL_BUSY:
            return W25Q16JVSSIQ_SPI_BUSY;
        case HAL_TIMEOUT:
            return W25Q16JVSSIQ_SPI_TIMEOUT;
        default:
            return W25Q16JVSSIQ_SPI_ERROR;
    }

    return W25Q16JVSSIQ_SPI_ERROR;
}

void User_Setup(void) {

    W25Q16JVSSIQ_Status checkError = W25Q16JVSSIQ_OK;

   W25Q16JVSSIQ_SpiConfig_Struct spiCfgStruct = {0};

   spiCfgStruct.delay_Fun = HAL_Delay;
   spiCfgStruct.chipSelect_Fun = SPI_MoveFlashCS;
   spiCfgStruct.spiTransmit_Fun = SPI_WriteToFlash;
   spiCfgStruct.spiReceive_Fun = SPI_ReadFromFlash;

    checkError = W25Q16JVSSIQ_Config_SpiFunctions(&spiCfgStruct);
    if(checkError != W25Q16JVSSIQ_OK) {
        //Print error or do something here
    }
}
    

void User_Loop(void) {

}