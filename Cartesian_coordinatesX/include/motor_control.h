#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <AccelStepper.h>

void motorSetup(uint16_t maxSpeed, uint16_t maxAccel);
void moveTomm(float targetX, float targetY, float targetZ);
void interruptLoop();
void resetBoard();

#endif
