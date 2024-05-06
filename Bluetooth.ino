//**************************************************************************************************************************************************
// This procedure reads the serial port - Serial1 - for bluetooth commands being sent from the Android device

void bluetooth()
{
  while (Bluetooth.available())                                    // Read bluetooth commands over Serial1 // Warning: If an error with Serial1 occurs, make sure Arduino Mega 2560 is Selected
 {  
  {  
      str = Bluetooth.readStringUntil('\n');                      // str is the temporary variable for storing the last sring sent over bluetooth from Android device
      //Serial.print(str);                                      // for testing purposes
  } 
    
    blueToothVal = (str.toInt());                               //  convert the string 'str' into an integer and assign it to blueToothVal
    Serial.println(blueToothVal);   

// **************************************************************************************************************************************************

 switch (blueToothVal) 
 {
      case 1:                                
        Bluetooth.println("Forward");
        Forward();
        break;

      case 2:                 
        Bluetooth.println("Reverse");
        Reverse();
        break;

      case 3:         
        Bluetooth.println("Left");
        LeftTurn();
        break;
        
      case 4:                     
        Bluetooth.println("Right");
        RightTurn();
        break;
        
      case 5:                                            
        Bluetooth.println("Stop Car ");
        StopCar();
        break; 

      case 6:                 
        setWaypoint();
        break;
      
      case 7:        
        goWaypoint();
        break;  
      
      case 8:        
        Bluetooth.println("Turn Around");
        turnAround();
        break;
      
//      case 9:        
//         //Serial1.println("Compass Forward");
//        setHeading();
//        Compass_Forward();
//        break;
      
//      case 10:
//        setHeading();
//        break; 

      case 11:
         gpsInfo();
        break;
      
      case 12:  
        Bluetooth.println("Compass Turn Right");
        CompassTurnRight();
        break;
      
      case 13:  
        Bluetooth.println("Compass Turn Left");
        CompassTurnLeft();
        break;
        
//      case 14:  
//        Bluetooth.println("Calibrate Compass");
//        calibrateCompass();
//        break;

//      case 15:  
//       fire_detection = 0;
//
//       break;  

      case 16:
        clearWaypoints();
        break;  

      case 17:                    // finish with waypoints
        //ac = 0;
        fire_detection = 1;
//        Serial1.print("Waypoints Complete");
        break;
      

 } // end of switch case

// **************************************************************************************************************************************************  
// Slider Value for Speed

if (blueToothVal)                                    
  {    
   //Serial.println(blueToothVal);
  if (blueToothVal >= 1000)
{
    Bluetooth.print("Speed set To:  ");
    Bluetooth.println(blueToothVal - 1000);
    turn_Speed = (blueToothVal - 1000); 
    Bluetooth.println();
    Bluetooth.print("Turn Speed ");
    Bluetooth.println(turn_Speed);
 } 
  }  

/*

// **************************************************************************************************************************************************
// Detect for Mines - Sweep Not Used

 else if (blueToothVal== 15)                                   
  {    
    Serial1.println("Detecting");
    sweep();
  }

// **************************************************************************************************************************************************  
*/
 }                                                              // end of while loop Serial1 read
 
                                                               // if no data from Bluetooth 
   if (Serial1.available() < 0)                                 // if an error occurs, confirm that the arduino mega board is selected in the Tools Menu
    {
     Serial1.println("No Bluetooth Data ");          
    }
  
} // end of bluetooth procedure
