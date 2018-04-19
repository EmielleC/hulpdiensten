
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

char decodeProtocol(char *completedString);

void addCharacter(char input, char *completedString);

void changeTrafficLight(int id, int state);

char recieveCharacter();

int cycleTrafficLights();

void trafficLightMode(int mode);

void changeToReturn(int mode);

void emergencyMode(int mode);

#endif
