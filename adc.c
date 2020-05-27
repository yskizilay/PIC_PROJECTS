#include"pic18f4520.h"

void interrupt kesme( void ){
    GIE = 0;
    if( T0IF ){
        TMR0 = 255- 156;
        T0IF = 0;    
        GO = 1;
    }
    if( ADIF ){
        ADIF = 0;
        LATC = ADRESH;
    
    }
    GIE = 1;
}

void main( void ){
    TRISC = 0; LATC = 0x55; 
    
    CHS3 = 0; CHS2 = 0; CHS1 = 0; CHS0 = 0;
    VCFG1 = 0; VCFG0 = 0;
    PCFG3 = 1; PCFG2 = 1; PCFG1 = 1; PCFG0 = 0;
    ADFM = 0;
    ACQT2 = 0; ACQT1 = 0; ACQT0 = 0;
    ADCS2 = 0; ADCS1 = 1; ADCS0 = 0;
    ADON = 1;
    
    ADIF = 0; ADIE = 1; 
    
    T08BIT = 1; T0CS = 0; PSA = 0;
    T0PS2 = 1; T0PS1 = 0; T0PS0 = 1;
    TMR0 = 255-156; T0IF = 0; T0IE = 1; 
    TMR0ON = 1;

    PEIE = 1; GIE = 1;
    
    while(1){}    
}

