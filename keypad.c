#include<pic16f877a.h>
#include"xc.h"

unsigned char i = 0;
const unsigned char disp[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned char birler = 0,onlar=0,yuzler =0,binler=0;
void interrupt sayici( void ){
    GIE = 0;
    if( T0IF ){
        TMR0 = 5;
        T0IF = 0;
        i++;
        if(i==1){PORTC=0x0E;PORTB=disp[binler];}
        if(i==2){PORTC=0x0D;PORTB=disp[yuzler];}
        if(i==3){PORTC=0x0B;PORTB=disp[onlar];}      
        if(i==4){PORTC=0x07;PORTB=disp[birler];i=0;}
    }
    GIE = 1;
}

void bekle(void){
    int k=0;
    for( k = 0; k < 100; k++ );
}

void arttir( void ){
    birler++;
    if( birler == 10 ) { birler = 0; onlar++;}
    if( onlar == 10 ) { onlar = 0; yuzler++;}
    if( yuzler == 10 ) { yuzler = 0; binler++;}
    if( binler == 10 ) binler = 0;    
}
void azalt( void ){
    birler--;
    if( birler == 255 ) { birler = 9; onlar--;}
    if( onlar == 255) { onlar = 9; yuzler--;}
    if( yuzler == 255 ) { yuzler = 9; binler--;}
    if( binler == 255 ) binler = 9;    
}
void sifirla( void ){
    birler =0;
    onlar =0;
    yuzler =0;
    binler = 0;
}

void main( void ){
    TRISC = 0;
    TRISD = 0xFF;
    TRISB = 0;
    PORTB = 0;
    T0CS = 0;
    PSA = 0;
    PS2 = 0;
    PS1 = 0;
    PS0 = 1;
    T0IF = 0;
    TMR0 = 5;
    T0IE = 1;
    GIE = 1;
    
    while(1){
        if( RD0 ){ 
            arttir(); bekle(); while( RD0 ); bekle();
        }
        if( RD1 ){
            azalt(); bekle(); while( RD1 ); bekle();
        }
        if( RD2 ){
            sifirla(); bekle(); while( RD2 ); bekle();
        }
    }
}
