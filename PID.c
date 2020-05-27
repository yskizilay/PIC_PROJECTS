#include"pic18f4520.h"

long int i=0;

float ref=128;

float hata=0;//hata de?eri
float integral=0.0,integral1=0.0,integral2=0.0,d=0.0,d1=0.0,d2=0.0;
long int sonuc=0;
long int sonuc1=0, gerilim = 0;


float kp=1,ki=25,kd=0;
//1 50
//10 500
//1 5
//1 10
//1 25
//float kp=2142.3321,ki=16041.5406,kd=-21.4233;
float T=0.001;



void interrupt kesme( void ){
    GIE = 0;
    if( T0IF ){
        TMR0 = 255-97;
        T0IF = 0;
        GO = 1;    
    }
    if( ADIF ){
        ADIF = 0; 
        LATB = 255;
        gerilim = ADRESH;
  
                hata=ref-gerilim;
	
				integral = integral1 + hata*T*ki/2 ;
				if(integral>255)integral=255;
				if(integral<-255)integral=-255;
				
				integral2=integral + integral1;
				if(integral2>255)integral2=255;
				if(integral2<-255)integral2=-255;	
				
				d1=(kd*hata)/T;
				if(d1>255)d1=255;
				if(d1<-255)d1=-255;
				
				d=d1-d2;
				if(d>255)d=255;
				if(d<-255)d=-255;
				
				d2=d1;
				integral1 = integral;
				sonuc1=hata*kp+integral2+d;
				if(sonuc1>255)sonuc1=255;
				if(sonuc1<0)sonuc1=0;
	
				sonuc=sonuc1;

                
        LATC  = sonuc;      
        LATB = 0;  
    }    
    GIE = 1;   
}

void main(void){
    //PLLEN = 1;
    TRISA = 0xFF; TRISC = 0; TRISB = 0; LATC = 0;
    CHS3 = 0; CHS2 = 0; CHS1 = 0; CHS0 = 0;
    VCFG1 = 0; VCFG0 = 0;
    PCFG3 = 1; PCFG2 = 1; PCFG1 = 1; PCFG0 = 0;
    ADFM = 0; ACQT2 = 0; ACQT1 = 0; ACQT0 = 0; 
    ADCS2 = 0; ADCS1 = 1; ADCS0 = 0; 
    ADON = 1;
    ADIF = 0; ADIE = 1;

    T08BIT = 1; T0CS = 0; PSA = 0; 
    T0PS2 = 1; T0PS1 = 1; T0PS0 = 1;
    TMR0 = 255-97;
    TMR0ON = 1; T0IF = 0; T0IE = 1;
    
    for( i = 0; i < 1000000 ; i++ );
    
    PEIE = 1; GIE = 1;

    while(1){}

}

