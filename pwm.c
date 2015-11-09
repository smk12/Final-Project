/* 
 * File:   pwm.h
 * Author: gvanhoy
 *
 * Created on October 8, 2015, 9:14 AM
 */

#include <xc.h>

#define OUTPUT 0
#define MAPOC11 RPD0Rbits.RPD0R   // map OC1 to RD0
#define MAPOC31 RPD2Rbits.RPD2R   // map OC3 to RD2
#define MAPOC12 RPD8Rbits.RPD8R   // map OC3 to RD2
#define MAPOC32 RPD10Rbits.RPD10R  // map OC3 to RD2
#define MAP1    0b1100
#define MAP3    0b1011

#define SETUPWHEEL11 TRISDbits.TRISD0
#define SETUPWHEEL31 TRISDbits.TRISD2
#define SETUPWHEEL12 TRISDbits.TRISD8
#define SETUPWHEEL32 TRISDbits.TRISD10


#define WHEEL11 LATDbits.LATD0
#define WHEEL31 LATDbits.LATD2
#define WHEEL12 LATDbits.LATD8
#define WHEEL32 LATDbits.LATD10
 

void initPWM(){
    SETUPWHEEL11 = OUTPUT; 
    SETUPWHEEL31 = OUTPUT;
    SETUPWHEEL12 = OUTPUT;
    SETUPWHEEL32 = OUTPUT;
            
    MAPOC11= MAP1; 
    OC1CON = 0x0000; // Turn off OC1 while doing setup.
    OC1R = 0x0000; // Initialize primary Compare Register
    OC1RS = 0X0000; // Initialize secondary Compare Register
    OC1CON = 0x0006; // Configure for PWM mode
    OC1CONSET = 0x8000; // Enable OC1
    
    
    MAPOC31 = MAP3; 
    OC3CON = 0x0000; // Turn off OC3 while doing setup.
    OC3R = 0x0000; // Initialize primary Compare Register
    OC3RS = 0x0000; // Initialize secondary Compare Register
    OC3CON = 0x0006; // Configure for PWM mode
    OC3CONSET = 0x8000; // Enable OC3 
     
    
    WHEEL12 = 0;
    WHEEL32 = 0;
}

void flipFlop(int direction){
    if (direction == 0){
        MAPOC12= MAP1;
        MAPOC32 = MAP3;
        WHEEL11 = 0;
        WHEEL31 = 0;  
    }
    else { 
        MAPOC11= MAP1;
        MAPOC31 = MAP3;
        WHEEL12 = 0;
        WHEEL32 = 0;  
    }
}
  
