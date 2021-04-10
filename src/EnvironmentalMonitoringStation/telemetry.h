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

#include "WString.h"

class Telemetry
{
  public:
    Telemetry();
    void setFirmwareVersion(const String firmware_version);
    void setTemperatureCelcius(float temperature_celcius);
    void setPhotoresistor(float photoresistor);
    void setBarometricPressure(float barometricPressure);
    void setPMS7003_MP_1(float mp_1);
    void setPMS7003_MP_2_5(float mp_2_5);
    void setPMS7003_MP_10(float mp_10);
    void setHumidity(float humidity);
    void setCarbonMonoxide(float carbonMonoxide);
    void setNitrogenDioxide(float nitrogenDioxide);
    void setCarbonDioxide(float carbonDioxide);
    void setHydrogen(float hydrogen);
    void setTelemetryUrl(String url);
    void setTelemetryPort(String port);
    void setTelemetryToken(String token);
    
    String getTelemetryUrl();
    String getTelemetryPort();
    String getTelemetryToken();
    String getFirmwareVersion();
    float getTemperatureCelcius();
    float getPhotoresistor();
    float getBarometricPressure();
    float getPMS7003_MP_1();
    float getPMS7003_MP_2_5();
    float getPMS7003_MP_10();
    float getHumidity();
    float getCarbonMonoxide();
    float getNitrogenDioxide();
    float getCarbonDioxide();
    float getHydrogen();
    String getTelemetryJson();
    
    void send_data_to_iot_server();
    void send_data_to_iot_server2();

  private:
    String m_firmware_version = "";
    float m_temperature_celcius = -300;
    float m_barometricPressure = -300;
    float m_humidity = -300;
    float m_carbonMonoxide = -300;
    float m_carbonDioxide = -300;
    float m_nitrogenDioxide = -300;
    float m_PMS7003_MP_1 = -300;
    float m_PMS7003_MP_2_5 = -300;
    float m_PMS7003_MP_10 = -300;
    float m_hydrogen = -300;
    String m_telemetry_url;
    String m_telemetry_port;
    String m_telemetry_token;
};
