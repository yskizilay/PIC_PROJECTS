#include<pic16f877a.h>
const unsigned char disp[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
unsigned int a = 0;
unsigned char i=0;
unsigned char binler=1,yuzler=8,onlar=1,birler=8;


void tarama(void)
{
        PORTC = 0x0E;
        PORTB = disp[binler];
        for(a=0;a<100;a++);
        PORTC = 0x0D;
        PORTB = disp[yuzler];
        for(a=0;a<100;a++);
        PORTC = 0x0B;
        PORTB = disp[onlar];
        for(a=0;a<100;a++);
        PORTC = 0x07;
        PORTB = disp[birler];
        for(a=0;a<100;a++);
}
void arttir(void)
{
        birler++; 
        if(birler == 10){ birler = 0;onlar++;}
        if(onlar == 10){ onlar=0;yuzler++;}
        if(yuzler == 10){ yuzler=0;binler++;} 
        if(binler == 10){ binler =0;}
}
void azalt(void)
{
        birler--; 
        if(birler == 255){ birler = 9;onlar--;}
        if(onlar == 255){ onlar=9;yuzler--;}
        if(yuzler == 255){ yuzler=9;binler--;} 
        if(binler == 255){ binler =9;}
}
void sifirla(void)
{
    birler=0;
    onlar=0;
    yuzler=0;
    binler=0;
}

void main(void)
{  

    TRISB = 0;
    TRISC = 0x0;
    TRISD = 0xFF;
    
    while(1)
    {   
        if(RD0){ arttir(); while(RD0) tarama();}
        if(RD1) {azalt(); while(RD1) tarama();}
        if(RD2){ sifirla(); while(RD2) tarama();}
        tarama(); 

        
        
    }
}
