/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

SPI_HandleTypeDef spi;

uint8_t spi_sendrecv(uint8_t byte)
{
	uint8_t answer;

	HAL_SPI_TransmitReceive(&spi, &byte, &answer, 1, HAL_MAX_DELAY);

	return answer;
}






int main(void)
{
	HAL_Init();

	__HAL_RCC_GPIOD_CLK_ENABLE();  //dioda
	__HAL_RCC_GPIOC_CLK_ENABLE();  //
	__HAL_RCC_SPI1_CLK_ENABLE();  //spi

	GPIO_InitTypeDef gpio;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pin = GPIO_PIN_5 | GPIO_PIN_7; // SCK, MOSI
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &gpio);


	gpio.Mode = GPIO_MODE_INPUT;
	gpio.Pin = GPIO_PIN_6; // MISO
	HAL_GPIO_Init(GPIOA, &gpio);

	gpio.Mode = GPIO_MODE_OUTPUT_PP;
	gpio.Pin = GPIO_PIN_0; // CS
	HAL_GPIO_Init(GPIOC, &gpio);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);

	SPI_HandleTypeDef spi;

	spi.Instance = SPI1;
	spi.Init.Mode = SPI_MODE_MASTER;
	spi.Init.NSS = SPI_NSS_SOFT;
	spi.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8; // 1MHz
	HAL_SPI_Init(&spi);

	__HAL_SPI_ENABLE(&spi);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,GPIO_PIN_RESET);
	spi_sendrecv(0x40);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,GPIO_PIN_RESET);

	while(1){

	}

}
