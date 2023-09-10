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

void xfer_data(void* data, int size){
    digitalWrite(SYNCpin, LOW);
    SPI.transfer(data, size);
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
    //Convert voltage to 16 bit data word
    int v_range = std::floor(voltage/DAC_RES);
    std::bitset<12> voltage_bits = std::bitset<12>(v_range);
    std::bitset<4> dc_bits = std::bitset<4>(0); //Don't care bits 
    std::bitset<16> data_bits = std::bitset<16>(voltage_bits.to_string() + dc_bits.to_string());

    //Convert register number to 4 bit address and combine with write command
    int DAC_num = reg/16;
    std::bitset<4> address = std::bitset<4>(reg - DAC_num*16);
    std::bitset<4> command_w = std::bitset<4>(0001); //0001 command: writes to addressed input register

    //Combine data bits, write command, and register address
    std::bitset<24> voltage_word = std::bitset<24>(command_w.to_string() + address.to_string() + data_bits.to_string());

    //Combine voltage word with no operation command for complete data word
    std::string container;
    std::bitset<24> no_op = std::bitset<24>(0000); //0000 command: no operation
    for (int i = N_DACS; i >= 0; i--){
        if (i == DAC_num + 1){
            container = container + voltage_word.to_string();
        }
        else{
            container = container + no_op.to_string();
        }
    }
    std::bitset<24*N_DACS> data_word = std::bitset<24*N_DACS>(container);

    //Send data word through SPI
    xfer_data(&data_word, 3*N_DACS);
    
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
