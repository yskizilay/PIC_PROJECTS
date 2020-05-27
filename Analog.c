#include"pic16f877a.h"
unsigned long int sonuc = 0;
unsigned char i = 0;
const unsigned char disp[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};
unsigned char birler = 0,onlar=0,yuzler =0,binler=0;
void interrupt adc( void )
{   GIE = 0;
    if( T0IF ){
        TMR0 = 5; T0IF = 0; GO = 1;
        i++;
        if(i==1){PORTC=0x0E;PORTB=disp[binler];}
        if(i==2){PORTC=0x0D;PORTB= disp[yuzler] | 0x80;}
        if(i==3){PORTC=0x0B;PORTB=disp[onlar];}      
        if(i==4){PORTC=0x07;PORTB=disp[birler];i=0;}     
    }
    if( ADIF ){
        ADIF = 0;
        sonuc = ADRESH;
        sonuc = ( sonuc * 500 ) / 256;
        binler = sonuc / 1000;
        yuzler = ( sonuc % 1000 ) / 100;
        onlar = ( sonuc % 100 ) / 10;
        birler = sonuc % 10;
    }
    GIE = 1;   
}
void main( void ){
    TRISA = 0xFF; TRISB = 0; TRISC = 0;
    
    T0CS = 0; PSA = 0; PS2 = 0; PS1 = 0; PS0 = 1;
    T0IF = 0;  TMR0 = 5; T0IE = 1;
    
    ADCS1 = 0; ADCS0 = 1; CHS2 = 0; CHS1 = 0; CHS0 = 0;
    PCFG3 = 1; PCFG2 = 1; PCFG1 = 1; PCFG0 = 0; 
    ADFM = 0; ADON = 1;
    
    PEIE = 1; GIE = 1;
    
    while(1){}
}
