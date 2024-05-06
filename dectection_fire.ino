void detection()
{
    bluetooth();
    if (blueToothVal == 5){      
      step1 = 1;
      fire_detection = 0;
    }
    ReceivePI();
    if (fireVal > 0) {
      StopCar();
      Bluetooth.println(fireVal);
      step1 = 1;
      fire_detection = 0;
    }
    SlowLeftTurn();
    delay(180);
    ReceivePI();
    StopCar();
    delay(1500);
}

void timlua()
{
  while(step1 == 1){
    bluetooth();
    ReceivePI();
    if (blueToothVal == 5){
      StopCar();
      step2 = 1;
      step1 = 0;
      break;
    }
    if((fireVal >= 10 && fireVal <= 50)){
      StopCar();
      step2 = 1;
      step1 = 0;
      break;
    }
    if(fireVal < 10){
      FireFoward();
    }
  }
}
