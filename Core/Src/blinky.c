#include "blinky.h"

void initBlinky (void) {
    RCC->AHB2ENR |= 0x01;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

	GPIOA->MODER &= ~(GPIO_MODER_MODER5); //Clear
	GPIOA->MODER |= (1 << 10);

    /*
    //Turn on
    GPIOA->BSRR = (1 << 5);
    HAL_Delay(1000);
    //Turn off
    GPIOA->BSRR = (1 << 21);
    HAL_Delay(1000);
    */
}