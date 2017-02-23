# Dream Team Web Server

This is Dream Team's implementation of the Web Server for CS 130.

## Usage

The webserver executable can be invoked with

```
./webserver <Nginx_Config_File>
```

where Nginx_Config_File is a configuration file as per the example in the
specification provided here: https://github.com/UCLA-CS130/webserver-api

## Source Code Organization

The code is organized into the two directories specified below.

src - Contains all classes and the main program for the web server

tests - Contains all unit tests and integration tests for the web server.

## Building The Web Server

Run ```make``` to compile the web server code. Following this, the web server
can be run as shown in the "Usage" section.

Other make targets of note:

```make unit-test``` - Runs all unit-tests, outputting the results of the tests
(using Gtest).

```make integration-test``` - Runs all integration tests, outputting success
or failure.

```make test``` - Runs both unit and integration
tests.

```make unit-test-coverage``` - Uses gcov to output unit-test coverage.

```make clean``` - Cleans up binary files generated as a result of other make
targets.