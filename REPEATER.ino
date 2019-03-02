#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t rxAddressList[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t txAddressList[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};

// User variables (can change depending on application)
//const uint8_t nodeId = 0x03;
const uint8_t payloadSize = 7;
const uint8_t numNodes = 3;
const uint8_t queueLength = 100;
uint8_t queueIndex;

unsigned long startTime;
unsigned long timeIncrement = 8000;


// Define a place for all data
uint8_t data[payloadSize];
uint8_t * pointerToPayload = data;
uint8_t queue[queueLength][payloadSize];
bool checked = false;

uint8_t startFlag[] = {0xFF,0xFF,0,0,0,0,0};

void queueClear(){
  // remove data
  for(uint8_t i = 0; i < queueLength; i++){
    for(uint8_t j = 0; j < payloadSize; j++){
      queue[i][j] = 0;
    }
  }
  // reset queue index
  queueIndex = 0;
}

void queueAdd(uint8_t * pointer){
  for(uint8_t i = 0; i < payloadSize; i++){
    queue[queueIndex][i] = pointer[i];
  }
  queueIndex++;
}

bool getQueueData(uint8_t index){
  if(index < queueIndex-1){
    for(uint8_t i = 0; i < payloadSize; i++){
      data[i] = queue[index][i];
    }
    return true;
  } else {
    queueClear();
    return false;
  }
}

void printQueueData(){
  for(uint8_t i = 0; i < queueIndex; i++){
    Serial.print("Queue index:");
    Serial.print(i);
    Serial.print("\t\n");
    for(uint8_t j = 0; j < payloadSize; j++){
      Serial.print(queue[i][j]);
      Serial.print("\t");
    }
    Serial.println("");
  }
}

void sendTo(uint8_t node){
  radio.openWritingPipe(txAddressList[node]);
  Serial.print("TX to ");
  Serial.println(node);
  //delay(1000);
  
}

bool checkForUpdates(){
  sendTo(0x00);
  if(radio.write(&startFlag, payloadSize)){
    printf("successfully pinged BASE");
    return true;
  } else {
    return false;
  }
}

bool transmitDataToNodes(){
  radio.stopListening();
  uint8_t counter = 0;
  while(getQueueData(counter)){
    sendTo(data[0]);
    if(!radio.write(&data, payloadSize)){
      printf("\nFailed to send payload\t");
      for(uint8_t i = 0; i < payloadSize; i++){
        printf("%d\t", data[i]);
      }
      //counter--;
      //printf("\n\n");
    }
    counter++;
  }
  
  return true;
  
} // end transmitData()

void setup(void) {

  Serial.begin(115200);
  radio.begin();
  
  radio.setChannel(100);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(payloadSize);
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(2,15);                 // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);         // Use 8-bit CRC for performance
  
  startTime = millis();
  
  // setup input pipes
  for(uint8_t i = 0; i < sizeof(rxAddressList)/sizeof(uint64_t); i++){
    radio.openReadingPipe(i, rxAddressList[i]);
  }
  
  // Listen by default
  radio.startListening();

  // Print some debug data
  Serial.println(F("\n\rRF24/examples/REPEATER/")); 
  
} // end setup loop

bool f0 = true;
bool f1 = true;
bool f2 = false;
bool f3 = false;
bool f4 = false;

void loop(void){
  
  if(f1 && f0){
    
    radio.stopListening();
    Serial.println("PINGING BASE");
    sendTo(0);
    radio.write(&startFlag, payloadSize);
    radio.startListening();    
    
    f0 = false;
    f1 = false;
    f2 = true;
    
  }
  
  if(f2){
    Serial.println("RECEIVING DATA:");
    while(radio.available()){
      radio.read(&data, payloadSize);
      for(int i = 0; i < payloadSize; i++){
        Serial.print(data[i]);
        Serial.print("\t");
      }
      Serial.println("");
      queueAdd(pointerToPayload);
    } 
    
    // check if terminating character
    if(data[0] == 255){
      f2 = false;
      f3 = true;
    }
  
  }
  
  if(f3){
   
    Serial.println("TRANSMIT TO NODES:");
    f3 = false;
    transmitDataToNodes();
    
   
   
  }
  
  
} // end loop


