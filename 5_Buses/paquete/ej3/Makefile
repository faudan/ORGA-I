# ************************************************** 
#   Taller de Buses - Organizacion del computador I
#      (por compatibilidad se omiten tildes)
# **************************************************

all: reloj memoria cpu print

CC=g++
# CCFLAGS = -Wall -g
CCFLAGS = -g


reloj: reloj.o bus.o
	$(CC) $^  -o $@

memoria: memoria.o bus.o
	$(CC) $^  -o $@

cpu: cpu.o bus.o
	$(CC) $^  -o $@

print: print.o bus.o
	$(CC) $^  -o $@

bus.o: bus.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

reloj.o: reloj.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@

memoria.o: memoria.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@

cpu.o: cpu.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

print.o: print.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

clean:
	rm -rf *.o *.pyc
	rm -rf reloj cpu memoria print
	rm -rf bus/*
