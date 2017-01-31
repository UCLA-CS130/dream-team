CC=g++
OPTIMIZE=-O2
FLAGS=-g -Wall -pthread -std=c++11 -lboost_system
CLASSES=src/*.cpp src/nginx-configparser/config_parser.cc

all: webserver

test: webserver
	python integration_tests.py

webserver: $(CLASSES)
	$(CC) -o bin/$@ $^ $(FLAGS)	

clean: 
	rm -rf src/*.o src/*~ src/*.gch src/*.swp src/*.dSYM *.tar.gz *\# bin/webserver
