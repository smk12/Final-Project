// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
//#include "lcd.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"
#include "config.h"
#include "interrupt.h"
#include "math.h"

#define  adcBuffer ADC1BUF0

#define FORWARD     1
#define BACKWARD    0
#define THRESHOLD   512

int direction = FORWARD;

int main(void)
{
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initADC();
    initPWM();
    initTimer2(); 
    
    while(1)
    {
        
        if(IFS0bits.AD1IF==1){  
         IFS0bits.AD1IF = 0;
         
         if((adcBuffer>=480)&(adcBuffer<=544))
         {
             OC1RS = 1023;
             OC3RS = 1023;
         }
         else if(adcBuffer>544)
         {
             OC1RS = 1023;
             if(adcBuffer > 980)
                 OC3RS = 0;
             else
                OC3RS = 1023-(int)(adcBuffer/2);
             
         }
         else 
         {
             OC3RS = 1023;
             OC1RS = adcBuffer * 2;
         }
         /*
         if(adcBuffer < 512){
                OC1RS = (THRESHOLD-adcBuffer)*2; 
                OC3RS = (THRESHOLD-adcBuffer)*2;
                direction= BACKWARD;
                flipFlop(direction);
            }
            else{
                OC1RS = (adcBuffer-THRESHOLD)*2; 
                OC3RS = (adcBuffer-THRESHOLD)*2;
                direction= FORWARD;
                flipFlop(direction);
            }
         */
        }    
    }
    return 0;   
}
