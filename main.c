

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
typedef enum stateTypeEnum{led1,led2,led3} stateType;

//volatile int state=1;//declaring a global volatile variable
volatile stateType state=led1;
volatile int time=0;
volatile int up=0;//if up = 1 lights going backwards
volatile int switch1=1; //if switch is pressed we change the direction of the lights

//TODO: Use volatile variables that change within interrupts

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function--done!
    initLEDs();
    //initTimer1();
   initTimer2();
    initSwitch1();
    
    
    while(1){         
        switch(state)
       {
                case led1:
                    //state=2;
                    if(up==1)
                    {
                        state=led3;
                    }
                    else if(switch1==1)
                    {
                        state=led2;
                    }
                    
                    up=0;
                    switch1=0;
                     delayMs(10);
                    break;
                
                case led2:
                    //state=3;
                    if(up==1)
                    {
                        state=led1;
                    }
                    else if(switch1==1)
                    {
                        state=led3;
                    }
                    
                    up=0;
                    switch1=0;
                      delayMs(10);
                    break;
                     
                case led3:
                    //state=1;
                    if(up==1)
                    {
                        state=led2;
                    }
                    else if(switch1==1)
                    {
                        state=led1;
                    }
                    
                    up=0;
                    switch1=0;
                       delayMs(10);
                    break;
        }
          switch(state)
          {
            case led1:
                 LATDbits.LATD0=1;
                    LATDbits.LATD1=0;
                    LATDbits.LATD2=0;
                    
                    break;
            case led2:
                LATDbits.LATD0=0;
                    LATDbits.LATD1=1;
                    LATDbits.LATD2=0;
                    
                    break;
            case led3:
                 LATDbits.LATD0=0;
                    LATDbits.LATD1=0;
                    LATDbits.LATD2=1;
                    
                    break;
          }
              
        
        
    }
    
    return 0;
}


void __ISR(_TIMER_1_VECTOR, IPL7SRS)_T1Interrupt()
{
 IFS0bits.T1IF=0; 
time=time+1;
}



void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
    
    IFS1bits.CNDIF=0;
    initTimer1(); 

     
    int j;
    j=PORTD;
    
    if(PORTDbits.RD6==1 && time>=1)
    {
        up=1;  
    }
    else if(PORTDbits.RD6==1)
    {
        switch1=1;
    }
      time=0;
   }
  

