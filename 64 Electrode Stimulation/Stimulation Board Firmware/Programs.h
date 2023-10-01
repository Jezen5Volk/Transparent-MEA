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
    void burst(int freq, int e_dly, int puls_dur_pos, int puls_dur_neg, int brst_dur, int amp_pos, int amp_neg, std::vector<int> e); 
   
};

#endif 