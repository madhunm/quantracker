/*
 Copyright (c) 2012 - 2013 Andy Little 

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>
*/
#include "settings.hpp"

// call functions to output data in sequence
// called at 1 call every 1/50th sec
namespace zapp1{
   void frsky_send_message();
}

namespace zapp2{
    void frsky_send_message(){}
}

void FrSky_send_message()
{
   switch (settings::frsky_protocol){
      case settings::protocol_t::zapp1:
         zapp1::frsky_send_message();
         break;
      case settings::protocol_t::zapp2:
         zapp2::frsky_send_message();
         break;
      default:
         break;
   }
}
