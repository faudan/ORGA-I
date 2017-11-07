/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "bus.h"
using namespace std;

int main(int argc, char *argv[]) {

	int clk = read(CLK);
	int req = 0;
	int ack = 0;
	int d0 = 0;
	int d1 = 0;
	int d2 = 0;
	int d3 = 0;
	bool esperando_leer=false;
	bool stdin_args = true;
	
	int dx0 = 1;
	int dx1 = 0;
	int dx2 = 1;
	int dx3 = 0;

	if (argc == 5) {
		dx0 = atoi(argv[1]);
		dx1 = atoi(argv[2]);
		dx2 = atoi(argv[3]);
		dx3 = atoi(argv[4]);
		stdin_args = false;
	}
	
	cout << "Inciar lectura:" << endl;
	cout << "Direccion:" << endl;
	if (stdin_args) {
		cout << "d0:" << endl; cin >> dx0;
		cout << "d1:" << endl; cin >> dx1;
		cout << "d2:" << endl; cin >> dx2;
		cout << "d3:" << endl; cin >> dx3;
	} else {
		cout << "d0:" << dx0 << endl;
		cout << "d1:" << dx1 << endl;
		cout << "d2:" << dx2 << endl;
		cout << "d3:" << dx3 << endl;
	}

	while( clk != 1 ) clk = read(CLK);
	cout << "CPU encendido" << endl;
	write(REQ,0);
	
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
		
		if(req == 0 && ack == 0 && !esperando_leer) {
			cout << "\tInicio una lectura" << endl;
			// Indico que voy a leer
			write(REQ,1);
			// Direccion de la cual voy a leer
			write(D0,dx0);
			write(D1,dx1);
			write(D2,dx2);
			write(D3,dx3);
			esperando_leer=true;
		}
		
		if( req == 1 ) {
			// Indico que libere las lineas
			cout << "\tlibera lineas" << endl;
			write(D0,-1);
			write(D1,-1);
			write(D2,-1);
			write(D3,-1);
			write(REQ,0);
		}
		
		if( ack == 1 ) {
			// se inicia una lectura de datos
			cout << "\tMe llego este dato: " << d3 << d2 << d1 << d0 << endl;
			esperando_leer = false;
		}
	}
}
