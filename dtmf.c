
#include<pic18f4520.h>
const unsigned char y1[]={
0	,
22	,
42	,
56	,
63	,
62	,
52	,
36	,
15	,
-7	,
-29	,
-47	,
-59	,
-63	,
-59	,
-47	,
-29	
			   
};
const unsigned char y2[]={
0,
37,
60,
60,
37,
0,
-37,
-60,
-60,
-37
} ;   
    
unsigned int a=0,b=0;

void interrupt timer(void)
{
    if(T0IF)
    {   TMR0 = 255-169;
        LATC = 128 + ( y1[ a ] + y2[ b ] );
        a++; b++;
        if( a == 17 ) a = 0;
        if( b == 10 ) b = 0;

        T0IF = 0;   
    }
}
void main(void)
{ 

    TRISC = 0;
    
    TMR0 = 255-169;
    T08BIT = 1;
    T0CS = 0;
    PSA = 0;
    T0PS2 = 0;
    T0PS1 = 0;
    T0PS0 = 1;
    TMR0ON = 1;
    
    T0IE = 1;
    T0IF = 0;
    GIE = 1;
    

    while(1)
    {  
    }
}