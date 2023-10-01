#ifndef PROGRAMS
#define PROGRAMS

#include <vector> 

class PROGRAM
{
    public:

    /*---
    Setup
    ---*/
    void start_up();
    
    void full_reset();

    /*-------------------------
    User Programmable Waveforms
    -------------------------*/
    void wvfrm(int freq, int e_dly, int puls_dur_pos, int puls_dur_neg, int brst_dur, int amp_pos, int amp_neg, std::vector<int> e); 
    /*
        freq: frequency in Hz of stimulation signals [Hz]
        e_dly: delay between activating sequential electrodes in milliseconds [mS]
        puls_dur_pos: duration of positive voltage signal in milliseconds [mS] 
        puls_dur_neg: duration of negative voltage signal in milliseconds [mS]
        brst_dur: duration of voltage waveform in seconds [S]
        amp_pos: amplitude of positive voltage in range from (0,2.5] Volts [V]
        amp_neg: amplitude of negative voltage in range from [-2.5,0) Volts [V]
        e: vector containing the electrodes to be stimulated, in order
    */

};

#endif 