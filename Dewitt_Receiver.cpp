//Code to Test Robotic Arm Remote Control - Written by Jonathan DeWitt
//Difference Between Rev 0 and Rev 1
//Rev 0 used Reference 1 as Technique for Transmitting data via the HC-12
//Rev 1 used Reference 2 as Technique for Transmitting data via the HC-12
//Rev 4 This is my attempt to completely clean up the code to make sure that the right value is getting transmitted to the servos
//Rev 4 partially works.  The robot responds to the remote control.  But the robot shakes and is jittery from the moment the transmitter on the remote is turned on.
//I tried some solutions in Rev 5 (don't use) to try to fix it.  But I was unable to fix it.

#include <Servo.h>
/* JDS */ // #include <SoftwareSerial.h>

/* JDS */ // SoftwareSerial HC12(8,7); // Arduino Pin 8 Rx to Tx on HC-12, Arduino Pin 7 Tx to Rx on HC-12

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;

int J1 = 5; //J1 Servo Signal Wire Attached to Pin 5
int J2 = 6; //J2 Servo Signal Wire Attached to Pin 6
int J3 = 9; //J3 Servo Signal Wire Attached to Pin 9
int J4 = 10; //J4 Servo Signal Wire Attached to Pin 10
int J5 = 11; //J5 Servo Signal Wire Attached to Pin 11
int J6 = 3; //J6 Servo Signal Wire Attached to Pin 3

//Home Position for Robot - Determined Through Careful Trial & Error Testing
int J1H = 90; //Joint 1 Home Position 90°
int J2H = 110; //Joint 2 Home Position 110°
int J3H = 120; //Joint 3 Home Position 120°
int J4H = 50; //Joint 4 Home Position 50°
int J5H = 50; //Joint 5 Home Position 50°
int J6H = 120; //Joint 6 Home Position 120°

int angle1 = J1H; //Stores Angle to Move Servo 1 To
int angle2 = J2H; //Stores Angle to Move Servo 2 To
int angle3 = J3H; //Stores Angle to Move Servo 3 To
int angle4 = J4H; //Stores Angle to Move Servo 4 To
int angle5 = J5H; //Stores Angle to Move Servo 5 To
int angle6 = J6H; //Stores Angle to Move Servo 6 To

int angle1L = J1H; //angle 1 Last
int angle2L = J2H; //angle 2 Last
int angle3L = J3H; //angle 3 Last
int angle4L = J4H; //angle 4 Last
int angle5L = J5H; //angle 5 Last
int angle6L = J6H; //angle 6 Last

////The following variables are needed only to receive data from the HC-12 remote control using Reference 1 Method
//String input;
int boundLow;
int boundHigh;
int boundF;
const char delimiter = ',';
const char finald = '.';

//Following Section Copied from Data Logger Sketch i.e. from Reference 2 Method
char incomingByte;
String readBuffer = "";
int byteD = 5; //byte delay is the delay in which each incoming byte is stored from the HC-12
int SMd = 250; //Serial Monitor Delay - The delay used to set the interval with which strings from the buffer are sent to the serial monitor - was originally 5000
//Note: SMd is dependent on sampP in the transmitter sketch.  SMd = 483 for the default sampP = 10.  This will need to be tweaked depending on frequency of sampling (sampP).
int stupD = 500; //Setup Delay

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Servo1.attach(J1); //Calls this is like a pinmode command but also does more from the servo library
  Servo2.attach(J2); //Calls this is like a pinmode command but also does more from the servo library
  Servo3.attach(J3); //Calls this is like a pinmode command but also does more from the servo library
  Servo4.attach(J4); //Calls this is like a pinmode command but also does more from the servo library
  Servo5.attach(J5); //Calls this is like a pinmode command but also does more from the servo library
  Servo6.attach(J6); //Calls this is like a pinmode command but also does more from the servo library

  //Move the robot to a good home pose
  servoWriter(J1H, J2H, J3H, J4H, J5H, J6H); //servoWriter function call
  
  /* JDS */ // HC12.begin(9600); //Start the HC-12 Module
  delay(stupD); //I assume this delay is to give the HC-12 time to read
}

void loop() {
  // put your main code here, to run repeatedly:

//It takes a while for the HC-12 to send a new message with servo angles
//So, at the start of the loop the angles will be written to the servo motors
servoWriter(angle1L, angle2L, angle3L, angle4L, angle5L, angle6L); //Function Call to Move Robot to Angles from End of Last Loop

//This section reads in the message coming from the HC-12 to a readBuffer
readBuffer = "";
  boolean start = false;
  //Reads incoming value
  /* JDS */ // while (HC12.available()) {        // If HC-12 has data
  while (Serial.available()) {        // If Serial has data
    /* JDS */ // incomingByte = HC12.read();      // Store each incoming byte from HC-12
    incomingByte = Serial.read();      // Store each incoming byte from Serial
    
    delay(byteD);
    //Reads the data between the start "s" and end marker "e"
    if (start == true) {
      if (incomingByte != 'e') {
        readBuffer += char(incomingByte); //Adds each byte to ReadBuffer string variable
      }
      else {
        start = false;
      }
    }
    else if (incomingByte == 's'){
      start = true; //If true start reading the message
    }
  }

String message = readBuffer; //Saves readBuffer contents to new String
//Serial.println(message); //For debugging purposes only

//This sections initializes the angles to a home position while the HC-12 message is not available
if(message == ""){
  angle1 = angle1L; //Stores Angle to Move Servo 1 To
  angle2 = angle2L; //Stores Angle to Move Servo 2 To
  angle3 = angle3L; //Stores Angle to Move Servo 3 To
  angle4 = angle4L; //Stores Angle to Move Servo 4 To
  angle5 = angle5L; //Stores Angle to Move Servo 5 To
  angle6 = angle6L; //Stores Angle to Move Servo 6 To

  servoWriter(angle1, angle2, angle3, angle4, angle5, angle6); //Function Call to Maintain Same Angle if No New Message
   
}
else{
boundLow = message.indexOf(delimiter); //Locates index of first delimiter i.e. comma https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/indexof/
angle1 = message.substring(0, boundLow).toInt(); //.substring creates a sub string of input string starting at index position zero up to but not including first comma https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/substring/
       
boundHigh = message.indexOf(delimiter, boundLow+1); //This instance is going to search for the next delimiter i.e. comma starting at boundLow+1 i.e. one character after the previous comma https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/indexof/
angle2 = message.substring(boundLow+1, boundHigh).toInt(); //Creates a substring of input starting one character after the first comma ending one character before the second comma

boundLow = message.indexOf(delimiter, boundHigh+1); //Does the same thing as the previous boundHigh line except this locates third comma's index
angle3 = message.substring(boundHigh+1, boundLow).toInt(); //Creates a substring from after second comma up to just before third comma

boundHigh = message.indexOf(delimiter, boundLow+1); //Repeats first boundHigh line operation, Locates fourth comma's index
angle4 = message.substring(boundLow+1, boundHigh).toInt(); //Creates a subtring of input starting one character after third comma up to just before fourth comma
       
boundLow = message.indexOf(delimiter, boundHigh+1); //Does the same thing as the previous boundHigh line except this locates fifth comma's index
angle5 = message.substring(boundHigh+1, boundLow).toInt(); //Creates a substring from after fourth comma up to just before fifth comma

boundF = message.indexOf(finald);
angle6 = message.substring(boundLow+1, boundF).toInt(); //Creates a substring of input starting one character after fifth comma up to just before final delimiter

servoWriter(angle1, angle2, angle3, angle4, angle5, angle6); //Function Call to Write New Angle to Servo Motors from Message

}

//Print out the angle for the servo motor to the serial monitor for debugging purposes
  /* JDS */ // Serial.print("Angle 1: ");
  /* JDS */ // Serial.print(angle1);
  /* JDS */ // Serial.print(", ");
  /* JDS */ // Serial.print("Angle 2: ");
  /* JDS */ // Serial.print(angle2);
  /* JDS */ // Serial.print(", ");
  /* JDS */ // Serial.print("Angle 3: ");
  /* JDS */ // Serial.print(angle3);
  /* JDS */ // Serial.print(", ");
  /* JDS */ // Serial.print("Angle 4: ");
  /* JDS */ // Serial.print(angle4);
  /* JDS */ // Serial.print(", ");
  /* JDS */ // Serial.print("Angle 5: ");
  /* JDS */ // Serial.print(angle5);
  /* JDS */ // Serial.print(", ");
  /* JDS */ // Serial.print("Angle 6: ");
  /* JDS */ // Serial.print(angle6);
  /* JDS */ // Serial.println(".");     

 
  delay(SMd);  //483 appears to be the sweet spot number.  480 and it occasionally skips displaying a reading on a line.  485 and it occasionally doubles up on a reading two for a line

  //Sets all the current angles to the Last variables to be carried over to the next loop
  angle1L = angle1; //Stores current loop's angle for next loop use
  angle2L = angle2; //Stores current loop's angle for next loop use
  angle3L = angle3; //Stores current loop's angle for next loop use
  angle4L = angle4; //Stores current loop's angle for next loop use
  angle5L = angle5; //Stores current loop's angle for next loop use
  angle6L = angle6; //Stores current loop's angle for next loop use
  
}


//Function Definitions

void servoWriter(int input1, int input2, int input3, int input4, int input5, int input6){
  //servoWriter moves all 6 servo motors to the angles input to the function
  Servo1.write(input1); //Moves Specified Servo to Specified Angle
  delay(15); //Gives Servos time to move to position
  Servo2.write(input2); //Moves Specified Servo to Specified Angle
  delay(15); //Gives Servos time to move to position
  Servo3.write(input3); //Moves Specified Servo to Specified Angle
  delay(15); //Gives Servos time to move to position
  Servo4.write(input4); //Moves Specified Servo to Specified Angle
  delay(15); //Gives Servos time to move to position
  Servo5.write(input5); //Moves Specified Servo to Specified Angle
  delay(15); //Gives Servos time to move to position
  Servo6.write(input6); //Moves Specified Servo to Specified Angle
  delay(15); //Gives Servos time to move to position
}









//Notes
//Restrict Joint 1 from 20 to 150 degrees.  It can go down to 0 degrees but buzzes.  I haven't taken it over 150.  It might go further
//Restrict Joint 2 from 110 to 150 degrees.  It can go down to 110 degrees but buzzes a little.  Any lower it can really buzz.  Over 150 it really buzzes.
//Restrict Joint 3 from 100 to 180 degrees.  100 seems to be very high up position (arm raised).  180 seems to be the arm lowered.
//Restrict Joint 4 from 0 to 140 degrees.  It can comfortably do this
//Restrict Joint 5 from 10 to 140 degrees.  It can 0 to 150 (I tested these)
//Restrict Joint 6 from 50 to 120 degrees.  50 is closed gripper.  120 is fully open.  

//A good resting pose
//  Servo1.write(90); //Moves Specified Servo to Specified Angle
//  Servo2.write(110); //Moves Specified Servo to Specified Angle
//  Servo3.write(120); //Moves Specified Servo to Specified Angle
//  Servo4.write(50); //Moves Specified Servo to Specified Angle
//  Servo5.write(50); //Moves Specified Servo to Specified Angle
//  Servo6.write(120); //Moves Specified Servo to Specified Angle

//Reference 1 https://rootsaid.com/long-range-remote-controller/
//Reference 2 https://howtomechatronics.com/tutorials/arduino/arduino-and-hc-12-long-range-wireless-communication-module/
//Reference 3 .remove function https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/remove/
//.remove(index,count) index is where you start removing and count is the number of characters to remove.