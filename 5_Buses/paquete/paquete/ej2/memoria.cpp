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

void set_memoria(int direccion,int bit, int value) {
    memoria[direccion*4+bit] = value;
}

int main(int argc, char *argv[]) {
  
	int clk = read(CLK);
	int req = 0;
	int ack = 0;
	int rw = 0;
	
	int d0 = 0;
	int d1 = 0;
	int d2 = 0;
	int d3 = 0;
	
	int x0 = 0;
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	
	bool ya_tengo_direccion = false;
	bool tengo_que_leer = false;
	bool leer_o_escribir = false;
	bool ya_tengo_dato = false;
	
	int direccion;
	int ciclo_que_espera = 0;
	
	while( clk != 1 ) clk = read(CLK);
	cout << "Memoria Encendida" << endl;
	write(ACK,0);
	
	while(1) {
		usleep(300000);
		while( clk != 0 ) clk = read(CLK);
		cout << "Inicio clk en 0" << endl;

		cout << "\tLectura de se.ales" << endl;
		ack = read(ACK);
		req = read(REQ);
		rw = read(RW);
		d0 = read(D0);
		d1 = read(D1);
		d2 = read(D2);
		d3 = read(D3);
		
		usleep(300000);
		while( clk != 1 ) clk = read(CLK);
		cout << "Inicio clk en 1" << endl;
		
		if(ciclo_que_espera == 0) {
			// Paso 1
			if(!ya_tengo_direccion && !ya_tengo_dato && !leer_o_escribir && req == 1 ) {
				ya_tengo_direccion=true;
				tengo_que_leer=rw;
				
				cout << "\tMe llego esta direccion " << d3 << d2 << d1 << d0 << " ";
				direccion = d3*8 + d2*4 + d1*2 + d0*1;
				
				x0 = get_memoria(direccion,0);
				x1 = get_memoria(direccion,1);
				x2 = get_memoria(direccion,2);
				x3 = get_memoria(direccion,3);
				
				if(tengo_que_leer)
					cout << "de donde leer" << endl;
				else
					cout << "donde escribir" << endl;

// 				ciclo_que_espera = 1; // Delay despues de leer
			}
			// Paso 3
			else if(ya_tengo_direccion && !ya_tengo_dato && !leer_o_escribir && req == 1 && ack == 0 ) {
				write(ACK,1);
			}
			// Paso 4
			else if(ya_tengo_direccion && !ya_tengo_dato && !leer_o_escribir && req == 1 && ack == 1 ) {
				write(ACK,0);
				leer_o_escribir = true;
			}
			// Paso 5 para escritura
			else if(ya_tengo_direccion && !ya_tengo_dato && leer_o_escribir && req == 1 && ack == 0 && tengo_que_leer == 0 ) {
				ya_tengo_dato=true;
				
				cout << "\tMe llego el dato " << d3 << d2 << d1 << d0 << " ";
				cout << "que tengo que escribir en " << direccion << endl;
				
				set_memoria(direccion,0,d0);
				set_memoria(direccion,1,d1);
				set_memoria(direccion,2,d2);
				set_memoria(direccion,3,d3);
				
				ciclo_que_espera = 1; // Delay despues de leer
			}
			// Paso 6 para escritura
			else if(ya_tengo_direccion && ya_tengo_dato && leer_o_escribir && req == 1 && ack == 0 && tengo_que_leer == 0 ) {
				write(ACK,1);
			}
			// Paso 7 para escritura
			else if(ya_tengo_direccion && ya_tengo_dato && leer_o_escribir && req == 1 && ack == 1 && tengo_que_leer == 0 ) {
				cout << "\tFin del ciclo de escritura" << endl;
				write(ACK,0);
				ya_tengo_direccion=false;
				ya_tengo_dato=false;
				leer_o_escribir=false;
			}
			// Paso 5 para lectura
			else if(ya_tengo_direccion && !ya_tengo_dato && leer_o_escribir && req == 0 && ack == 0 && tengo_que_leer == 1 ) {
				ya_tengo_dato=true;
				
				cout << "\tTengo que leer el dato en la direccion " << direccion << endl;

				write(D0,x0);
				write(D1,x1);
				write(D2,x2);
				write(D3,x3);
				write(ACK,1);
			}
			// Paso 8 para lectura
			else if(ya_tengo_direccion && ya_tengo_dato && leer_o_escribir && req == 1 && ack == 1 && tengo_que_leer == 1 ) {
				cout << "\tFin del ciclo de lectura" << endl;
				write(ACK,0);
				write(D0,-1);
				write(D1,-1);
				write(D2,-1);
				write(D3,-1);
				ya_tengo_direccion=false;
				ya_tengo_dato=false;
				leer_o_escribir=false;
			}

		} else
			ciclo_que_espera--;
	}
}
