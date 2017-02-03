
/*
 Copyright (c) 2013 -2015 Andy Little 

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

#include <stm32f4xx.h>
#include <misc.h>
#include <quan/time.hpp>
#include <quan/frequency.hpp>
#include <quan/stm32/get_module_bus_frequency.hpp>
#include <quan/stm32/usart/irq_handler.hpp>
#include <quan/stm32/gpio.hpp>

#include "resources.hpp"
#include "../azimuth/servo.hpp"

void osd_setup();

namespace {

void enable_heartbeat_led()
{
   quan::stm32::module_enable< heartbeat_led_pin::port_type>();
      quan::stm32::apply<
         heartbeat_led_pin
         , quan::stm32::gpio::mode::output
         , quan::stm32::gpio::otype::push_pull
         , quan::stm32::gpio::pupd::none
         , quan::stm32::gpio::ospeed::slow
         , quan::stm32::gpio::ostate::low
      >();
}
}


extern "C" void setup()
{
  osd_setup();
  enable_heartbeat_led();
  gcs_serial::setup<9600>(local_interrupt_priority::gcs_serial_port);
  gcs_serial::enable();

  azimuth_servo::setup();
 
}