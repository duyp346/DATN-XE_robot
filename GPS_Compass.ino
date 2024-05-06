void calibrateCompass()                                           // Experimental Use Only to Calibrate Magnetometer/ Compass
{
int minX = 0;
int maxX = 0;
int minY = 0;
int maxY = 0;
int minZ = 0;
int maxZ = 0;
int offX = 0;
int offY = 0;
int offZ = 0;

  for (int i=1000; i >= 1; i--) 
  {
  Vector mag = compass.readRaw();                                 // Read compass data
  
  // Determine Min / Max values
 if (mag.XAxis < minX) minX = mag.XAxis;
  if (mag.XAxis > maxX) maxX = mag.XAxis;
  if (mag.YAxis < minY) minY = mag.YAxis;
  if (mag.YAxis > maxY) maxY = mag.YAxis;
  if (mag.ZAxis < minZ) minZ = mag.ZAxis;
  if (mag.ZAxis > maxZ) maxZ = mag.ZAxis;

  // Calculate offsets
  offX = (maxX + minX)/2;
  offY = (maxY + minY)/2;
  offZ = (maxZ + minZ)/2;

  
  delay(10);

  
  }                                                               // end of for loop
  
  StopCar();

  compass.setOffset(offX,offY,offZ);                                  // Set calibration offset
}
 
 // ************************************************************************************************************************************************* 

void getGPS()                                                 // Get Latest GPS coordinates
{
    while (Serial2.available() > 0)
    gps.encode(Serial2.read());
} 

// *************************************************************************************************************************************************
 
void setWaypoint()                                            // Set up to 5 GPS waypoints
{


if (wpCount >= 0)
  {
//    Serial1.print("GPS Waypoint ");
//    Serial1.print(wpCount + 1);
    Bluetooth.println(" Set ");
    getGPS();                                                 // get the latest GPS coordinates
    getCompass();                                             // update latest compass heading     
                                               
    Home_LATarray[ac] = gps.location.lat();                   // store waypoint in an array   
    Home_LONarray[ac] = gps.location.lng();                   // store waypoint in an array   
                                                              
    Serial.print("Waypoint #1: ");
    Serial.print(Home_LATarray[0],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[0],6);
    Serial.print("Waypoint #2: ");
    Serial.print(Home_LATarray[1],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[1],6);
    Serial.print("Waypoint #3: ");
    Serial.print(Home_LATarray[2],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[2],6);
    Serial.print("Waypoint #4: ");
    Serial.print(Home_LATarray[3],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[3],6);
    Serial.print("Waypoint #5: ");
    Serial.print(Home_LATarray[4],6);
    Serial.print(" ");
    Serial.println(Home_LONarray[4],6);

    wpCount++;                                                  // increment waypoint counter
    ac++;                                                       // increment array counter
        
  }         
  else {Serial1.print("Waypoints Full");}
}

// ************************************************************************************************************************************************* 

void clearWaypoints()
{
   memset(Home_LATarray, 0, sizeof(Home_LATarray));             // clear the array
   memset(Home_LONarray, 0, sizeof(Home_LONarray));             // clear the array
   wpCount = 0;                                                 // reset increment counter to 0
   ac = 0;
   
   Bluetooth.print("GPS Waypoints Cleared");                      // display waypoints cleared
  
}

 // *************************************************************************************************************************************************
 
void getCompass()                                               // get latest compass value
 {  

  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);
 float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;
   if (heading < 0)
  {
    heading += 2 * PI;
  }

  if (heading > 2 * PI)
  {
    heading -= 2 * PI;
  }
  compass_heading = (int)(heading * 180/M_PI);                   // assign compass calculation to variable (compass_heading) and convert to integer to remove decimal places                                                              

 }

 // *************************************************************************************************************************************************

void setHeading()
                                                                 // This procedure will set the current heading and the Heading(s) of the robot going away and returning using opposing degrees from 0 to 360;
                                                                 // for instance, if the car is leaving on a 0 degree path (North), it will return on a 180 degree path (South)
{
   for (int i=0; i <= 5; i++)                                    // Take several readings from the compass to insure accuracy
      { 
        getCompass();                                            // get the current compass heading
      }                                               
    
    desired_heading = compass_heading;                           // set the desired heading to equal the current compass heading
    Heading_A = compass_heading;                                 // Set Heading A to current compass 
    Heading_B = compass_heading + 180;                           // Set Heading B to current compass heading + 180  

      if (Heading_B >= 360)                                      // if the heading is greater than 360 then subtract 360 from it, heading must be between 0 and 360
         {
          Heading_B = Heading_B - 360;
         }
     
    Serial1.print("Compass Heading Set: "); 
    Serial1.print(compass_heading);   
    Serial1.print(" Degrees");

    Serial.print("desired heading");
    Serial.println(desired_heading);
    Serial.print("compass heading");
    Serial.println(compass_heading);

}

// *************************************************************************************************************************************************
 
void gpsInfo()                                                  // displays Satellite data to user
  {
        getGPS();
        getCompass();
        Number_of_SATS = (int)(gps.satellites.value());         //Query Tiny GPS for the number of Satellites Acquired 
        Distance_To_Home = gps.distanceBetween(gps.location.lat(),gps.location.lng(),Home_LATarray[ac-1], Home_LONarray[ac-1]);  //Query Tiny GPS for Distance to Destination  
         GPS_Course = gps.courseTo(gps.location.lat(),gps.location.lng(),Home_LATarray[ac-1],Home_LONarray[ac-1]);
         int cuongcho = abs(GPS_Course - compass_heading);
        Serial.print("Lat:");
        Serial.print(gps.location.lat(),6);
        Serial.print(" Lon:");
        Serial.print(gps.location.lng(),6);
        Serial.print(" ");
        Serial.print(Number_of_SATS); 
        Serial.print(" SATs ");
        Serial.print(Distance_To_Home);
        Serial.print(" m"); 
        Serial.println(GPS_Course);
Bluetooth.print("Distance to Home ");
Bluetooth.println(Distance_To_Home);
Bluetooth.print("GPS_Course ");
Bluetooth.println(cuongcho);

  
  }
