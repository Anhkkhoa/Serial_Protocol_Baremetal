//UART Driver Source File
#include "uart.h"

void initUART (void) {
    RCC -> APB1ENR1 |= RCC_APB1ENR1_USART2EN;
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //Enable GPIOA

	//Pin PA2 Setup,TX
	GPIOA -> MODER &= ~(GPIO_MODER_MODER2); //Clear PA2
	GPIOA -> MODER |= (1<<5); // 10 for Alternate Function mode
	GPIOA -> AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos); //AF7 for TX
	//Pin PA3 Setup,RX
	GPIOA -> MODER &= ~(GPIO_MODER_MODER3); //Clear PA3, already 00 for input mode
	GPIOA -> MODER |= (2 << GPIO_MODER_MODE3_Pos); // 10 for Alternate Function mode
	GPIOA -> AFR[0] |= (7 << GPIO_AFRL_AFSEL3_Pos); //AF7 mode for RX

	//Setting up UART
	USART2 -> CR1 = 0x00000000; //Reset
	// USART2 -> CR1 = (1 << 28); //1 Start Bit, 8 data bit, n stop bits
	uint16_t uartdiv = 4000000 / 115200;
	USART2 -> BRR = (((uartdiv / 16) << USART_BRR_DIV_MANTISSA_Pos) | ((uartdiv % 16) << USART_BRR_DIV_FRACTION_Pos));

	//Enable Transmitter
	USART2 -> CR1 |= USART_CR1_TE;
	//Enable Receiver
	USART2 -> CR1 |= USART_CR1_RE;
	//Enable UART
	USART2 -> CR1 |= USART_CR1_UE;

    /*
	while (!(USART2->ISR & USART_ISR_TXE)) {}
	USART2 -> TDR = buffer[0];
	while (!(USART2->ISR & USART_ISR_TC)) {}

	while (!(USART2->ISR & USART_ISR_TXE)) {}
	USART2 -> TDR = RX_buffer[0];
	while (!(USART2->ISR & USART_ISR_TC)) {}
	*/

    /* 
    USART2->TDR = 'h';
    while (!(USART2 -> ISR & USART_ISR_RXNE));

	  RX_buffer[0] = USART2 -> RDR;

	  while (!(USART2->ISR & USART_ISR_TXE)) {}
	  USART2 -> TDR = RX_buffer[0];
	  while (!(USART2->ISR & USART_ISR_TC)) {}

	  HAL_Delay(100);
    */
}