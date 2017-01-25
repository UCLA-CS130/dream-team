CC=g++
OPTIMIZE=-O2
FLAGS=-o -g -Wall -pthread -std=++11
CLASSES=*.cpp

server: $CLASSES
	$CC -o $@ $^ $FLAGS $@.cpp	

clean: 
	rm -rf *.o *~ *.gch *.swp *.dSYM *.tar.gz *\#
