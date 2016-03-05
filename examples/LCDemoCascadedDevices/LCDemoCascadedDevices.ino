//We always have to include the library
#include "MatrixCascade.h"

/*
 Now we need a LedMatrix to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 ***** Please set the number of devices you have *****
 But the maximum default of 8 MAX72XX wil also work.
 */
MatrixCascade<3> lc(12, 11, 10);

/* we always wait a bit between updates of the display */
unsigned long delaytime = 30;

/* 
 This time we have more than one device. 
 But all of them have to be initialized 
 individually.
 */
void setup() {
    
    Serial.begin(9600);

    Serial.print( "size: " );
    Serial.println( lc.size() );

    //we have already set the number of devices when we created the LedMatrix
    int devices = lc.size();
    //we have to init all devices in a loop
    for(int address=0; address<devices; address++) {
        
        Serial.print( "I: " );
        Serial.print( address );
        Serial.print( "\t" );
        Serial.println( lc[address].getIndex() );

        // The MAX72XX is in power-saving mode on startup
        lc[address].wakeup();
        //  Set the brightness to a medium values
        lc[address].setIntensity(1);
        //  and clear the display
        lc[address].clear();

        Serial.println( "^" );



        /*
        lc.wakeup();
        // Set the brightness to a medium values
        //lc.setIntensity(8);
        lc.setIntensity(1);
        // and clear the display
        lc.clear();
        */
    }
    lc[1].setRotation(2);
    lc[2].setRotation(2);
}

/*
void loop() { 
    //read the number cascaded devices
    int devices=lc.size();
    
    //we have to init all devices in a loop
    for(int row=0; row<8; row++) {
        for(int col=0; col<8; col++) {
            for(int address=0; address<devices; address++) {
                delay(delaytime);
                lc[address].on(row, col);
                //delay(delaytime);
                //lc[address].off(row, col);

                Serial.print( "loop :" );
                Serial.print( row );
                Serial.print( "\t" );
                Serial.println( col );
            }
        }
    }
}
*/

void loop() { 
    //read the number cascaded devices
    int devices=lc.size();
    
    for(uint8_t rotate = 0; rotate < 4; rotate++) {
        for(int ind = 0; ind < devices; ind++) {
            lc[ind].setRotation();
            for(int row=0; row<8; row++) {
                for(int col=0; col<8; col++) {
                    delay(delaytime);
                    lc[ind].on(row, col);
                }
            }
            lc[ind].clear();
        }
        /*
        for(int ind = devices-1; ind >= 0; ind--) {
            for(int col=0; col < 8; col++) {
                for(int row=0; row < 8; row++) {
                    delay(delaytime);
                    lc[ind].off(row, col);
                }
            }
        }
        */


    }


}

/*
void loop() { 
    //read the number cascaded devices
    int devices=lc.size();
    
        for(int row=0; row<8; row++) {
            for(int col=0; col<8; col++) {
                delay(delaytime);
                lc[0].on(row, col);
            }
        }
        for(int col=0; col<8; col++) {
            for(int row=0; row<8; row++) {
                delay(delaytime);
                lc[0].off(row, col);
            }
        }
}
*/
