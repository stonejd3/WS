#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t rxAddressList[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t txAddressList[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};

uint8_t payload = 15;
uint8_t rec_payload = 0;
uint8_t swap = 255;
uint8_t * pointerToPayload = &payload;

void setup(){
  
  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.setPayloadSize(1);
  
  // Set all pipes to read
  for(uint8_t i = 0; i < sizeof(rxAddressList)/sizeof(uint64_t); i++)
    radio.openReadingPipe(i, rxAddressList[i]);
  
  // Listen by default
  radio.startListening();
  
}

void loop(){

  radio.stopListening();
  radio.openWritingPipe(txAddressList[2]);
  if(radio.write(&payload, 1)){
    Serial.print("sent ");
    Serial.println(payload);
  }

}













