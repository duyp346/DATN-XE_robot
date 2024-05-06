



#include <AFMotor.h>                                              // the Adafruit Motor Shield Library ver. 1 https://learn.adafruit.com/adafruit-motor-shield/library-install
#include "Wire.h"                                                 // Used by I2C and HMC5883L compass
#include <HMC5883L.h>                                           // Library for the compass - Download from Github @ https://github.com/jarzebski/Arduino-HMC5883L
#include <Servo.h>                                                // Servo library to control Servo arm for metal detector
#include <SoftwareSerial.h>                                       // Software Serial for Serial Communications - not used
#include <TinyGPS++.h>                                            // Tiny GPS Plus Library - Download from http://arduiniana.org/libraries/tinygpsplus/
                                                                  // TinyGPS++ object uses Hardware Serial 2 and assumes that you have a
                                                                  // 9600-baud serial GPS device hooked up on pins 16(tx) and 17(rx).                                                                  
SoftwareSerial Bluetooth(13, 2);
//******************************************************************************************************                                                                  
// GPS Variables & Setup

int GPS_Course;                                                    // variable to hold the gps's determined course to destination
int Number_of_SATS;                                                // variable to hold the number of satellites acquired
TinyGPSPlus gps;                                                   // gps = instance of TinyGPS 
                                                                   // pin 17 (blue)   is connected to the TX on the GPS
                                                                   // pin 16 (yellow) is connected to the RX on the GPS

//******************************************************************************************************
// Setup Drive Motors using the Adafruit Motor Controller version 1.0 Library

AF_DCMotor motor1(1, MOTOR12_64KHZ);                               // create motor #1, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ);                               // create motor #2, 64KHz pwm
AF_DCMotor motor3(3, MOTOR12_64KHZ);                               // create motor #3, 64KHz pwm
AF_DCMotor motor4(4, MOTOR12_64KHZ);                               // create motor #4, 64KHz pwm

int turn_Speed = 140;                                              // motor speed when using the compass to turn left and right
int mtr_Spd = 180;                                                 // motor speed when moving forward and reverse

//******************************************************************************************************
// Compass Variables & Setup

HMC5883L compass;                                                  // HMC5883L compass(HMC5883L)
int16_t mx, my, mz;                                                // variables to store x,y,z axis from compass (HMC5883L)
int desired_heading;                                               // initialize variable - stores value for the new desired heading
int compass_heading;                                               // initialize variable - stores value calculated from compass readings
int compass_dev = 5;                                               // the amount of deviation that is allowed in the compass heading - Adjust as Needed
                                                                   // setting this variable too low will cause the robot to continuously pivot left and right
                                                                   // setting this variable too high will cause the robot to veer off course

int Heading_A;                                                     // variable to store compass heading
int Heading_B;                                                     // variable to store compass heading in Opposite direction
int pass = 0;                                                      // variable to store which pass the robot is on

//******************************************************************************************************
// Servo Control

//Servo myservo;                                                     // create servo object to control a servo 
//int pos = 0;                                                       // variable to store the servo position

//******************************************************************************************************
// Ping Sensor for Collision Avoidance

//boolean pingOn = false;                                            // Turn Collision detection On or Off
//
int trig = 43;                                                  // Trig - Orange
int echo = 42;                                                  // Echo - Yellow
unsigned long thoigian; 
int khoangcach; 
int gioihan = 20;
int pump = 28;

 
//******************************************************************************************************
// Bluetooth Variables & Setup

String str;                                                        // raw string received from android to arduino
String str_fire;
int fireVal;
int blueToothVal;                                                  // stores the last value sent over via bluetooth

//*****************************************************************************************************
// GPS Locations

double Distance_To_Home;                                    // variable for storing the distance to destination

int ac =0;                                                         // GPS array counter
int wpCount = 0;                                                   // GPS waypoint counter
double Home_LATarray[50];                                          // variable for storing the destination Latitude - Only Programmed for 5 waypoint
double Home_LONarray[50];                                          // variable for storing the destination Longitude - up to 50 waypoints


//int increment = 0;
int fire_detection = 0;
int step1 = 0;
int step2 = 0;



void setup() 
{  
  Serial.begin(115200);                                            // Serial 0 is for communication with the computer
 // Serial1.begin(9600);                                             // Serial 1 is for Bluetooth communication - DO NOT MODIFY - JY-MCU HC-06 v1.40
  Bluetooth.begin(9600); 
  Bluetooth.setTimeout(1);
  Serial2.begin(9600);                                             // Serial 2 is for GPS communication at 9600 baud - DO NOT MODIFY - Ublox Neo 6m 
//  myservo.attach(9);                                               // attaches the servo to pin 9 (Servo 0 on the Adafruit Motor Control Board)
  

//

  pinMode(trig, OUTPUT);                                        
  pinMode(echo, INPUT); 
  pinMode(pump,OUTPUT);                                        

  // Compass
  Wire.begin();                                                    // Join I2C bus used for the HMC5883L compass
   while (!compass.begin())
  {
    Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
    Bluetooth.println("HMC5883L sensor");
    delay(500);
  }

  // Set measurement range
  compass.setRange(HMC5883L_RANGE_1_3GA);

  // Set measurement mode
  compass.setMeasurementMode(HMC5883L_CONTINOUS);

  // Set data rate
  compass.setDataRate(HMC5883L_DATARATE_30HZ);

  // Set number of samples averaged
  compass.setSamples(HMC5883L_SAMPLES_8);

  // Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(-15,-102,-112);
  
  //Startup();                                                       // Run the Startup procedure on power-up one time
}

//********************************************************************************************************
// Main Loop

void loop()
{ 
  
  bluetooth();                                                     // Run the Bluetooth procedure to see if there is any data being sent via BT                                                    
  getGPS();                                                        // Update the GPS location
  getCompass();                                                    // Update the Compass Heading
//  check();                                                          // Use at your own discretion, this is not fully tested
 if(fire_detection == 1) detection();
 if(step1 == 1) timlua();
 if(step2 == 1) daplua();

}
