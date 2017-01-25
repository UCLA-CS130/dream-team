CC=g++
OPTIMIZE=-O2
FLAGS=-g -Wall -pthread -std=c++11 -lboost_system
CLASSES=*.cpp

all: webserver

webserver: $(CLASSES)
	$(CC) -o $@ $^ $(FLAGS)	

clean: 
	rm -rf *.o *~ *.gch *.swp *.dSYM *.tar.gz *\#
