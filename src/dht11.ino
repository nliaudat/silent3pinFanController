//DHT11 tutorial : https://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/

/*
Here are the ranges and accuracy of the DHT11:

    Humidity Range: 20-90% RH
    Humidity Accuracy: ±5% RH
    Temperature Range: 0-50 °C
    Temperature Accuracy: ±2% °C
    Operating Voltage: 3V to 5.5V
*/



//dht DHT;
#include "dht11.h" //https://playground.arduino.cc/Main/DHT11Lib/ 

dht11 DHT;

#define DHT11_PIN 7


void dht11_refresh(){
  int chk = DHT.read(DHT11_PIN); //DHT.humidity and DHT.temperature variables updated
  actual_temperature = DHT.temperature;
  actual_humidity = DHT.humidity;
}
