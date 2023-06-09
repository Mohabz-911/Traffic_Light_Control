#Main application file name
MAIN_APP = main
#Main hex file path in windows format
MAIN_HEX_PATH = $(MAIN_APP).hex

#Other required source files
TIMER = MCAL/TIMER/TIMER
INT = MCAL/INT/INT
DIO = MCAL/DIO/DIO
LED = HAL/LED/LED
APP = APP/App

# Compiler and other Section
CC = avr-gcc
#   JCOPY = avr-objcopy
# avr-objcopy -oihex -R .eeprom blink.elf blink.hex
OBJCOPY = avr-objcopy
AVRDUDE := avrdude

#Options for avr-gcc
CFLAGS = -g -Os -o

#Linking options for avr-gcc

LFLAGS = -Os -mmcu=atmega32 -o

#Options for HEX file generation
HFLAGS =  -O ihex -R .eeprom
#Options for avrdude to burn the hex file
#MMCU model here according to avrdude options
DUDEFLAGS = -c
DUDEFLAGS += usbasp 
DUDEFLAGS += -p
DUDEFLAGS += m32  
DUDEFLAGS += -P 
DUDEFLAGS += COM3 # add port of the isp programmer here
DUDEFLAGS += -b 
DUDEFLAGS += 19200 
DUDEFLAGS += -U flash:w:$(MAIN_HEX_PATH):i

# Sources files needed for building the application 
SRC = $(MAIN_APP).c
SRC += $(TIMER).c
SRC += $(INT).c
SRC += $(DIO).c
SRC += $(LED).c
SRC += $(APP).c



# The headers files needed for building the application
INCLUDE = -I. 

# commands Section

Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)
Build : $(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(MAIN_APP).hex
	
$(MAIN_APP).elf: $(MAIN_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
$(MAIN_APP).o:$(SRC)
	$(CC) $^ $(INCLUDE) $(CFLAGS) $@
