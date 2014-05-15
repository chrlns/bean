[![Build Status](https://travis-ci.org/cli/bean.svg?branch=master)](https://travis-ci.org/cli/bean)

Bean JVM
=========

Bean is my effort to create a Java Virtual Machine. 

Some statements:
 - Made for embedded devices
 - No full-featured JVM
 - No extensive security features
 - No HW-threads (e.g. POSIX)

The target platform is the [Arduino Zero](http://arduino.cc/en/Main/ArduinoBoardZero) board with an Atmel ATSAMD21G (48 MHz, 32 KBytes RAM). At least as soon as I get one...

Usage
-----

To compile Bean you need Maven, a JDK and a GCC-compatible C compiler.

    $ mvn clean compile
 
To start Bean with the "Hello World" sample programm:

    $ target/nar/.../bin/bean target/classes/Hello
