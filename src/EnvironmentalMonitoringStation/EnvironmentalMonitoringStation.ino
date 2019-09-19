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

//conditional variables for various purposes
//#define DISABLE_PMS7003 // if defined, disables PMS7003 sensor and delay
#define DEBUG_FAST_LOOP
#define USE_UART0

//the board should support an ADC resolution of 12bits
//TODO: check if there is a constant to get the ADC resolution of the board at compile time
static const unsigned int ADC_RESOLUTION = 4096;

#define LED_PIN      2
#define MQ7_CO_PIN   39 //ADC GPIO34 - Carbon Monoxide Sensor

#include "WiFi.h"
#include "failure_watchdog.h"
#include "MQ7.h"

#ifndef DISABLE_PMS7003
#include "PMS.h"
PMS pms(Serial);
PMS::DATA data;
#endif


//headers for reading temperature 
#include <OneWire.h> 
#include <DallasTemperature.h>

#include <limits.h>
MQ7 mq7(MQ7_CO_PIN, 5.0);

//BME280 atmospheric pressure and hunidity sensor (temperature sensor not used)
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme280;


//library that collects and sends data to the IoT server
#include "telemetry.h"
Telemetry telemetry;

//setup code runs once at the beginning
void setup() {
  
  #ifndef DISABLE_PMS7003
  //PMS7003 Serial - UART2
  Serial.begin(PMS::BAUD_RATE);
  #else
  Serial.begin(115200);
  #endif
  
  Serial2.begin(9600);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_PIN, OUTPUT);

  // BME280 sensor init
  if (bme280.begin(0x76))
  {
    #ifdef DISABLE_PMS7003
    Serial.println("BME2800 init success");
    #endif

    bme280.setSampling(Adafruit_BME280::MODE_NORMAL,
    Adafruit_BME280::SAMPLING_NONE, // temperature sensor off
    Adafruit_BME280::SAMPLING_X16, // pressure
    Adafruit_BME280::SAMPLING_X16, // humidity
    Adafruit_BME280::FILTER_X2,
    Adafruit_BME280::STANDBY_MS_500);
  } else {
    // Oops, something went wrong, this is usually a connection problem,
    #ifdef DISABLE_PMS7003
    Serial.println("BMP280 init fail\n\n");
    #endif
    //Serial.println(std::numeric_limits<unsigned long>::max());
  }

  //set carbon monixide sensor analog pin for input
  pinMode(MQ7_CO_PIN, INPUT);

  // Your WiFi credentials.// Set password to "" for open networks.
  static char * ssid     = "steth";
  static char * password = "ilovecomputers";
  #ifdef DISABLE_PMS7003
  Serial.println(ssid);
  #endif
 

/*
 * CONFIGURATION FOR STATIC IP -
  IPAddress ip (192,168,1,25);
  IPAddress dns (1,1,1,1);
  IPAddress gateway (192,168,1,20);
  IPAddress netmask (255,255,255,0);
  //bool config(IPAddress local_ip, IPAddress gateway, IPAddress subnet, IPAddress dns1 = (uint32_t)0x00000000, IPAddress dns2 = (uint32_t)0x00000000);
  WiFi.config(ip, gateway, netmask, dns); 
  //WiFi.config(ip); 
  */

  //connect to the WiFi
  #ifdef DISABLE_PMS7003
  Serial.println("WiFi.begin(ssid, password)...");
  #endif
  WiFi.begin(ssid, password);

  #ifdef DISABLE_PMS7003
  Serial.println("Starting ...");
  #endif
}

long double mypow(float v, float p)
{
    int sign=1;
    float r;
    if (v<0)
    {
        sign = (-1);
        v *= sign;
    }
    r = pow(v, p);
    return (r*sign);
}

void read_carbon_monoxide()
{
  //analog read 
  int sensorValue = analogRead(MQ7_CO_PIN);
 
  //read R0 resistanse
  static float R0_ok = false;
  static const float R0 = 7000; //used for sensor calibration
  static float sensor_volt = 0;
  static float RS_gas = 0;

  /*
  if (true){
    int R2 = 2000;
    sensor_volt = (float)sensorValue / 4096 * 5.0;
    RS_gas = ((5.0 * R2) / sensor_volt) - R2;
    R0 = RS_gas / 1;
    Serial.print("R0: ");
    Serial.println(R0);
    R0_ok = true;
  }
  */

   sensor_volt = ((float)sensorValue / 4) / ADC_RESOLUTION * 5.0;
   RS_gas = (5.0 - sensor_volt) / sensor_volt;
   float ratio = RS_gas / R0; //Replace R0 with the value found using the sketch above
   float x = 1538.46 * ratio;
   float ppm = mypow(x, -1.709);
   telemetry.setCarbonMonoxide(ppm);
   #ifdef DISABLE_PMS7003
   Serial.println("Carbon Monoxide is: " + (String)telemetry.getCarbonMonoxide() +" ppm");
   #endif

   
}

void read_temperature()
{
  // temperature Data wire is plugged into pin 13 on the Arduino
  static const byte ONE_WIRE_BUS = 4;
  // 9 - 12 precision
  static const byte TEMPERATURE_PRECISION = 12;
  
  // Setup a oneWire instance to communicate with any OneWire devices  
  // (not just Maxim/Dallas temperature ICs) 
  static OneWire oneWire(ONE_WIRE_BUS); 
  // Pass our oneWire reference to Dallas Temperature. 
  static DallasTemperature temperature_sensors(&oneWire);

  #ifdef DISABLE_PMS7003
  Serial.println("Requesting temperatures...");
  #endif
  temperature_sensors.requestTemperatures(); // Send the command to get temperature readings
  #ifdef DISABLE_PMS7003
  Serial.print("Temperature is: ");
  #endif
  telemetry.setTemperatureCelcius(temperature_sensors.getTempCByIndex(0));
  #ifdef DISABLE_PMS7003
  Serial.println(telemetry.getTemperatureCelcius());
  #endif
}

void read_barometric_pressure()
{
  telemetry.setBarometricPressure(bme280.readPressure() / 100);
  #ifdef DISABLE_PMS7003
  Serial.println("Barometric pressure is: " + (String)telemetry.getBarometricPressure() + " hPa");
  #endif
}

void read_humidity()
{
  telemetry.setHumidity(bme280.readHumidity());
  #ifdef DISABLE_PMS7003
  Serial.println("Humidity is: " + (String)telemetry.getHumidity() + " %");
  #endif
}

void connect_to_wifi()
{
  if(WiFi.status() != WL_CONNECTED){
    WiFi.reconnect();
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      #ifdef DISABLE_PMS7003
      Serial.println("Connecting to WiFi..");
      #endif
      FailureWatchdog::reportError();
    }
  }

  #ifdef DISABLE_PMS7003
  Serial.println("Connected to the WiFi network.");
  Serial.print("WiFi IP address: ");
  #endif
  Serial.println(WiFi.localIP());
  FailureWatchdog::reportSuccess();
}

#ifndef DISABLE_PMS7003
void read_pms7003_data()
{
  
  //Serial.println("Waking up PMS7003, wait 30 seconds for stable readings...");
  pms.wakeUp();
  #ifdef DEBUG_FAST_LOOP
  delay(3000);
  #else
  delay(30000);
  #endif

  //Serial.println("Send read requestÂ...");
  pms.requestRead();

  //Serial.println("Wait max. 1 second for read...");
  if (pms.readUntil(data))
  {
    telemetry.setPMS7003_MP_1(data.PM_AE_UG_1_0);
    //Serial.print("PM 1.0 (ug/m3): ");
    //Serial.println(telemetry.getPMS7003_MP_1());
    
    telemetry.setPMS7003_MP_2_5(data.PM_AE_UG_2_5);
    //Serial.print("PM 2.5 (ug/m3): ");
    //Serial.println(telemetry.getPMS7003_MP_2_5());
    
    telemetry.setPMS7003_MP_10(data.PM_AE_UG_10_0);
    //Serial.print("PM 10.0 (ug/m3): ");
    //Serial.println(telemetry.getPMS7003_MP_10());
  }
  else
  {
    //Serial.println("No data.");
    telemetry.setPMS7003_MP_1(-300);
    telemetry.setPMS7003_MP_2_5(-300);
    telemetry.setPMS7003_MP_10(-300);
  }

  //Serial.println("PMS7003 going to sleep.");
  pms.sleep();
}
#endif

void read_mh_z19_co2_data()
{
  static byte request[9] = {0xFF, 0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79};
  static unsigned char response[9];

   Serial2.write(request, 9);
   memset(response, 0, 9);
   Serial2.readBytes(response, 9);
   int i;
   byte crc =0;
   for (i = 1; i < 8; i++) crc+=response[i];
   crc = 255 - crc;
   crc++;

   if (!(response[0] == 0xFF && response[1] == 0x86 && response[8] == crc) ) 
   { 
    //Serial.println("CRC error");
    telemetry.setCarbonDioxide(-300);
   } else {
    unsigned int HLconcentration = (unsigned int) response[2];
    unsigned int LLconcentration = (unsigned int) response[3];
    unsigned int co2 = (256*HLconcentration) + LLconcentration;
    telemetry.setCarbonDioxide(co2);
    
    #ifdef DISABLE_PMS7003
    Serial.print("CO2: ");
    Serial.println(telemetry.getCarbonDioxide());
    #endif
   }
}

void loop() {
  #ifdef DISABLE_PMS7003
  Serial.println("Begin loop");
  #endif

  read_mh_z19_co2_data();

  #ifndef DISABLE_PMS7003
  //reads pms7003 data
  read_pms7003_data();
  #endif

  //reads the temperature from the sensor
  read_temperature();

  //reads the barometric pressure from the BME280 sensor
  read_barometric_pressure();

  //reads the humidity from the BME280 sensor
  read_humidity();
  
  //reads the carbon monoxide value from the MQ-7 sensor
  read_carbon_monoxide();

  //connects to the wifi if not connected.
  //Returns only when a wifi connection is established.
  connect_to_wifi();
  
  //sends all sensor data to the iot server
  telemetry.send_data_to_iot_server();

  //wait 60sec to read next sensor data
  #ifdef DEBUG_FAST_LOOP
  static const unsigned int DEVICE_DELAY_MS = 3000; //3 seconds
  #else
  static const unsigned int DEVICE_DELAY_MS = 60000; //60 seconds
  #endif

  #ifdef DISABLE_PMS7003
  Serial.println("Delay for: " + (String)(DEVICE_DELAY_MS / 1000) + " sec");
  Serial.println("\n");
  #endif
  delay(DEVICE_DELAY_MS);
}
