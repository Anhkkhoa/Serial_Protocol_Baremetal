#include "stm32l476xx.h"
#pragma once

void initSPI1(); //initialize SPI clock & Peripheral
void configSPI1(); //SPI setting
int8_t transferSPI(uint8_t tx_data); //Transmit and Receive SPI address and data byte