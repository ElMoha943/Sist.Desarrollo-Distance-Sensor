#include<xc.h>
#include"hcsr04.h"

void ConmutarDigito()
{
    if(Digito==0)
    {
        PORTD=D1;
        Digito=1;
        BJT1 = 1;
        BJT2 = 0;
    }
    else
    {
        PORTD=D2;
        Digito=0;
        BJT1 = 0;
        BJT2 = 1;
    }
}

void MostrarDisplay(unsigned int d)
{
    D1 = Codificar(d/10);
    D2 = Codificar(d%10);
}


unsigned int Codificar(unsigned int distancia)
{
    switch(distancia) 
    { 
    case 0: 
        return 0b0111111; 
        break; 

    case 1: 
        return 0b0000110;
        break; 

    case 2: 
        return 0b1011011;
        break; 

    case 3: 
        return 0b1001111; 
        break; 
    case 4: 

        return 0b1100110; 
        break; 

    case 5: 
        return 0b1101101;
        break; 
    case 6: 

        return 0b1111101; 
        break; 
    case 7: 

        return 0b0000111; 
        break; 
    case 8: 

        return 0b1111111; 
        break; 
    case 9: 
    
        return 0b1100111; 
        break; 
    } 
}
