/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "bus.h"
using namespace std;

int main(int argc, char *argv[]) {

	vector<string> nombres;
	vector<int> estados;
	
	nombres.push_back(CLK); estados.push_back(0);
	nombres.push_back(D0);  estados.push_back(0);
	nombres.push_back(D1);  estados.push_back(0);
	nombres.push_back(D2);  estados.push_back(0);
	nombres.push_back(D3);  estados.push_back(0);
	nombres.push_back(ACK); estados.push_back(0);
	nombres.push_back(REQ); estados.push_back(0);
	
	int size = nombres.size();
	
	for(int i=0;i<size;i++)
		cout << nombres[i] << "\t";
	cout << endl;
	
	while(1) {
		for(int i=0;i<size;i++) {
			int x;
			x = read(nombres[i]);
			if( x != -1 && x != estados[i] ) {
				estados[i] = x;
				for(int j=0;j<size;j++) {
					int x = read(nombres[j]);
					if( x == -1)
						cout << "x" << "\t";
					else
						cout << estados[j] << "\t";
				}
				cout << endl;
			}
		}
	}  
}
