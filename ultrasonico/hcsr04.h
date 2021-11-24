#ifndef HCSR04_H
#define HCSR04_H

void ConmutarDigito();
unsigned int Codificar(unsigned int distancia);
unsigned int MedirDistancia();
void MostrarDisplay();

unsigned int D1=0b0111111, D2=0b0111111, Digito=0;

#define TRIGGER RA3 //pin de salida del sensor
#define ECHO RA0 //pin de entrada del sensor
#define BJT1 RB6
#define BJT2 RB5
#define _XTAL_FREQ 4000000

#endif