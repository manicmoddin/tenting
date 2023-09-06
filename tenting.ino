///////////////////////////////////////
//
// Tenting
//
// As an active camper, I find that having some conforts are useful.
// Current Thinking is:
// 
// 1. Bedroom Illumination
// 2. Living room Illumination
// 3. Doorway Illumination (full colour addressable LEDs 
//   a. Scout Group Necker colours
//   b. unique colour, so can spot it from a distance
// 4. Perimiter Illumination to help people avoid tripping up on guy-lines
// 5. remote control for the illumination - current remote is :
// 6. Temperature logging (pub bragging rights, it got to -5 XD
// 7. Light Level logging - interested...
// 8. Battery Level 
// 9. Solar input?
//
// Author: Jimmy Kemp   Date: 06/09/2023
// Email : arduino(at)manicmoddin(dot)co(dot)uk
//
///////////////////////////////////////////////////////

// Libraies
#include <IRremote.hpp>

// Constants
#define IR_RECEIVE_PIN 2

// Chosen below as they have PWM contol to change brightness
const int bedroomPin = 3;
const int livingPin = 4;
const int guylinePin = 9;

// Global Variables
int lightBank = 1;      // Current selected bank of lights, 1 Bedroom, 2: living 3: guyline 4: Archway

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop() {
    /*
     * Check if received data is available and if yes, try to decode it.
     * Decoded result is in the IrReceiver.decodedIRData structure.
     *
     * E.g. command is in IrReceiver.decodedIRData.command
     * address is in command is in IrReceiver.decodedIRData.address
     * and up to 32 bit raw data in IrReceiver.decodedIRData.decodedRawData
     */
    if (IrReceiver.decode()) {

        /*
         * Print a short summary of received data
         */
        // IrReceiver.printIRResultShort(&Serial);
        // IrReceiver.printIRSendUsage(&Serial);
        // if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
        //     Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
        //     // We have an unknown protocol here, print more info
        //     IrReceiver.printIRResultRawFormatted(&Serial, true);
        // }
        // Serial.println();

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value

        /*
         * Finally, check the received data and perform actions according to the received command
         */

        if (IrReceiver.decodedIRData.command == 0xA1) {
            Serial.println("Button A1 pressed");
        } else if (IrReceiver.decodedIRData.command == 0xA2) {
            Serial.println("Button A2 pressed");
        }
    }
}
