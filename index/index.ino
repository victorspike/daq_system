/*
 * Data Acquisition System for FSAE ASU 2018
 * 
 * A data collection system written for the 2018 SAE racing car. 
 * The system connects to the sensors mounted on the car, records 
 * the data transmitted by the sensors, saves the records in a SD
 * card.
 * 
 * The circuit:
 * * Components             Pins
 * * Accelerometer:         SDA
 * * Linear Potentiometers: A0 - A3
 * * Hall Effect:           D38 - D41
 * * Steering Angle:        D42
 * * Brake Pedal:           D43
 * * Tire Temperature:      D22 - D25
 * 
 * Created Oct. 22, 2017
 * Authors:
 * * Alvin Addisho
 * * Olu Gbadebo
 * * Victor Fraga
 * * Xavier Sifuentes
 * * Joseph Young
 * * Alexjandro Desiderio
 * * Eunsol Ko
 */

/*
 * external libraries
 */
#include<Wire.h>
#include<SD.h>

/*
 * this array holds the pin number for all components
 */
int allPins[] = [0, 1, 2, 3, 38, 39, 40, 41, 42,43, 22, 23, 24, 25];

/*
 * you can declare any global variable you might need below
 */

// I2C address of MPU-6050 for accelerometer
const int MPU_addr = 0x68;
// keep track of elapsed time in seconds
unsigned long elapsedTime;
// SD Card pin
const int cardPin = 53;

void setup() {
  Serial.begin(115200);
  Wire.begin();

//  confirm that serial port is connected
  while(!Serial){}

//  initialize SD Card
  if (!SD.begin(cardPin)) {
    Serial.println("SD Card failed to initialize or is not present"); 
    return;
  }
  
//  record time and date
  String programStart = current_date + " - " current_time();

//  GPS setup

// record start time in milli-seconds
  elapsedTime = millis();
}

// the loop function runs over and over again forever
void loop() {
  elapsedTime =  millis() - elapsedTime;
}

void gps(){
  
}

void hall_effect(){
  // pins: allPins[4], allPins[5], allPins[6], allPins[7]
}

void linear_potentiometer(){
  // pins: allPins[0], allPins[1], allPins[2], allPins[3]
}

void steering_angle(){
  // pin: allPins[8]
}

void brake_pedal(){
  // pin: allPins[9]
}

void tire_temperature(){
  // pins: allPins[10], allPins[11], allPins[12], allPins[13]
}

void setup_MPU(){
  //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.beginTransmission(0b1101000);
  //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0x6B);                 
  //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.write(0b00000000);           
  Wire.endTransmission();  
  //I2C address of the MPU
  Wire.beginTransmission(0b1101000);
  //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4)  
  Wire.write(0x1B);                 
  //Setting the gyro to full scale +/- 250deg./s 
  Wire.write(0x00000000);           
  Wire.endTransmission(); 
  //I2C address of the MPU
  Wire.beginTransmission(0b1101000);
  //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0x1C);                 
  //Setting the accel to +/- 8g
  Wire.write(0b00010000);           
  Wire.endTransmission(); 
}

int16_t[] accelerometer(){
  Wire.beginTransmission(MPU_addr);
  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.write(0x3B);
  Wire.endTransmission(false);
  // request a total of 14 registers
  Wire.requestFrom(MPU_addr,14,true);  
  
  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  int16_t X_axis = Wire.read()<<8|Wire.read();  
  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  int16_t Y_axis = Wire.read()<<8|Wire.read();  
  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  int16_t Z_axis = Wire.read()<<8|Wire.read();  

  return [X_axis, Y_axis, Z_axis];
}

String current_date(){
  return year() + "/" + month() + "/" + day();
}

String current_time(){
  return hour() + ":" + minute() + ":" + second();
}


