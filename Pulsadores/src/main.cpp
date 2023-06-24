#include <Arduino.h>
const int16_t led_amarillo = 22;
const int16_t led_verde = 15;
const int16_t led_rojo = 21;
const int16_t push1 = 23;
const int16_t push2 = 24;
typedef enum{
  BUTTOM_UP,
  BUTTOM_DOWN,
  BUTTOM_FALLING,
  BUTTOM_RISING
} fsmButtonState_t;

fsmButtonState_t fsmButtonState;

/******************Prototipo de funciones*******************/

int16_t nbDelay(int16_t t_delay);

void fsmButtonInit(void);
void fsmButtonUpdate(int16_t sw);
void buttonPressed(int16_t sw);
void buttonReleased(int16_t sw);
void buttonError(void);

bool apagarLeds(int16_t* leds, int16_t len);

void setup() {
  pinMode(led_verde, OUTPUT);
  pinMode(led_amarillo, OUTPUT);
  pinMode(led_rojo, OUTPUT);
  pinMode(push1, INPUT);
  pinMode(push2, INPUT);
}

void loop() {
  int16_t leds[] = {led_verde, led_amarillo, led_rojo};
  int16_t lon = sizeof(leds) / sizeof(int16_t);

  fsmButtonInit();
  while (1){
    fsmButtonUpdate(push1);
  }

  buttonPressed(push1);
  buttonReleased(push2);

}

/*********************************************/
void fsmButtonInit(void){
  fsmButtonState = BUTTOM_UP;
}

/*********************************************/
void fsmButtonUpdate(int16_t sw){
  switch (fsmButtonState){
    case BUTTOM_UP:
      if (!digitalRead(sw)){
        fsmButtonState = BUTTOM_FALLING;
      }
      break;
    case BUTTOM_DOWN:
      if (digitalRead(sw)){
        fsmButtonState = BUTTOM_RISING;
      }
      break;
    case BUTTOM_FALLING:
      if (nbDelay(40)){
        if (!digitalRead(sw)){
          fsmButtonState = BUTTOM_DOWN;
          buttonPressed();
        }else{
          fsmButtonState = BUTTOM_UP;
        }
      }
      break;
    case BUTTOM_RISING:
      if (nbDelay(40)){
        if (digitalRead(sw)){
          fsmButtonState = BUTTOM_UP;
          buttonReleased();
        }else{
          fsmButtonState = BUTTOM_DOWN;
        }
      }
      break;
    default:
      buttonError();
      break;
  }
}

/*********************************************/

void buttonError(void){
  fsmButtonState = BUTTOM_UP;
}

/*********************************************/

void buttonPressed(int16_t tecla){
  static int16_t pos = 0;
  if (digitalRead(tecla)){
    pos--;
  }
}

/*********************************************/

void buttonReleased(int16_t tecla){
  static int16_t pos = 0;
  if (digitalRead(tecla)){
    pos++;
  }
}

/*************Non-blocking delay**************/

int16_t nbDelay(int16_t t_delay){
  int16_t t_base = 1;
  static int16_t count = 0;
  int16_t n_time = t_delay / t_base;

  if (count >= n_time){
    count = 0;
    return 1;
  }
  else{
    count++;
    return 0;
  }
}

bool apagarLeds(int16_t* leds, int16_t len){
  int16_t aux = 1;
  for(int16_t i = 0; i < len; i++){
    digitalWrite(leds[i], LOW);
    if (digitalRead(leds[i] == HIGH)){
      aux = 0;
    }
  }
  return aux;
}