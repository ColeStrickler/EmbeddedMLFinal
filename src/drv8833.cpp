#include "drv8833.h"



void SetMotorPWM(int pwm, int pin1, int pin2)
{
    printf("speed: %d\n", pwm);
    
    if (pwm < 0)
    {
        pwm = 0;
        analogWrite(pin1, pwm);
        //digitalWrite(pin1, HIGH);
        digitalWrite(pin2, LOW);
    }
    else
    {
        pwm = max(pwm, 254);
        digitalWrite(pin1, LOW);
        //digitalWrite(pin2, HIGH);
        analogWrite(pin2, pwm);
    }
}

DRV8833Driver::DRV8833Driver() : currSpeed(DEFAULT_SPEED), isStopped(true)
{
    //pinMode(ULT, OUTPUT); // Set the pin as output
    pinMode(EEP, OUTPUT); // Set the pin as output
    pinMode(MOTOR_IN1, OUTPUT); // Set the pin as output
    pinMode(MOTOR_IN2, OUTPUT); // Set the pin as output
    pinMode(MOTOR_IN3, OUTPUT); // Set the pin as output
    pinMode(MOTOR_IN4, OUTPUT); // Set the pin as output
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, LOW);
    digitalWrite(MOTOR_IN3, LOW);
    digitalWrite(MOTOR_IN4, LOW);
//
    digitalWrite(EEP, HIGH);
    //SetMotorPWM(currSpeed, MOTOR_IN1, MOTOR_IN2);
}

DRV8833Driver::~DRV8833Driver()
{
}

void DRV8833Driver::PerLoop()
{
    if (!isStopped)
    {
        //printf("PERLOOP\n");
        //analogWrite(MOTOR_IN1, currSpeed);
        //digitalWrite(MOTOR_IN2, LOW);
    }
   
}

void DRV8833Driver::Stop()
{
    digitalWrite(EEP, LOW);
    isStopped = true;
    digitalWrite(MOTOR_IN3, LOW);
    digitalWrite(MOTOR_IN4, HIGH);
    //SetMotorPWM(-currSpeed, MOTOR_IN3, MOTOR_IN4);
    
}

void DRV8833Driver::Go()
{
    isStopped = false;
    digitalWrite(MOTOR_IN3, HIGH);
    digitalWrite(MOTOR_IN4, LOW);
    digitalWrite(EEP, HIGH);
    
    //SetMotorPWM(currSpeed, MOTOR_IN3, MOTOR_IN4);
}

void DRV8833Driver::Right()
{
    digitalWrite(MOTOR_IN1, HIGH);
    digitalWrite(MOTOR_IN2, LOW);

    
}

void DRV8833Driver::Left()
{
    digitalWrite(MOTOR_IN1, LOW);
    digitalWrite(MOTOR_IN2, HIGH);
}

void DRV8833Driver::IncSpeed()
{
    currSpeed += SPEED_RESOLUTION;
    //SetMotorPWM(currSpeed, MOTOR_IN1, MOTOR_IN2);
}

void DRV8833Driver::DecSpeed()
{
    currSpeed -= SPEED_RESOLUTION;
    //SetMotorPWM(currSpeed, MOTOR_IN1, MOTOR_IN2);
}
