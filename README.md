# SPI Communication
## STM32 NUCLEO-C031C6 to Arduino Bare-Metal Implementation

This repository demonstrates a bare-metal C implementation of SPI communication between an STM32 Nucleo-C031C6 (Controller) and Arduino Uno (Peripheral). The Nucleo sends the Arduino a number, and in response, the Arduino returns the same number added by 10. For the Nucleo, STM32's CubeMX is used to configure SWD/debug and clock initialization. All GPIO,timer, USART, and SPI manipulation are performed via direct memory-mapped register access. Similarly for the Arduino, all SPI parameters are configured using direct memory-mapped register access. The Arduino library is only used to initialize and utilize the serial port.

### Wiring
<img width="2020" height="1132" alt="Nucleo to Arduino SPI" src="https://github.com/user-attachments/assets/3b2b0274-fee7-4450-a2f8-699ae85148d1" />

---

### ⚡ 5V to 3.3V Bi-directional Logic Converter
* **Nucleo Side (Low Voltage):**
  * 3V3/GND leads connected to **LV** / **GND** respectively.
  * SCK (PA5) connected to **LV1**.
  * MISO/CIPO (PA6) connected to **LV2**.
  * MOSI/COPI (PA7) connected to **LV3**.
  * NSS (PB0) connected to **LV4**.
* **Arduino Side (High Voltage):**
  * 5V/GND leads connected to **HV** / **GND** respectively.
  * SCK (PB5) connected to **HV1**.
  * MISO/CIPO (PB4) connected to **HV2**.
  * MOSI/COPI (PB3) connected to **HV3**.
  * SS (PB2) connected to **HV4**.

---

### 🔵 STM32 Nucleo Setup

| Category | Details |
| :--- | :--- |
| **Hardware** | NUCLEO-C031C6 (ARM Cortex-M0+) |
| **Debugger** | ST-LINK V2-1 (SWD interface) |
| **IDE** | STM32CubeIDE 2.0.0 |
| **Toolchain** | GNU Tools for STM32 (13.3.rel1) |
| **Libraries** | STM32 LL, CMSIS STM32C0xx, CMSIS STM32C031xx |

#### How to Run
1. **Import:** Import the "STM32C031C6_SPI_Controller" sub-folder as an STM32CubeIDE project.
2. **Setup (Optional):** Review and adjust the error handler logging and error indicator settings within `error_check_utilities.h`.
3. **Build:** Select **Project > Build Project**.
4. **Flash:** Use the **Run** or **Debug** icons.
5. **Run:**
    * Ensure that the Arduino has been initialized before the Nucleo. Otherwise, reset the Nucleo using the reset button on the board.
    * Open serial terminal and set to **9600 Baud**.
    * Observe the controller transmitting a number to the Arduino and receiving a response. Due to the nature of SPI the response by the Arduino
      is behind by one cycle with respect to the Nucleo. 

---

### 🟢 Arduino Uno Setup

| Category | Details |
| :--- | :--- |
| **Hardware** | Arduino Uno R3 (Atmega 328p) |
| **IDE** | Visual Studio Code + PlatformIO |
| **Toolchain** | avr-gcc, AVR Dude (via PlatformIO) |
| **Libraries** | Arduino.h (Used for Serial UART) |

#### How to Run
1. **Open Folder:** Select **File > Open Folder**, then select the "Arduino_SPI_Periph" folder.
2. **Build:** Select **PlatformIO: Build**.
3. **Flash:** Select **PlatformIO: Upload**.
4. **Run:**
    * Open serial terminal and set to **9600 Baud**.
    * Observe the Arduino receiving a number from the controller and transmitting a response. Due to the nature of SPI the response by the Arduino
      is behind by one cycle with respect to the Nucleo. 
