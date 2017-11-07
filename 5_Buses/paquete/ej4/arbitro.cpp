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
	
	int req1 = 0;
	int ack1 = 0;
	int req2 = 0;
	int ack2 = 0;
	int req3 = 0;
	int ack3 = 0;

	while( clk != 1 ) clk = read(CLK);
	cout << "Arbitro encendido" << endl;
	
	write(ACK1,0);
	write(ACK2,0);
	write(ACK3,0);
	
	bool ocupado = false;
	
	while(1) {
		usleep(300000);
		while( clk != 0 ) clk = read(CLK);
		cout << "Inicio clk en 0" << endl;
		
		req1 = read(REQ1);
		ack1 = read(ACK1);
		req2 = read(REQ2);
		ack2 = read(ACK2);
		req3 = read(REQ3);
		ack3 = read(ACK3);
	  
		usleep(300000);
		while( clk != 1 ) clk = read(CLK);
		cout << "Inicio clk en 1" << endl;
		
		if( req1 == 1 && !ocupado ) {
			cout << "\totorgado a 1" << endl;
			write(ACK1,1);
			ocupado=true;
		} else
		if( req2 == 1 && !ocupado ) {
			cout << "\totorgado a 2" << endl;
			write(ACK2,1);
			ocupado=true;
		} else
		if( req3 == 1 && !ocupado ) {
			cout << "\totorgado a 3" << endl;
			write(ACK3,1);
			ocupado=true;
		}
		  
		if( req1 == 0 && ack1 == 1 && ocupado ) {
			cout << "\tliberado 1" << endl;
			write(ACK1,0);
			ocupado=false;
		} else
		if( req2 == 0 && ack2 == 1 && ocupado ) {
			cout << "\tliberado 2" << endl;
			write(ACK2,0);
			ocupado=false;
		} else
		if( req3 == 0 && ack3 == 1 && ocupado ) {
			cout << "\tliberado 3" << endl;
			write(ACK3,0);
			ocupado=false;
		}
	}
}