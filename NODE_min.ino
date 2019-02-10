#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint8_t nodeId = 1;

const uint64_t rxAddressList[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t txAddressList[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};

const uint64_t txAddress = rxAddressList[nodeId];
const uint64_t rxAddress = txAddressList[nodeId];

uint8_t payload = 5;
uint8_t rec_payload;
uint8_t swap = 255;

void setup(){

  Serial.begin(115200);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setChannel(108);
  radio.setPayloadSize(1);
  radio.openReadingPipe(0, rxAddress);
  radio.startListening();
  
}

void loop(){
  while(radio.available()){
    radio.read(&rec_payload, 1);
    Serial.print("received ");
    Serial.println(rec_payload);
  }
}