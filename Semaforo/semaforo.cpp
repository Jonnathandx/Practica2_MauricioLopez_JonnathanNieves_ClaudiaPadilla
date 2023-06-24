/*
 * semaforo.c
 *
 */

#include "Arduino.h"
#include "semaforo.h"

extern int16_t longitudLeds;
void initializeFSMSem()
{
	estadoActualSem = normal;
}


int16_t updateFSMSem()
{
  static uint16_t k = 0;
  apagarLeds();
  switch(estadoActualSem)
  {
    case normal:
    	if(k < (float) multiplicador*3000)
    		digitalWrite(leds[0],HIGH);

    	else if(k > (float) multiplicador*3000 || k < (float) multiplicador*3500)
    		{
    			digitalWrite(leds[1],HIGH);
    			digitalWrite(leds[0],HIGH);
    		}

    	else if(k > (float) multiplicador*3500 || k < (float) multiplicador*5500)
    		digitalWrite(leds[2],HIGH);

    	else if(k > (float) multiplicador*5500)
    		k = 0;
      break;

    case alarma:
    	if(k > (float) multiplicador*500)
    	  	digitalWrite(leds[1],HIGH);

    	else if(k > (float) multiplicador*1000)
    	  	k = 0;
      break;

    case desconectado:
    	if(k > (float) multiplicador*1000)
    		digitalWrite(leds[2],HIGH);

    	else if(k > (float) multiplicador*2000)
    		 k = 0;
      break;


    default:
      initializeFSMSem();
      break;
    }
  k++;
  delay(1);
  return k;
}

void apagarLeds()
{
	for(int i = 0; i < longitudLeds; i++)
			digitalWrite(leds[i],LOW);
}

