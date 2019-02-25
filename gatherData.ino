#include <SparkFun_VEML6075_Arduino_Library.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"
#include "Adafruit_AS726x.h"
#include "Adafruit_BME680.h"

#define SEALEVELPRESSURE_HPA (1013.25)
VEML6075 uv; // Create a VEML6075 object
Adafruit_AS726x ams; 
Adafruit_BME680 bme; // I2C
Adafruit_TSL2591 tsl = Adafruit_TSL2591(2591); // pass in a number for the sensor identifier (for your use later)

uint32_t lum;
uint16_t ir, full, lux, Altitude, Gas, Humidity, Pressure, Temp, UVI, UVB, UVA, sensorValues[AS726x_NUM_CHANNELS], red, orange, yellow, green, blue, violet;
uint16_t sensorData[16];

void configureSensor(void)
{
tsl.setGain(TSL2591_GAIN_LOW);    // 1x gain (bright light)
tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);  // shortest integration time (bright light)
}

void bmeRead(void){
Temp = bme.temperature;
Pressure = bme.pressure / 100.0;
Humidity = bme.humidity;
Gas = bme.gas_resistance / 1000.0;
Altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
sensorData[0]= Temp;
sensorData[1]= Pressure;
sensorData[2]= Humidity;
sensorData[3]= Gas;
sensorData[4]= Altitude;
}
void colorRead(void){
  ams.startMeasurement(); //begin a measurement
  bool rdy = false;   //wait till data is available
  while(!rdy){
    delay(5);
    rdy = ams.dataReady();
    }
    ams.readRawValues(sensorValues); //read the values!
violet = sensorValues[AS726x_VIOLET];
blue = sensorValues[AS726x_BLUE];
green = sensorValues[AS726x_GREEN];
yellow = sensorValues[AS726x_YELLOW];
orange = sensorValues[AS726x_ORANGE];
red = sensorValues[AS726x_RED];
sensorData[5]= violet;
sensorData[6]= blue;
sensorData[7]= green;
sensorData[8]= yellow;
sensorData[9]= orange;
sensorData[10]= red; 
}
void uvRead(void){
  UVA = uv.uva();
  UVB = uv.uvb();
  UVI = uv.index();
  sensorData[11]= UVA;
  sensorData[12]= UVB;
  sensorData[13]= UVI;
  } 
void whiteRead(void){
  // More advanced data read example. Read 32 bits with top 16 bits IR, bottom 16 bits full spectrum
  // That way you can do whatever math and comparisons you want!
  lum = tsl.getFullLuminosity();
  ir = lum >> 16;
  full = lum & 0xFFFF;
  lux = tsl.calculateLux(full, ir);
  sensorData[14]= ir;
  sensorData[15]= full;
  sensorData[16]= lux;
}  

void setup() {
  
  configureSensor();
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320ºC for 150 ms
  
}

void loop() {

  bmeRead();
  colorRead();
  uvRead();
  whiteRead();
  
}
