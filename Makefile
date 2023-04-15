# Compiler settings
CC = avr-gcc
CFLAGS = -Wall -I include -mmcu=atmega328p -Os -DF_CPU=8000000UL
LDFLAGS = -Wall -mmcu=atmega328p

# Source files
SRC = src/main.c include/7segments.c include/bit.c

# Object files
OBJ = $(SRC:.c=.o)

# Target executable
TARGET = build/main

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

$(TARGET).elf: $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c
	if [ ! -d "build" ]; then mkdir build; fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET).elf