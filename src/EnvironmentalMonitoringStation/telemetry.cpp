/* ***********************************************************************
 * Environmental Monitoring Station
 * (C) 2019 by Yiannis Bourkelis (https://github.com/YiannisBourkelis/)
 * (C) 2019 by Yiannis Grigoriadis
 * (C) 2019 by Kostas Laftsis
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
#include "failure_watchdog.h"
#include "ArduinoJson.h"

//for http post request to IoT server
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>

#include "uptime_formatter.h"

Telemetry::Telemetry()
{
  //The station sends data to thingboard server every 90 seconds.
  //We set the watchdog to restart arduino almost every hour in case there 
  //is no connection to the internet, because of a router bug or 
  //an unknown issue that might appear.
  FailureWatchdog::setErrorsRestartThreshold(35);
}

void Telemetry::setFirmwareVersion(const String firmware_version)
{
  m_firmware_version = firmware_version;
}

void Telemetry::setTemperatureCelcius(float temperature_celcius)
{
  m_temperature_celcius = temperature_celcius;
}

void Telemetry::setBarometricPressure(float barometricPressure)
{
  m_barometricPressure = barometricPressure;
}

void Telemetry::setHumidity(float humidity)
{
  m_humidity = humidity;
}

void Telemetry::setCarbonMonoxide(float carbonMonoxide)
{
  m_carbonMonoxide = carbonMonoxide;
}

void Telemetry::setNitrogenDioxide(float nitrogenDioxide)
{
  m_nitrogenDioxide = nitrogenDioxide;
}

void Telemetry::setCarbonDioxide(float carbonDioxide)
{
  m_carbonDioxide = carbonDioxide;
}

void Telemetry::setPMS7003_MP_1(float mp_1)
{
  m_PMS7003_MP_1 = mp_1;
}

void Telemetry::setPMS7003_MP_2_5(float mp_2_5)
{
  m_PMS7003_MP_2_5 = mp_2_5;
}

void Telemetry::setPMS7003_MP_10(float mp_10)
{
  m_PMS7003_MP_10 = mp_10;
}

void Telemetry::setHydrogen(float hydrogen)
{
  m_hydrogen = hydrogen;
}

String Telemetry::getFirmwareVersion()
{
  return m_firmware_version;
}

float Telemetry::getTemperatureCelcius()
{
  return m_temperature_celcius;
}

float Telemetry::getBarometricPressure()
{
  return m_barometricPressure;
}

float Telemetry::getHumidity()
{
  return m_humidity;
}

float Telemetry::getCarbonMonoxide()
{
  return m_carbonMonoxide;
}

float Telemetry::getCarbonDioxide()
{
  return m_carbonDioxide;
}

float Telemetry::getNitrogenDioxide()
{
  return m_nitrogenDioxide;
}

float Telemetry::getPMS7003_MP_1()
{
  return m_PMS7003_MP_1;
}

float Telemetry::getPMS7003_MP_2_5()
{
  return m_PMS7003_MP_2_5;
}

float Telemetry::getPMS7003_MP_10()
{
  return m_PMS7003_MP_10;
}

float Telemetry::getHydrogen()
{
  return m_hydrogen;
}

void Telemetry::send_data_to_iot_server2()
{
  HTTPClient https;
  https.begin("https://iot.filoxeni.com/api/user/device/measurement");

  https.addHeader("Content-Type", "application/json"); //Specify content-type header
  https.addHeader("Host", "iot.filoxeni.com"); //Specify content-type header
  https.addHeader("Authorization", "Bearer DCRkyCeUXE1u44z6rBLnWJ6STjRSzpgiRbTYYOa9"); //Specify content-type header

  int httpResponseCode = https.POST(getTelemetryJson()); //Send the actual POST request

  if(httpResponseCode > 0){
    String response = https.getString();  //Get the response to the request
    Serial.println("HTTP POST response code: " + (String)httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
    StaticJsonDocument<1024> json_doc;                         //Memory pool
    deserializeJson(json_doc, response);//Parse message

    
    
    if (json_doc == NULL) {   //Check for errors in parsing
      Serial.println("Json parsing failed");
    } else {
      
      bool upgrade_available = json_doc["upgrade_available"].as<bool>();
      if (upgrade_available){
      
         Serial.println("Upgrade available!");
         Serial.println(upgrade_available);

        const char * fw_update_url = json_doc["firmware_upgrade_url"];
      
        Serial.println(fw_update_url);    
        
        t_httpUpdate_return ret = ESPhttpUpdate.update(fw_update_url);
        switch(ret) {
            case HTTP_UPDATE_FAILED:
                //Serial.println("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                Serial.println("error update");
                break;

            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;

            case HTTP_UPDATE_OK:
                Serial.println("HTTP_UPDATE_OK");
                break;
        }
         

         
      } //if (upgrade_available){
        
    }
    
    } else {
    Serial.print("Error on sending POST (filoxeni): ");
    Serial.println(httpResponseCode);
  }

  //If the http post response is not 200 or 201(laravel api)
  //then report the error to the watchdog
  if(httpResponseCode == 200 || httpResponseCode == 201){
    FailureWatchdog::reportSuccess();
  } else {
    FailureWatchdog::reportError();
  }
  
  https.end();  //Free resources
}

void Telemetry::send_data_to_iot_server()
{
  HTTPClient http;
  //http.begin("http://iot.techthrace.com:8080/api/v1/wGNzhlUkS6EFpW41FcuZ/telemetry");
  //http.begin("http://iot.techthrace.com:8080/api/v1/hVDr5uCDchaFcnojdMzH/telemetry");

  String telemetryPort = getTelemetryPort();
  if (telemetryPort == NULL || telemetryPort == "" || telemetryPort == "0"){
    telemetryPort = "443";
  }
  
  String url = "https://" + getTelemetryUrl() + ":" + telemetryPort + "/api/v1/" + getTelemetryToken() + "/telemetry";
  Serial.println(url);
  http.begin(url);
  http.addHeader("Content-Type", "application/json"); //Specify content-type header
  http.addHeader("Host", "iot.techthrace.com"); //Specify content-type header

  int httpResponseCode = http.POST(getTelemetryJson()); //Send the actual POST request

  if(httpResponseCode > 0){
    String response = http.getString();  //Get the response to the request
    Serial.println("HTTP POST response code: " + (String)httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  } else {
    Serial.print("Error on sending POST (thingsboard): ");
    Serial.println(httpResponseCode);
  }

  //If the http post response is not 200
  //then report the error to the watchdog
  if(httpResponseCode == 200){
    FailureWatchdog::reportSuccess();
  } else {
    FailureWatchdog::reportError();
  }
  
  http.end();  //Free resources
}

String Telemetry::getTelemetryJson()
{
  String json;

  String firmware_version =  (String)getFirmwareVersion();
  String temperature      =  (String)getTemperatureCelcius();
  String pressure         =  (String)getBarometricPressure();
  String humidity         =  (String)getHumidity();
  String carbonMonoxide   =  (String)getCarbonMonoxide();
  String carbonDioxide    =  (String)getCarbonDioxide();
  String nitrogenDioxide  =  (String)getNitrogenDioxide();
  String PMS7003_MP_1     =  (String)getPMS7003_MP_1();
  String PMS7003_MP_2_5   =  (String)getPMS7003_MP_2_5();
  String PMS7003_MP_10    =  (String)getPMS7003_MP_10();
  String hydrogen         =  (String)getHydrogen();
  

  json += "{";
  json += "\"team_id\":\""           + ((String)3)                   + "\"";
  json += ",\"firmware_version\":\"" + ((String)firmware_version)    + "\"";
  json += ",\"temperature\":\""      + temperature                   + "\"";
  json += ",\"pressure\":\""         + pressure                      + "\"";
  json += ",\"humidity\":\""         + humidity                      + "\"";
  json += ",\"carbonMonoxide\":\""   + carbonMonoxide                + "\"";
  json += ",\"carbonDioxide\":\""    + carbonDioxide                 + "\"";
  json += ",\"nitrogenDioxide\":\""  + nitrogenDioxide               + "\"";
  json += ",\"hydrogen\":\""         + hydrogen                      + "\"";
  
  if(getPMS7003_MP_10() > -1){ //pms library returns NULL sometimes probably because of a bug in the implementation. We do not send PMS data in case of NULL (-300 in our case)
  json += ",\"PMS7003_MP_1\":\""     + PMS7003_MP_1                  + "\"";
  json += ",\"PMS7003_MP_2_5\":\""   + PMS7003_MP_2_5                + "\"";
  json += ",\"PMS7003_MP_10\":\""    + PMS7003_MP_10                 + "\"";
  }
  
  json += ",\"uptime\":\""           + uptime_formatter::getUptime() + "\"";
  json += "}";

  Serial.println("Uptime: " + uptime_formatter::getUptime());

  return json;
}

void Telemetry::setTelemetryUrl(String url)
{
  m_telemetry_url = url;
}

void Telemetry::setTelemetryPort(String port)
{
  m_telemetry_port = port;
}

void Telemetry::setTelemetryToken(String token)
{
  m_telemetry_token = token;
}

String Telemetry::getTelemetryUrl()
{
  return m_telemetry_url;
}

String Telemetry::getTelemetryPort()
{
  return m_telemetry_port;
}

String Telemetry::getTelemetryToken()
{
  return m_telemetry_token;
}
