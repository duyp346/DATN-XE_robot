
void Avoid_object()
 { 
  check();
  int khoangcachtrai=khoangcach;
  moveSidewaysRight();
  delay(600);
  check();
  int khoangcachphai=khoangcach;
  moveSidewaysLeft();
  delay(300);
  if(khoangcachphai >= khoangcachtrai){
    Reverse();
    delay(300);
    StopCar();
    delay(300);
    moveSidewaysRight();
    delay(400);
    check();
    }
    if(khoangcachphai < khoangcachtrai){
    Reverse();
    delay(300);
    StopCar();
    delay(300);
    moveSidewaysLeft();
    delay(400);
    check();
    }
 }
