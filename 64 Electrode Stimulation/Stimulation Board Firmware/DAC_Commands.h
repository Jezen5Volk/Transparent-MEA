#ifndef DAC_COMMANDS
#define DAC_COMMANDS

#define N_DACS 4 //There are 4 DACs on the Stimulation Board
#define DAC_RES (5.0/4095) //Max voltage is 5, 12 bit DAC, so resolution is 5/(2^12-1)

#define RESETpin 10
#define SYNCpin 14
#define LDACpin 15

class DAC
{
    public:
    
    /*-----------------
    Low Level Functions
    -----------------*/
    void xfer_data(std::string data);
    void reset(); //Resets to zero scale

    /*--------------------
    Medium Level Functions
    --------------------*/
    void DCEN(); //Daisy Chain Enable  
    void write_DAC_reg(float voltage, int reg); //Write a voltage to a DAC Register

    /*------------------
    High Level Functions
    ------------------*/
    void ref_reset(); //Resets all DAC outputs to REF voltage (2.5 V) 
    void sync_write(float voltage, int regs[]); //Writes voltage to selected registers simultaneously
    void seq_write(float voltage, int regs[], int delay_msec); //Writes voltage to selected registers sequentially with delay in mSec
};



#endif 