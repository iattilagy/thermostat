#include "thermostat.h"

// PINS
#define RP D1

const float hysteresis = 0.25;

void Thermostat::initialize()
{
    // set pinmodes to LED and relay
    pinMode(RP, OUTPUT);
}

// Set thermostat ON/OFF and temperature
ThermostatStatus Thermostat::controll(Data data)
{
    ThermostatStatus status;
    if (data.dataAreValid()) {
        int requiredTemperature = EEPROM.read(2);
        if (requiredTemperature >= 10 && requiredTemperature <= 30 && data.temperature <= requiredTemperature - hysteresis) {
            digitalWrite(RP, HIGH);
            status.isHeating = true;
            Serial.println("Heating");
        } else {
            digitalWrite(RP, LOW);
            status.isHeating = false;
        }
    } else {
        digitalWrite(RP, LOW);
        status.isHeating = false;
        Serial.println("Temperature data is invalid, switching heating off");
    }
    return status;
}
