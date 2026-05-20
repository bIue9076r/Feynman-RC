#ifndef FLIGHT_H
#define FLIGHT_H
#include "genlib.h"

void getAccelData(void);
void getBaroData(void);
void ShowAccelData(unsigned long n);
void ShowBaroData(unsigned long n);
void SaveAccelData(unsigned long n, float x, float y, float z);
void SaveBaroData(unsigned long n, float p, float a);

int Flight(void);

#endif