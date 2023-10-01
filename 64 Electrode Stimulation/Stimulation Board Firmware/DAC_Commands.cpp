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


/*-----------------
Low Level Functions
-----------------*/

void xfer_data(std::string data, int size){

    //Convert binary string into array of bytes, MSB First
    std::vector<uint8_t> byte_stream;
    for (int i = 0; i < size; i++){
      std::string byte_string = data.substr(i*8, 8);
      uint8_t byte = std::bitset<8>(byte_string).to_ulong();
      byte_stream[i] = byte;
    }

    //Transfer byte stream over SPI, one byte at a time
    digitalWrite(SYNCpin, LOW);
    for (int i = 0; i < sizeof(byte_stream); i++){
        SPI.transfer(byte_stream[i]);
    }
    digitalWrite(SYNCpin, HIGH);

};

//Resets to zero scale
void reset(){

    digitalWrite(RESETpin, LOW);
    elapsedMicros RESET_timer;
    if (RESET_timer >= 1){
        digitalWrite(RESETpin, HIGH);
    };

}; 


/*--------------------
Medium Level Functions
--------------------*/

//Daisy Chain Enable
void DCEN(){

    //Make data strings to transfer
    std::string DCEN_cmd = std::bitset<4>(1000).to_string(); //1000 command: Set up the daisy-chain enable (DCEN) register
    std::string DCEN = std::bitset<20>(1).to_string(); //toggling LSB enables/disables daisy chain mode
    std::string DCEN_word = DCEN_cmd + DCEN;
    std::string no_op = std::bitset<24>(0).flip().to_string(); //1111 command: no operation, in daisy chain mode

    //Enable Daisy Chaining on each DAC sequentially starting at DAC 1
    for(int i = 1; i <= N_DACS; i++){
        std::string data_word;
        for(int j = 0; j < i; j++){
            if(j == 0){
                data_word = DCEN_word;
            }
            else{
                data_word = data_word + no_op;
            }
        }
        xfer_data(data_word, i*3);
    }

};   
    
//Write a voltage to a DAC Register
void write_DAC_reg(float voltage, int reg){

    //Convert to 12 bit voltage + 4 don't care bits
    int v_res = std::floor(voltage/DAC_RES);
    std::string voltage_bits = std::bitset<12>(v_res).to_string();
    std::string dc_bits = std::bitset<4>(0).to_string();  

    //Convert register number to 4 bit address and combine with write command
    int DAC_num = reg/16;
    std::string address = std::bitset<4>(reg - DAC_num*16).to_string();
    std::string command_wrt = std::bitset<4>(0001).to_string(); //0001 command: writes to addressed input register

    //Combine voltage, don't care, address, and command bits
    std::string voltage_word = command_wrt + address + voltage_bits + dc_bits;

    //Combine voltage word with no operation command for data word for all DACs
    std::string data_word;
    std::string no_op = std::bitset<24>(0).flip().to_string(); //1111 command: no operation, in daisy chain mode
    for (int i = N_DACS; i > 0; i--){
        if (i == DAC_num + 1){
            data_word = data_word + voltage_word;
        }
        else{
            data_word = data_word + no_op;
        }
    }
    
    //Send data word through SPI
    xfer_data(data_word, N_DACS*3);

}; 


/*------------------
High Level Functions
------------------*/

//Resets all DAC outputs to REF voltage (2.5 V) 
void ref_reset(){
    
    for(int i = 0; i < 16*N_DACS; i ++){
        write_DAC_reg(2.5, i);
    }

    //ensure LDAC is held low long enough 
    digitalWrite(LDACpin, LOW);
    elapsedMicros LDAC_timer; 
    if (LDAC_timer >= 1){
        digitalWrite(LDACpin, HIGH);
    }

}; 

//Writes voltage to selected registers simultaneously
void sync_write(float voltage, std::vector<int> regs){

    for(int i = 0; i < sizeof(regs) - 1; i++){
        write_DAC_reg(voltage, regs[i]);
    }

    //ensure LDAC is held low long enough 
    digitalWrite(LDACpin, LOW);
    elapsedMicros LDAC_timer; 
    if (LDAC_timer >= 1){
        digitalWrite(LDACpin, HIGH);
    }


}; 

//Writes voltage to selected registers sequentially with delay in mSec
void seq_write(float voltage, std::vector<int> regs, int seq_delay){

    digitalWrite(LDACpin, LOW); //when LDAC is low, the input register is transparent
    elapsedMillis timer;
    for(int i = 0; i < sizeof(regs) - 1; i++){
        write_DAC_reg(voltage,regs[i]);
        while(timer <= seq_delay){}; //delay without occupying hardware
        timer = 0;
    }
    
    //ensure LDAC is held low long enough 
    elapsedMicros LDAC_timer; 
    if (LDAC_timer >= 1){
        digitalWrite(LDACpin, HIGH);
    }

}; 

void p_pulse(int e_dly, int puls_dur_pos, int puls_dur_neg, int brst_dur, float amp_pos, float amp_neg, std::vector<int> regs){
    
    //Stimulate each electrode simultaneously
    if (e_dly == 0){
        elapsedMicros clock;
        if(clock <= puls_dur_pos){
            sync_write(amp_pos, regs);
        };
        if(clock > puls_dur_pos && clock < puls_dur_pos + puls_dur_neg){
        sync_write(amp_neg, regs);
        };
        if(clock >= puls_dur_pos + puls_dur_neg){
        sync_write(2.5, regs); //at pulse end, set back to ref voltage
        };
    }

    //Stimulate each electrode with delay between each electrode
    else{
        digitalWrite(LDACpin, LOW); //when LDAC is low, the input register is transparent
        elapsedMillis clock_ms;
        elapsedMicros clock_us;
        for(int i = 0; i < sizeof(regs) - 1; i++){
            while(clock_ms < e_dly){
                if (clock_us <= puls_dur_pos){
                    write_DAC_reg(amp_pos, regs[i]); 
                };
                if (clock_us > puls_dur_pos && clock_us < puls_dur_pos + puls_dur_neg){
                    write_DAC_reg(amp_neg, regs[i]);
                };
                if (clock_us >= puls_dur_pos + puls_dur_neg){
                    write_DAC_reg(2.5, regs[i]); //at pulse end, set back to ref voltage
                };
            }
            clock_ms = 0;
            clock_us = 0;
        }
    
        //ensure LDAC is held low long enough 
        elapsedMicros LDAC_timer; 
        if (LDAC_timer >= 1){
            digitalWrite(LDACpin, HIGH);
        }
    }

};