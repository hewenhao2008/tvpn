/*
 *  This file is part of TVPN.
 *
 *  vnddmgr is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  TVPN is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with TVPN; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  US
 *
 *  Author:	Antonino Calderone, <acaldmail@gmail.com>
 *
 */


/* -------------------------------------------------------------------------- */

#ifndef __MACADDR_H__
#define __MACADDR_H__


/* -------------------------------------------------------------------------- */

#include <string>
#include <stdio.h>
#include <memory.h>
#include <array>


/* -------------------------------------------------------------------------- */

class mac_addr_t 
{
   public:
      enum { MAC_LEN = 6 };

   private:
      char _macaddr[MAC_LEN] = {0};

      char _getdigitval(const char c) const noexcept
      {
         return c>='0' && c<='9' ? c - '0' : 
            c>='A' && c<='F' ? c - 'A' + 0xA: 
            c>='a' && c<='f' ? c - 'a' + 0xA: 0;
      }

      char _getbs2(const char* str) const noexcept
      {
         return (_getdigitval(str[0]) << 4) | _getdigitval(str[1]);
      }

      std::string _getpstr() const noexcept;

   public:
      mac_addr_t() = default;

      mac_addr_t(const char mac[MAC_LEN]) noexcept
      {
         memcpy(&_macaddr[0], &mac[0], MAC_LEN);
      }

      mac_addr_t(const mac_addr_t& mac_obj) noexcept
      {
         memcpy(&_macaddr[0], &mac_obj._macaddr[0], MAC_LEN);
      }

      void assign_to(char dst_mac[MAC_LEN]) const noexcept
      {
         memcpy(&dst_mac[0], &_macaddr[0], MAC_LEN);
      }

      bool operator==(const mac_addr_t& mac) const noexcept
      {
         return memcmp(&_macaddr[0], &mac._macaddr[0], MAC_LEN) == 0;
      }

      explicit operator std::string() const noexcept
      {
         return _getpstr();
      }

      mac_addr_t(const std::string& mac) noexcept;
      mac_addr_t& operator=(const mac_addr_t& mac_obj) noexcept;
      char operator[](size_t i) const noexcept;
      char& operator[](size_t i) noexcept;
};


// -----------------------------------------------------------------------------

#endif  

