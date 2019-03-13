/* ***********************************************************************
 * Uptime library for Arduino devices
 * (C) 2019 by Yiannis Bourkelis (https://github.com/YiannisBourkelis/)
 *
 * This file is part of Uptime library for Arduino devices
 *
 * Uptime library for Arduino devices is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Uptime library for Arduino devices is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Uptime library for Arduino devices.  If not, see <http://www.gnu.org/licenses/>.
 * ***********************************************************************/

#include <Arduino.h> //for millis()
#include "uptime.h"

unsigned long uptime::m_milliseconds;
unsigned long uptime::m_seconds;
unsigned long uptime::m_minutes;
unsigned long uptime::m_hours;
unsigned long uptime::m_days;

unsigned long uptime::m_last_milliseconds = 0;   
unsigned long uptime::m_remaining_seconds = 0;
unsigned long uptime::m_remaining_minutes = 0;
unsigned long uptime::m_remaining_hours = 0;
unsigned long uptime::m_remaining_days = 0;

unsigned long uptime::m_mod_milliseconds;
unsigned long uptime::m_mod_seconds;
unsigned long uptime::m_mod_minutes;
unsigned long uptime::m_mod_hours;
    
uptime::uptime()
{
}

unsigned long uptime::get_milliseconds()
{
  return uptime::m_mod_milliseconds;
}
unsigned long uptime::get_seconds()
{
  return uptime::m_mod_seconds;
}
unsigned long uptime::get_minutes()
{
  return uptime::m_mod_minutes;
}
unsigned long uptime::get_hours()
{
  return uptime::m_mod_hours;
}
unsigned long uptime::get_days()
{
  return uptime::m_days;
}

void uptime::calculate_uptime()
{
  uptime::m_milliseconds = millis();
  
  if (uptime::m_last_milliseconds > uptime::m_milliseconds){
    //uptime::get_milliseconds_from_boot() overflow
    uptime::m_remaining_seconds      += uptime::m_seconds;
    uptime::m_remaining_minutes      += uptime::m_minutes;
    uptime::m_remaining_hours        += uptime::m_hours;
    uptime::m_remaining_days         += uptime::m_days;  
  }
  
  uptime::m_last_milliseconds = uptime::m_milliseconds;
  
  uptime::m_seconds      = (uptime::m_milliseconds / 1000) + uptime::m_remaining_seconds;
  uptime::m_minutes      = (uptime::m_seconds      / 60)   + uptime::m_remaining_minutes;
  uptime::m_hours        = (uptime::m_minutes      / 60)   + uptime::m_remaining_hours;
  uptime::m_days         = (uptime::m_hours        / 24)   + uptime::m_remaining_days;

  uptime::m_mod_milliseconds = uptime::m_milliseconds % 1000;
  uptime::m_mod_seconds      = uptime::m_seconds      % 60;
  uptime::m_mod_minutes      = uptime::m_minutes      % 60;
  uptime::m_mod_hours        = uptime::m_hours        % 24;
}
