/*
* File: w25q16jvssiq.c
* Created On: 2026-11-24 at 11:30
* Author: Andrea Rantin
* @brief: Implementation file for w25q16jvssiq.h
*/

#include <w25q16jvssiq/w25q16jvssiq.h>
#include "w25q16jvssiq_private.h"
#include <stddef.h>

/**
* @brief Structure of type @ref W25Q16JVSSIQ_SpiConfig_Struct that contains all the needed
* SPI function pointers. This is filled in W25Q16JVSSIQ_Config_SpiFunctions.
* 
*/
static W25Q16JVSSIQ_SpiConfig_Struct spiConfig = {0};

//TODO
static W25Q16JVSSIQ_Status W25Q16JVSSIQ_Write_Instruction(uint8_t instruction, bool keepCsActive) {
    
    spiConfig.chipSelect_Fun(true);
    spiConfig.delay_Fun(1);

    W25Q16JVSSIQ_SpiStatus checkError = spiConfig.spiTransmit_Fun(&instruction, 1);
    if(checkError != W25Q16JVSSIQ_SPI_OK) {
        spiConfig.chipSelect_Fun(false);
        return W25Q16JVSSIQ_ERROR_WRITE_INSTRUCTION;
    }

    spiConfig.delay_Fun(1);
    if(!keepCsActive) {
        spiConfig.chipSelect_Fun(false);
    }
    return W25Q16JVSSIQ_OK;
}

//TODO
static W25Q16JVSSIQ_Status W25Q16JVSSIQ_Read_Reg8(uint8_t reg, uint8_t *readValue) {

    if(readValue == NULL) return W25Q16JVSSIQ_ERROR_NULL_READ_VALUE;

    W25Q16JVSSIQ_Status checkError = W25Q16JVSSIQ_Write_Instruction(reg,true);
    if(checkError != W25Q16JVSSIQ_OK) return checkError;

    W25Q16JVSSIQ_SpiStatus spiCheckError = spiConfig.spiReceive_Fun(readValue,1);
    if(spiCheckError != W25Q16JVSSIQ_SPI_OK) {
        spiConfig.chipSelect_Fun(false);
        return W25Q16JVSSIQ_ERROR_READ_REGISTER8;
    }

    spiConfig.chipSelect_Fun(false);
    spiConfig.delay_Fun(1);

    return W25Q16JVSSIQ_OK;
}

//TODO
static W25Q16JVSSIQ_Status W25Q16JVSSIQ_PollStatusReg_Bit(uint32_t bitMsk, uint8_t expectedValue, W25Q16JVSSIQ_StatusReg reg, uint32_t timeout) {

    uint8_t statusReg1 = 0;
    uint32_t startTick = spiConfig.getTick_Fun();
    uint8_t bitValue = 0;

    do{
        W25Q16JVSSIQ_Status checkError = W25Q16JVSSIQ_Read_Reg8(reg,&statusReg1);
        if(checkError != W25Q16JVSSIQ_OK) return checkError;
        uint32_t currentTick = spiConfig.getTick_Fun();
        if((currentTick - startTick) >= timeout) return W25Q16JVSSIQ_ERROR_STATUS_REG1_TIMEOUT;
        bitValue = (statusReg1 & bitMsk) != 0;
    }while((bitValue) != expectedValue);
    
    return W25Q16JVSSIQ_OK;
}

W25Q16JVSSIQ_Status W25Q16JVSSIQ_Config_SpiFunctions(const W25Q16JVSSIQ_SpiConfig_Struct * spiCfgStruct) {

    if(spiCfgStruct == NULL) return  W25Q16JVSSIQ_ERROR_NULL_SPI_CFG_STRUCT;

    if(spiCfgStruct->chipSelect_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_NULL_CS_FUN;
    if(spiCfgStruct->spiTransmit_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_TX_FUN;
    if(spiCfgStruct->spiReceive_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_RX_FUN;
    if(spiCfgStruct->delay_Fun == NULL) return  W25Q16JVSSIQ_ERROR_NULL_DELAY_FUN;
    if(spiCfgStruct->getTick_Fun == NULL) return W25Q16JVSSIQ_ERROR_NULL_GET_TICK_FUN;

    spiConfig.chipSelect_Fun = spiCfgStruct->chipSelect_Fun;
    spiConfig.spiTransmit_Fun = spiCfgStruct->spiTransmit_Fun;
    spiConfig.spiReceive_Fun = spiCfgStruct->spiReceive_Fun;
    spiConfig.delay_Fun = spiCfgStruct->delay_Fun;
    spiConfig.getTick_Fun = spiCfgStruct->getTick_Fun;

    return W25Q16JVSSIQ_OK;
}

W25Q16JVSSIQ_Status W25Q16JVSSIQ_Read_DeviceIdentification(W25Q16JVSSIQ_DeviceIdentification *deviceIdentificationStruct) {

    if(deviceIdentificationStruct == NULL) return W25Q16JVSSIQ_ERROR_NULL_IDENTIFICATION_STRUCT;

    W25Q16JVSSIQ_Status checkError = W25Q16JVSSIQ_Write_Instruction(W25Q16JVSSIQ_CMD_READ_JEDEC_ID,true);
    if(checkError != W25Q16JVSSIQ_OK) return checkError;

    uint8_t readBuf[3] = {0};

    W25Q16JVSSIQ_SpiStatus spiCheckError = spiConfig.spiReceive_Fun(readBuf,3);
    if(spiCheckError != W25Q16JVSSIQ_SPI_OK) {
        spiConfig.chipSelect_Fun(false);
        return W25Q16JVSSIQ_ERROR_READ_JEDEC_ID;
    }

    deviceIdentificationStruct->jedecId = readBuf[0];
    deviceIdentificationStruct->memoryType = readBuf[1];
    deviceIdentificationStruct->capacity = readBuf[2];

    spiConfig.chipSelect_Fun(false);
    spiConfig.delay_Fun(1);

    return W25Q16JVSSIQ_OK;
}

W25Q16JVSSIQ_Status W25Q16JVSSIQ_Read_UniqueId(W25Q16JVSSIQ_UniqueId *uidStruct) {

    if(uidStruct == NULL) return W25Q16JVSSIQ_ERROR_NULL_UID_STRUCT;

    uint8_t txBuf[5] = {0};

    txBuf[0] = W25Q16JVSSIQ_CMD_READ_UID;

    spiConfig.chipSelect_Fun(true);
    spiConfig.delay_Fun(1);

    W25Q16JVSSIQ_SpiStatus spiCheckError = spiConfig.spiTransmit_Fun(txBuf,5);
    if(spiCheckError != W25Q16JVSSIQ_SPI_OK) {
        spiConfig.chipSelect_Fun(false);
        return W25Q16JVSSIQ_ERROR_READ_UID;
    }

    spiCheckError = spiConfig.spiReceive_Fun(uidStruct->uid,8);
    if(spiCheckError != W25Q16JVSSIQ_SPI_OK) {
        spiConfig.chipSelect_Fun(false);
        return W25Q16JVSSIQ_ERROR_READ_UID;
    }

    spiConfig.chipSelect_Fun(false);
    spiConfig.delay_Fun(1);

    return W25Q16JVSSIQ_OK;
}

W25Q16JVSSIQ_Status W25Q16JVSSIQ_ResetChip(void) {

    W25Q16JVSSIQ_Status checkError = W25Q16JVSSIQ_PollStatusReg_Bit(W25Q16JVSSIQ_STATUS_REG_1_BUSY_BIT,0,W25Q16JVSSIQ_STATUS_REG_1,W25Q16JVSSIQ_STATUS_REG1_POLL_BEFORE_RESET_TIMEOUT_MS);
    if(checkError != W25Q16JVSSIQ_OK) return checkError;

    checkError = W25Q16JVSSIQ_PollStatusReg_Bit(W25Q16JVSSIQ_STATUS_REG_1_SUS_BIT,0,W25Q16JVSSIQ_STATUS_REG_2,W25Q16JVSSIQ_STATUS_REG1_POLL_BEFORE_RESET_TIMEOUT_MS);
    if(checkError != W25Q16JVSSIQ_OK) return checkError;

    checkError = W25Q16JVSSIQ_Write_Instruction(W25Q16JVSSIQ_CMD_ENABLE_RST,false);
    if(checkError != W25Q16JVSSIQ_OK) return checkError;

    checkError = W25Q16JVSSIQ_Write_Instruction(W25Q16JVSSIQ_CMD_RESET_DEVICE,false);
    if(checkError != W25Q16JVSSIQ_OK) return checkError;

    spiConfig.delay_Fun(1);
    return W25Q16JVSSIQ_OK;
}