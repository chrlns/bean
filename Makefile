SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)

# Arduino Duemilanove ATmega168
CFLAGS=-mmcu=atmega168 -Os

micro:
	avr-gcc -DATMEGA $(CFLAGS) -I src/include/ $(SRCS) -o bean
