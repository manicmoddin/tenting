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
#define IR_USE_AVR_TIMER1
#include <IRremote.hpp>

// Constants
#define IR_RECEIVE_PIN 2

// Chosen below as they have PWM contol to change brightness
const int bedroomPin = 3;
const int livingPin = 5;
const int guylinePin = 6;

// Global Variables
int lightBank = 1;      // Current selected bank of lights, 1 Bedroom, 2: living 3: guyline 4: Archway

unsigned long lastCommand = millis();
int commandTimeInterval = 500;

int bedroomPower = 0;
int livingPower = 0;
int guylinePower = 0;
int archwayPower = 0;

int brightnessStep = 30;

int bedroomBrightness = 150;
int livingBrightness = 150;
int guylineBrightness = 150;
int archwayBrightness = 150;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void increaseBrightness() {
    
    switch (lightBank)
    {
    case 1:
        Serial.println("Increasing Bedroom");
        if (bedroomBrightness + brightnessStep >= 255){
            bedroomBrightness = 255;
        }
        else {
            bedroomBrightness = bedroomBrightness + brightnessStep;
        }
        Serial.print("Bedroom Brightness : ");
        Serial.println(bedroomBrightness);
        break;
    
    case 2:
        Serial.println("Increasing Living");
        if (livingBrightness + brightnessStep >= 255){
            livingBrightness = 255;
        }
        else {
            livingBrightness = livingBrightness + brightnessStep;
        }
        Serial.print("Living Brightness : ");
        Serial.println(livingBrightness);
        break;
    
    case 3:
        Serial.println("Increasing Guyline");
        if (guylineBrightness + brightnessStep >= 255){
            guylineBrightness = 255;
        }
        else {
            guylineBrightness = guylineBrightness + brightnessStep;
        }
        Serial.print("Guyline Brightness : ");
        Serial.println(guylineBrightness);
        break;

    case 4:
        Serial.println("Increasing Archway");
        if (archwayBrightness + brightnessStep >= 255){
            archwayBrightness = 255;
        }
        else {
            archwayBrightness = archwayBrightness + brightnessStep;
        }
        Serial.print("Archway Brightness : ");
        Serial.println(archwayBrightness);
        break;

    default:
        break;
    }
}

void decreaseBrightness() {
    
    switch (lightBank)
    {
    case 1:
        Serial.println("Decreasing Bedroom");
        if (bedroomBrightness - brightnessStep <= 0){
            bedroomBrightness = 0;
        }
        else {
            bedroomBrightness = bedroomBrightness - brightnessStep;
        }
        Serial.print("Bedroom Brightness : ");
        Serial.println(bedroomBrightness);
        break;
    
    case 2:
        Serial.println("Decreasing Living");
        if (livingBrightness - brightnessStep <= 0){
            livingBrightness = 0;
        }
        else {
            livingBrightness = livingBrightness - brightnessStep;
        }
        Serial.print("Living Brightness : ");
        Serial.println(livingBrightness);
        break;
    
    case 3:
        Serial.println("Decreasing Guyline");
        if (guylineBrightness - brightnessStep <= 0){
            guylineBrightness = 0;
        }
        else {
            guylineBrightness = guylineBrightness - brightnessStep;
        }
        Serial.print("Guyline Brightness : ");
        Serial.println(guylineBrightness);
        break;

    case 4:
        Serial.println("Decreasing Archway");
        if (archwayBrightness - brightnessStep <= 0){
            archwayBrightness = 0;
        }
        else {
            archwayBrightness = archwayBrightness - brightnessStep;
        }
        Serial.print("Archway Brightness : ");
        Serial.println(archwayBrightness);
        break;

    default:
        break;
    }
}

void changeBank(int bankNumber) {
    lightBank = bankNumber;

    // Serial.println("Selected a new light bank");

    switch (lightBank)
    {
    case 1:
        Serial.println("Selected Bedroom");
        break;
    
    case 2:
        Serial.println("Selected Living");
        break;
    
    case 3:
        Serial.println("Selected GuyLine");
        break;

    case 4:
        Serial.println("Selected Archway");
        break;

    default:
        break;
    }
}

void togglePower() {
    switch (lightBank)
    {
    case 1:
        bedroomPower = ! bedroomPower;
        Serial.print("Bedroom going to ");
        Serial.println(bedroomPower);
        break;
    
    case 2:
        livingPower = ! livingPower;
        Serial.print("Living going to ");
        Serial.println(livingPower);
        break;
    
    case 3:
        guylinePower = ! guylinePower;
        Serial.print("guyline going to ");
        Serial.println(guylinePower);
        break;

    case 4:
        archwayPower = ! archwayPower;
        Serial.print("Archway going to ");
        Serial.println(archwayPower);
        break;

    default:
        break;
    }


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

        if (millis() - lastCommand >= commandTimeInterval) {
            Serial.println("I can now run");

        
            if (IrReceiver.decodedIRData.command == 0xA1) {
                changeBank(1);
            }
            
            if (IrReceiver.decodedIRData.command == 0xA2) {
                changeBank(2);
            }
            
            if (IrReceiver.decodedIRData.command == 0xA3) {
                changeBank(3);
            }

            if (IrReceiver.decodedIRData.command == 0xA4) {
                changeBank(4);
            }

            if (IrReceiver.decodedIRData.command == 0x8E) {
                togglePower();
            }

            if (IrReceiver.decodedIRData.command == 0x84) {
                increaseBrightness();
            }

            if (IrReceiver.decodedIRData.command == 0x85) {
                decreaseBrightness();
            }
            lastCommand = millis();
        }            
    }

    if (bedroomPower == 1) {
        analogWrite(bedroomPin, bedroomBrightness);
    }

    else {
        digitalWrite(bedroomPin, 0);
    }

    if (livingPower == 1) {
        analogWrite(livingPin, livingBrightness);
    }

    else {
        digitalWrite(livingPin, 0);
    }

    if (guylinePower == 1) {
        analogWrite(guylinePin, guylineBrightness);
    }

    else {
        digitalWrite(guylinePin, 0);
    }
}
