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

class uptime
{
  public:
    uptime();

    static void          calculate_uptime();

    static unsigned long get_milliseconds();
    static unsigned long get_seconds();
    static unsigned long get_minutes();
    static unsigned long get_hours();
    static unsigned long get_days();
      
  private:
    static unsigned long m_milliseconds;
    static unsigned long m_seconds;
    static unsigned long m_minutes;
    static unsigned long m_hours;
    static unsigned long m_days;

    static unsigned long m_mod_milliseconds;
    static unsigned long m_mod_seconds;
    static unsigned long m_mod_minutes;
    static unsigned long m_mod_hours;
    
    static unsigned long m_last_milliseconds;  
    static unsigned long m_remaining_seconds;
    static unsigned long m_remaining_minutes;
    static unsigned long m_remaining_hours;
    static unsigned long m_remaining_days;
};
