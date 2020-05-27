#include <pic16f877a.h>
int i = 0, j = 0;
void main( void ){
    TRISB = 0xFF; TRISC = 0; TRISD = 0x0F;
    EEPGD = 0; WREN = 1; 
   
    while(1){        
        if( RD0 ){
            EEADR = i;
            EEDATA = PORTB;
            EECON2= 0x55;
            EECON2= 0xAA;
            WR = 1;
            while( WR );
            if( WRERR ) RD7 = 1;
            i++; 
            if( i == 10 ) i = 0;
            while( RD0 );
        }
        if( RD1 ){
            EEADR = j;
            RD = 1;
            while( RD );
            PORTC = EEDATA; 
            j++; 
            if( j == 10 ) j = 0;
            while( RD1 );
        }
    }
}
