#include <string>
#include <fstream>
#include <cstring>
#include "Functions.hpp"
#include "aes.h"

using std::string;
using std::ofstream;
using std::ifstream;
using std::ios;

void generateKey(const string& filename, const int key_size)
{
    byte *key;
    key = new byte[key_size];
    srand(time(nullptr));
    for(int i = 0; i < key_size; i++)
        key[i] = rand()%0xFF;
    ofstream fOut(filename, ios::binary | ios::trunc);
    fOut.write((char*)key, key_size);
    fOut.close();
    delete[] key;
}

void Process_Request(ifstream& fIn, ofstream& fOut,
                     const byte* key,
                     const int block_size,
                     const bool encrypt,
                     const string& operation_mode)
{
    srand(time(nullptr));
    fIn.seekg(0, ios::end);
    int origin_size = int(fIn.tellg()) - 1;
    fIn.seekg(0, ios::beg);   
    byte* origin = new byte[block_size];
    byte* result = new byte[block_size];
    byte* aux = nullptr;
    byte* IV = nullptr;
    if(operation_mode != "ECB")
    {
        aux = new byte[block_size];
        IV = new byte[block_size];
        if(encrypt)
        {
            for(int i = 0; i < block_size; i++)
                IV[i] = rand()%0xFF;
            fOut.write((char*)IV, block_size);
            if(operation_mode == "CBC")
                memcpy(result, IV, block_size);
        }
        else
        {
            fIn.read((char*)IV, block_size);
            origin_size -= block_size;
            if(operation_mode == "CBC")
                memcpy(aux, IV, block_size);
        }
    }
    for(int i = 0; i < origin_size; i += block_size)
    {
        fIn.read((char*)origin, block_size);
        if(fIn.eof())
            for(int j = fIn.gcount()-1; j < block_size; j++)
                origin[j] = 0;
        if(operation_mode == "ECB")
            cipher(origin, result, key, block_size, encrypt);
        else if(operation_mode == "CBC")
            CBC(origin, aux, result, key, block_size, encrypt);
        else if(operation_mode == "CTR")
            CTR(origin, IV, result, key, block_size, encrypt);
        fOut.write((char*)result, block_size);
    }
    delete[] origin;
    delete[] result;
    if(aux != nullptr)
    {
        delete[] aux;
        delete[] IV;
    }
}

void CBC(const byte* origin, byte* aux, byte* result,
         const byte* key, const int block_size,
         bool encrypt)
{
    if(encrypt)
    {
        XOR_Block(origin, result, aux, block_size);
        cipher(aux, result, key, block_size, encrypt);
    }
    else
    {
        cipher(origin, result, key, block_size, encrypt);
        XOR_Block(result, aux, result, block_size);
        memcpy(aux, origin, block_size);
    }
}

void CTR(const byte* origin, byte* IV, byte* result,
         const byte* key, const int block_size,
         bool encrypt)
{
    cipher(IV, result, key, block_size, true);
    XOR_Block(result, origin, result, block_size);
    add(IV, 1, block_size);
}

void add(byte* array, char number, int array_size)
{
    for(int i = array_size - 1; i >= 0; i--)
    {
        byte aux = array[i];
        array[i] = array[i] + number;
        if(aux == 0xFF && number != 0)
            number = 1;
        else break;
    }
}

void XOR_Block(const byte* argument1, const byte* argument2,
               byte* result, int array_size)
{
    for(int i = 0; i < array_size; i++)
        result[i] = argument1[i] ^ argument2[i];
}

void cipher(const byte* origin, byte* result, const byte* key,
            const int block_size, bool encrypt)
{
    if(encrypt)
        AES128_ECB_encrypt(origin, key, result);
    else
        AES128_ECB_decrypt(origin, key, result);
}
