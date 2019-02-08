#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <RF24/RF24.h>
#include <unistd.h>
#include <inttypes.h>

using namespace std;

// Setup for GPIO 15 CE and CE0 CSN with SPI Speed @ 8Mhz
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t addresses[2] = { 0xABCDABCD71LL, 0x544d52687CLL };

const uint8_t payloadSize = 7;
uint8_t data[payloadSize];
unsigned long startTime, stopTime, counter, rxTimer=0;

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

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// MAIN METHOD START
/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
int main(int argc, char** argv){

  // Print preamble:
  cout << "RF24/examples/Transfer/\n";

  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(payloadSize);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  //radio.printDetails();


  /******** Role is fixed to PING OUT *********/
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1,addresses[0]);
  radio.stopListening();

  /********* Load the buffer with all ones -- start flag ****************/
  // TODO: PUT REAL DATA HERE!
  uint8_t node = 0x01;
  uint8_t output = 0x01;
  uint16_t sensor1H = 1023;
  uint16_t sensor1L = 128;
  
  uint8_t sensor1H_array[2];
  uint8_t sensor1L_array[2];
  
  uint8_t * s1H_p = sensor1H_array;
  uint8_t * s1L_p = sensor1L_array;
  
  intToBytes(s1H_p, sensor1H);
  intToBytes(s1L_p, sensor1L);
  
  // Put all data into packet
  data[0] = node;
  data[1] = output;
  data[2] = 0x01; // sens_id
  data[3] = sensor1L_array[0]; //s1L_MSB
  data[4] = sensor1L_array[1]; //s1L_LSB
  data[5] = sensor1H_array[0]; //s1h_MSB
  data[6] = sensor1H_array[1]; //s1h_LSB
  
  for(uint8_t i = 0; i < 7; i++){
	  printf("%d\t", data[i]);
  }
  printf("\n");
  
  
  
  printf("\n");

  /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////
  // LOOP CODE STARTS HERE
  /////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////

  // Infinite Loop:
  while (1){
      
	  sleep(2);
      printf("Initiating Basic Data Transfer\n\r");

      long int cycles = 1;
      for(int i = 0; i < cycles; i++){
        radio.writeFast(&data, payloadSize);
      }
	  
	  break;
  
  } // end infinity loop

} // end main

