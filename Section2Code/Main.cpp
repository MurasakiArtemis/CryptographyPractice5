/*
  Eron Romero Argumedo
  Erwin Hernández García
*/

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Functions.hpp"

using std::cout;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::ios;
using std::string;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
	cout << "Se debe especificar un modo de uso" << endl;
	return -1;
    }
    string opcion(argv[1]);
    if(opcion.size() != 2)
    {	
	cout << "El modo de uso consiste en un guión seguido de la letra del modo" << endl;
	return -1;
    }
    else if(opcion == "-k")
    {
	if(argc != 4)
	{
	    cout << "El modo de uso es: " << argv[0] << " " << argv[1] << " <nombre del archivo> <tamaño de la llave>" << endl;
	    return -1;
	}
	generateKey(argv[2], std::stoi(argv[3])/8);
    }
    else if(opcion == "-e" || opcion == "-d")
    {
	if(argc != 6)
	{
	    cout << "El modo de uso es: " << argv[0] << " " << argv[1] << " <llave>" << (opcion == "-e"?" <texto plano> <texto cifrado>":"<texto cifrado> <texto plano>") << " <modo de operación>" << endl;
	    return -1;
	}
	ifstream fIn(argv[2], ios::binary);
	fIn.seekg(0, ios::end);
	int fileSize = fIn.tellg();
	fIn.seekg(0, ios::beg);
	int block_size = fileSize;
	byte* key = new byte[block_size];
	fIn.read((char*)key, block_size);
	fIn.close();
	fIn.open(argv[3], ios::binary);
	ofstream fOut(argv[4], ios::binary);
	Process_Request(fIn, fOut, key, block_size, opcion == "-e", argv[5]);
	fIn.close();
	fOut.close();
	delete[] key;
    }
    else
    {
	cout << "Los modos de uso son: -k -e -d" << endl;
	return -1;
    }
    return 0;
}

