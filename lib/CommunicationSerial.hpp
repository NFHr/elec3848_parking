#ifndef __COMMUNICATION_SERIAL_HPP__
#define __COMMUNICATION_SERIAL_HPP__

#include "Display_SSD1306.hpp"
#include "MotorController.hpp"
#include "Sensor.hpp"
#include <Arduino.h>

#define SR Serial  // Serial on USB
#define WR Serial3 // Wireless Module on Serial 3 (D14 & D15)

class CommunicationSerial
{
public:
    CommunicationSerial(void);
    void begin();

    inline char serialControlMotor(MotorController *motor_controller);
    inline char wirelessControlMotor(MotorController *motor_controller);

    inline void serialSensorDataTX(Sensor *sensor);
    inline void wirelessSensorDataTX(Sensor *sensor);
};

CommunicationSerial::CommunicationSerial(void) {}

void CommunicationSerial::begin()
{
    SR.begin(115200);
    WR.begin(38400);
}

inline char CommunicationSerial::serialControlMotor(MotorController *motor_controller)
{
    static char buffer;
    if (SR.available())
    {
        buffer = SR.read();
        SR.flush();
        motor_controller->controlByCommand(buffer);
    }
    return buffer;
}

inline char CommunicationSerial::wirelessControlMotor(MotorController *motor_controller)
{
    static char buffer;
    if (WR.available())
    {
        buffer = WR.read();
        WR.flush();
        motor_controller->controlByCommand(buffer);
    }
    return buffer;
}

inline void CommunicationSerial::serialSensorDataTX(Sensor *sensor)
{
    SR.print("LL=");
    SR.print(sensor->getLightL());
    SR.print(",LR=");
    SR.print(sensor->getLightR());
    SR.print(",DT=");
    SR.print(sensor->getDistance());
    SR.print(",AX=");
    SR.print(sensor->getAngleX());
    SR.print(",AZ=");
    SR.print(sensor->getAngleZ());
    SR.println("");
}

inline void CommunicationSerial::wirelessSensorDataTX(Sensor *sensor)
{
    WR.print("LL=");
    WR.print(sensor->getLightL());
    WR.print(",LR=");
    WR.print(sensor->getLightR());
    WR.print(",DT=");
    WR.print(sensor->getDistance());
    WR.print(",AX=");
    WR.print(sensor->getAngleX());
    WR.print(",AZ=");
    WR.print(sensor->getAngleZ());
    WR.println("");
}

#endif