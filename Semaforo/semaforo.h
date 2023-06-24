/*
 * semaforo.h
 *
 */

#ifndef SEMAFORO_H_
#define SEMAFORO_H_

const int16_t ledVe = 2;
const int16_t ledAm = 3;
const int16_t ledRo = 4;

int16_t leds[] = {2, 3, 4};
float multiplicador;

typedef enum {
  normal,
  desconectado,
  alarma
} stateSem_t;

stateSem_t estadoActualSem;

typedef enum {
  x05,
  x1,
  x2
} mult;

mult velocidad;

void initializeFSMSem();
int16_t updateFSMSem();
void apagarLeds();
#endif /* SEMAFORO_H_ */
