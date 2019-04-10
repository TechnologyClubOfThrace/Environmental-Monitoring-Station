/* ************************************************************************
 * Environmental Monitoring Station
 * (C) 2019 by Yiannis Bourkelis (https://github.com/YiannisBourkelis/)
 * (C) 2019 by Marios Zikos
 *
 * This file is part of Environmental Monitoring Station.
 *
 * Environmental Monitoring Station is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Environmental Monitoring Station is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Environmental Monitoring Station.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************/

#define LED_PIN      2

#include "WiFi.h"

//headers for reading temperature 
#include <OneWire.h> 
#include <DallasTemperature.h>

#include <limits>

//BMP180
#include <Wire.h>
#include <Adafruit_BMP085.h>
Adafruit_BMP085 bmp180;

#include "telemetry.h"
Telemetry telemetry;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);

  if (bmp180.begin())
    Serial.println("BMP180 init success");
  else {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.
    Serial.println("BMP180 init fail\n\n");

    Serial.println(std::numeric_limits<unsigned long>::max());
  }

  // Your WiFi credentials.// Set password to "" for open networks.
  static char * ssid = "steth";
  static char * password = "ilovecomputers";

  IPAddress ip (192,168,1,25);
  IPAddress dns (1,1,1,1);
  IPAddress gateway (192,168,1,20);
  IPAddress netmask (255,255,255,0);
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t)0x00000000, IPAddress dns2 = (uint32_t)0x00000000);
  WiFi.config(ip, gateway, netmask, dns); 
  //WiFi.config(ip); 
  
  Serial.println("WiFi.begin(ssid, password)...");
  WiFi.begin(ssid, password);

  Serial.println("Starting ...");
  delay(2000);
}

void read_temperature()
{
  // temperature Data wire is plugged into pin 13 on the Arduino
  static const byte ONE_WIRE_BUS = 13;
  // 9 - 12 precision
  static const byte TEMPERATURE_PRECISION = 12;
  
  // Setup a oneWire instance to communicate with any OneWire devices  
  // (not just Maxim/Dallas temperature ICs) 
  static OneWire oneWire(ONE_WIRE_BUS); 
  // Pass our oneWire reference to Dallas Temperature. 
  static DallasTemperature temperature_sensors(&oneWire);
  
  Serial.println("Requesting temperatures...");
  temperature_sensors.requestTemperatures(); // Send the command to get temperature readings
  Serial.print("Temperature is: ");
  telemetry.setTemperatureCelcius(temperature_sensors.getTempCByIndex(0));
  Serial.println(telemetry.getTemperatureCelcius());
}

void read_photoresistor()
{
  telemetry.setPhotoresistor(analogRead(34));
  Serial.print("Photoresistor is: ");
  Serial.println(telemetry.getPhotoresistor());
}

void read_barometric_pressure()
{
  telemetry.setBarometricPressure(bmp180.readPressure() / 100);
  Serial.println("Barometric pressure is: " + (String)telemetry.getBarometricPressure() + " hPa");
}

void connect_to_wifi()
{
  if(WiFi.status() != WL_CONNECTED){
    WiFi.reconnect();
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
    
    Serial.println("Connected to the WiFi network.");
    Serial.print("WiFi IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void loop() {
  //connects to the wifi if not connected.
  //Returns only when a wifi connection is established.
  connect_to_wifi();

  //reads the temperature from the sensor
  read_temperature();

  //reads the barometric pressure from the sensor
  read_barometric_pressure();

  //reads the photoresistor value from the sensor
  read_photoresistor();

  //sends all sensor data to the iot server
  telemetry.send_data_to_iot_server();

  Serial.println("\n");
  delay(5000);
}
