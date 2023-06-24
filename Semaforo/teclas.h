/*
 * teclas.h
 *
 */

#ifndef TECLAS_H_
#define TECLAS_H_

const int16_t psh1 = 10;
const int16_t psh2 = 8;


typedef enum {
  buttonUp,
  buttonFalling,
  buttonRising,
  buttonDown
} stateFSM_t;

typedef struct {
	stateFSM_t actualState;
	int16_t psh[2] = {psh1, psh2};
	int16_t Delay;
} dbn_t;

dbn_t *teclasMEF;

typedef struct {
	void initializeFSM(dbn_t *teclasMEF);
	void updateFSM(dbn_t *teclasMEF);
	void buttonPressed();
	void buttonReleased(int16_t teclaDef);
}funciones;

#endif /* TECLAS_H_ */
