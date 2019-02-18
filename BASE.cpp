#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <RF24/RF24.h>
#include <unistd.h>
#include <inttypes.h>

using namespace std;

RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);

const uint64_t rxAddressList[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL};  
const uint64_t txAddressList[] = {0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
const uint8_t nodeId = 0x00;
const uint64_t txAddress = rxAddressList[nodeId];
const uint64_t rxAddress = txAddressList[nodeId];

const uint8_t payloadSize = 7;
const uint8_t queueLength = 100;

uint8_t queueIndex;
uint8_t queue[queueLength][payloadSize];

uint8_t data[payloadSize];
uint8_t * pointerToPayload = data;

uint8_t stopFlag[] = {0xFF,0xFF,0,0,0,0,0};

uint8_t byteArray[2];
uint8_t *pointerToByteArray = byteArray;

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
  if(index < queueIndex){
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
  for(uint8_t i = 0; i < 100; i++){
    for(uint8_t j = 0; j < payloadSize; j++){
      printf("%d\t",queue[i][j]);
    }
    printf("\n");
  }
}

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

vector<string> explode( const string &del, const string &str){
  
  vector<string> arr; 

  uint8_t str_len = str.length();
 
  uint8_t l_index = 0;
  uint8_t h_index = 0;
  
  for(uint8_t i = 0; i < str_len; i++){
    if(str[i] == del[0]){
      h_index = i - l_index;
      arr.push_back(str.substr(l_index, h_index));
      l_index = i+1;
    }
  }
  arr.push_back(str.substr(l_index, str_len));
  return arr;
  
}

vector<uint16_t> vStrToVInt(vector<string> &vStr){
  vector<uint16_t> vInt;
  for(uint8_t i = 0; i < vStr.size(); i++){
    vInt.push_back((uint16_t)atoi(vStr[i].c_str()));
  }
  return vInt;
}

bool vIntToData(vector<uint16_t> &vInt){
  uint8_t c = 0;
  for(uint8_t i = 0; i < vInt.size(); i++){
    if(i < 3){
      data[i] = vInt[i];
    } else {
      intToBytes(pointerToByteArray, vInt[i]);
      if((i + c + 1) < payloadSize){
        data[i + c] = byteArray[0];
        data[i + c + 1] = byteArray[1];
        if(i == vInt.size()-1){
          c = 0;
        } else {
          c++;
        } 
      } else {
        return false;
      }
      
    }
  }  
  return true;
}

bool fileIsEmpty(ifstream& pFile){
    return pFile.peek() == ifstream::traits_type::eof();
}

bool buildPayloads(){
  
	// Create a variable for storing lines in.
	string line = "";

	// Create instance of the stream:
	ifstream file;

	// Open the file:
	file.open("downstreamData.txt");
  
  if(fileIsEmpty(file)){
    return false;
  }
	// Check to see if file is really open:
	if(file.is_open()){

		// Read file line-by-line:
		while(getline(file, line)){
      vector<string> v = explode(",", line);
      vector<uint16_t> vInt = vStrToVInt(v);
      if(vIntToData(vInt)){
        queueAdd(pointerToPayload);
      } else {
        printf("failed - payload / file length mismatch");
        return false;
      }
		}

		file.close();		
    return true;
	
  } else {
    printf("Unable to open file\n");
    return false;
	}

}

void setCommunicationDirection(char c){
  
  if(c == 'R'){                                    // Swap to TX Mode:
    radio.startListening();
    printf("Role is 'RX'\n");
  } else {                                         // Swap to RX Mode:
    radio.stopListening();
    radio.openWritingPipe(txAddress);
    printf("Role is 'TX'\n");
  } // end COMM direction conditional
  
} // end setCommunicationDirection()

bool transmitData(){

  // Set up TX mode
  setCommunicationDirection('T');
  sleep(1);
  
  // Build payloads
  if(!buildPayloads()){  
    return false;
  }
  
  uint8_t counter = 0;
  while(getQueueData(counter)){
    if(!radio.write(&data, payloadSize)){
      printf("\nFailed to send payload\t");
      for(uint8_t i = 0; i < payloadSize; i++){
        printf("%d\t", data[i]);
      }
      printf("\n\n");
    }
    counter++;
  }
  
  return radio.write(&stopFlag, payloadSize);
  
  

}

void setup(){
  
  cout << "RF24/examples/BASE/\n";
  radio.begin();                           // Setup and configure rf radio
  radio.setChannel(1);
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(payloadSize);
  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(2,15);                  // Optionally, increase the delay between retries & # of retries
  radio.setCRCLength(RF24_CRC_8);          // Use 8-bit CRC for performance
  
  radio.openReadingPipe(0, rxAddress);
  setCommunicationDirection('R');
  
}

int main(){
  setup();  
  while(1==1){ // void loop()
    
    
    while(radio.available()){
      radio.read(&data, payloadSize);
      
      if(data[0] == 0xFF){
        printf("Need to TX\n");
        if(transmitData()){
          setCommunicationDirection('R');
        }
      } else {
      
        for(int i = 0; i < payloadSize; i++){
          printf("%d\t", data[i]);
        }
        printf("\n");
      }
    }
    
    
    
  }
  
} // end main



