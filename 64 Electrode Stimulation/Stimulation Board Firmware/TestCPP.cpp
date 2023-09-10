#include <bitset>
#include <iostream>
#include <string>
#define DAC_RES (5.0/4095)
#define N_DACS 4


void main(){
    float voltage = 2.5;
    int reg = 1;

    //Convert voltage to 16 bit data word
    int v_range = std::floor(voltage/DAC_RES);
    std::bitset<12> voltage_bits = std::bitset<12>(v_range);
    std::bitset<4> dc_bits = std::bitset<4>(0); 
    std::bitset<16> data_bits = std::bitset<16>(voltage_bits.to_string() + dc_bits.to_string());

    //Convert register number to 4 bit address and combine with write command
    int DAC_num = reg/16;
    std::bitset<4> address = std::bitset<4>(reg - DAC_num*16);
    std::bitset<4> command = std::bitset<4>(0001); //0001 command writes to addressed input register

    //Combine data bits, write command, and register address
    std::bitset<24> voltage_word = std::bitset<24>(command.to_string() + address.to_string() + data_bits.to_string());

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

    std::cout << data_word;
}
