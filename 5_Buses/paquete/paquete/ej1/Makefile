# ************************************************** 
#   Taller de Buses - Organizacion del computador I
#      (por compatibilidad se omiten tildes)
# **************************************************

all: reloj KITT print

CC=g++
# CCFLAGS = -Wall -g
CCFLAGS = -g

reloj: reloj.o bus.o
	$(CC) $^  -o $@

KITT: KITT.o bus.o
	$(CC) $^  -o $@

print: print.o bus.o
	$(CC) $^  -o $@

bus.o: bus.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

reloj.o: reloj.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@

KITT.o: KITT.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@

print.o: print.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

clean:
	rm -rf *.o *.pyc
	rm -rf reloj KITT print
	rm -rf bus/*
