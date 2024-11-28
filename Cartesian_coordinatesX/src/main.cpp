#include <Arduino.h>
#include "motor_control.h"

void setup()
{

  Serial.begin(115200);
  motorSetup(10000, 2500); // 2500 คือ 2500 step/s ยกกำลัง 2


}

void loop()
{
  // put your main code here, to run repeatedly:

   moveTomm(100, 100, 50); // คำสั่งให้ robot move ในแกน x, y,z 
   moveTomm(0, 0, 0); // คำสั่งให้ robot move กลับมาในแกนตำแหน่ง 0 
}
