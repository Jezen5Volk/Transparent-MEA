//Local Headers
#include <DAC_Commands.h>

//STL Headers
#include <cmath>
#include <bitset>
#include <string>
#include <vector> 

//3rd Party Headers
#include <Arduino.h>
#include <SPI.h>
#include <elapsedMillis.h>

//Define a DAC object
DAC dac;

/*---
Setup
---*/

void start_up(){

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

    //Low Level DAC commands
    dac.DCEN(); //Enable daisy chain
    dac.ref_reset(); //Resets all DAC outputs to REF voltage (2.5 V) 

};

void full_reset(){

    dac.reset(); //Resets to zero scale
    dac.ref_reset(); //Resets all Dac outputs to REF voltage (2.5 V)

};

/*-------------------------
User Programmable Waveforms
-------------------------*/

void burst(int freq, int e_dly, int puls_dur_pos, int puls_dur_neg, int brst_dur, int quiet_dur, int rounds, float amp_pos, float amp_neg, std::vector<int> e){ 

    /*
    freq: frequency in Hz of stimulation signals [Hz]
    e_dly: delay between activating sequential electrodes in milliseconds [mS]
    puls_dur_pos: duration of positive voltage signal in microseconds [uS] 
    puls_dur_neg: duration of negative voltage signal in microseconds [uS]
    brst_dur: duration of voltage waveform in seconds [S]
    quiet_dur: duration of silent period in seconds [S]
    rounds: number of repetitions of burst + quiet periods [unitless]
    amp_pos: amplitude of positive voltage in range from (2.5, 5] Volts [V]
    amp_neg: amplitude of negative voltage in range from [0, 2.5) Volts [V]
    e: electrodes in order of stimulation from [0, 63]
    */

    elapsedMillis burst_clck;
    elapsedMillis pulse_delay; 
    elapsedMillis quiet_clck;

    for(int i; i < rounds; i ++){
        burst_clck = 0;
        while (burst_clck < brst_dur*1000){
            if(pulse_delay >= 1000/freq){
                dac.p_pulse(e_dly, puls_dur_pos, puls_dur_neg, brst_dur, amp_pos, amp_neg, e);
                pulse_delay = 0;
            }
        }
        quiet_clck = 0;
        while (quiet_clck < quiet_dur*1000){
            // wait and don't be a buffer hog :)
        }
    }

};

void burst_all(int freq, int e_dly, int puls_dur_pos, int puls_dur_neg, int brst_dur, int quiet_dur, int rounds, float amp_pos, float amp_neg){
    
    std::vector<int> all_e;
    for (int i; i < N_DACS*16; i ++){
        all_e.push_back(i);
    }
    burst(freq, e_dly, puls_dur_pos, puls_dur_neg, brst_dur, quiet_dur, rounds, amp_pos, amp_neg, all_e);

};