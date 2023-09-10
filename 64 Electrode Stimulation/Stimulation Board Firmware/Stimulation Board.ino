/*
The MIT License (MIT)

Author: Samantha Herman (They/Them), Bouwmeester Group — UCSB

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions: The above copyright notice and this 
permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <DAC_Commands.h>
#include <Arduino.h>
#include <SPI.h>

void setup(){

    //Setting up output pins
    pinMode(RESETpin, OUTPUT);
    pinMode(SYNCpin, OUTPUT); 
    pinMode(LDACpin, OUTPUT); 
    digitalWrite(RESETpin,HIGH); //When RESET is activated, the input register and the DAC register are updated with zero-scale
    digitalWrite(SYNCpin, HIGH); //Bring the SYNC line low to begin the write sequence
    digitalWrite(LDACpin, HIGH); //When LDAC is low, the input registers for all DACs are transparent

    //SPI Initialization
    SPI.begin();
    SPI.beginTransaction(SPISettings(50000000, MSBFIRST, SPI_MODE0));

};


void loop(){

};