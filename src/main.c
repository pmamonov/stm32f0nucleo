/*
 * COPYRIGHT 2014 STMicroelectronics
 *
 * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *        http://www.st.com/software_license_agreement_liberty_v2
 *
 * Unless required by applicable law or agreed to in writing, software 
 * distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "main.h"
#include "led.h"
#include "stm32f0xx_usart.h"

int main(void)
{
	volatile int i;
	GPIO_InitTypeDef gpio_init = {
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_Speed = GPIO_Speed_Level_2,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_NOPULL
	};
	USART_InitTypeDef usart_init = {
		.USART_BaudRate = 115200,
		.USART_WordLength = USART_WordLength_8b,
		.USART_Parity = USART_Parity_No,
		.USART_StopBits = USART_StopBits_1,
		.USART_HardwareFlowControl = USART_HardwareFlowControl_None,
		.USART_Mode = USART_Mode_Tx | USART_Mode_Rx
	};
	struct led ld2 = {
		.gpio_rcc = RCC_AHBPeriph_GPIOA,
		.gpio = GPIOA,
		.pin = GPIO_Pin_5,
	};

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	gpio_init.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA, &gpio_init);
	gpio_init.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA, &gpio_init);
	USART_Init(USART2, &usart_init);
	USART_Cmd(USART2, ENABLE);

	led_init(&ld2);
	led_on(&ld2);

	while (1) {
		i = 1000000;
		while (i--)
			;
		led_toggle(&ld2);
		USART_SendData(USART2, 'A');
	}
}

void assert_param()
{
}
