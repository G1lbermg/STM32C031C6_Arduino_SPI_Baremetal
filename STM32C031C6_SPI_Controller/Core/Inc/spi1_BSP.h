#ifndef SPI_1_BSP_H
#define SPI_1_BSP_H

#include <stdint.h>
#include "error_codes.h"
#include "stm32c0xx.h"

ErrorCode_t initCtrl_SPI1(void);
ErrorCode_t exchangeByteCtrl_Spi1(uint8_t transmitData, uint8_t *readData);

#endif

