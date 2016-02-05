/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"
#define ON 1
#define OUTPUT 0

void initLEDs(){
    
LATDbits.LATD0=ON;//define LED1 as output and initialize as ON
    TRISDbits.TRISD0= OUTPUT;
    
LATDbits.LATD1= ON;//define LED2 as output and initialize as ON
    TRISDbits.TRISD1= OUTPUT;
    
LATDbits.LATD2= ON; //define LED3 as output and initialize as ON
    TRISDbits.TRISD2= OUTPUT;    
}

void turnOnLED(int led){
//    
//    led=ON;
//    return;
//    
}
//
//void turnOffLED(int led){
//    led=0;
//    return;
//    
//}