//Local Headers
#include <DAC_Commands.h>

//STL Headers
#include <cmath>
#include <bitset>
#include <string>

//3rd Party Headers
#include <Arduino.h>
#include <SPI.h>
#include <elapsedMillis.h>


/*-----------------
Low Level Functions
-----------------*/

void xfer_data(std::string data){

    //Convert binary string into array of bytes, MSB First
    uint8_t byte_stream[3*N_DACS];
    for (int i = 0; i < 3*N_DACS; i++){
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
    std::string no_op = std::bitset<24>(0000).to_string(); //0000 command: no operation
    for (int i = N_DACS; i > 0; i--){
        if (i == DAC_num + 1){
            data_word = data_word + voltage_word;
        }
        else{
            data_word = data_word + no_op;
        }
    }
    
    //Send data word through SPI
    xfer_data(data_word);

}; 


/*------------------
High Level Functions
------------------*/

//Resets all DAC outputs to REF voltage (2.5 V) 
void ref_reset(){

}; 

//Writes voltage to selected registers simultaneously
void sync_write(float voltage, int regs[]){

}; 

//Writes voltage to selected registers sequentially with delay
void seq_write(float voltage, int regs[], int delay_msec){

}; 
