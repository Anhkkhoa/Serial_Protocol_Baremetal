#include "stm32l476xx.h"
/*
SPI Header Source File
PA4 - SPI1 Chip Selection
PA5 - SPI1 SCK
PA6 - SPI1 MISO
PA7 - SPI1 MOSI

W25Q16 Clock behavior: addresses or data to the device on the rising edge of CLK. The DO output pin is used to read data or status from the device on the falling edge of CLK. 
*/

void initSPI1() {
    //GPIOA SPI pin Initlize
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enable bit 0 for GPIOA EN

    //SPI Peripheral Clock Initilize
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Enable bit 12 for SPI1 EN

    //Pin Alternate Mode
    GPIOA->MODER &=    ~(GPIO_MODER_MODE4_Msk
                        |GPIO_MODER_MODE5_Msk
                        |GPIO_MODER_MODE6_Msk
                        |GPIO_MODER_MODE7_Msk); // Clearing MODER Bit PA4, PA5, PA6, PA7
    GPIOA->MODER |=     ((2u << GPIO_MODER_MODE4_Pos)
                        |(2u << GPIO_MODER_MODE5_Pos)
                        |(2u << GPIO_MODER_MODE6_Pos)
                        |(2u << GPIO_MODER_MODE7_Pos)); // Alternate Function for PA4, PA5, PA6, PA7

    //Alternate Function Mode Selection (SPI1 AF5) 
    GPIOA->AFR[0] &=   ~(GPIO_AFRL_AFSEL4_Msk
                        |GPIO_AFRL_AFSEL5_Msk
                        |GPIO_AFRL_AFSEL6_Msk
                        |GPIO_AFRL_AFSEL7_Msk); // Access AF Lower Register, Clear all SPI AF mode bit
    GPIOA->AFR[0] |=    ((5u << GPIO_AFRL_AFSEL4_Pos)
                        |(5u << GPIO_AFRL_AFSEL5_Pos)
                        |(5u << GPIO_AFRL_AFSEL6_Pos)
                        |(5u << GPIO_AFRL_AFSEL7_Pos)); //Setting to AF5
}

void configSPI1() {
    //Disable SPI Peripheral to config
    SPI1->CR1 &= ~((1u << 6));

    //SPI Control Register 1
    SPI1->CR1 &=   ~((1u << 15) //Two line unidirectional
                    |(1u << 13) //Disable CRC
                    |(1u << 10) //Full Duplex Mode
                    |(1u << 9) //Hardware NSS management
                    |(7u << 3) //Clear Baud Rate Control Bit
                    |(1u << 1) // Clock to 0 when idle
                    |(1u << 0)); // Shift out data when on first clock transition

    SPI1->CR1 |=    ((1u << 3) //Baudrate fpclk/4 => 4MHz/4 = 1MHz; W25Q16 can handle up to 133MHz
                    |(1u << 2)); //Master Mode

    //SPI Control Register 2
    SPI1->CR2 &=   ~((1u << 7) // TXE interrupt masked
                    |(1u << 6) // RXE interrupt masked
                    |(1u << 5) // Error Interupt masket
                    |(1u << 4) // Motorola Frame Format
                    |(1u << 3) // No NSS Pulse
                    |(1u << 1) | (1u << 0)); // TX & RX Buffer DMA disable

    SPI1->CR2 |=    ((1u << 12) //RXNE event when FIFO level larger than 8-bit
                    |(6u << 10) // 7-bit SPI Transfer
                    |(1u << 2)); //SS output enable for master 

    //Enable SPI Peripheral
    SPI1->CR1 |= ((1u << 6));
}



