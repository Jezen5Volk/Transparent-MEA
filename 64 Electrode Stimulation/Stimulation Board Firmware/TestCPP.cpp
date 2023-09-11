#include <bitset>
#include <iostream>
#include <string>
#define DAC_RES (5.0/4095)
#define N_DACS 4


void main(){
    //Make data strings to transfer
    std::string DCEN_cmd = std::bitset<4>(1000).to_string(); //1000 command: Set up the daisy-chain enable (DCEN) register
    std::string DCEN = std::bitset<20>(1).to_string(); //toggling LSB enables/disables daisy chain mode
    std::string DCEN_word = DCEN_cmd + DCEN;
    std::string no_op = std::bitset<24>(0).flip().to_string(); //1111 command: no operation, in daisy chain mode

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
        std::cout << data_word << std::endl;


    }
}