#include <stdint.h>
#include "stm32f4xx.h"			// Header del micro
#include "stm32f4xx_gpio.h"		// Perifericos de E/S
#include "stm32f4xx_rcc.h"		// Para configurar el (Reset and clock controller)
#include "stm32f4xx_adc.h"		//Para configurar el adc
#include "stm32f4xx_syscfg.h"	// configuraciones Generales
#include "misc.h"				// Vectores de interrupciones (NVIC)
#include "bsp.h"


#define LED_D1 GPIO_Pin_0
#define LED_D2 GPIO_Pin_1
#define LED_D3 GPIO_Pin_2
#define LED_D4 GPIO_Pin_3
#define LED_D5 GPIO_Pin_6
#define LED_D6 GPIO_Pin_7
#define LED_D7 GPIO_Pin_10
#define LED_D8 GPIO_Pin_11

#define BOTON GPIO_Pin_0


/* Puertos de los leds disponibles */
GPIO_TypeDef* leds_port[] = { GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD, GPIOD  };
/* Leds disponibles */
const uint16_t leds[] = { LED_D1, LED_D2, LED_D3, LED_D4, LED_D5, LED_D6, LED_D7, LED_D8 };




void led_on(uint8_t led) {
	GPIO_SetBits(leds_port[led], leds[led]);
}

void led_off(uint8_t led) {
	GPIO_ResetBits(leds_port[led], leds[led]);
}

void led_toggle(uint8_t led) {
	GPIO_ToggleBits(leds_port[led], leds[led]);
}

uint8_t sw_getState(void) {
	return GPIO_ReadInputDataBit(GPIOA, BOTON);
}

float get_posicion_giro(void){

	uint16_t valor_adc;
	float valor_porcentaje;

	// Selecciono el canal a convertir
	ADC_RegularChannelConfig(ADC1, 12, 1, ADC_SampleTime_15Cycles);
	ADC_SoftwareStartConv(ADC1);

	// Espero a que la conversión termine
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET)
	        ;

	// Guardo el valor leido
	valor_adc =  ADC_GetConversionValue(ADC1);

	valor_porcentaje =((float)valor_adc * 100)/4095;

	return valor_porcentaje;


}



void bsp_led_init();
void bsp_adc_init();


void bsp_init() {
	bsp_led_init();
	bsp_adc_init();

}



/**
 * @brief Inicializa Leds
 */
void bsp_led_init() {
	GPIO_InitTypeDef GPIO_InitStruct;

	// Arranco el clock del periferico
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStruct.GPIO_Pin |= GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11;

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // (Push/Pull)
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/**
 * @brief Inicializa ADC
 */

void bsp_adc_init(){

	GPIO_InitTypeDef GPIO_InitStruct;
	ADC_CommonInitTypeDef ADC_CommonInitStruct;
	ADC_InitTypeDef ADC1_InitStruct;

	// Habilito los clock a los periféricos
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	// Configuro el pin en modo analógico
	GPIO_StructInit(&GPIO_InitStruct);              // Reseteo la estructura
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;      // Modo Analógico
	GPIO_Init(GPIOC, &GPIO_InitStruct);

	// Configuro el prescaler del ADC
	ADC_CommonStructInit(&ADC_CommonInitStruct);
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

	/* Configuro el ADC  */
	ADC_StructInit(&ADC1_InitStruct);
	ADC1_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC1_InitStruct);
	ADC_Cmd(ADC1, ENABLE);



}








