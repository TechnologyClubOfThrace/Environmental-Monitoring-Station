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
                                         

IotWebConfSeparator IotWebConfFactory::separator1 = IotWebConfSeparator();
IotWebConfParameter IotWebConfFactory::iotwebconf_url_string_param_value = IotWebConfParameter("Server Url", "stringParam_url", url_string_param_value, STRING_LEN);
IotWebConfParameter IotWebConfFactory::iotwebconf_port_int_param_value = IotWebConfParameter("Port", "intParam_port", port_int_param_value, NUMBER_LEN, "number", "1..65535", NULL, "min='1' max='65535' step='1'");
IotWebConfParameter IotWebConfFactory::iotwebconf_token_string_param_value = IotWebConfParameter("Token", "stringParam_token", token_string_param_value, STRING_LEN);

IotWebConfFactory::IotWebConfFactory()                                  
{
}

void IotWebConfFactory::setup()
{
  Serial.println();
  Serial.println("IotWebConfFactory Setup start");

  pinMode(23, INPUT);
  if(digitalRead(23) == HIGH){
    Serial.println("Pin is HIGH!!!");
    IotWebConfFactory::clean_eeprom();
  }

  //Serial.println(IotWebConfFactory::wifiInitialApPassword);


  IotWebConfFactory::iotWebConf.setStatusPin(IotWebConfFactory::STATUS_PIN);
  //iotWebConf.setConfigPin(CONFIG_PIN);
  IotWebConfFactory::iotWebConf.addParameter(&IotWebConfFactory::separator1);
  IotWebConfFactory::iotWebConf.addParameter(&IotWebConfFactory::iotwebconf_url_string_param_value);
  IotWebConfFactory::iotWebConf.addParameter(&IotWebConfFactory::iotwebconf_port_int_param_value);
  IotWebConfFactory::iotWebConf.addParameter(&IotWebConfFactory::iotwebconf_token_string_param_value);
  IotWebConfFactory::iotWebConf.setConfigSavedCallback(&IotWebConfFactory::configSaved);
  IotWebConfFactory::iotWebConf.setFormValidator(&IotWebConfFactory::formValidator);

  // -- Initializing the configuration.
  IotWebConfFactory::iotWebConf.init();

  // -- Set up required URL handlers on the web server.
  IotWebConfFactory::server.on("/", handleRoot);
  IotWebConfFactory::server.on("/config", []{ IotWebConfFactory::iotWebConf.handleConfig(); });
  IotWebConfFactory::server.onNotFound([](){ IotWebConfFactory::iotWebConf.handleNotFound(); });

  Serial.println("IotWebConfFactory Setup Done!");
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

boolean IotWebConfFactory::formValidator()
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

void IotWebConfFactory::mydelay(unsigned long mmillis)
{
  unsigned long delayStart = millis();
  while (mmillis > millis() - delayStart)
  {
    IotWebConfFactory::iotWebConf.doLoop();
    delay(1);
  }
  //IotWebConfFactory::iotWebConf.delay(mmillis);
}
