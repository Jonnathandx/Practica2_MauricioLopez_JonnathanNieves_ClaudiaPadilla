/**
 * Práctica 2 Control Digital
 */
#include "Arduino.h"
#include "semaforo.h"
#include "teclas.h"
#include "uart.h"

extern dbn_t *teclasMEF;
extern int16_t leds[3];

uint16_t tiempo = 200;
int16_t longitudLeds = sizeof(leds)/sizeof(int16_t);
int16_t longitudPsh = sizeof(teclasMEF->psh)/sizeof(int16_t);

void setup()
{
  for(int16_t j = 0; j < longitudLeds; j++)
    pinMode(leds[j], OUTPUT);
  for(int16_t j = 0; j < longitudPsh; j++)
    pinMode(teclasMEF->psh[j], INPUT);

  Serial.begin(9600);
}

void loop()
{
	funciones funcion;
	imprimir Datos;
	funcion.initializeFSM(teclasMEF);
	while(1)
	{
		funcion.updateFSM(teclasMEF);
		if((updateFSMSem()%100) == 0)
			  Datos.imprimirDatos();
	}
}

