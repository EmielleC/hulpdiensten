
#include <Arduino.h>
#include "functions.h"

char recieveCharacter();

  int beginCycle = 0;
  int toReturn = 1;
  int lastSwitch = millis();
  int difference = 0;
  int indexFilled = 0;
  char String[63];
  long timeTillSwitch = 0;
  int tempMode = 0;

void changeToReturn(int mode){
  toReturn = mode;
};

void emergencyMode(int mode){

  if(mode == tempMode){
    trafficLightMode(mode);
    Serial.println("1");
    toReturn = tempMode;
  }
  else if(tempMode == 1 || tempMode == 3 || tempMode == 5 || tempMode ==7){
    Serial.println("2");
    long temp5 = millis();
    if(timeTillSwitch == 0){
      trafficLightMode(tempMode + 1);
      timeTillSwitch = millis() + 2000;

    }
    else if(timeTillSwitch < temp5){
      tempMode = tempMode + 1;
      trafficLightMode(tempMode);
      timeTillSwitch = 0;
  }
}
else {
  Serial.println("3");
  long temp5 = millis();
  if(timeTillSwitch == 0){
    timeTillSwitch = millis() + 2000;
  }
  else if(timeTillSwitch < temp5){
    tempMode = mode;
    trafficLightMode(tempMode);
    timeTillSwitch = 0;
}
}
}


char decodeProtocol(char completedString[]){
    char toReturn2 = '0';
    bool phrase1s = true;
    bool phrase2s = true;
    char phrase1[63] = {'M', 'O', 'D', 'E'};
    char phrase2[63] = {'N', 'O', 'R', 'M', 'A', 'L'};
    for (int i = 0; i < 63; i++) {

      if (completedString[i] == '(') {
        break;
        }

  if( completedString[i] != phrase1[i]){
    phrase1s = false;
  }

  if( completedString[i] != phrase2[i]){
    phrase2s = false;
  }
}

  if(phrase1s){
    toReturn2 =  completedString[5];
  }

  if(phrase2s){
    toReturn2 = '0';
  }

return toReturn2;
}

//zodra bericht compleet is wordt de bool true anders is die false
//berichten beginnen met # en eindigen met %
void addCharacter(char input, char *completedString){
  if(input == '#'){
    indexFilled = 0;
    for (int i = 0; i < 63; i++) {
          String[i] = 0;
  }
}
  else if(input == '%'){

    for (int i = 0; i < 63; i++) {
          *(completedString + i) = String[i];
       }
  }
  else{
    String[indexFilled] = input;
    indexFilled++;
  }
}

long nextSwitch = 0 ;

int cycleTrafficLights(){

  long timeNow = millis();




  if(nextSwitch <= timeNow){
    toReturn = toReturn + 1;
    nextSwitch = timeNow + 2000;
  }
  if( toReturn == 9){
    toReturn = 1;
  }

return toReturn;
}

void trafficLightMode(int mode){
  tempMode = mode;
  switch(mode){
    case 1:
      changeTrafficLight(1,1);
      changeTrafficLight(2,0);
      changeTrafficLight(3,0);
      changeTrafficLight(4,0);
    break;

    case 2:
      changeTrafficLight(1,2);
      changeTrafficLight(2,0);
      changeTrafficLight(3,0);
      changeTrafficLight(4,0);
    break;

    case 3:
      changeTrafficLight(1,0);
      changeTrafficLight(2,1);
      changeTrafficLight(3,0);
      changeTrafficLight(4,0);
    break;

    case 4:
      changeTrafficLight(1,0);
      changeTrafficLight(2,2);
      changeTrafficLight(3,0);
      changeTrafficLight(4,0);
    break;

    case 5:
      changeTrafficLight(1,0);
      changeTrafficLight(2,0);
      changeTrafficLight(3,1);
      changeTrafficLight(4,0);
    break;

    case 6:
      changeTrafficLight(1,0);
      changeTrafficLight(2,0);
      changeTrafficLight(3,2);
      changeTrafficLight(4,0);
    break;

    case 7:
      changeTrafficLight(1,0);
      changeTrafficLight(2,0);
      changeTrafficLight(3,0);
      changeTrafficLight(4,1);
    break;

    case 8:
      changeTrafficLight(1,0);
      changeTrafficLight(2,0);
      changeTrafficLight(3,0);
      changeTrafficLight(4,2);
    break;
  }
};

void changeTrafficLight(int id, int state){

switch(id){
  case 2:
  if(state ==0){
    PORTC =  PORTC | 0b01;
    PORTC =  0b010 ^ (PORTC | 0b010);
    PORTC =  0b0100 ^ (PORTC | 0b0100);
  }
  else if (state == 1){
    PORTC =  0b01 ^ (PORTC | 0b01);
    PORTC =  PORTC | 0b010;
    PORTC =  0b0100 ^ (PORTC | 0b0100);
  }
  else{
    PORTC =  0b01 ^ (PORTC | 0b01);
    PORTC =  0b010 ^ (PORTC | 0b010);
    PORTC =  PORTC | 0b0100;
  }
  break;

  case 1:
  if(state ==0){
    PORTC =  PORTC | 0b01000;
    PORTC =  0b010000 ^ (PORTC | 0b010000);
    PORTC =  0b0100000 ^ (PORTC | 0b0100000);
  }
  else if (state == 1){
    PORTC =  0b01000 ^ (PORTC | 0b01000);
    PORTC =  PORTC | 0b010000;
    PORTC =  0b0100000 ^ (PORTC | 0b0100000);
  }
  else{
    PORTC =  0b01000 ^ (PORTC | 0b01000);
    PORTC =  0b010000 ^ (PORTC | 0b010000);
    PORTC =  PORTC | 0b0100000;
  }
  break;

  case 3:
  if(state == 0){
    PORTD =  PORTD | 0b10000;
    PORTD = 0b1000 ^ (PORTD | 0b1000);
    PORTD = 0b100 ^ (PORTD | 0b100);
  }
  else if (state == 1){
    PORTD = 0b100 ^ (PORTD | 0b100);
    PORTD =  PORTD | 0b1000;
    PORTD = 0b10000 ^ (PORTD | 0b10000);
  }
  else{
    PORTD = 0b10000 ^ (PORTD | 0b10000);
    PORTD = 0b1000 ^ (PORTD | 0b1000);
    PORTD =  PORTD | 0b100;
  }
  break;

  case 4:
  if(state ==0){
    PORTB =  PORTB | 0b01;
    PORTD =  0b1000000 ^ (PORTD | 0b1000000);
    PORTD =  0b100000 ^ (PORTD | 0b100000);
  }
  else if (state == 1){
    PORTB =   0b1^ (PORTB | 0b1);
    PORTD =  PORTD | 0b1000000;
    PORTD =  0b100000 ^ (PORTD | 0b100000);
  }
  else{
    PORTB =   0b1^ (PORTB | 0b1);
    PORTD =  0b1000000 ^ (PORTD | 0b1000000);
    PORTD =  PORTD | 0b100000;
  }
  break;

  default:
  break;
}

}
