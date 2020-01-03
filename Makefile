SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)

# Arduino Duemilanove ATmega328P
CFLAGS=-mmcu=atmega328 -Os -std=c11 -Wall

all: micro

micro:
	avr-gcc -DATMEGA $(CFLAGS) -I src/include/ $(SRCS) -o bean

program:
	avrdude -p ATmega328p -P /dev/ttyUSB0 -c arduino -b 57600 -U flash:w:./bean:e
