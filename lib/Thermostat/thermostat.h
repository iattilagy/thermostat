#ifndef __Thermostat_H
#define __Thermostat_H

#include <Data.h>
#include <EEPROM.h>

struct ThermostatStatus
{
    char *message;
    char *color;
    bool isHeating;
};

class Thermostat
{
  public:
    static ThermostatStatus controll(Data data);
    static void initialize();
};

#endif
