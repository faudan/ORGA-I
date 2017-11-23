/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "bus.h"
using namespace std;

int memoria[] = {1,0,0,0,
                 1,0,0,1,
                 1,0,1,1,
                 1,0,1,0,
                 1,1,1,0,
                 1,1,1,1,
                 1,1,0,1,
                 1,1,0,0,
                 0,1,0,0,
                 0,1,0,1,
                 0,1,1,1,
                 0,1,1,0,
                 0,0,1,0,
                 0,0,1,1,
                 0,0,0,1,
                 0,0,0,0};

int get_memoria(int direccion,int bit) {
    return memoria[direccion*4+bit];
}

int main(int argc, char *argv[]) {
  
	int clk = read(CLK);
	int req = 0;
	int ack = 0;
	int d0 = 0;
	int d1 = 0;
	int d2 = 0;
	int d3 = 0;
	int x0 = 0;
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	bool ya_tengo_direccion=false;
	
	while( clk != 1 ) clk = read(CLK);
	cout << "Memoria encendida" << endl;
	write(ACK,0);
	
	while(1) {
		usleep(300000);
		while( clk != 0 ) clk = read(CLK);
		cout << "Inicio clk en 0" << endl;

		cout << "\tLectura de se.ales" << endl;
		ack = read(ACK);
		req = read(REQ);
		
		d0 = read(D0);
		d1 = read(D1);
		d2 = read(D2);
		d3 = read(D3);
		
		usleep(300000);
		while( clk != 1 ) clk = read(CLK);
		cout << "Inicio clk en 1" << endl;
		
		if( req == 1 ) {
			cout << "\tMe llego esta direccion: " << d3 << d2 << d1 << d0 << endl;
			ya_tengo_direccion=true;
			int direccion = d3*8 + d2*4 + d1*2 + d0*1;
			x0 = get_memoria(direccion,0);
			x1 = get_memoria(direccion,1);
			x2 = get_memoria(direccion,2);
			x3 = get_memoria(direccion,3);
		}
		
		if( ya_tengo_direccion && req == 0 ) {
			cout << "\tEscribo un dato en el bus" << endl;
			write(ACK,1);
			write(D0,x0);
			write(D1,x1);
			write(D2,x2);
			write(D3,x3);
		}
		
		if( ack == 1 ) {
			// Termino la transmision
			cout << "\tFin de la transmision" << endl;
			write(D0,-1);
			write(D1,-1);
			write(D2,-1);
			write(D3,-1);
			write(ACK,0);
			ya_tengo_direccion=false;
		}
		
	}
}
