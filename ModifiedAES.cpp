#include "modified-aes.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void generate_key(unsigned char* key) {
    int i;
    for (i=0; i<16; i++) {
	key[i] = rand()%255;
    }
};

int main(int argc, char* argv[])
{
    unsigned char* key = new unsigned char[16];
    generate_key(key);
    uint8_t* RoundKey = AES128_ECB_encrypt(key);
    ofstream fOut(argv[1]);
    for(int i = 0; i < 11; i++)
    {
	fOut << "0x";
	for(int j = 0; j < 16; j++)
	{
	    fOut << std::hex << setw(2) << setfill('0') << int(RoundKey[i*16 + j]);
	}
	fOut << endl;
    }
    return 0;
}
