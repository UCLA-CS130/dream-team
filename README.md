# Dream Team Web Server

This is Dream Team's implementation of the Web Server for CS 130.

## Usage

The webserver executable can be invoked with

```
./bin/webserver <Nginx_Config_File>
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

## Class APIs

Apart from the classes mentioned in the specification mentioned earlier, there
are various other classes that are used in the web server. The APIs for these
classes are mentioned below.

### BasicServerConfig

This object is a class representation of the input config file. It is generated
when the server is initially started. Important methods include:

```bool Init``` - Initializes the BasicServerConfig object by internally
parsing for the port number and creating RequestHandler objects based on
the information specified in the config file. Returns true on success, false
on any failure to parse the config file.

```unsigned GetPortNumber``` - Returns the port number specified in the
config file.

```RequestHandler* GetRequestHandlerFromUri``` - Returns a pointer to the
RequestHandler object created from the config file, given a valid URI prefix
specified in the config file. If the uri is not found, returns a pointer to
the default NotFoundHandler object.