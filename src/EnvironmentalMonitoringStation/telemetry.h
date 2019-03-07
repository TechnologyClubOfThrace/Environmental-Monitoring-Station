/* ***********************************************************************
 * Environmental Monitoring Station
 * (C) 2019 by Yiannis Bourkelis (hello@andama.org)
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
    void setTemperatureCelcius(float temperature_celcius);
    void setPhotoresistor(float photoresistor);
    void setBarometricPressure(float barometricPressure);
    
    float getTemperatureCelcius();
    float getPhotoresistor();
    float getBarometricPressure();
    String getTelemetryJson();
    
    void send_data_to_iot_server();

  private:
    float m_temperature_celcius = -300;
    float m_photoresistor = -300;
    float m_barometricPressure = -300;
};
