#include <DAC_Commands.h>
#include <Arduino.h>
#include <SPI.h>

/*-----------------
Low Level Functions
-----------------*/

void xfer_data(void* data, int size){

};

//Resets to zero scale
void reset(){

}; 


/*--------------------
Medium Level Functions
--------------------*/

//Daisy Chain Enable
void DCEN(){

};   
    
//Write a voltage to a DAC Register
void write_DAC_reg(void* voltage){

}; 


/*------------------
High Level Functions
------------------*/

//Resets all DAC outputs to REF voltage (2.5 V) 
void ref_reset(){

}; 

//Writes voltage to selected registers simultaneously
void sync_write(int voltage, int registers[]){

}; 

//Writes voltage to selected registers sequentially with delay
void seq_write(int voltage, int registers[], int delay_msec){

}; 
