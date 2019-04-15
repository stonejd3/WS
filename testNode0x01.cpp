#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <RF24/RF24.h>
#include <unistd.h>
#include <inttypes.h>

using namespace std;

RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

const uint64_t rxAddressList[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t txAddressList[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};


const uint8_t payloadSize = 7;

uint8_t rec_data[payloadSize];
uint8_t o0_s0_data[payloadSize];
uint8_t o0_s1_data[payloadSize];
uint8_t o1_s0_data[payloadSize];
uint8_t o1_s1_data[payloadSize];
uint8_t tdata[payloadSize];
uint8_t nullset[payloadSize];

uint16_t thresh1 = 600;
uint16_t thresh2 = 1023;

uint8_t thresh1_array[2];
uint8_t thresh2_array[2];

uint8_t * t1_p = thresh1_array;
uint8_t * t2_p = thresh2_array;

uint8_t nodeId = 0x01;

unsigned long startTime, stopTime, counter, rxTimer=0;

void intToBytes (uint8_t * bytesAddress, uint16_t num){
    
	// Default return 0
	uint8_t byteArray[2] = {0,0};
	if(num > 0){
		if(num >= 0 && num <= 255){
			byteArray[0] = 0x00;
			byteArray[1] = (uint8_t) num;		
		} else if(num > 255 && num <=65535){
			byteArray[0] = (num >> 8);
			byteArray[1] = num & 0x00FF;
		}	
	}
	
	// Change the values
	*bytesAddress = byteArray[0];
	*(bytesAddress+1) = byteArray[1];
	
}

void setup(){
  
  cout << "RF24/examples/txDownstream/\n";
  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(payloadSize);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  radio.openReadingPipe(1,rxAddressList[1]);
  
  intToBytes(t1_p, thresh1);
  intToBytes(t2_p, thresh2);
  
  if(1==1){ // Put all data into packets
    
    // Node 0, Output 0, Sensor 0
    o0_s0_data[0] = 0x01;	 					// node
    o0_s0_data[1] = 0;						// output
    o0_s0_data[2] = 0;						// sens_id
    o0_s0_data[3] = thresh1_array[0];		// s1L_MSB
    o0_s0_data[4] = thresh1_array[1];		// s1L_LSB
    o0_s0_data[5] = thresh2_array[0];		// s1H_MSB
    o0_s0_data[6] = thresh2_array[1];		// s1H_LSB
        
    // Node 0, Output 0, Sensor 1
    o0_s1_data[0] = 0x01;	 					// node
    o0_s1_data[1] = 0;						// output
    o0_s1_data[2] = 1;						// sens_id
    o0_s1_data[3] = 0;						// s1L_MSB
    o0_s1_data[4] = 0;						// s1L_LSB
    o0_s1_data[5] = thresh1_array[0];		// s1H_MSB
    o0_s1_data[6] = thresh1_array[1];		// s1H_LSB
        
    // Node 0, Output 1, Sensor 0
    o1_s0_data[0] = 0x01;	 					// node
    o1_s0_data[1] = 1;						// output
    o1_s0_data[2] = 0;						// sens_id
    o1_s0_data[3] = 0;						// s1L_MSB
    o1_s0_data[4] = 0;						// s1L_LSB
    o1_s0_data[5] = thresh1_array[0];		// s1H_MSB
    o1_s0_data[6] = thresh1_array[1];		// s1H_LSB  
        
    // Node 0, Output 1, Sensor 1
    o1_s1_data[0] = 0x01;	 					// node
    o1_s1_data[1] = 1;						// output
    o1_s1_data[2] = 1;						// sens_id
    o1_s1_data[3] = thresh1_array[0];		// s1L_MSB
    o1_s1_data[4] = thresh1_array[1];		// s1L_LSB
    o1_s1_data[5] = thresh2_array[0];		// s1H_MSB
    o1_s1_data[6] = thresh2_array[1];		// s1H_LSB
    printf("\n");

    // Node 0, Output 1, Sensor 1
    tdata[0] = 0x03;				// node
    tdata[1] = 0xFF;				// output
    tdata[2] = 1;						// sens_id
    tdata[3] = thresh1_array[0];		// s1L_MSB
    tdata[4] = thresh1_array[1];		// s1L_LSB
    tdata[5] = thresh2_array[0];		// s1H_MSB
    tdata[6] = thresh2_array[1];		// s1H_LSB
    
    // Null payload for testing
    nullset[0] = 0x03;
    nullset[1] = 0;
    nullset[2] = 0;
    nullset[3] = 0;
    nullset[4] = 0;
    nullset[5] = 0;
    nullset[6] = 0;
    
  }
  
}

int main(){
  
  setup();

  printf("Initiating Basic Data Transfer\n\r");
  radio.stopListening();
  radio.openWritingPipe(txAddressList[1]);
  
  // Infinite Loop:
  while (1){

    sleep(2); 
    
    for(int i = 0; i < 1; i++){
      radio.write(&o0_s0_data, payloadSize);
      radio.write(&o0_s1_data, payloadSize);
      radio.write(&o1_s0_data, payloadSize);
      radio.write(&o1_s1_data, payloadSize);  
    }
    
    break;

  } // end infinity loop

} // end main

