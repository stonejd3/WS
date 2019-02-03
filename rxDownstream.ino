#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };   // Radio pipe addresses for the 2 nodes to communicate.

byte data[2];

void setup(void) {

  Serial.begin(115200);

  radio.begin();
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(2);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  
  Serial.println(F("\n\rRF24/examples/Transfer/"));
  Serial.println(F("*** fixed to receive mode only"));
  
  randomSeed(analogRead(0));
  
  for(int i=0; i<2; i++){
     data[i] = random(255);               
  }
  radio.powerUp();
}

void loop(void){
  while(radio.available()){       
    radio.read(&data,2);
    Serial.print(data[0]);
    Serial.print(' ');
    Serial.print(data[1]);
    Serial.print('\n');
  }
}