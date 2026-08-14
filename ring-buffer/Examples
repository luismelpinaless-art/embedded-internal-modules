#include "buffer.h"
//INSTANCE
BUFFER bff1; //Buffer module instance

int main(void){

  char data[2] = "L";            //Data to be written in the buffer  
  char data_read[2] = {0};      //Array that contains the readed data from the buffer 
  buffer_init(&bff1);          // Buffer set

while(1){

buffer_write(&bff1, data);         //Write from data to bff1
	  buffer_read(&bff1,data_read); //read from bff1 to data_read 
  }  
}
