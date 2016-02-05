#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

void initSwitch1()
{
    TRISDbits.TRISD6= INPUT;
    CNPUDbits.CNPUD6= ENABLED;
    CNCONDbits.ON =1;
    CNENDbits.CNIED6= ENABLED;
    IFS1bits.CNDIF=0;
    IEC1bits.CNDIE= ENABLED;
    IPC8bits.CNIP=7;
    //IPC8bits.CNIP=7;
    
  
}