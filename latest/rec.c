#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

byte gotByte;
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
RF24 radio(7,8);

const uint64_t pipes[2] = { 0xABCDABCD71LL, 0x544d52687CLL };              // Radio pipe addresses for the 2 nodes to communicate.

void setup(){
  pinMode(4, OUTPUT);
  radio.begin();
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.enableAckPayload();               // Allow optional ack payloads
  radio.setRetries(0,15);                 // Smallest time between retries, max no. of retries
  radio.setPayloadSize(1);                // Here we are sending 1-byte payloads to test the call-response speed
  radio.openWritingPipe(pipes[1]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,  pipes[0]);
  radio.startListening();                 // Start listening
  
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("No sig recd");
  
}

bool flag = true;
bool flag2 = false;

void loop(void) {
  
  if (flag)
  {
     radio.openWritingPipe(pipes[1]);
     radio.openReadingPipe(1,pipes[0]);
     radio.startListening();
     flag = false;
  }
  
  if(flag2){
  lcd.setCursor(1,0);
  lcd.print((char)gotByte); 
  } else {
  lcd.setCursor(1,0);
  lcd.print("           "); 
  }
  
  flag2 = false;
  byte pipeNo;
                                         // Dump the payloads until we've gotten everything
  while( radio.available(&pipeNo)){
    radio.read( &gotByte, 1 );
    radio.writeAckPayload(pipeNo,&gotByte, 1 );    
  flag2 = true;
 }
}