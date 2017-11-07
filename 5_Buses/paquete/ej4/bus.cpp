/* ************************************************** 
   Taller de Buses - Organizacion del computador I
      (por compatibilidad se omiten tildes)
************************************************** */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int read(string linea) {
	int x=-1;
	ifstream inFile;
	inFile.open(linea.c_str());
	inFile >> x;
	inFile.close();
	return x;
}

void write(string linea, int x) {
	ofstream outFile;
	outFile.open(linea.c_str());
	outFile << x;
	outFile.close();
}