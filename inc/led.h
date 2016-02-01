#include "stm32f0xx_rcc.h"
#include "stm32f0xx_gpio.h"

struct led {
	uint32_t	gpio_rcc;
	GPIO_TypeDef	*gpio;
	uint16_t	pin;
};

void led_init(struct led *);
void led_on(struct led *);
void led_off(struct led *);
void led_toggle(struct led *);
