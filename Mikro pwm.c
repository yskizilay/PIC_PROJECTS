#include"pic16f877a.h"
int a = 0;
void main( void ){
    TRISC = 0; TRISB = 0xFF;
    CCP1M3 = 1; CCP1M2 = 1; CCPR1L = 64;
    T2CKPS1 = 0; T2CKPS0 = 1; TMR2ON = 1;

    while(1){
        if( RB0 ){
            a = a + 10;
            if( a > 255 ) a = 255;
            CCPR1L = a;
            while( RB0 );       
        }
        if( RB1 ){
            a = a - 10;
            if( a < 0 ) a = 0;
            CCPR1L = a;
            while( RB1 );         
        }
    }
}
