# Copyright (c) 2013 -2015 Andy Little 
#
# With Grateful Acknowledgements to the prior work of:
#   Sami Korhonen(Openpilot.org)
#   taulabs ( taulabs.com) 
#   brainFPV ( brainfpv.com)
#   Thomas Oldbury (super-osd.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>

#--------------------------------------------

LINKER_SCRIPT = stm32f4.ld

QUANTRACKER_ROOT_DIR = ../../../

TELEMETRY_DIRECTION = QUAN_OSD_TELEM_NONE

include $(QUANTRACKER_ROOT_DIR)include/quantracker/build/osd.mk

INCLUDES += $(MAVLINK_INCLUDE_PATH)

OBJDIR = obj/
BINDIR = bin/

static_library_files = \
     $(TARGET_LIB_NAME_PREFIX)_system.a \
     $(TARGET_LIB_NAME_PREFIX)_osd.a \
     $(TARGET_LIB_NAME_PREFIX)_graphics_api.a \
   flash_variables.a

# in the board directory
board_objects = main.o setup.o serial_port.o fsk_output.o \
fsk_task.o frsky_task.o frsky_zapp1.o mavlink_task.o settings.o \
heartbeat_task.o mode_check.o board_graphics_api.o  bitmaps.o fonts.o \
flash_vars.o

obj_board_objects = $(patsubst %,$(OBJDIR)%,$(board_objects))

# in the common directory
common_objects = on_draw.o draw_altitude.o draw_artificial_horizon.o \
draw_compass.o draw_home.o draw_gps_state.o draw_batteries.o symbology.o \
flash.o aircraft.o

obj_common_objects = $(patsubst %,$(OBJDIR)%,$(common_objects))

objects = $(obj_board_objects) $(obj_common_objects) 

#----------------------------

all: test

test: $(BINDIR)main.elf
	@ echo "...copying"
	$(CP) $(CPFLAGS) $(BINDIR)main.elf $(BINDIR)main.bin
	$(OD) $(ODFLAGS) $(BINDIR)main.elf > $(BINDIR)main.lst
	$(SIZ) -A $(BINDIR)main.elf

$(BINDIR)main.elf: $(objects) $(static_libraries) 
	@ echo "..linking"
	$(LD) $(LDFLAGS) -Wl,-Map=$(BINDIR)output.map -o $(BINDIR)main.elf  $(objects) \
   -Wl,--undefined=_sbrk $(static_libraries) 

$(obj_board_objects): $(OBJDIR)%.o : %.cpp
	$(CC) $(CFLAGS) $< -o $@

$(obj_common_objects) : $(OBJDIR)%.o : ../common/%.cpp
	$(CC) $(CFLAGS) -DQUAN_OSD_TARGET_BOARD $< -o $@

$(static_libraries) :
	$(MAKE) -C ../../../air/osd -f all_osd_libs.mk

#-----------------------------------------

upload : test
	st-flash write $(BINDIR)main.bin 0x8000000

# try add -b115200 to increase upload rate
upload_sp : test
	$(STM32FLASH) -f -v -w $(BINDIR)main.bin /dev/ttyUSB0
#----------------------------------------

clean:
	-rm -rf $(OBJDIR)*.o $(BINDIR)*.elf $(BINDIR)*.bin $(BINDIR)*.lst
