/* ************************************************************************
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

#include "IotWebConfFactory.h"
#include "EEPROM.h"

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char IotWebConfFactory::thingName[] = "EnvStation";

// -- Initial password to connect to the Thing, when it creates an own Access Point.
const char IotWebConfFactory::wifiInitialApPassword[] = "88888888";

const int IotWebConfFactory::STRING_LEN = 128;
const int IotWebConfFactory::NUMBER_LEN = 32;

// -- Configuration specific key. The value should be modified if config structure was changed.
const char IotWebConfFactory::CONFIG_VERSION[] = "configv1";

 
// -- Status indicator pin.
//      First it will light up (kept LOW), on Wifi connection it will blink,
//      when connected to the Wifi it will turn off (kept HIGH).
const int IotWebConfFactory::STATUS_PIN = 2;

DNSServer IotWebConfFactory::dnsServer;
WebServer IotWebConfFactory::server(80);

char IotWebConfFactory::url_string_param_value[STRING_LEN];
char IotWebConfFactory::port_int_param_value[NUMBER_LEN];
char IotWebConfFactory::token_string_param_value[STRING_LEN];


IotWebConf IotWebConfFactory::iotWebConf(IotWebConfFactory::thingName, 
                                         &IotWebConfFactory::dnsServer, 
                                         &IotWebConfFactory::server, 
                                         IotWebConfFactory::wifiInitialApPassword, 
                                         IotWebConfFactory::CONFIG_VERSION);
                                         

iotwebconf::ParameterGroup IotWebConfFactory::separator1 = iotwebconf::ParameterGroup("group1", "");
iotwebconf::TextParameter IotWebConfFactory::iotwebconf_url_string_param_value = iotwebconf::TextParameter("Server Url", "stringParam_url", url_string_param_value, STRING_LEN);
iotwebconf::NumberParameter IotWebConfFactory::iotwebconf_port_int_param_value = iotwebconf::NumberParameter("Port", "intParam_port", port_int_param_value, NUMBER_LEN, "number", "1..65535", "min='1' max='65535' step='1'");
iotwebconf::TextParameter IotWebConfFactory::iotwebconf_token_string_param_value = iotwebconf::TextParameter("Token", "stringParam_token", token_string_param_value, STRING_LEN);

IotWebConfFactory::IotWebConfFactory()                                  
{
}

void IotWebConfFactory::setup()
{
  Serial.println();
  Serial.println("IotWebConfFactory Setup start");

  pinMode(23, INPUT);
  IotWebConfFactory::read_factory_reset_button();

  IotWebConfFactory::iotWebConf.setStatusPin(IotWebConfFactory::STATUS_PIN);
  //iotWebConf.setConfigPin(CONFIG_PIN);
  IotWebConfFactory::separator1.addItem(&IotWebConfFactory::iotwebconf_url_string_param_value);
  IotWebConfFactory::separator1.addItem(&IotWebConfFactory::iotwebconf_port_int_param_value);
  IotWebConfFactory::separator1.addItem(&IotWebConfFactory::iotwebconf_token_string_param_value);
  IotWebConfFactory::iotWebConf.addParameterGroup(&IotWebConfFactory::separator1);
  
  //IotWebConfFactory::iotWebConf.addParameter(&IotWebConfFactory::iotwebconf_url_string_param_value);
  //IotWebConfFactory::iotWebConf.addParameter(&IotWebConfFactory::iotwebconf_port_int_param_value);
  //IotWebConfFactory::iotWebConf.addParameter(&IotWebConfFactory::iotwebconf_token_string_param_value);
  IotWebConfFactory::iotWebConf.setConfigSavedCallback(&IotWebConfFactory::configSaved);
  IotWebConfFactory::iotWebConf.setFormValidator(&IotWebConfFactory::formValidator);

  // -- Initializing the configuration.
  IotWebConfFactory::iotWebConf.init();

  // -- Set up required URL handlers on the web server.
  IotWebConfFactory::server.on("/", handleRoot);
  IotWebConfFactory::server.on("/config", []{ IotWebConfFactory::iotWebConf.handleConfig(); });
  IotWebConfFactory::server.on("/status", handleStatus);
  IotWebConfFactory::server.onNotFound([](){ IotWebConfFactory::iotWebConf.handleNotFound(); });

  Serial.println("IotWebConfFactory Setup Done!");
}


void IotWebConfFactory::read_factory_reset_button()
{
  static int read_counter = 0;
  static String read_result = "";
  read_result += "read counter: ";
  read_result += (String)read_counter;
  read_result += " Pin is: ";
  if(digitalRead(23) == HIGH){
    Serial.println("Pin is HIGH!!!");
    read_result += "HIGH , ";
    IotWebConfFactory::clean_eeprom();
  } else {
    Serial.println("Pin is LOW!!!");
    read_result += "LOW , ";
  }
  Serial.println(read_result);
  read_counter++;
}

void IotWebConfFactory::clean_eeprom()
{
  Serial.print("cleanning eeprom...\n");

  int EEPROM_SIZE = 512;
  
  EEPROM.begin(EEPROM_SIZE); //EEPROM Emulation of ESP32 flash

  for (int i = 0; i < EEPROM_SIZE; i++)
  {
    EEPROM.write(i, 255);
  }
  EEPROM.commit();
  
  Serial.print("cleanning eeprom done!\n");
}

void IotWebConfFactory::configSaved()
{
  Serial.println("Configuration was updated.");
}

boolean IotWebConfFactory::formValidator(iotwebconf::WebRequestWrapper* webRequestWrapper)
{
  return true;
  
  Serial.println("Validating form.");
  boolean valid = true;

  int l = server.arg(iotwebconf_url_string_param_value.getId()).length();
  if (l < 3)
  {
    iotwebconf_url_string_param_value.errorMessage = "Please provide at least 3 characters for url";
    valid = false;
  }

  int l1 = server.arg(iotwebconf_token_string_param_value.getId()).length();
  if (l1 < 3)
  {
    iotwebconf_token_string_param_value.errorMessage = "Please provide at least 3 characters for token";
    valid = false;
  }

  return valid;
}

void IotWebConfFactory::handleRoot()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  String s = "<!DOCTYPE html><html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>";
  s += "<title>Environmental Monitoring Station Configuration</title></head><body>Environmental Monitoring Station Configuration.";
  s += "<ul>";
  s += "<li>Url value: ";
  s += url_string_param_value;
  s += "<li>Token value: ";
  s += token_string_param_value;
  s += "<li>Port value: ";
  s += atoi(port_int_param_value);
  s += "</ul>";
  s += "Go to <a href='config'>configure page</a> to change values.";
  s += "</body></html>\n";

  server.send(200, "text/html", s);
}

void IotWebConfFactory::handleStatus()
{
  // -- Let IotWebConf test and handle captive portal requests.
  if (iotWebConf.handleCaptivePortal())
  {
    // -- Captive portal request were already served.
    return;
  }
  String s = "EvironmentalMonitoringStation";

  server.send(200, "text/html", s);
}

void IotWebConfFactory::loop()
{
  IotWebConfFactory::iotWebConf.doLoop();
  //Serial.println("loop called");
}

String IotWebConfFactory::getConfigUrl()
{
  return (String)url_string_param_value;
}

String IotWebConfFactory::getConfigToken()
{
  return (String)token_string_param_value; 
}

String IotWebConfFactory::getConfigPort()
{
  return (String)port_int_param_value;
}

void IotWebConfFactory::mydelay(unsigned long milliseconds)
{
  unsigned long delayStart = millis();
  while (milliseconds > millis() - delayStart)
  {
    IotWebConfFactory::iotWebConf.doLoop();
    delay(1);
  }
  //IotWebConfFactory::iotWebConf.delay(milliseconds);
}
