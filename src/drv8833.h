#ifndef DRV8833_H
#define DRV8833_H
#include <I2S.h>


#define ULT D2
#define EEP D3
#define MOTOR_IN1 D4
#define MOTOR_IN2 D5
#define MOTOR_IN3 D6
#define MOTOR_IN4 D7
#define SPEED_RESOLUTION 20
#define MAX_SPEED 256
#define MIN_SPEED 0
#define DEFAULT_SPEED 150
class DRV8833Driver
{
public:
    DRV8833Driver();
    ~DRV8833Driver();


    void PerLoop();
    void Stop();
    void Go();
    void Right();
    void Left();
    void IncSpeed();
    void DecSpeed();

private:
    int currSpeed;
    bool isStopped;

};



#endif 