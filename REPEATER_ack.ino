#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t secondaryPipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t primaryPipes[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
const uint8_t ackResponse = 1;
uint8_t pipeNo;

// User variables (can change depending on application)
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
  
  Serial.print("Tx to ");
  Serial.println(node);
  
  radio.openWritingPipe(primaryPipes[node]);        // Both radios listen on the same pipes by default, and switch when writing
  radio.openReadingPipe(1,secondaryPipes[node]);
  radio.stopListening();
  
}

void listenTo(uint8_t node){
    Serial.print("Rx from ");
    Serial.println(node);
    
    radio.openWritingPipe(secondaryPipes[node]);        // Both radios listen on the same pipes by default, and switch when writing
    radio.openReadingPipe(1,primaryPipes[node]);
    radio.startListening();
}

bool pingBase(){
  sendTo(0x00);
  
  uint8_t recd = 0;
  
  while(recd == 0){
    radio.write(&startFlag, payloadSize);
    if(!radio.available()){
      Serial.println("Error pinging base: Trying again");
    } else {
      while(radio.available()){
        radio.read(&recd, 1);
        recd = 1;
        Serial.println("Got Response!");
      }
    } 
  }
  
  listenTo(0x00);
  return true;
  
}

bool receiveBaseData(){
  bool listening = true;
    while(listening){
      while(radio.available(&pipeNo)){
        radio.read(&data, payloadSize);
        radio.writeAckPayload(pipeNo, &ackResponse, 1);
        queueAdd(pointerToPayload);
        
        if(data[0]==0xFF){
          Serial.println("END Transmission");
          Serial.println(":::::::RECEIVED ::::::");
          printQueueData();
          listening = false;
        }
      } 
    }
    return true;
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
  radio.enableAckPayload();
  radio.setRetries(0,15);                 // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);         // Use 8-bit CRC for performance
  
  startTime = millis();

  // Print some debug data
  Serial.println(F("\n\rRF24/examples/REPEATER/")); 
  
} // end setup loop

bool f1=false, f2 = false;
void loop(void){
  
    if(!f1){
      pingBase();  
      f1 = true;
    }
    
    if(!f2){
      listenTo(0x00);
      receiveBaseData();  
    }
    
    //Serial.println(data[0]);
    
    

} // end loop


