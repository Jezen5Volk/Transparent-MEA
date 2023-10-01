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
#include <Programs.h>
#include <Arduino.h>
#include <SPI.h>

/*-------------------------------
USER PROGRAMMABLE HYPERPARAMETERS
-------------------------------*/

int freq; //frequency in Hz of stimulation signals [Hz]
int e_dly; //delay between activating sequential electrodes in milliseconds [mS]
int puls_dur_pos; //duration of positive voltage signal in microseconds [mS] 
int puls_dur_neg; //duration of negative voltage signal in microseconds [mS]
int brst_dur; //duration of voltage waveform in seconds [S]
int quiet_dur; //duration of silent period in seconds [S]
int rounds; //number of repetitions of burst + quiet periods [unitless]
float amp_pos; //amplitude of positive voltage in range from (2.5, 5] Volts [V]
float amp_neg; //amplitude of negative voltage in range from [0, 2.5) Volts [V]
std::vector<int> e; //containing the electrodes to be stimulated, in order

/*------------------------------
NOTHING ELSE NEED BE MODIFIED :)
------------------------------*/

void setup(){

    

};


void loop(){
    
};