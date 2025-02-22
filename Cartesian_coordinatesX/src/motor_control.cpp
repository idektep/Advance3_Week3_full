#include "motor_control.h"
#include <Arduino.h>
#include <AccelStepper.h>
#include <stdint.h>

#define MOTORX_STEP_PIN 2
#define MOTORX_DIR_PIN 5
#define MOTORY_STEP_PIN 3
#define MOTORY_DIR_PIN 6
#define MOTORZ_STEP_PIN 4
#define MOTORZ_DIR_PIN 7

int MICROSTEP_RES = 16;
int STEPRATE = 50;
int STEP_INCREMENT = 100;
int TO_MILLI = 10;

volatile bool INTERRUPT_FLAG = false;

AccelStepper MOTORX(AccelStepper::DRIVER, MOTORX_STEP_PIN, MOTORX_DIR_PIN);
AccelStepper MOTORY(AccelStepper::DRIVER, MOTORY_STEP_PIN, MOTORY_DIR_PIN);
AccelStepper MOTORZ(AccelStepper::DRIVER, MOTORZ_STEP_PIN, MOTORZ_DIR_PIN);

void motorSetup(uint16_t maxSpeed, uint16_t maxAccel)
{
 
  MOTORX.setMaxSpeed(maxSpeed);
  MOTORY.setMaxSpeed(maxSpeed);
  MOTORZ.setMaxSpeed(maxSpeed);
  MOTORX.setAcceleration(maxAccel);
  MOTORY.setAcceleration(maxAccel); 
  MOTORZ.setAcceleration(maxAccel);
}

void moveTomm(float targetX, float targetY, float targetZ)
{
    MOTORX.setSpeed(10000);
    MOTORY.setSpeed(10000);
    MOTORZ.setSpeed(10000);

    float stepsX = targetX * MICROSTEP_RES * STEPRATE / TO_MILLI;
    float stepsY = targetY * MICROSTEP_RES * STEPRATE / TO_MILLI;
    float stepsZ = targetZ * MICROSTEP_RES * STEPRATE / TO_MILLI;

    MOTORX.moveTo(stepsX);
    MOTORY.moveTo(stepsY);
    MOTORZ.moveTo(stepsZ);

    while (MOTORX.distanceToGo() != 0 || MOTORY.distanceToGo() != 0 || MOTORZ.distanceToGo() != 0)
    {
      if (INTERRUPT_FLAG)
      {
        interruptLoop();
        Serial.println("Cartesian was interrupted..!");
        resetBoard();
      }
      else
      {
        MOTORX.run();
        MOTORY.run();
        MOTORZ.run();
      }
    }

    Serial.print("X: ");
    Serial.print(targetX);
    Serial.print(" mm, ");
    Serial.print("y: ");
    Serial.print(targetY);
    Serial.print(" mm, ");
    Serial.print("Z: ");
    Serial.print(targetZ);
    Serial.println(" mm");

}

void interruptLoop()
{
    INTERRUPT_FLAG = true; // ตั้งค่าสถานะให้หยุด loop
}

/////////////////////////////////////////////////////////////////////
void resetBoard()
{
  Serial.println("Arduino reset...");
  delay(1000);
  asm volatile("  jmp 0"); // คำสั่ง Assembly สำหรับรีเซ็ตบอร์ด
}