CC = g++
FLAGS = -g -Wall -pthread -std=c++11 -lboost_system
NGINX_DIR = src/nginx-configparser

CLASSES = src/*.cpp

TEST_FLAGS = -std=c++0x -isystem
GTEST_DIR = $(NGINX_DIR)/googletest/googletest
TEST_ARGS = -pthread -lboost_system
TEST_CLASSES = 	src/http_header.cpp \
		src/http_message.cpp \
		src/http_response.cpp \
		src/status_line.cpp \
		src/http_request.cpp \
		src/http_request_line.cpp \
		src/connection_manager.cpp

TEST_IO = tests/*.cpp $(TEST_CLASSES) $(GTEST_DIR)/src/gtest_main.cc build/libgtest.a -o bin/$@

all: webserver

test: unit-test integration-test

unit-test: gunit webserver	
	$(CC) $(TEST_FLAGS) $(GTEST_DIR)/include $(TEST_IO) $(TEST_ARGS)
	./bin/$@

gunit:
	$(CC) $(TEST_FLAGS) $(GTEST_DIR)/include -I${GTEST_DIR} -c $(GTEST_DIR)/src/gtest-all.cc $(TEST_ARGS)
	ar -rv build/libgtest.a gtest-all.o
	rm gtest-all.o

unit-test-coverage: TEST_ARGS += -fprofile-arcs -ftest-coverage
unit-test-coverage: unit-test
	gcov -o . -r $(TEST_CLASSES)

integration-test: webserver
	python tests/integration_tests.py

webserver: $(CLASSES) $(NGINX_DIR)/config_parser.cc
	$(CC) -o bin/$@ $^ $(FLAGS)	

clean: 
	rm -rf *.o *.a *.gcov *.gcda *.gcno
	rm -rf build/*
	rm -rf bin/*
