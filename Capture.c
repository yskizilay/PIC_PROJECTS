#include"pic16f877a.h"
unsigned int a=0,b=0,period=0;
unsigned char i=0,k=0;
const unsigned char disp[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x00};
unsigned char birler = 0,onlar=0,yuzler =0,binler=0;
unsigned int frekans = 0;


void interrupt capture(void)
{
    GIE = 0;
    if( T0IF ){
        TMR0 = 5;
        T0IF = 0;
        i++;
        if(i==1){PORTD=0x0E;PORTB=disp[binler];}
        if(i==2){PORTD=0x0D;PORTB=disp[yuzler];}
        if(i==3){PORTD=0x0B;PORTB=disp[onlar];}      
        if(i==4){PORTD=0x07;PORTB=disp[birler];i=0;}
    }
    if( CCP1IF ){
        CCP1IF = 0;
        k++;
        if( k == 1 ) a = ( CCPR1H << 8 ) + CCPR1L; 
        if( k == 2 ){ 
            k = 0;
            b = ( CCPR1H << 8 ) + CCPR1L; 
            
            if( a < b ) period = b - a;
            else period = ( 65535 - a ) + b;  
            
            frekans = 1000000 / ( period * 4 );
            
            binler = frekans / 1000;
            yuzler = ( frekans % 1000) / 100;
            onlar = ( frekans % 100) / 10;
            birler  = frekans %  1;           
        }  
    }
    GIE = 1;
}
       
void main( void )
{   TRISC = 0xFF; TRISB = 0; TRISD = 0;

    T0CS = 0; PSA = 0; PS2 = 0; PS1 = 0; PS0 = 1;
    T0IF = 0; TMR0 = 5; T0IE = 1;

    T1CKPS1 = 1; T1CKPS0 = 0; TMR1CS = 0;
    TMR1ON = 1;
    CCP1M3 = 0; CCP1M2 = 1; CCP1M1 = 0; CCP1M0 = 1;
    CCP1IF = 0; CCP1IE = 1; PEIE = 1; GIE = 1;

    while(1);
}
