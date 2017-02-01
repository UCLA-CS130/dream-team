CC = g++
OPTIMIZE = -O2
FLAGS = -g -Wall -pthread -std=c++11 -lboost_system
NGINX_DIR = src/nginx-configparser

CLASSES = src/*.cpp

TEST_FLAGS = -std=c++0x -isystem
GTEST_DIR = $(NGINX_DIR)/googletest/googletest
TEST_CLASSES = 	src/http_header.cpp \
		src/http_message.cpp	

all: webserver

test: unit-test integration-test

unit-test: webserver
	$(CC) $(TEST_FLAGS) $(GTEST_DIR)/include -I${GTEST_DIR} -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv build/libgtest.a gtest-all.o
	rm gtest-all.o
	$(CC) $(TEST_FLAGS) $(GTEST_DIR)/include -pthread tests/*.cpp $(TEST_CLASSES) $(GTEST_DIR)/src/gtest_main.cc build/libgtest.a -o bin/$@

integration-test: webserver
	python integration_tests.py

webserver: $(CLASSES) $(NGINX_DIR)/config_parser.cc
	$(CC) -o bin/$@ $^ $(FLAGS)	

clean: 
	rm -rf *.o *.a bin/webserver
	rm -rf ./build/*
