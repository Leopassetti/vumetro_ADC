#ifndef _BSP_H
#define _BSP_H

/**
 * @brief Prende un led
 *
 * @param led Led a prender
 */
void led_on(uint8_t led);

/**
 * @brief Apaga un led
 *
 * @param led Led a apagar
 */
void led_off(uint8_t led);

/**
 * @brief Delay por software
 */

void led_toggle(uint8_t led);
/**
 * @brief conmutar un led
 *
 * @param led Led a conmutar
 *
 */

uint8_t sw_getState();


void bsp_init();

/**
 * @brief Obtiene la posicion de giro
 *
 */
float get_posicion_giro();





#endif
