﻿/* ***********************************************************************
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

#include "uptime_formatter.h"
#include "uptime.h"

uptime_formatter::uptime_formatter()
{
}

String uptime_formatter::get_uptime()
{
  uptime::calculate_uptime();
  
  return  (String)(uptime::get_days()   ) + " days, "    +
          (String)(uptime::get_hours()  ) + " hours, "   +
          (String)(uptime::get_minutes()) + " minutes, " +
          (String)(uptime::get_seconds()) + " seconds";
}

String uptime_formatter::get_uptime_with_millis()
{
 return  uptime_formatter::get_uptime()        + ", " +
          (String)(uptime::get_milliseconds()) + " milliseconds";
}