#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

void initSwitch1()
{
    TRISDbits.TRISD6= INPUT;
    CNCONDbits.ON =1;
    CNENDbits.CNIED6= ENABLED;
    CNPUDbits.CNPUD6= ENABLED;
    IFS1bits.CNDIF=0;
    IPC8bits.CNIP=2;
    IPC8bits.CNIP=3;
    IEC1bits.CNDIE= ENABLED;
  
}