/*
* File: w25q16jvssiq_private.h
* Created On: 2026-11-25 at 14:35
* Author: Andrea Rantin
* @brief: //TODO
*/

#ifndef W25Q16JVSSIQ_PRIVATE_H
#define W25Q16JVSSIQ_PRIVATE_H

/**
* @brief Definitions for commands handled by the flash chip as per the datasheet
* 
*/
#define W25Q16JVSSIQ_CMD_READ_JEDEC_ID  0x9F
#define W25Q16JVSSIQ_CMD_READ_UID       0x4B
#define W25Q16JVSSIQ_CMD_READ_STATUS_REG_1   0x01
#define W25Q16JVSSIQ_CMD_READ_STATUS_REG_2   0x31
#define W25Q16JVSSIQ_CMD_ENABLE_RST          0x66
#define W25Q16JVSSIQ_CMD_RESET_DEVICE        0x99

/**
* @brief Time in milliseconds that a read for the status register checks for a specific bit. If the bit is still wrong
* after this time, then a timeout error will be returned
* 
*/
#define W25Q16JVSSIQ_STATUS_REG1_POLL_BEFORE_RESET_TIMEOUT_MS    100

//TODO SICURAMENTE SERVIRA TIMEOUT PIU LUNGO PER PAGE PROGAM LUNGHI MA ANCHE PER FLASH ERASE, ETC

/**
* @brief Addresses/Commands for all "parts" of the status register
* 
*/
typedef enum {
    W25Q16JVSSIQ_STATUS_REG_1 = 0x05,
    W25Q16JVSSIQ_STATUS_REG_2 = 0x35,
    W25Q16JVSSIQ_STATUS_REG_3 = 0x15,
}W25Q16JVSSIQ_StatusReg;

/**
* @brief Bitmasks for specific bits of the status register
* 
*/
#define W25Q16JVSSIQ_STATUS_REG_1_BUSY_BIT  (0x01 << 0)
#define W25Q16JVSSIQ_STATUS_REG_1_SUS_BIT   (0x01 << 15)

#endif /* W25Q16JVSSIQ_PRIVATE_H */
