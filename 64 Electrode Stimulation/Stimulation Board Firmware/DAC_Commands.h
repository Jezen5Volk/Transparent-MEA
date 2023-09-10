#ifndef DAC_COMMANDS
#define DAC_COMMANDS

#define REGISTER_0 0b0000
#define REGISTER_1 0b0001
#define REGISTER_2 0b0010
#define REGISTER_3 0b0011
#define REGISTER_4 0b0100
#define REGISTER_5 0b0101
#define REGISTER_6 0b0110
#define REGISTER_7 0b0111
#define REGISTER_8 0b1000
#define REGISTER_9 0b1001
#define REGISTER_10 0b1010
#define REGISTER_11 0b1011
#define REGISTER_12 0b1100
#define REGISTER_13 0b1101
#define REGISTER_14 0b1110
#define REGISTER_15 0b1111

#define RESET 10
#define SYNCpin 14
#define LDACpin 15

class DAC
{
    public:
    
    /*-----------------
    Low Level Functions
    -----------------*/
    void xfer_data(void* data, int size);
    void reset(); //Resets to zero scale

    /*--------------------
    Medium Level Functions
    --------------------*/
    void DCEN(); //Daisy Chain Enable  
    void write_DAC_reg(void* voltage); //Write a voltage to a DAC Register

    /*------------------
    High Level Functions
    ------------------*/
    void ref_reset(); //Resets all DAC outputs to REF voltage (2.5 V) 
    void sync_write(int voltage, int registers[]); //Writes voltage to selected registers simultaneously
    void seq_write(int voltage, int registers[], int delay_msec); //Writes voltage to selected registers sequentially with delay
};



#endif 