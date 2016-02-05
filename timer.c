/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#include "timer.h"

void initTimer1(){
    TMR1=0; //clear timer
    PR1=39061;//initializing PR1
    T1CONbits.TCKPS= 3;//setting prescalar for 1 sec
    T1CONbits.TCS=0;//counter
    IEC0bits.T1IE=1; //interrupt configuration
    IFS0bits.T1IF=0;
    IPC1bits.T1IP=7; //priority
    T1CONbits.ON=1; //turning timer on

}

initTimer2(){
    TMR2=0;
    T2CONbits.TCKPS=0;
    T2CONbits.TCS=0;
    IFS0bits.T2IF=0;
}

delayMs(unsigned int delay){
    TMR2= 0;
    PR2 = 624*delay;
    IFS0bits.T2IF=0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF==0){};
    T2CONbits.ON=0;
}

void resetTimer1() {
    TMR1=0;
    T1CONbits.ON=0;
}

void resetTimer2() {
    TMR2=0;
    T2CONbits.ON=0;
}