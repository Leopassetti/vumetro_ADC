#include <stdint.h>
#include "bsp/bsp.h"

/**
 * @brief Delay por software
 *
 * @param nCount Numero de ciclos del delay
 */
void Delay(volatile uint32_t nCount);

void vumetro(float posicion);



/**
 * @brief Aplicacion principal
 */
int main(void) {
	bsp_init();

	float posicion_obtenida;


	while (1) {

	posicion_obtenida =	get_posicion_giro();



	vumetro(posicion_obtenida);



	}
}

void vumetro(float posicion){

uint8_t i;

if(posicion < 1){

	for(i=0; i<8; i++)
		led_off(i);

}

if(posicion < 13 && posicion >= 1){
	for(i=0; i<1; i++ )
		led_on(i);
	for(i=1; i<8; i++)
		led_off(i);

}

if(posicion >= 13 && posicion < 26 ){
	for(i=0; i<2; i++ )
		led_on(i);
	for(i=2; i<8; i++)
		led_off(i);

}

if(posicion >= 26 && posicion < 39){
	for(i=0; i<3; i++ )
		led_on(i);
	for(i=3; i<8; i++)
		led_off(i);

}

if(posicion >= 39 && posicion < 52){
	for(i=0; i<4; i++ )
		led_on(i);
	for(i=4; i<8; i++)
		led_off(i);

}

if(posicion >= 52 && posicion < 65){
	for(i=0; i<5; i++ )
		led_on(i);
	for(i=5; i<8; i++)
		led_off(i);

}

if(posicion >= 65 && posicion < 78){
	for(i=0; i<6; i++ )
		led_on(i);
	for(i=6; i<8; i++)
		led_off(i);

}

if(posicion >= 78 && posicion < 91){
	for(i=0; i<7; i++ )
		led_on(i);
	for(i=7; i<8; i++)
		led_off(i);

}

if(posicion >= 91 && posicion <= 100){
	for(i=0; i<8; i++ )
		led_on(i);


}




}





void Delay(volatile uint32_t nCount) {
	while (nCount--) {
	}
}





