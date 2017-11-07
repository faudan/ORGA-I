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

	write(REQ1,-1);
	write(REQ2,-1);
	write(REQ3,-1);
	write(ACK1,-1);
	write(ACK2,-1);
	write(ACK3,-1);
	write(D0,-1);
	write(D1,-1);
	write(D2,-1);
	write(D3,-1);
	write(A0,-1);
	write(A1,-1);
	write(A2,-1);
	write(A3,-1);
	write(RW,-1);
	write(DEV0,-1);
	write(DEV1,-1);

	bool clk = false;
	while(1) {
		if(clk) write(CLK,1); else write(CLK,0);
		cout << clk << endl;
		sleep(1);
		clk = !clk;
	}
}
