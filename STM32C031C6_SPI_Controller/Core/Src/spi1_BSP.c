#include "spi1_BSP.h"

void initSPI1(void)
{

	/***Setting up GPIO Pins to SPI ******/

	//MOSI(PA7),MISO(PA6), SCK(PA5), NSS(PB0)

	// Enable GPIOA/B clocks
	SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);
	SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOBEN);


	//Set to Alternate Function Zero for MOSI, MISO, & SCK
	CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE5 | GPIO_MODER_MODE6 | GPIO_MODER_MODE7);
	SET_BIT(GPIOA->MODER, GPIO_MODER_MODE5_1 | GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);

	CLEAR_BIT(GPIOA->AFR[0], GPIO_AFRL_AFSEL5 | GPIO_AFRL_AFSEL6 | GPIO_AFRL_AFSEL7);

	CLEAR_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED5 |GPIO_OSPEEDR_OSPEED6 | GPIO_OSPEEDR_OSPEED7);
	SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED5_0 |GPIO_OSPEEDR_OSPEED6_0 | GPIO_OSPEEDR_OSPEED7_0);

	//NSS(PB0) will be manually driven to low: output, push-pull,low speed, no pull up/down
	CLEAR_BIT(GPIOB->MODER, GPIO_MODER_MODE0);
	SET_BIT(GPIOB->MODER, GPIO_MODER_MODE0_0);

	CLEAR_BIT(GPIOB->OTYPER,GPIO_OTYPER_OT0);

	CLEAR_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED0);
	SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED0_0);

	CLEAR_BIT(GPIOB->PUPDR, GPIO_PUPDR_PUPD0);

	//Set NSS to default high
	GPIOB->BSRR = GPIO_BSRR_BS0;


	/***********Configuring SPI CR1 *******************/
	// Enable SPI 1 Clock
	SET_BIT(RCC->APBENR2, RCC_APBENR2_SPI1EN);

	//Set baud rate to 750,000 Hz for Arduino
	CLEAR_BIT(SPI1->CR1,SPI_CR1_BR);
	SET_BIT(SPI1->CR1,SPI_CR1_BR_0 | SPI_CR1_BR_2);

	//Set clock polarity to 0, clock phase to 0
	CLEAR_BIT(SPI1->CR1, SPI_CR1_CPOL);
	CLEAR_BIT(SPI1->CR1, SPI_CR1_CPHA);

	//Set to Full Duplex Mode
	CLEAR_BIT(SPI1->CR1, SPI_CR1_RXONLY);

	//Frame format set to MSB first and 8 bits
	CLEAR_BIT(SPI1->CR1, SPI_CR1_LSBFIRST);

	//software slave Select pin management
	SET_BIT(SPI1->CR1, SPI_CR1_SSM);
	SET_BIT(SPI1->CR1, SPI_CR1_SSI);

	//Configure as Master
	SET_BIT(SPI1->CR1, SPI_CR1_MSTR);

	/***********Configuring SPI CR2 *******************/
	//Configure data length for transfer
	CLEAR_BIT(SPI1->CR2, SPI_CR2_DS);
	SET_BIT(SPI1->CR2, SPI_CR2_DS_0 |SPI_CR2_DS_1 | SPI_CR2_DS_2);

	//Set FIFO threshold to 8 bits
	SET_BIT(SPI1->CR2, SPI_CR2_FRXTH);

	//Enable the SPI, Arduino SPI should be enabled before this
	SET_BIT(SPI1->CR1, SPI_CR1_SPE);

}


uint8_t spi1_TransferAndRead(uint8_t data)
{
    // Assert NSS low
    GPIOB->BSRR = GPIO_BSRR_BR0;

    // Wait until TX buffer empty
    while(!(SPI1->SR & SPI_SR_TXE))
        ;
    // Send byte
    *((__IO uint8_t *)&SPI1->DR) = data;

    // Wait for RX buffer to contain received byte
    while(!(SPI1->SR & SPI_SR_RXNE))
        ;

    // Read the received byte
   uint8_t received = *((__IO uint8_t *)&SPI1->DR);

    // Wait until SPI is not busy
   while(SPI1->SR & SPI_SR_BSY)
        ;


    // Release NSS high
   GPIOB->BSRR = GPIO_BSRR_BS0;

    return received;
}


void SPI_Transmit(uint8_t data)
{
		// Assert NSS low
	    GPIOB->BSRR = GPIO_BSRR_BR0;

	    // Wait until TX buffer empty
	    while(!(SPI1->SR & SPI_SR_TXE))
	        ;
	    // Send byte
	    SPI1->DR = data;

	   // Wait until TX buffer empty
	   while(!(SPI1->SR & SPI_SR_TXE))
	    	;
	    // Wait until SPI is not busy
	    while(SPI1->SR & SPI_SR_BSY)
	    	;

	    //Perform a dummy read to clear the data register and read the SPI SR register to clear overrun
	    uint16_t temp = SPI1->DR;
	    temp = SPI1->SR;

	    // Release NSS high
	   GPIOB->BSRR = GPIO_BSRR_BS0;
}

uint8_t SPI_Receive(void)
{
	uint8_t data;

	// Assert NSS low
    GPIOB->BSRR = GPIO_BSRR_BR0;

   // Wait until transmit buffer is empty
   while (!(SPI1->SR & SPI_SR_TXE))
        ;

	// Wait until SPI is not busy
	while(SPI1->SR & SPI_SR_BSY)
		;

	// Send dummy byte to generate clock
	*((uint8_t *)&SPI1->DR) = 0xFF;  // use 8-bit access to DR

    // Wait for RX buffer to contain received byte
    while(!(SPI1->SR & SPI_SR_RXNE))
        ;

    // Read received data
    data = *((uint8_t *) &SPI1->DR);

    // Release NSS high
   GPIOB->BSRR = GPIO_BSRR_BS0;

   return data;
}

