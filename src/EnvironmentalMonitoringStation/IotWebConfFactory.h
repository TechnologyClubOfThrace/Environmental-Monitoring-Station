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

#include <IotWebConf.h>

class IotWebConfFactory
{
  public:
    IotWebConfFactory();
    static void setup();
    static void loop();
    static void mydelay(unsigned long milliseconds);

    static String getConfigUrl();
    static String getConfigToken();
    static String getConfigPort();
    static void read_factory_reset_button();

  private:
    // -- Initial name of the Thing. Used e.g. as SSID of the own Access Point.
    static const char thingName[];
    
    // -- Initial password to connect to the Thing, when it creates an own Access Point.
    static const char wifiInitialApPassword[];
    
    static const int STRING_LEN;
    static const int NUMBER_LEN;
    
    // -- Configuration specific key. The value should be modified if config structure was changed.
    static const char CONFIG_VERSION[];
    
    
    // -- Status indicator pin.
    //      First it will light up (kept LOW), on Wifi connection it will blink,
    //      when connected to the Wifi it will turn off (kept HIGH).
    static const int STATUS_PIN;

    // -- Callback method declarations.
    static void configSaved();
    static boolean formValidator();

    static DNSServer dnsServer;
    static WebServer server;

    static char url_string_param_value[];
    static char port_int_param_value[];
    static char token_string_param_value[];

    static IotWebConf iotWebConf;

    static IotWebConfSeparator separator1;
    static IotWebConfParameter iotwebconf_url_string_param_value;
    static IotWebConfParameter iotwebconf_port_int_param_value;
    static IotWebConfParameter iotwebconf_token_string_param_value;

    static void clean_eeprom();

    static void handleRoot();
    static void handleStatus();
};
