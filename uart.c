#include <pic16f877a.h>
#include<xc.h>
#include<stdio.h>
unsigned int i = 0;
int a = 58;

void putch(char data) {
 while( ! TXIF); // check buffer
// wait till ready
 TXREG = data; // send data
}


void main( void ){
    TRISC = 0xFF; TRISB = 0; PORTB = 0;
    TX9 = 0; TXEN = 1; SYNC = 0; BRGH = 1; SPBRG = 25;
    SPEN = 1; RX9 = 0; CREN = 1; ADDEN = 0;
    TXIF = 0; RCIF = 0;
    
    while(1){
        
        printf("a degiskeni = %d",a);
        while(1);
                      
    }
}
