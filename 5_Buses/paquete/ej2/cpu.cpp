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

int main(int argc, char *argv[]) {

	int clk = read(CLK);
	int req = 0;
	int rw  = 0;
	int ack = 0;
	int d0 = 0;
	int d1 = 0;
	int d2 = 0;
	int d3 = 0;

	int dx0 = 0;
	int dx1 = 0;
	int dx2 = 0;
	int dx3 = 0;
	
	int vx0 = 0;
	int vx1 = 0;
	int vx2 = 0;
	int vx3 = 0;
	
	cout << "Inciar Escritura:" << endl;
	cout << "Direccion:" << endl;
	cout << "d0:" << endl; cin >> dx0;
	cout << "d1:" << endl; cin >> dx1;
	cout << "d2:" << endl; cin >> dx2;
	cout << "d3:" << endl; cin >> dx3;
	cout << "Dato:" << endl;
	cout << "v0:" << endl; cin >> vx0;
	cout << "v1:" << endl; cin >> vx1;
	cout << "v2:" << endl; cin >> vx2;
	cout << "v3:" << endl; cin >> vx3;

	while( clk != 1 ) clk = read(CLK);
	cout << "CPU Encendido" << endl;
	write(REQ,0);
	
	while(1) {
		usleep(300000);
		while( clk != 0 ) clk = read(CLK);
		cout << "Inicio clk en 0" << endl;

		cout << "\tLectura de se.ales" << endl;
		ack = read(ACK);
		req = read(REQ);
		rw  = read(RW);
		
		d0 = read(D0);
		d1 = read(D1);
		d2 = read(D2);
		d3 = read(D3);
		
		usleep(300000);
		while( clk != 1 ) clk = read(CLK);
		cout << "Inicio clk en 1" << endl;
		
		cout << "\tEscritura de se.ales" << endl;

		// COMPLETAR
	}
}
