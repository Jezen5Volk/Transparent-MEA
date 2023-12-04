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
    void burst(unsigned long int freq, unsigned long int e_dly, unsigned long int puls_dur_pos, unsigned long int puls_dur_neg, unsigned long int brst_dur, unsigned long int quiet_dur, int rounds, float amp_pos, float amp_neg, std::vector<int> e); 
    
    void burst_all(unsigned long int freq, unsigned long int e_dly, unsigned long int puls_dur_pos, unsigned long int puls_dur_neg, unsigned long int brst_dur, unsigned long int quiet_dur, int rounds, float amp_pos, float amp_neg, std::vector<int> e);

};




#endif 
