#include<pthread.h>
#include<assert.h>

const uint8_t ledPin = 2;
unsigned long startTime=0, timeIncrement=0;
bool ledOn = false;
bool userInputtedValue = false;

void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  startTime = millis();
}

void * getUserInput(void* params){
  
  if(Serial.available()){
    while(Serial.available()){
      timeIncrement = Serial.parseInt();
      userInputtedValue = true;
    }
  }
  return NULL;
  
}

void * writeOutputs(void* params){
  unsigned long currentTime = millis();
  if((currentTime > (startTime + timeIncrement)) && userInputtedValue){
    if(ledOn){
      digitalWrite(ledPin, LOW);
      Serial.println("off");
    } else {
      digitalWrite(ledPin, HIGH);
      Serial.println("on");
    }
    ledOn = !ledOn;
    startTime = millis();
  }
  return NULL;
}

void loop(){

  pthread_t threads[2];
  int r;
  
  r = pthread_create(&threads[0], NULL, getUserInput, NULL);
  assert(r==0);
  r = pthread_create(&threads[1], NULL, writeOutputs, NULL);
  assert(r==0);
  r = pthread_join(threads[0], NULL);
  assert(r==0);
  r = pthread_join(threads[1], NULL);
  assert(r==0);
  
}

