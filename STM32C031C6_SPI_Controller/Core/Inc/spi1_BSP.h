#ifndef SPI_1_BSP_H
#define SPI_1_BSP_H

#include "error_codes.h"
#include <stdint.h>
#include "stm32c0xx.h"

void initSPI1(void);

ErrorCode_t transmitAndRead_Spi1(uint8_t transmitData, uint8_t *readData);

#endif

