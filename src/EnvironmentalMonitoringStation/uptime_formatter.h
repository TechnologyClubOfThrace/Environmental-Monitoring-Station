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

#include "WString.h"

class uptime_formatter
{
  public:
    uptime_formatter();
    
    static String get_uptime();
    static String get_uptime_with_millis();
};