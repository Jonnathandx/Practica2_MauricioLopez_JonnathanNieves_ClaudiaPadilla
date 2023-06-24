/*
 * teclas.cpp
 *
 */
#include "Arduino.h"
#include "semaforo.h"
#include "teclas.h"

int16_t tiempoPres = 0;
int16_t tiempoPresAnt = 0;
int16_t tecla;
funciones funcion;

void initializeFSM(dbn_t teclasMEF)
{
	teclasMEF.actualState = buttonUp;
}


void updateFSM(dbn_t teclasMEF)
{
  tiempoPres = updateFSMSem();
  switch(teclasMEF.actualState)
  {
    case buttonUp:
    	if(!digitalRead(teclasMEF.psh[0]) && digitalRead(teclasMEF.psh[1]))
    		teclasMEF.actualState = buttonFalling;

    	if(!digitalRead(teclasMEF.psh[1]) && digitalRead(teclasMEF.psh[0]))
    	    teclasMEF.actualState = buttonFalling;
      break;

    case buttonFalling:
    	if((tiempoPres - tiempoPresAnt)<40)
    		break;
    	if(!digitalRead(teclasMEF.psh[1]) && digitalRead(teclasMEF.psh[0]))
    		{
    			funcion.buttonPressed();
    			teclasMEF.actualState = buttonDown;
    		}
    	else if(!digitalRead(teclasMEF.psh[0]) && digitalRead(teclasMEF.psh[1]))
    	    {
    	    	funcion.buttonPressed();
    	    	teclasMEF.actualState = buttonDown;
    	    }
    	else
    		teclasMEF.actualState = buttonUp;
      break;

    case buttonDown:
    	if(!digitalRead(teclasMEF.psh[0]) && digitalRead(teclasMEF.psh[1]))
    	   teclasMEF.actualState = buttonRising;

    	  if(!digitalRead(teclasMEF.psh[1]) && digitalRead(teclasMEF.psh[0]))
    	   teclasMEF.actualState = buttonRising;
      break;

    case buttonRising:
    	if((tiempoPres - tiempoPresAnt)<40)
    	    break;
    	if(!digitalRead(teclasMEF.psh[1]) && digitalRead(teclasMEF.psh[0]))
    	    {
    	    	tecla = 1;
    	    	funcion.buttonReleased(tecla);
    	    	teclasMEF.actualState = buttonUp;
    	    }
    	else if(!digitalRead(teclasMEF.psh[0]) && digitalRead(teclasMEF.psh[1]))
    	    {
    	    	tecla = 2;
    	    	funcion.buttonReleased(tecla);
    	    	teclasMEF.actualState = buttonUp;
    	    }
    	 else
    	    teclasMEF.actualState = buttonDown;

      break;

    default:
      funcion.initializeFSM(&teclasMEF);
      break;
    }
  tiempoPresAnt = tiempoPres;
}

void buttonPressed()
{

}

void buttonReleased(int16_t teclaDef)
{
	if(teclaDef == 1)
	{
		if(estadoActualSem == normal)
			estadoActualSem = desconectado;

		else if(estadoActualSem == desconectado)
			estadoActualSem = alarma;

		else if(estadoActualSem == alarma)
			estadoActualSem = normal;
	}

	else if(teclaDef == 2)
	{

		if(velocidad == x05)
			multiplicador = 0.5;

		else if(velocidad == x1)
			multiplicador = 1;

		else if(velocidad == x2)
			multiplicador = 2;

	}
}
