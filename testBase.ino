#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t rxAddressList[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t txAddressList[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};

const uint8_t payloadSize = 7;
uint8_t payload[payloadSize];
uint8_t rec_payload[payloadSize];

void setup(){
  
  Serial.begin(115200);
  radio.begin();
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(payloadSize);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);
  radio.setCRCLength(RF24_CRC_8);
  radio.setRetries(2,15);
  
  // Set all pipes to read
  radio.openReadingPipe(0, rxAddressList[0]);
  radio.openReadingPipe(1, rxAddressList[1]);
  radio.openReadingPipe(2, rxAddressList[2]);
  
  // Listen by default
  radio.startListening();
  
}

void loop(){

  while(radio.available()){
    radio.read(&rec_payload, 7);
    for(int i = 0; i < 7; i++){
      Serial.print(rec_payload[i]);
      Serial.print("\t");
    }
    Serial.print("\n");
  }

}













