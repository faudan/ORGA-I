/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#ifndef BUS_H
#define BUS_H

#define BUS "bus/"
#define CLK  string(BUS) + "clk"

#define A0   string(BUS) + "a0"
#define A1   string(BUS) + "a1"
#define A2   string(BUS) + "a2"
#define A3   string(BUS) + "a3"

#define D0   string(BUS) + "d0"
#define D1   string(BUS) + "d1"
#define D2   string(BUS) + "d2"
#define D3   string(BUS) + "d3"

#define RW   string(BUS) + "rw"

#define CLK  string(BUS) + "clk"
#define REQ1  string(BUS) + "req1"
#define ACK1  string(BUS) + "ack1"
#define REQ2  string(BUS) + "req2"
#define ACK2  string(BUS) + "ack2"
#define REQ3  string(BUS) + "req3"
#define ACK3  string(BUS) + "ack3"

#define DEV0  string(BUS) + "dev0"
#define DEV1  string(BUS) + "dev1"

#include <fstream>
#include <string>
using namespace std;

int read(string linea);
void write(string linea, int x);

#endif