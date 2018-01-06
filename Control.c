#include <16F628a.h>         //Se indica el micro que se va a utilizar.

#use delay (clock=20000000)  //Se indica la velocidad del XTAL=4MHz.

#fuses HS, NOWDT  //Se indican los fuses activos/inactivos. Y el indicativo de alta velocidad

#Byte TRISA = 0x85
#Byte PORTA = 0x05
#Byte TRISB = 0x86
#Byte PORTB = 0x06


#DEFINE S1 PIN_A2
#DEFINE S2 PIN_A3

//65256,65170,65088,65014,64949,64894,64852,64823,64809,64807,64809,64823,64852,64894,64949,65014,65088,65170,65256,65344,65369,65394,65417,65438,65457,65473,65485,65493,65505,65493,65485,65473,65457,65438,65417,65394,65369,65344,65256

unsigned int16 value[39]={64925,64910,64875,64801,64728,64652,64619,64581,64578,64567,64578,64581,64619,64652,64728,64801,64875,64910,64925,65096,65131,65208,65244,65315,65343,65386,65426,65438,65449,65438,65426,65386,65343,65315,65244,65208,65131,65096,65097};
unsigned int i;


#int_TIMER1
void timer1(){
output_low(S1);
delay_us(15);// Tiempo muerto
output_high(S2);
}

#int_TIMER2
void timer2(){
output_low(S2);
delay_us(15);// Tiempo muerto
output_high(S1);
if(i==37){
i=0;
}else{
i++;
}
SET_TIMER1(value[i]);
}


void main ()
{
//Entradas y salidas
TRISA = 0b00011; //1 = ENTRADA, 0 = SALIDA
TRISB = 0b00000001; //1 = ENTRADA, 0 = SALIDA
output_low(S1);

setup_timer_1 ( T1_INTERNAL | T1_DIV_BY_2);//Setup timer: Reloj interno, preescaler= 2
enable_interrupts(INT_TIMER1);//habilitamos la interrupcion que deseamos
enable_interrupts(GLOBAL);

setup_timer_2(T2_DIV_BY_16,136,1);//Setup timer: Reloj interno, preescaler = 1, Poscaler 1/frecuencia de 6060 Hz
enable_interrupts(INT_TIMER2);//Por desbordamiento 
enable_interrupts(GLOBAL);

    while(true){}
}
