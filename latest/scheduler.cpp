class schedule {

private:
  
  uint32_t startTime;
  uint32_t delayTime;
  
  void (*schedule_function)(void *);
  void * schedule_function_args;
  
public:
  
  schedule(void (*function)(void *), void * args, uint32_t delayTime){
    
  this->startTime = millis();
    this->delayTime = delayTime;
    this->schedule_function = function;
    this->schedule_function_args = args;
    
  }
  
  void givePriority(){
    
    uint32_t currentTime = millis();
    
    if((currentTime-startTime) >= delayTime){
      this->schedule_function(this->schedule_function_args);
      startTime = millis();
    }
    
    return;
  
  }
  
};

void ledToggle(void* ledPin){
  
  if(digitalRead((uint8_t)ledPin) == HIGH)
    digitalWrite((uint8_t)ledPin, LOW);
  else
    digitalWrite((uint8_t)ledPin, HIGH);
  
  return;

}

const uint8_t numScheduledTasks = 9;
schedule * sched[numScheduledTasks];

void setup(){
  
  for(uint8_t i = 0; i < numScheduledTasks; i++){
    pinMode(i, OUTPUT);
	sched[i] = new schedule(ledToggle, (void *)(i+2), (1000+1000*i));
  }
  
  return;

}

void loop(){

  for(uint8_t i = 0; i < numScheduledTasks; i++)
  sched[i]->givePriority();
  
}