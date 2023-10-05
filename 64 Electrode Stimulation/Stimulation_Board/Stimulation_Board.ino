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

#include "DAC_Commands.h"
#include "Programs.h"
#include <Arduino.h>
#include <SPI.h>

PROGRAM stim; //define PROGRAM object for running functions

/*-------------------------------
USER PROGRAMMABLE HYPERPARAMETERS
-------------------------------*/

unsigned long int freq = 50;                       //frequency in Hz of stimulation signals [Hz]
unsigned long int e_dly = 5;                       //delay between activating sequential electrodes in milliseconds [mS]
unsigned long int puls_dur_pos = 1000;             //duration of positive voltage signal in microseconds [uS] 
unsigned long int puls_dur_neg = 1000;             //duration of negative voltage signal in microseconds [uS]
unsigned long int brst_dur = 60;                   //duration of voltage waveform in seconds [S]
unsigned long int quiet_dur = 60;                  //duration of silent period in seconds [S]
int rounds = 10;                                   //number of repetitions of burst + quiet periods [unitless]
float amp_pos = 3;                                 //amplitude of positive voltage in range from (2.5, 5] Volts [V]
float amp_neg = 1;                                 //amplitude of negative voltage in range from [0, 2.5) Volts [V]
std::vector<int> e = {12, 53, 5, 0};               //electrodes in order of stimulation from [0, 63]

/*------------------------------
NOTHING ELSE NEED BE MODIFIED :)
------------------------------*/


/*
    Things to note: 
        -If you wish to enable all electrodes, replace stim.burst(...) with stim.burst_all();
            -This will require moving the electrode argument (e)

        -If you wish to stimulate a selection of electrodes simultaneously, set e_dly to 0
*/

void setup(){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    stim.start_up();
    stim.burst(freq, e_dly, puls_dur_pos, puls_dur_neg, brst_dur, quiet_dur, rounds, amp_pos, amp_neg, e);
};


void loop(){
    digitalWrite(LED_BUILTIN,HIGH); //LED turning on indicates the program has finished
};
