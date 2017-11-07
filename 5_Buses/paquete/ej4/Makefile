# ************************************************** 
#   Taller de Buses - Organizacion del computador I
#      (por compatibilidad se omiten tildes)
# **************************************************

all: reloj dispositivo1 dispositivo2 dispositivo3 print arbitro

CC=g++
# CCFLAGS = -Wall -g
CCFLAGS = -g


reloj: reloj.o bus.o
	$(CC) $^  -o $@

dispositivo1: dispositivo1.o bus.o
	$(CC) $^  -o $@

dispositivo2: dispositivo2.o bus.o
	$(CC) $^  -o $@

dispositivo3: dispositivo3.o bus.o
	$(CC) $^  -o $@


print: print.o bus.o
	$(CC) $^  -o $@

arbitro: arbitro.o bus.o
	$(CC) $^  -o $@

bus.o: bus.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

reloj.o: reloj.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@

dispositivo1.o: dispositivo.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@ -DDISPOSITIVO=1

dispositivo2.o: dispositivo.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@ -DDISPOSITIVO=2

dispositivo3.o: dispositivo.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@ -DDISPOSITIVO=3

print.o: print.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

arbitro.o: arbitro.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@


clean:
	rm -rf *.o
	rm -rf reloj print arbitro dispositivo1 dispositivo2 dispositivo3
	rm -rf bus/*
