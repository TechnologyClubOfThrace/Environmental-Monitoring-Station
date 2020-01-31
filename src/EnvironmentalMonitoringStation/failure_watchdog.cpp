/* ***********************************************************************
 * Environmental Monitoring Station
 * (C) 2019 by Yiannis Bourkelis (https://github.com/YiannisBourkelis/)
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
 
#include "failure_watchdog.h"
#include "ESP.h"

long FailureWatchdog::errorsCounter = 0;
long FailureWatchdog::errorsRestartThreshold = 10;

FailureWatchdog::FailureWatchdog()
{
  
}

void FailureWatchdog::reportError()
{
  FailureWatchdog::errorsCounter++;
  Serial.print("FailureWatchdog::reportError _errorCounter:");
  Serial.println(FailureWatchdog::errorsCounter);

  if(FailureWatchdog::errorsCounter >= FailureWatchdog::errorsRestartThreshold){
    Serial.println("Watchdog error threshold reached. Restarting ESP32...");
    ESP.restart();
  } 
}

void FailureWatchdog::reportSuccess()
{
  FailureWatchdog::errorsCounter = 0;
}

void FailureWatchdog::setErrorsRestartThreshold(long maxErrors)
{
  FailureWatchdog::errorsRestartThreshold = maxErrors;
}
