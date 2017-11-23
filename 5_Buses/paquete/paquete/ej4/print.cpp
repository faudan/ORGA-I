/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>
#include "bus.h"
using namespace std;

int main(int argc, char *argv[]) {

	vector<string> nombres;
	nombres.push_back(CLK);
	
	nombres.push_back(REQ1);
	nombres.push_back(ACK1);
	nombres.push_back(REQ2);
	nombres.push_back(ACK2);
	nombres.push_back(REQ3);
	nombres.push_back(ACK3);
	nombres.push_back(RW);
	nombres.push_back(A0);
	nombres.push_back(A1);
	nombres.push_back(A2);
	nombres.push_back(A3);
	nombres.push_back(D0);
	nombres.push_back(D1);
	nombres.push_back(D2);
	nombres.push_back(D3);
	nombres.push_back(DEV0);
	nombres.push_back(DEV1);
	
	int size = nombres.size();
	int clk = read(CLK);
	
	for(int i=0;i<size;i++)
		cout << (nombres[i]).substr(4,-1) << "\t";
	cout << endl;
	
	while(1) {
		usleep(300000);
		while( clk != 0 ) clk = read(CLK);	
		
		for(int j=0;j<size;j++) {
			int x = read(nombres[j]);
			if( x == -1)
				cout << "x" << "\t";
			else
				cout << read(nombres[j]) << "\t";
		}
		cout << endl;
		
		usleep(300000);
		while( clk != 1 ) clk = read(CLK);

		for(int j=0;j<size;j++)
			if( nombres[j] == CLK)
				cout << clk << "\t";
			else
				cout << "." << "\t";
		cout << endl;
		
	}  
}
