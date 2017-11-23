# ************************************************** 
#   Taller de Buses - Organizacion del computador I
#      (por compatibilidad se omiten tildes)
# **************************************************

all: reloj memoria cpu print print_asinc

CC=g++
# CCFLAGS = -Wall -g
CCFLAGS = -g


reloj: reloj.o bus.o
	$(CC) $^  -o $@

cpu: cpu.o bus.o
	$(CC) $^  -o $@

memoria: memoria.o bus.o
	$(CC) $^  -o $@

print: print.o bus.o
	$(CC) $^  -o $@

print_asinc: print_asinc.o bus.o
	$(CC) $^  -o $@

bus.o: bus.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

reloj.o: reloj.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@

cpu.o: cpu.cpp 
	$(CC) $(CCFLAGS) -c $<  -o $@

memoria.o: memoria.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

print.o: print.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

print_asinc.o: print_asinc.cpp
	$(CC) $(CCFLAGS) -c $<  -o $@

clean:
	rm -rf *.o *.pyc
	rm -rf reloj memoria cpu print print_asinc
	rm -rf bus/*
