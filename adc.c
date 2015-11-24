/* 
 * File:   adc.h
 * Author: gvanhoy
 *
 * Created on October 1, 2015, 10:19 AM
 */

#include <xc.h>

void initADC(){
    
    //TRISBbits.TRISB1 = 1;
    //ANSELBbits.ANSB1 = 0; // pin 33 j11
    TRISEbits.TRISE6 = 1;   //AN23 right sensor
    ANSELEbits.ANSE6 = 0;
    TRISEbits.TRISE4 = 1;   //AN21 middle sensor
    ANSELEbits.ANSE4 = 0;
    TRISEbits.TRISE2 = 1;   //AN20 left sensor
    ANSELEbits.ANSE2 = 0;
    
    AD1CON1bits.FORM = 0; // 16 unsigned integer
    AD1CON1bits.SSRC = 7; // Auto-convert mode
    AD1CON1bits.ASAM = 1; // Auto-sampling
    AD1CON2bits.VCFG = 0; // Use board refernece voltages
    AD1CON2bits.CSCNA = 1; // Enable scanning
    AD1CON2bits.SMPI = 2; // 3 burrito
    AD1CON2bits.ALTS = 0; // Only Mux A
    AD1CON3bits.ADRC = 0; // Use PBCLK
    AD1CON3bits.SAMC = 2; // 2 Tad per sample
    AD1CON3bits.ADCS = 1; // 4 times the PBCLK
    AD1CHSbits.CH0NA = 0; // Use Vref- as negative reference
    
    //AD1CHSbits.CH0SA = 1; // Scan AN0 at least
    
    AD1CSSLbits.CSSL20 = 1; //left sensor
    AD1CSSLbits.CSSL21 = 1; //middle
    AD1CSSLbits.CSSL23 = 1; //right

    
    IFS0bits.AD1IF = 0; // Put down ADC flag
    //IPC5bits.AD1IP = 7;
    //IEC0bits.AD1IE = 1;
    AD1CON1bits.ADON = 1; // turn on the ADC
}
