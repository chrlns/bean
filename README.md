[![Build Status](https://travis-ci.org/chrlns/bean.svg?branch=master)](https://travis-ci.org/chrlns/bean)

Bean JVM
=========

Bean is my effort to create a Java Virtual Machine. 

Some statements:
 - Made for embedded devices
 - No full-featured JVM
 - No extensive security features
 - No HW-threads (e.g. POSIX)

The target platform is my ancient [Arduino Duemilanove](https://www.arduino.cc/en/Main/arduinoBoardDuemilanove) board with an Atmel ATmega320p (16 MHz, 32 KiB Flash, 2 KiB RAM). Not that much hardware for a Java VM ;-)

Usage
-----

To compile and flash Bean you need avr-gcc and avrdude:

    $ make micro
    $ make program

Currently you cannot do anything useful with Bean but I will try to make a simple "hello world" pin 13 blink java class runable on the Bean VM.
