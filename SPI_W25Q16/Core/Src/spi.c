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
    RCC->AHB2ENR |= (1u << 0); //Enable bit 0 for GPIOA EN

    //SPI Peripheral Clock Initilize
    RCC->APB2ENR |= (1u << 12); // Enable bit 12 for SPI1 EN

    //Pin Alternate Mode
    GPIOA->MODER &= ~((3u << (2 * 4)) | (3u << (2 * 5)) | (3u << (2 * 6)) | (3u << (2 * 7))) // Clearing MODER Bit PA4, PA5, PA6, PA7 with Analog Mode (Reset State)
    GPIOA->MODER |= ((2u << (2 * 4)) | (2u << (2 * 5)) | (2u << (2 * 6)) | (2u << (2 * 7))) // Alternate Function for PA4, PA5, PA6, PA7

    //Alternate Function Mode Selection (SPI1 AF5) 
    GPIOA->AFR[0] &= ~((15u << (4 * 4)) | (15u << (4 * 5)) | (15u << (4 * 6)) | (15u << (4 * 7))); // Access AF Lower Register, Clear all SPI AF mode bit
    GPIOA->AFR[0] |= ((5u << (4 * 4)) | (5u << (4 * 5)) | (5u << (4 * 6)) | (5u << (4 * 7))); //Setting to AF5
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

    //Enable SPI Peripheral
    SPI1->CR1 |= ((1u << 6));
}

