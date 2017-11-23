/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#ifndef BUS_H
#define BUS_H

#define BUS "bus/"
#define CLK  string(BUS) + "clk"
#define D0   string(BUS) + "d0"
#define D1   string(BUS) + "d1"
#define D2   string(BUS) + "d2"
#define D3   string(BUS) + "d3"
#define REQ  string(BUS) + "req"
#define RW   string(BUS) + "rw"
#define ACK  string(BUS) + "ack"

#include <fstream>
#include <string>
using namespace std;

int read(string linea);
void write(string linea, int x);

#endif