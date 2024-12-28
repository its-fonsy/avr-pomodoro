# Pomodoro timer for Atmega328p

This is a personal project that uses the Atmega328p an oled display and a
button to make a pomodoro timer.

It is developed using Arduino UNO board, but not with Arduino IDE. It doesn't
use any external library, only the AVR header files.

Everything is implemented from scratch just for learning purpose.

## Building and flashing

Prerequisite: the _AVR-binutils_ is used to build the code, meanwhile _avrdude_
to flash the microcontroller. Be sure to have both installed on the system.

Once the prerequisite software has been installed you can clone the repo and
compile it

    git clone git@github.com:its-fonsy/avr-pomodoro.git
    cd avr-pomodoro
    make all

then you can flash the microcontroller

    make flash

The flashing configuration is inside the `Makefile`. If you use a different
programmer (or something else) change the `Makefile` accordingly to your setup.
