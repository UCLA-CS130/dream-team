CC=g++
OPTIMIZE=-O2
FLAGS=-g -Wall -pthread -std=c++11 -lboost_system
CLASSES=*.cpp nginx-configparser/config_parser.cc

all: webserver

webserver: $(CLASSES)
	$(CC) -o $@ $^ $(FLAGS)	

clean: 
	rm -rf *.o *~ *.gch *.swp *.dSYM *.tar.gz *\# webserver
