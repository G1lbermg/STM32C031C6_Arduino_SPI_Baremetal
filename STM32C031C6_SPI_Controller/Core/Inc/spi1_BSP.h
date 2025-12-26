#ifndef SPI_1_BSP_H
#define SPI_1_BSP_H

#include <stdint.h>
#include "stm32c0xx.h"

void initSPI1(void);
void SPI_Transmit(uint8_t data);
uint8_t SPI_Receive(void);

uint8_t spi1_TransferAndRead(uint8_t data);


//void transmitSPI1(uint8_t byte);
//uint8_t receiveSPI1(void);

#endif

