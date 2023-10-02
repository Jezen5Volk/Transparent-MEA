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
    void burst(int freq, int e_dly, int puls_dur_pos, int puls_dur_neg, int brst_dur, int quiet_dur, int rounds, float amp_pos, float amp_neg, std::vector<int> e); 
    
    void burst_all(int freq, int e_dly, int puls_dur_pos, int puls_dur_neg, int brst_dur, int quiet_dur, int rounds, float amp_pos, float amp_neg);
};

#endif 