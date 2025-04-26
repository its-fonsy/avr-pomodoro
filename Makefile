# MCU
MCU   := atmega328p
F_CPU := 16000000UL  
BAUD  := 115200
PORT  := /dev/ttyACM0

LIBDIR := /usr/avr/include

# Programmer
PROGRAMMER_TYPE := arduino
PROGRAMMER_ARGS := -P $(PORT) -b $(BAUD) 

# Programs
CC		:= avr-gcc
OBJCOPY := avr-objcopy
OBJDUMP := avr-objdump
AVRSIZE := avr-size
AVRDUDE := avrdude

TARGET		:= pomo

# Project folder
SRC_DIR		:= src
BUILD_DIR	:= build

SRCS := $(wildcard $(SRC_DIR)/*.c) $(SRC_DIR)/font.c
INCS := $(wildcard $(SRC_DIR)/*.h)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# C Flags
CPPFLAGS	:= -DF_CPU=$(F_CPU) -DBAUD=$(BAUD) -I$(LIBDIR)
CFLAGS  	:= -Os -g -std=gnu99 -Wall
CFLAGS 		+= -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums 
CFLAGS 		+= -ffunction-sections -fdata-sections 

# LD Flags
LDFLAGS		:= -Wl,-Map,$(BUILD_DIR)/$(TARGET).map 
LDFLAGS		+= -Wl,--gc-sections 
TARGET_ARCH	:= -mmcu=$(MCU)

# Font source files
NUMBER_FONT_SRC			:= scripts/font/7-segment/number_20x32.c
LETTER_FONT_SRC			:= scripts/font/sans-serif/letters_8x16.c
GENERATION_FONT_SCRIPT	:= scripts/font/gen_font.py

.PHONY: all size clean flash font debug

all: $(BUILD_DIR)/$(TARGET).hex 

# Generate Objects files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INCS) Makefile $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c -o $@ $<

# Generate ELF
$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $(TARGET_ARCH) $^ $(LDLIBS) -o $@

# Generate HEX
$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	 $(OBJCOPY) -j .text -j .data -O ihex $< $@

# Create build folder
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Generate font.c
$(SRC_DIR)/font.c: $(NUMBER_FONT_SRC) $(LETTER_FONT_SRC) $(GENERATION_FONT_SCRIPT)
	$(GENERATION_FONT_SCRIPT) -n $(NUMBER_FONT_SRC) -l $(LETTER_FONT_SRC) -o $@

debug:
	@echo
	@echo "Source files:"  $(SRCS)
	@echo "Obkect files:"  $(OBJS)
	@echo "         MCU:"  $(MCU)
	@echo "       F_CPU:"  $(F_CPU)
	@echo "        BAUD:"  $(BAUD)
	@echo	

size: $(BUILD_DIR)/$(TARGET).elf
	$(AVRSIZE) -C --mcu=$(MCU) $<

clean:
	rm -rf $(BUILD_DIR) $(SRC_DIR)/font.c

flash: $(BUILD_DIR)/$(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER_TYPE) -p $(MCU) $(PROGRAMMER_ARGS) -U flash:w:$<

font: $(SRC_DIR)/font.c
