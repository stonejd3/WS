#include <SPI.h>
#include "RF24.h"

RF24 radio(7,8);

const uint64_t secondaryPipes[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t primaryPipes[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
const uint8_t ackResponse = 1;
uint8_t pipeNo;

// User variables (can change depending on application)
const uint8_t nodeId = 0x01;
const uint8_t payloadSize = 7;
const uint8_t numOutputs = 2;
const uint8_t numInputs = 2;

// Define a place for all data
uint8_t data[payloadSize];
uint8_t * pointerToPayload = data;
uint16_t outputs[numOutputs][2*numInputs+1];
uint8_t outputPins[2] = {4,6};
uint8_t inputPins[numInputs] = {0,1};
uint16_t gatheredData[numInputs];
uint16_t *pointerToGatheredData = gatheredData;

// Function declarations:

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
		} else if(num > 255 && num <=65535){
			byteArray[0] = (num >> 8);
			byteArray[1] = num & 0x00FF;
		}	
	}
	
	// Change the values
	*bytesAddress = byteArray[0];
	*(bytesAddress+1) = byteArray[1];
	
}

void setCommunicationDirection(char c){
  if(c == 'R'){
    Serial.println("Role is Rx");
    radio.openWritingPipe(secondaryPipes[nodeId]);        // Both radios listen on the same pipes by default, and switch when writing
    radio.openReadingPipe(1,primaryPipes[nodeId]);
    radio.startListening();
  } else {
    Serial.println("Role is Tx");
    radio.openWritingPipe(primaryPipes[nodeId]);        // Both radios listen on the same pipes by default, and switch when writing
    radio.openReadingPipe(1,secondaryPipes[nodeId]);
    radio.stopListening();
  }
} // end setCommunicationDirection()

void gatherData(uint16_t * pointerToGatheredData){
  
  for(uint8_t i = 0; i < numInputs; i++)
    *(pointerToGatheredData+i) = analogRead(inputPins[i]);
  
} // end gatherData

void buildPayload(uint8_t * pointerToPayload, uint8_t inputId){
  
  // Split input value into two bytes
  uint8_t bArray[2];
  uint8_t *pBArray = bArray;
  intToBytes(pBArray, gatheredData[inputId]);
  
  // Populate payload with data
  *(pointerToPayload+0) = nodeId; 
  *(pointerToPayload+1) = inputId;
  *(pointerToPayload+2) = bArray[0];
  *(pointerToPayload+3) = bArray[1];
  *(pointerToPayload+4) = 0;
  *(pointerToPayload+5) = 0;
  *(pointerToPayload+6) = 0;
  
  if(inputId == 255){                   // Build terminating payload
    *(pointerToPayload+1) = 0xFF;
  } // end terminating payload conditional
 
} // end buildPayload()

void transmitData(){
  
    setCommunicationDirection('T');               // Prepare radio to transmit
    delay(1000);                                  // Give the other time to swap roles
    
    // Loop through inputData:
    for(uint8_t i = 0; i <= numInputs; i++){ 
      if(i < numInputs){
        buildPayload(pointerToPayload, i);        // Build standard payload
      } else {
        buildPayload(pointerToPayload, 0xFF);     // Build terminating payload
      }
      
      for(uint8_t j = 0; j < 7; j++){
        Serial.print(data[j], HEX);
        Serial.print("\t");
      }
      Serial.print("\n");
      
      int recd = 0;
      
      while(recd == 0){                           // Keep sending until receive ack response
        radio.write(&data, payloadSize);
        if(!radio.availabe()){
          Serial.print("Transmission ");
          Serial.print(i);
          Serial.print(" of ");
          Serial.print(numInputs);
          Serial.print(" FAILED! ");
        } else {
          while(radio.available()){
            radio.read(&recd,1);
          }
        }
      }
      
      Serial.print("Transmission ");
      Serial.print(i);
      Serial.print(" of ");
      Serial.print(numInputs);
      Serial.print(" SUCCEEDED! ");
      
    } // end input loop
    
    setCommunicationDirection('R');               // Prepare radio to receive
    
} // end transmitData()

void setup(void) {

  Serial.begin(115200);

  radio.begin();
  radio.setChannel(100);
  radio.setAutoAck(1);
  radio.enableAckPayload();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.setPayloadSize(payloadSize);
  radio.setAutoAck(1);                    // Ensure autoACK is enabled
  radio.setRetries(0,15);                 // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);         // Use 8-bit CRC for performance
  
  setCommunicationDirection('R');
  
  // Do some output pin configurations
  for(uint8_t i = 0; i < sizeof(outputPins)/sizeof(uint8_t); i++){
    outputs[i][0] = outputPins[i];        // Put output pins in outputs[]
    pinMode(outputPins[i], OUTPUT);       // Establish pin modes
    digitalWrite(outputPins[i],LOW);      // Default to LOW pin state
  } // end outputPins loop
  
  // Print some debug data
  radio.printDetails();                   // Dump the configuration of the rf unit for debugging
  Serial.println(F("\n\rRF24/examples/NODE1/"));
 
  radio.powerUp();
  
  gatherData();
  
} // end setup loop

void loop(void){
  bool test = false;
  // Check incoming messages
  while(radio.available(&pipeNo)){       
    
    radio.read(&data,payloadSize);
    radio.writeAckPayload(pipeNo, &ackResponse, 1);
    
    if(data[0] == nodeId){                          // See if this device needs to listen
      if(data[1] == 0xFF){                          // Need to TX Data
        Serial.println("Need to TX Data!");
        transmitData();
      } else {                                      // Need to RX Data
        if(data[1] <= numOutputs && data[1] >= 0){  // Output Range Check
          if(data[2] <= numInputs){                 // Input Range Check
            outputs[data[1]][2*data[2]+1] = bytesToInt(data[3],data[4]);
            outputs[data[1]][2*data[2]+2] = bytesToInt(data[5],data[6]);
          } // end input range conditional
        } // end output range conditional
      } // end tx/rx conditional 
    } // end nodeId conditional
  } // end radio.available() loop
  
  // Write to outputs
  for(uint8_t i = 0; i < numOutputs; i++){
    bool flag = true;                               // Flag used for multiple conditions
    for(uint8_t j = 0; j < numInputs; j++){
      if(gatheredData[j] < outputs[i][2*j+1] || gatheredData[j] > outputs[i][2*j+2]){
        flag = false;                               // Output should not be high
      } // end input check conditional
    } // end input loop
    
    if(flag){                                       // Output should be HIGH
      digitalWrite(outputs[i][0], HIGH);
    } else {                                        // Output should be LOW
      digitalWrite(outputs[i][0], LOW);
    } // end flag conditional   
  } // end output loop
  
  // Grab the current sensor data
  gatherData(pointerToGatheredData);
  
  // Print to console
  for(uint8_t i = 0; i < 1; i++){
    Serial.print("IN0:  "); 
    Serial.println(gatheredData[0]);
    Serial.print("IN1:  "); 
    Serial.println(gatheredData[1]);   
    for(uint8_t i = 0; i < numOutputs; i++){
      for(uint8_t j = 0; j < 2*numInputs+1; j++){
        Serial.print(outputs[i][j]);
        Serial.print("\t");
      } // end input loop
      Serial.println("");
    } // end output loop   
  } // end print loop
} // end loop









