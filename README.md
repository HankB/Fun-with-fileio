# Fun-with-fileio

Fun with file I/O, of course.

## Motivation

TL;DR - Need some C code to read three values from a disk file and write three new values back.

Shaggy dog version - A program that runs on a Raspberry Pi (Linux environment) reads stuff from a BME280 sensor and publishes using MQTT. Occasionally the values are wonky. Some times wildly different from what they should be. The program runs 1/minute and the values (temperature, humidity and pressure) won't change too much from one run to another. One strategy to deal with this is to compare valies from a minute previous and if they differ too much, discard the readings and bail. It will be easier to develop and test outside the context of the original application.

## Plan

Write `C` functions to

* Open a file if it exists and read and transform three space separated values to floats.
* Write three new values back to the file and close it.
