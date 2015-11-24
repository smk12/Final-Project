/* 
 * File:   switch.c
 * Author: Sean Kenney
 *
 * Created on August 27, 2015, 3:12 PM
 */

#include <xc.h>

#define INPUT 1
#define OUTPUT 0

void initSwitch1()
{
    TRISDbits.TRISD6 = INPUT;   //SW1 = input
    CNCONDbits.ON = 1;          //CN on
    CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    CNPUDbits.CNPUD6 = 1;       //Enable PUR    
}
