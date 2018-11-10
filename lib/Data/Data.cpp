#include "Data.h"
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;


void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// Initialize and get metheorological data
Data::Data()
{
    sensors.begin();
    pinMode (D2, INPUT_PULLUP);
    if (!sensors.getAddress(insideThermometer, 0)) 
        Serial.println("Unable to find address for DS18b20"); 
    Serial.print("DS18b20 Address: ");
    printAddress(insideThermometer);
    Serial.println();

    sensors.setResolution(insideThermometer, 11);

    Serial.print("DS18b20 Resolution: ");
    Serial.print(sensors.getResolution(insideThermometer), DEC); 
    Serial.println();

    anim = 0;
}

void Data::setData(void)
{
    sensors.requestTemperatures();
    temperature = sensors.getTempC(insideThermometer);

    if (isnan(temperature))
    {
        Serial.println("Error during read temperature");
    }
    
    Serial.print("DS18b20 Temp: ");
    Serial.print(temperature);
    Serial.println(" C");
}

bool Data::dataAreValid(void)
{
    return temperature <= 50.0 && temperature >= 5.0;
}
