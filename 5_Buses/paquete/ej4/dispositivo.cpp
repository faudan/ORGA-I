/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include "bus.h"

#if DISPOSITIVO == 1
    #define ACK ACK1
    #define REQ REQ1
    #define SOY_DEV0 0
    #define SOY_DEV1 1
#elif DISPOSITIVO == 2
    #define ACK ACK2
    #define REQ REQ2
    #define SOY_DEV0 1
    #define SOY_DEV1 0
#elif DISPOSITIVO == 3
    #define ACK ACK3
    #define REQ REQ3
    #define SOY_DEV0 1
    #define SOY_DEV1 1
#endif

#define LEER 1
#define ESCRIBIR 2 
#define NADA 3

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
	int d0 = 0, d1 = 0, d2 = 0, d3 = 0, xd0 = 0, xd1 = 0, xd2 = 0, xd3 = 0;
	int a0 = 0, a1 = 0, a2 = 0, a3 = 0, xa0 = 0, xa1 = 0, xa2 = 0, xa3 = 0;
	int dev0 = 0, dev1 = 0, xdev0 = 0, xdev1 = 0;
	
	int opcion = NADA;
	int dos_ciclos = 0;
	bool respuesta_lectura=false;
	bool tengo_el_bus = false;
	
	cout << "Seleccione:" << endl;
	cout << "     Leer     -> 1" << endl;
	cout << "     Escribir -> 2" << endl;
	cout << "     NADA     -> 3" << endl;
	cout << endl << "Opcion: " << endl;
	cin >> opcion;
	
	if(opcion != NADA ) {
		cout << "Dispositivo destino:" << endl;
		cout << "dev0:" << endl; cin >> xdev0;
		cout << "dev1:" << endl; cin >> xdev1;
		
		if(opcion == LEER) {
			cout << "Direccion donde leer:" << endl;
			cout << "a0:" << endl; cin >> xa0;
			cout << "a1:" << endl; cin >> xa1;
			cout << "a2:" << endl; cin >> xa2;
			cout << "a3:" << endl; cin >> xa3;
		} else {
			cout << "Direccion donde escribir:" << endl;
			cout << "a0:" << endl; cin >> xa0;
			cout << "a1:" << endl; cin >> xa1;
			cout << "a2:" << endl; cin >> xa2;
			cout << "a3:" << endl; cin >> xa3;
			cout << "Dato que escribir:" << endl;
			cout << "d0:" << endl; cin >> xd0;
			cout << "d1:" << endl; cin >> xd1;
			cout << "d2:" << endl; cin >> xd2;
			cout << "d3:" << endl; cin >> xd3;
		}
	}

	while( clk != 1 ) clk = read(CLK);
	cout << "Dispositivo " << DISPOSITIVO << " encendido" << endl;
	write(REQ,0);
	
	while(1) {
		usleep(300000);
		while( clk != 0 ) clk = read(CLK);
		cout << "Inicio clk en 0" << endl;
		
		cout << "\tLectura de se.ales" << endl;
		ack = read(ACK);
		req = read(REQ);
		rw  = read(RW);
		a0 = read(A0);
		a1 = read(A1);
		a2 = read(A2);
		a3 = read(A3);
		d0 = read(D0);
		d1 = read(D1);
		d2 = read(D2);
		d3 = read(D3);
		dev0 = read(DEV0);
		dev1 = read(DEV1);
		
		usleep(300000);
		while( clk != 1 ) clk = read(CLK);
		cout << "Inicio clk en 1" << endl;
		
		if( !tengo_el_bus ) {
			if( dev0 == SOY_DEV0 && dev1 == SOY_DEV1 ) {
				
				if( rw == 1 ) {
				  
					// COMPLETAR EL CODIGO PARA RESPONDER UNA LECTURA
					
				} else {
				  
					// COMPLETAR EL CODIGO PARA RESPONDER UNA ESCRITURA
					
				}
				
			} else if(opcion != NADA ) {
				
				if(req==0)
					write(REQ,1);
				
				if( ack==1 && req==1)
					tengo_el_bus=true;
			}
		}
		else // tengo el bus
		{  
			if(opcion == LEER) {

			  // COMPLETAR EL CODIGO PARA LEER
			  
			} else {
			  
			  // COMPLETAR EL CODIGO PARA ESCRIBIR
			  
			}
		}
	}
}
