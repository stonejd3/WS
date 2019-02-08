#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };   // Radio pipe addresses for the 2 nodes to communicate.

// User variables (can change depending on application)
const uint8_t nodeId = 0x01;
const uint8_t payloadSize = 7;
const uint8_t numOutputs = 2;
const uint8_t numInputs = 2;

// Define a place for all data
uint8_t data[payloadSize];
uint16_t outputs[numOutputs][2*numInputs+1];
uint8_t outputPins[2] = {12,13};
uint8_t inputs[numInputs] = {0,1};
uint16_t currentData[numInputs];


uint16_t makeInt(uint8_t high, uint8_t low){
	return (uint16_t)(high<<8) + (uint16_t)low;
}

void getCurrentData(uint16_t * address){
	
	for(uint8_t i = 0; i < numInputs; i++){
		*(address+i) = analogRead(inputs[i]);
		Serial.print(i);
		Serial.print(":\t");
		Serial.println(analogRead(inputs[i]));
	}
	
}

void setup(void) {

  Serial.begin(115200);

  radio.begin();
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(payloadSize);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  
  Serial.println(F("\n\rRF24/examples/Transfer/"));
  Serial.println(F("*** fixed to receive mode only"));
 
  radio.powerUp();
  
  for(uint8_t i = 0; i < sizeof(outputPins)/sizeof(uint8_t); i++){
	outputs[i][0] = outputPins[i];
  }
  
}

void loop(void){
  
  // Check incoming messages
  while(radio.available()){       
    radio.read(&data,payloadSize);
	
	// Check to make sure this device is the receiver
	if(data[0] == nodeId){
		
		Serial.println("Node is active");
		
		// Check if output is in range
		if(data[1] <= numOutputs && data[1] >= 0){
			if(data[2] <= numInputs){
				outputs[data[1]][2*data[2]+1] = makeInt(data[3],data[4]);
				outputs[data[1]][2*data[2]+2] = makeInt(data[5],data[6]);
			}
		}
	
	}
  } // end while(radio.available())

  
  uint16_t *pointerToCurrentData = currentData;
  getCurrentData(pointerToCurrentData);

  
  for(uint8_t i = 0; i < numOutputs; i++){
	bool flag = true;
	for(uint8_t j = 0; j < numInputs; j++)
		if(currentData[j] > outputs[2*j+1] && currentData[j] < outputs[2*j+2])
		  flag = false;
	if(flag){
	  Serial.print("output ");
	  Serial.print(i);
	  Serial.println("HIGH");
	  //digitalWrite(outputs[i][0], HIGH);
	} else{ 
	  Serial.print("output ");
	  Serial.print(i);
	  Serial.println("LOW");
	  //digitalWrite(outputs[i][0], LOW);
	}
  
  }

  // For debugging only
  for(uint8_t i = 0; i < numOutputs; i++){
	for(uint8_t j = 0; j < 2*numInputs+1; j++){
		Serial.print(outputs[i][j]);
		Serial.print("\t");
	}
	Serial.println("");
  }
  delay(1000);
  // End debugging
  
}