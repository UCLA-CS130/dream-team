CC = g++
FLAGS = -g -Wall -pthread -std=c++11 -lboost_system
NGINX_DIR = src/nginx-configparser

CLASSES = src/*.cpp

TEST_FLAGS = -std=c++0x -isystem
GTEST_DIR = $(NGINX_DIR)/googletest/googletest
GMOCK_DIR = $(NGINX_DIR)/googletest/googlemock
TEST_ARGS = -pthread -lboost_system
TEST_CLASSES = 	src/connection_manager.cpp \
                src/utils.cpp \
		src/parsed_config.cpp \
		src/basic_server_config.cpp \
		src/request.cpp \
		src/response.cpp \
		src/echo_handler.cpp \
		src/static_handler.cpp \
		src/not_found_handler.cpp \
		src/request_handler.cpp \
		src/status_handler.cpp \
		src/proxy_handler.cpp \
		src/traffic_monitor.cpp

TEST_IO = tests/*.cpp $(TEST_CLASSES) $(NGINX_DIR)/config_parser.cc $(GTEST_DIR)/src/gtest_main.cc build/libgtest.a -o bin/$@

all: webserver

test: unit-test integration-test

unit-test: gunit webserver	
	$(CC) $(TEST_FLAGS) $(GTEST_DIR)/include -isystem $(GMOCK_DIR)/include $(TEST_IO) $(TEST_ARGS)
	./bin/$@

gunit:
	$(CC) $(TEST_FLAGS) $(GTEST_DIR)/include -I${GTEST_DIR} -isystem $(GMOCK_DIR)/include -I${GMOCK_DIR} -c $(GTEST_DIR)/src/gtest-all.cc $(TEST_ARGS)
	$(CC) $(TEST_FLAGS) $(GTEST_DIR)/include -I${GTEST_DIR} -isystem $(GMOCK_DIR)/include -I${GMOCK_DIR} -c $(GMOCK_DIR)/src/gmock-all.cc $(TEST_ARGS)
	ar -rv build/libgtest.a gtest-all.o gmock-all.o
	rm gtest-all.o
	rm gmock-all.o

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
