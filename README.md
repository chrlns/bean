[![Build Status](https://travis-ci.org/cli/bean.svg?branch=master)](https://travis-ci.org/cli/bean)

Bean JVM
=========

Bean is my effort to create a Java Virtual Machine. 

Some statements:
 - Made for embedded devices
 - No full-featured JVM
 - No extensive security features
 - No HW-threads (e.g. POSIX)

Usage
-----

To compile Bean you need Maven, a JDK and a GCC-compatible C compiler.

    $ mvn clean compile
 
To start Bean with the "Hello World" sample programm:

    $ target/nar/.../bin/bean target/classes/Hello
