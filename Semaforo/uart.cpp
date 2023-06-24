/*
 * uart.cpp
 *
 */

#include "Arduino.h"
#include "uart.h"
#include "semaforo.h"
#include "teclas.h"

void imprimirDatos()
{
	Serial.print("Cambios en antirreobote:");
	Serial.println(velocidad);
	Serial.print("Cambios en el orden del controlador:");
	Serial.println(estadoActualSem);
}


