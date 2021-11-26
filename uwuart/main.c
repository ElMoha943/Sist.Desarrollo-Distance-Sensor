#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = ON
#pragma config FCMEN = ON
#pragma config LVP = OFF
#pragma config BOR4V = BOR40V
#pragma config WRT = OFF

#include <xc.h>
#include <stdio.h>
#include"hcsr04.h"

void main(){
    // Configuracion de puertos
    TRISA3 = 0;
    TRISA0 = 1;
    TRISB = 0x00;
    TRISC = 0x00;
    TRISC7 = 1;
    TRISD = 0x00;
    ANSEL=0;
    ANSELH=0;

    //CONFIGURACION DE UWART
    TRISCbits.TRISC6=0;
    BRG16=0;
    BRGH=1;
    SPBRG=25;
    TXSTAbits.TXEN=1;
    RCSTAbits.CREN=1;
    RCSTAbits.SPEN=1;

    //Timer0 Registers Prescaler= 256 - TMR0 Preset = 60 - Freq = 19.93 Hz - Period = 0.050176 seconds
    T0CS = 0;  // bit 5  TMR0 Clock Source Select bit...0 = Internal Clock (CLKO) 1 = Transition on T0CKI pin
    T0SE = 0;  // bit 4 TMR0 Source Edge Select bit 0 = low/high 1 = high/low
    PSA = 0;   //s bit 3  Prescaler Assignment bit...0 = Prescaler is assigned to the Timer0
    PS2 = 1;   // bits 2-0  PS2:PS0: Prescaler Rate Select bits
    PS1 = 1;
    PS0 = 1;
    TMR0 = 60; // preset for timer register

    //Timer1 Registers Prescaler= 1 - TMR1 Preset = 65535 - Freq = 1000000.00 Hz - Period = 0.000001 seconds
    T1CKPS1 = 0;   // bits 5-4  Prescaler Rate Select bits
    T1CKPS0 = 0;   // bit 4
    T1OSCEN = 1;   // bit 3 Timer1 Oscillator Enable Control bit 1 = on
    T1SYNC = 1;    // bit 2 Timer1 External Clock Input Synchronization Control bit...1 = Do not synchronize external clock input
    TMR1CS = 0;    // bit 1 Timer1 Clock Source Select bit...0 = Internal clock (FOSC/4)
    TMR1ON = 1;    // bit 0 enables timer
    TMR1H = 255;   // preset for timer1 MSB register
    TMR1L = 255;   // preset for timer1 LSB register

    unsigned int t=0, d=0, s=0;
    while (1)
    {
        //TIMER0
        if(T0IF==1) //CONTADOR DE 50ms
        {    
            T0IF=0;
            TMR0=60;
            ConmutarDigito();
            s++;
            if(s==20)
            {
                s=0;
                // Send 10us pulse to HC-SR04 Trigger pin
                TRIGGER = 1;
                __delay_us(10);
                TRIGGER = 0;
                // Read pulse comes from HC-SR04 Echo pin
                while(ECHO==0);
                TMR1ON = 0;
                TMR1H = 0;
                TMR1L = 0;
                TMR1ON = 1;
                while(ECHO==1);
                TMR1ON = 0;
                t = (TMR1H << 8) | TMR1L;
                d = (t/58)+1;
                printf("Tiempo: %d\r\n",t);
                printf("Distancia: %d\r\n",d);
            }
        }
    }
}

void putch(char c){
    while(TXIF==0);
    TXREG=c;
}