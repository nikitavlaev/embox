/**
 * @file stm32_spi2.c
 * @brief
 * @author Denis Deryugin <deryugin.denis@gmail.com>
 * @version
 * @date 25.12.2019
 */

#include <string.h>
#include <drivers/spi.h>
#include <drivers/spi/stm32_spi_conf.h>

#include <embox/unit.h>

#include "stm32_spi.h"

EMBOX_UNIT_INIT(stm32_spi2_init);

static struct stm32_spi stm32_spi2 = {
	.nss_port = SPI2_NSS_GPIO_PORT,
	.nss_pin  = SPI2_NSS_PIN
};

static int stm32_spi2_init(void) {
	GPIO_InitTypeDef  GPIO_InitStruct;

	spi2_enable_gpio_clocks();
	spi2_enable_spi_clocks();

	stm32_spi_init(&stm32_spi2, SPI2);

	memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));
	GPIO_InitStruct.Pin       = SPI2_SCK_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_LOW;
	GPIO_InitStruct.Alternate = SPI2_SCK_AF;

	HAL_GPIO_Init(SPI2_SCK_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SPI2_MISO_PIN;
	GPIO_InitStruct.Alternate = SPI2_MISO_AF;

	HAL_GPIO_Init(SPI2_MISO_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SPI2_MOSI_PIN;
	GPIO_InitStruct.Alternate = SPI2_MOSI_AF;

	HAL_GPIO_Init(SPI2_MOSI_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = SPI2_NSS_PIN;
	GPIO_InitStruct.Alternate = SPI2_MOSI_AF;

	HAL_GPIO_Init(SPI2_NSS_GPIO_PORT, &GPIO_InitStruct);

	return 0;
}

SPI_DEV_DEF("STM32 SPI", &stm32_spi_ops, &stm32_spi2, 2);
