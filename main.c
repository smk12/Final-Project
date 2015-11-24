// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "adc.h"
#include "pwm.h"
#include "config.h"
#include "switch.h"
#include "interrupt.h"
#include "math.h"

#define Rthresh 60
#define Cthresh 115
#define Lthresh 200
#define MAX 250
#define MIN 0

#define  rightBuff ADC1BUF0
#define  centerBuff ADC1BUF1
#define  leftBuff ADC1BUF2

#define rightMotor OC1RS
#define leftMotor OC3RS

#define PRESS 0
#define SWITCH PORTDbits.RD6



typedef enum {
    wait, forward, Lturn, Rturn, logic, Aturn
} stateType;

volatile stateType currState = wait;
volatile stateType lastState = forward;
volatile int temp;
volatile int x, y, z;
volatile int dt=6;

int main(void)
{
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    initADC();
    initPWM();
    initTimer2(); 
    
    while(1)
    {
        switch(currState)
        {
                case wait:
                    leftMotor = MIN; rightMotor = MIN;
                    if(SWITCH == PRESS)
                        currState = forward;
                    break;
                case forward:
                    lastState = currState;
                    leftMotor = MAX; rightMotor = MAX;    //Real Code
                    //leftMotor = MIN; rightMotor = MIN;      //Test Code
                    currState = logic;
                    delayMs(dt);
                    break;
                case Lturn:
                    lastState = currState;
                    leftMotor = MIN; rightMotor = MAX;
                    /*
                    for(temp=0;leftBuff < Lthresh;temp++)
                    {
                        leftMotor = MIN; rightMotor = MAX;  //Real code
                        //leftMotor = MIN; rightMotor = MIN;         //Test Code
                        IFS0bits.AD1IF = 0;
                    }
                    */
                    delayMs(dt);
                    currState = logic;
                    break;
                case Rturn:
                    lastState = currState;
                    rightMotor = MIN; leftMotor = MAX;
                    /*
                    for(temp=0;rightBuff < Rthresh;temp++)
                    {
                        rightMotor = MIN; leftMotor = MAX;
                        //leftMotor = MIN; rightMotor = MIN;      //Test Code
                        IFS0bits.AD1IF = 0;
                    }
                    */
                    currState = logic;
                    delayMs(dt);
                    break;
                case Aturn:
                    lastState = currState;
                    leftMotor = MIN; rightMotor = 1000;
                    currState = logic;
                    delayMs(dt);
                    break;
                case logic:
                    while(IFS0bits.AD1IF!=1){}
                    IFS0bits.AD1IF = 0;
                    if((leftBuff > Lthresh)&&(rightBuff > Rthresh))
                        currState = forward;
                    else if((leftBuff < Lthresh)&&(rightBuff < Rthresh)&&(centerBuff < Cthresh))
                        currState = Aturn;
                    else if((leftBuff < Lthresh)&&(rightBuff < Rthresh))
                        currState = Lturn;
                    else if(leftBuff < Lthresh)
                        currState = Lturn;
                    else if(rightBuff < Rthresh)
                        currState = Rturn;
                    else
                        currState = forward;

                    break;
                
        }
    }
    return 0;   
}

