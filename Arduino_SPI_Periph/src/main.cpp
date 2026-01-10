#include <Arduino.h>

void SPI_PeriphInit(void);
uint8_t SPI_PeriphReceiveAndTransmit(void);

void setup()
{
  //Initialize as a SPI Peripheral
  SPI_PeriphInit();

  //Initialize UART 
  Serial.begin(9600);
  Serial.println("Arduino init succesful!");
}

void loop()
{
  //Receive Data on SPI line
  uint8_t spiData = SPI_PeriphReceiveAndTransmit();

  //Transmit Received Data to console
  Serial.print("Arduino received: ");
  Serial.println(spiData);

}

uint8_t SPI_PeriphReceiveAndTransmit(void)
{

  while(!(SPSR & (1<< SPIF)))
    ;

  uint8_t byte = SPDR;

  SPDR = (byte + 10);

  return byte;
}

void SPI_PeriphInit(void)
{
  /****************SET UP GPIO pins*********************************/
  //PB5, PB3, PB2 forced by hardware to be an inputs when SPI enabled
  //PB4 to be defined by the software, therefore it will be defined as output

  DDRB |= (1<< DDB4);

/****************SET UP SPI************************/
  //Set Clock polarity and phase to zero
  SPCR &= ~ ((1<< CPOL) | (1<< CPHA));

  //Set data order to MSB first
  SPCR &= ~(1<< DORD);

  //Configure as a peripheral device
  SPCR &= ~(1<< MSTR);
 
  //Enable the SPI
  SPCR |= (1 << SPE);
}