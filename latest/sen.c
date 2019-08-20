#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(7,8);
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.

void setup(){

  Serial.begin(115200);
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,pipes[0]);
  radio.startListening();                 // Start listening
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  
}
bool flag = true;
void loop(void) {


  //Run once for role selection
  if(flag){
    Serial.println("HARD CODED TO TX ONLY!");
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
    flag = false;
    radio.stopListening();
  }
  
  Serial.println("sending payload");
  byte gotByte;  
  byte num = (char) 'c';
  radio.write(&num, 1);
  if(!radio.available()){
    Serial.println("Didn't get response");
  } else {
    while(radio.available()){
      radio.read(&gotByte, 1);
      Serial.println("Got response");
    }
  }

}