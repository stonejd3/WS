#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t rxAddressList[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t txAddressList[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};

// User variables (can change depending on application)
const uint8_t nodeId = 0x03;
const uint8_t payloadSize = 7;
const uint8_t numNodes = 3;

// Define a place for all data
uint8_t data[payloadSize];
uint8_t rec_data[payloadSize];

uint8_t payloads[][payloadSize] = {
  // For node 1:
  {0x01,  0,  0,  2,  88, 3,  255 },   // 0 - o0_s0
  {0x01,  0,  1,  0,  0,  2,  88  },   // 1 - o0_s1
  {0x01,  1,  0,  0,  0,  2,  88  },   // 2 - o1_s0
  {0x01,  1,  1,  2,  88, 3,  255 },   // 3 - o1_s1
  {0x01,  0xFF, 1,  0,  0,  0,  0 },   // 4 - terminating character
  // For node 2:
  {0x02,  0,  0,  2,  88, 3,  255 },   // 5 - o0_s0
  {0x02,  0,  1,  0,  0,  2,  88  },   // 6 - o0_s1
  {0x02,  1,  0,  0,  0,  2,  88  },   // 7 - o1_s0
  {0x02,  1,  1,  2,  88, 3,  255 },   // 8 - o1_s1
  {0x02,  0xFF, 1,  0,  0,  0,  0 },   // 9 - terminating character
};

uint8_t * pointerToPayload = data;
uint8_t activeNode = 1;
//uint8_t dataQueue[50][payloadSize];


uint16_t bytesToInt(uint8_t high, uint8_t low){
  return (uint16_t)(high<<8) + (uint16_t)low;
}

void intToBytes (uint8_t * bytesAddress, uint16_t num){
    
  // Default return 0
  uint8_t byteArray[2] = {0,0};
  if(num > 0){
    if(num >= 0 && num <= 255){
      byteArray[0] = 0x00;
      byteArray[1] = (uint8_t) num;   
    } else if(num > 255 && num <=1023){
      byteArray[0] = (num >> 8);
      byteArray[1] = num & 0x00FF;
    } 
  }
  
  // Change the values
  *bytesAddress = byteArray[0];
  *(bytesAddress+1) = byteArray[1];
  
}

void buildPayload(uint8_t payloadId){
  for(uint8_t i = 0; i < 7; i++){
    data[i] = payloads[payloadId][i];
  }
}

bool transmitData(uint8_t node, uint8_t payloadId){
  
  radio.stopListening();
  radio.openWritingPipe(txAddressList[node]);
  buildPayload(payloadId);
  return radio.write(&data, payloadSize);
  
  
} // end transmitData()

void setup(void) {

  Serial.begin(115200);
  radio.begin();
  
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(payloadSize);
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(2,15);                 // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);         // Use 8-bit CRC for performance
  
  // setup input pipes
  for(uint8_t i = 0; i < sizeof(rxAddressList)/sizeof(uint64_t); i++){
    radio.openReadingPipe(i, rxAddressList[i]);
  }
  
  // Listen by default
  radio.startListening();

  // Print some debug data
  radio.printDetails();
  Serial.println(F("\n\rRF24/examples/BASE/")); 
  radio.powerUp();
  
} // end setup loop


bool test = false;
void loop(void){
  
  if(!test){
    transmitData(0x01, 0);  
    transmitData(0x01, 1);  
    transmitData(0x01, 2);  
    transmitData(0x01, 3);  
    transmitData(0x01, 4);  
    test = true;
    radio.startListening();
  }

  while(radio.available()){
    radio.read(&rec_data, payloadSize);
    for(uint8_t i = 0; i < 7; i++){
      Serial.print(rec_data[i]);
      Serial.print("\t");
    }
    Serial.println("");
    
    if(rec_data[1] == 0xFF){
      Serial.println("Done Listening");
      radio.stopListening();   
    }
    
  }
  
  
} // end loop









