
#include <Arduino.h>
#include "functions.h"

char recieveCharacter();

  int beginCycle = 0;
  int toReturn = 1;
  int lastSwitch = millis();
  int difference = 0;
  int indexFilled = 0;
  char String[63];
  char CompletedString[63];

//zodra bericht compleet is wordt de bool true anders is die false
//berichten beginnen met # en eindigen met %
char addCharacter[](char input){

  if(input == '#'){
    indexFilled = 0;
  }

  else if(input == '%'){
    for (i = 0; i < 63; i++) {
          CompletedString[i] = String[i];
       }
  }
  else{
    String[indexFilled] = input;
  }

  return CompletedString;
}

int cycleTrafficLights(){

  int timeNow = millis();
timeNow = timeNow - difference;

  if(lastSwitch < timeNow){
    toReturn = toReturn + 1;
    difference =  difference + 2000;
    lastSwitch = timeNow;
  }
  if( toReturn == 9){
    toReturn = 1;
  }

return toReturn;
}

void trafficLightMode(int mode){
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
