#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.
const uint64_t primaryPipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t secondaryPipes[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};

uint8_t stopFlag[] = {0xFF,0xFF,0,0,0,0,0};
void setup(){

  Serial.begin(115200);
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(7);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(secondaryPipes[2]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,primaryPipes[2]);
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  
}
bool flag = true;
void loop(void) {


  //Run once for role selection
  if(flag){
    Serial.println("HARD CODED TO TX ONLY!");
    radio.openWritingPipe(primaryPipes[2]);
    radio.openReadingPipe(1,secondaryPipes[2]);
    flag = false;
    radio.stopListening();
  }
  
  Serial.println("sending payload");
  byte gotByte[7];  
  byte num = 3;
  radio.write(&stopFlag, 7);
  if(!radio.available()){
    Serial.println("Didn't get response");
  } else {
    while(radio.available()){
      radio.read(&num, 1);
      Serial.println("Got response");
    }
  }

}