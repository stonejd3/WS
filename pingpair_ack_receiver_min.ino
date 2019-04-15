#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(7,8);

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.

void setup(){
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,  pipes[0]);
  radio.startListening();                 // Start listening
}

bool flag = true;

void loop(void) {
  
  if (flag)
  {
     radio.openWritingPipe(pipes[1]);
     radio.openReadingPipe(1,pipes[0]);
     radio.startListening();
     flag = false;
  }
  
  byte pipeNo;
  byte gotByte;                                       // Dump the payloads until we've gotten everything
  while( radio.available(&pipeNo)){
    radio.read( &gotByte, 1 );
    radio.writeAckPayload(pipeNo,&gotByte, 1 );    
 }
}