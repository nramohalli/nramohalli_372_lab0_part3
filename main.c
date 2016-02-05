/* 
 * File:   main.c
 * Author: gvanhoy/ nramohalli
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"
#include "interrupt.h"
#include "switch.h"
#include "led.h"
#include "timer.h"




#define OUTPUT 0
#define INPUT 1

//TODO: Define states of the state machine
//typedef enum stateTypeEnum{led1,led2,led3} stateType;

volatile int state=1;//declaring a global volatile variable
unsigned int temp=0;

//TODO: Use volatile variables that change within interrupts

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function--done!
    initLEDs();
    initTimer1();
    //initTimer2();
  
    initSwitch1();
    
    
    while(1){         
        switch(state)
       {
                case 1:
                    
                    LATDbits.LATD0=1;
                    LATDbits.LATD1=0;
                    LATDbits.LATD2=0;
                    break;
                
                case 2:
                    LATDbits.LATD0=0;
                    LATDbits.LATD1=1;
                    LATDbits.LATD2=0;
                    break;
                     
                case 3:
                    LATDbits.LATD0=0;
                    LATDbits.LATD1=0;
                    LATDbits.LATD2=1;
                    break;
                
                case 4: 
                    T2CONbits.ON=1;
             
                    break;
                case 5:
                    T2CONbits.ON=1;
                    break;
                case 6:
                    T2CONbits.ON=1;
                    break;
        }
        resetTimer1();
        resetTimer2();
    }
    
    return 0;
}


void __ISR(_TIMER_1_VECTOR, IPL3SRS)_T1Interrupt()
{
  if(state==1) state=5;
  else if(state==2)state=6;
  else if(state==3)state=4;
  T1CONbits.ON=0;
     TMR1=0;
IFS0bits.T1IF=0;  
}

void __ISR(_TIMER_2_VECTOR, IPL3SRS)_T2Interrupt()
{
   if(state==4) state=2; 
  else if(state==5)state=3;
  else if(state==6)state=1;
  
IFS0bits.T2IF=0;  
}
void __ISR(_CHANGE_NOTICE_VECTOR, IPL2SRS) _CNInterrupt() {
    
    if(state==1) state=4;
    else if(state==2)state=5;
    else if(state==3)state=6;
  if(PORTDbits.RD6==PRESSED) T1CONbits.ON=1;//put in if- else with condition of switch being pressed...maybe while loop
  IFS1bits.CNDIF=0;
}