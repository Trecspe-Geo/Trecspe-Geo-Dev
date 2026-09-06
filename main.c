#define F_CPU 3333333UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Src/hw_desc/inc/hw_desc_io.h"



int main(void)
{

    sDio_t sDigIO = {0};  // Initialize the sDio_t structure to zero

    vInitPin(&sDigIO, IO_PORT_A_PIN_00, IO_DIR_OUTPUT,PULL_NONE);


    // if (sDigIO.pfvLevelOn != NULL)
    // {
    //     sDigIO.pfvLevelOn();
    // }

    while (1) 
    {

       sDigIO.pfvLevelOn();  // Set the pin to high
       _delay_ms(100); // Delay for 1 second
        sDigIO.pfvLevelOff();  // Set the pin to high

        _delay_ms(100); // Delay for 1 second 
        sDigIO.pfvLevelOn();  // Set the pin to high
       _delay_ms(100); // Delay for 1 second

       sDigIO.pfvLevelOff();  // Set the pin to high
        _delay_ms(1000); // Delay for 1 second
        

    }
}