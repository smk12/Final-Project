/*
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"
#include "interrupt.h"

void initTimer2(){
    TMR2 = 0;
    PR2 = 1023;
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    T2CONbits.ON = 1;
}


void delayUs(unsigned int delay)
{

    //TODO: Create a delay for "delay" micro seconds using timer 2
    TMR2 = 0;
    PR2 = delay*10-1;
    T2CONbits.TCKPS = 3;//pre-scalar
    T2CONbits.TCS = 0;//osc config
    IFS0bits.T2IF = 0;//flag
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0){}
    T2CONbits.ON = 0;
    IFS0bits.T2IF = 0;
    
}



void delayMs(unsigned int delay){
    //TODO: Create a delay using timer 2 for "delay" microseconds.
    TMR2 = 0;
    PR2 = delay*39;
    T2CONbits.TCKPS = 7;//pre-scalar
    T2CONbits.TCS = 0;//osc config
    IFS0bits.T2IF = 0;//flag
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF == 0){}
    T2CONbits.ON = 0;
    IFS0bits.T2IF = 0;

}
