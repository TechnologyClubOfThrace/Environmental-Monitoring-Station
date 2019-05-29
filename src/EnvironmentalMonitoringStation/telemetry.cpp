/* ***********************************************************************
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

#include "telemetry.h"

//for http post request to IoT server
#include "HTTPClient.h"

#include "uptime_formatter.h"

Telemetry::Telemetry()
{
  
}

void Telemetry::setTemperatureCelcius(float temperature_celcius)
{
  m_temperature_celcius = temperature_celcius;
}

void Telemetry::setPhotoresistor(float photoresistor)
{
  m_photoresistor = photoresistor;
}

void Telemetry::setBarometricPressure(float barometricPressure)
{
  m_barometricPressure = barometricPressure;
}

void Telemetry::setHumidity(float humidity)
{
  m_humidity = humidity;
}

float Telemetry::getTemperatureCelcius()
{
  return m_temperature_celcius;
}

float Telemetry::getPhotoresistor()
{
  return m_photoresistor;
}

float Telemetry::getBarometricPressure()
{
  return m_barometricPressure;
}

float Telemetry::getHumidity()
{
  return m_humidity;
}

void Telemetry::send_data_to_iot_server()
{
  HTTPClient http; 
  http.begin("http://chat.steth.gr:8080/api/v1/wGNzhlUkS6EFpW41FcuZ/telemetry");
  http.addHeader("Content-Type", "application/json"); //Specify content-type header 
 
  int httpResponseCode = http.POST(getTelemetryJson()); //Send the actual POST request
  
  if(httpResponseCode > 0){
    String response = http.getString();  //Get the response to the request 
    Serial.println("HTTP POST response code: " + (String)httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  } else { 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode); 
  }
  
  http.end();  //Free resources
}

String Telemetry::getTelemetryJson()
{
  String json;

  String temperature = (String)getTemperatureCelcius();
  String pressure = (String)getBarometricPressure();
  String humidity = (String)getHumidity();
  String photoresistor = (String)getPhotoresistor();
  
  json += "{";
  json += "\"temperature\":\""+ temperature +"\"";
  json += ",\"pressure\":\""+ pressure + "\"";
    json += ",\"humidity\":\""+ humidity + "\"";
  json += ",\"photoresistor\":\""+ photoresistor + "\"";
  json += ",\"uptime\":\"" + uptime_formatter::getUptime() + "\"";
  json += "}";

  Serial.println("Uptime: " + uptime_formatter::getUptime());

  return json;
}
