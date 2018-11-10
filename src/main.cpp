#include <Arduino.h>
#include <Ticker.h>
#include <InternetConnection.h>
#include <Data.h>
#include <MatrixDisplay.h>
#include <thermostat.h>
#include <EEPROM.h>


const int readMetheoDataDisplayDataControllThermostatInterval = 5000;
const int sendDataToInternetInterval = 10000;
const int animInt = 1000;

Data data;
MatrixDisplay display;
InternetConnection connection;

void readMetheoDataDisplayDataControllThermostat();
void sendDataToInternet();
void animate();
Ticker timerReadDataDisplayDataControllThermostat(readMetheoDataDisplayDataControllThermostat, readMetheoDataDisplayDataControllThermostatInterval);
Ticker timerSendDataToInternet(sendDataToInternet, sendDataToInternetInterval);
Ticker animation(animate, animInt);

// Connections to APIs are OK
bool apisAreConnected = false;

void readMetheoDataDisplayDataControllThermostat()
{
    data.setData();    
    ThermostatStatus status = Thermostat::controll(data);
   
    InternetConnection::setIsHeatingToBlynk(status.isHeating);
    data.heating = status.isHeating;
    display.update(data);
}

void animate(){
    if(data.anim == 1){
        data.anim = 0;
    } else {
        data.anim = 1;
    }

    display.update(data);
}

void initializeInternetConnection()
{
    if (connection.initializeThingSpeak())
    {
        apisAreConnected = connection.initializeBlynk();
        connection.initializeOTA();
    }
}

void sendDataToInternet()
{
    if (apisAreConnected)
    {
        connection.setMeteoDataToThingSpeakObject(data);
        //bool successThingSpeak = connection.sendDataToThingSpeakApi();
        bool successBlynk = connection.sendDataToBlynk(data);

        if (/*successThingSpeak &&*/ successBlynk)
        {
            Serial.println("Data was sent");
        }
        else
        {
            Serial.println("No internet connection, try initialize connection");
            apisAreConnected = false;
            initializeInternetConnection();
        }
    }
    else
    {
        initializeInternetConnection();
    }
}

void startTimers()
{
    timerReadDataDisplayDataControllThermostat.start();
    timerSendDataToInternet.start();
    animation.start();
}

void updateTimers()
{
    timerReadDataDisplayDataControllThermostat.update();
    timerSendDataToInternet.update();
    animation.update();
}

// Set up environment before loop
void setup()
{
    // Two bytes for device status (enabled/disabled, required temperature)
    EEPROM.begin(2);
    Serial.begin(9600);
    delay(100);

    Thermostat::initialize();
    initializeInternetConnection();
    startTimers();
}

// Excecute code in forever loop
void loop()
{
    updateTimers();
    connection.runBlynk();
    connection.handleOTA();
}