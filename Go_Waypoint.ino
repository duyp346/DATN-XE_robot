
void goWaypoint()
{   


 while (true)  
  {                                                                // Start of Go_Home procedure 
   bluetooth();                                                     // Run the Bluetooth procedure to see if there is any data being sent via BT
   if (blueToothVal == 5){break;}                                   // If a 'Stop' Bluetooth command is received then break from the Loop
   getCompass();                                                    // Update Compass heading                                          
   getGPS();                                                        // Tiny GPS function that retrieves GPS data - update GPS location// delay time changed from 100 to 10
   check();
   if (millis() > 5000 && gps.charsProcessed() < 10)                // If no Data from GPS within 5 seconds then send error
   Bluetooth.println(F("No GPS data: check wiring"));     
 
  Distance_To_Home =  gps.distanceBetween(gps.location.lat(),gps.location.lng(),Home_LATarray[ac-1], Home_LONarray[ac-1]);  //Query Tiny GPS for Distance to Destination
  GPS_Course = gps.courseTo(gps.location.lat(),gps.location.lng(),Home_LATarray[ac-1],Home_LONarray[ac-1]);                               //Query Tiny GPS for Course to Destination   
   
    if (Distance_To_Home <= 2 && Distance_To_Home >= 1)                                   // If the Vehicle has reached it's Destination, then Stop
        {
        StopCar();                                               // Stop the robot after each waypoint is reached
        Bluetooth.println("You have arrived!");       
      //  ac++;                                                    // increment counter for next waypoint
        break;                                                   // Break from Go_Home procedure and send control back to the Void Loop
        }   
   
  if (khoangcach > gioihan || khoangcach == 0)
  {
   if ( abs(GPS_Course - compass_heading) <= 30)                  // If GPS Course and the Compass Heading are within x degrees of each other then go Forward                                                                  
                                                                  // otherwise find the shortest turn radius and turn left or right  
       { 
        Bluetooth.print(Distance_To_Home);
        //check();
         Forward();                                               // Go Forward
         bluetooth();                                                     // Run the Bluetooth procedure to see if there is any data being sent via BT
        if (blueToothVal == 5){break;} 
        Bluetooth.print(" THANG ");
       } 
     else 
         {                                                       
            int x = (GPS_Course - 360);                           // x = the GPS desired heading - 360
            int y = (compass_heading - (x));                      // y = the Compass heading - x
            int z = (y - 360);                                    // z = y - 360
            Bluetooth.print(Distance_To_Home);;
            if ((z <= 180) && (z >= 0))                           // if z is less than 180 and not a negative value then turn left otherwise turn right
              { 
                SlowLeftTurn();
                Bluetooth.print(" TRAI "); 
                bluetooth();                                                     // Run the Bluetooth procedure to see if there is any data being sent via BT
                if (blueToothVal == 5){break;} 
              }
            else 
              { 
               SlowRightTurn();
               Bluetooth.print(" PHAI ");
               bluetooth();                                                     // Run the Bluetooth procedure to see if there is any data being sent via BT
                if (blueToothVal == 5){break;} 
              }               
        } 
    }
    else {
      StopCar();
      delay(300);
      moveSidewaysLeft();
      delay(300);
      Avoid_object();
      }
  }                                                              // End of While Loop

}                                                                // End of Go_Home procedure
