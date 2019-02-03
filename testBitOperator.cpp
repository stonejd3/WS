
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
using namespace std;

void intToBytes (uint8_t * address, uint16_t num){
    
	// Default return 0
	uint8_t byteArray[2] = {0,0};
	if(num > 0){
		if(num >= 0 && num <= 255){
			byteArray[0] = 0x00;
			byteArray[1] = (uint8_t) num;		
		} else if(num > 255 && num <=1023){
			byteArray[0] = (num >> 8);
			byteArray[1] = num & 0x00FF;
		}	
	}
	
	// Change the values
	*address = byteArray[0];
	*(address+1) = byteArray[1];
	
}

int main(){
	
		uint8_t byte1 = 0x03;
		uint8_t byte2 = 0xDA;

		uint16_t nByte1 = (uint16_t) byte1;
		uint16_t nByte2 = (uint16_t) byte2;
		
		uint16_t num = (nByte1<<8)+nByte2;
		
		printf("%d",num);
		
        return 0;

}




