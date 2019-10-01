#include <IotWebConf.h>
#include "EEPROM.h" //????

// -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
const char thingName[] = "EnvStation";

// -- Initial password to connect to the Thing, when it creates an own Access Point.
const char wifiInitialApPassword[] = "88888888";

#define STRING_LEN 128
#define NUMBER_LEN 32

// -- Configuration specific key. The value should be modified if config structure was changed.
#define CONFIG_VERSION "configv1"


// -- Status indicator pin.
//      First it will light up (kept LOW), on Wifi connection it will blink,
//      when connected to the Wifi it will turn off (kept HIGH).
#define STATUS_PIN 2

// -- Callback method declarations.
void configSaved();
boolean formValidator();

DNSServer dnsServer;
WebServer server(80);

char url_string_param_value[STRING_LEN];
char port_int_param_value[NUMBER_LEN];
char token_string_param_value[STRING_LEN];

IotWebConf iotWebConf(thingName, &dnsServer, &server, wifiInitialApPassword, CONFIG_VERSION);

IotWebConfSeparator separator1 = IotWebConfSeparator();
IotWebConfParameter iotwebconf_url_string_param_value = IotWebConfParameter("Server Url", "stringParam_url", url_string_param_value, STRING_LEN);
IotWebConfParameter iotwebconf_port_int_param_value = IotWebConfParameter("Port", "intParam_port", port_int_param_value, NUMBER_LEN, "number", "1..65535", NULL, "min='1' max='65535' step='1'");
IotWebConfParameter iotwebconf_token_string_param_value = IotWebConfParameter("Token", "stringParam_token", token_string_param_value, STRING_LEN);



void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting up...");

  pinMode(33, INPUT);
  if(digitalRead(33) == HIGH){
    Serial.println("Pin is HIGH!!!");
    clean_eeprom();
  }


  iotWebConf.setStatusPin(STATUS_PIN);
//  iotWebConf.setConfigPin(CONFIG_PIN);
  iotWebConf.addParameter(&separator1);
  iotWebConf.addParameter(&iotwebconf_url_string_param_value);
  iotWebConf.addParameter(&iotwebconf_port_int_param_value);
  iotWebConf.addParameter(&iotwebconf_token_string_param_value);
  iotWebConf.setConfigSavedCallback(&configSaved);
  iotWebConf.setFormValidator(&formValidator);

  // -- Initializing the configuration.
  iotWebConf.init();

  // -- Set up required URL handlers on the web server.
  server.on("/", handleRoot);
  server.on("/config", []{ iotWebConf.handleConfig(); });
  server.onNotFound([](){ iotWebConf.handleNotFound(); });

  Serial.println("Ready.");
}


void clean_eeprom()
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


void loop()
{
  // -- doLoop should be called as frequently as possible.
  iotWebConf.doLoop();
}

/**
 * Handle web requests to "/" path.
 */
void handleRoot()
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

void configSaved()
{
  Serial.println("Configuration was updated.");
}

boolean formValidator()
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
