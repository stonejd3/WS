/*
  // March 2014 - TMRh20 - Updated along with High Speed RF24 Library fork
  // Parts derived from examples by J. Coliz <maniacbug@ymail.com>
*/
/**
 * Example for efficient call-response using ack-payloads 
 *
 * This example continues to make use of all the normal functionality of the radios including
 * the auto-ack and auto-retry features, but allows ack-payloads to be written optionally as well.
 * This allows very fast call-response communication, with the responding radio never having to 
 * switch out of Primary Receiver mode to send back a payload, but having the option to if wanting
 * to initiate communication instead of respond to a commmunication.
 */
 


#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <RF24/RF24.h>
#include <unistd.h>
#include <inttypes.h>


// Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

// Topology
const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.
const uint64_t primaryPipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t secondaryPipes[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};


// Role management: Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  
// A single uint8_t to keep track of the data being sent back and forth
uint8_t counter = 1;

uint8_t stopFlag[] = {0xFF,0xFF,0,0,0,0,0};

void setup(){
  
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(7);                // Here we are sending 1-uint8_t payloads to test the call-response speed
  radio.openWritingPipe(secondaryPipes[2]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,primaryPipes[2]);
  radio.startListening();                 // Start listening
  
  }

void loop(void) {

  // Pong back role.  Receive each packet, dump it out, and send it ba
  uint8_t pipeNo;
  uint8_t gotuint8_t[7];                                       // Dump the payloads until we've gotten everything
  while( radio.available(&pipeNo)){
    radio.read( &gotuint8_t, 7 );
    radio.writeAckPayload(pipeNo,&pipeNo, 1 );    
  }
}

int main(){
  setup();
  while(1){
    loop();
  }
}