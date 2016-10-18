#ifndef FUNCTIONS_HPP

#define FUNCTIONS_HPP

#include <string>
#include <fstream>
#include <cstdint>

using std::string;
using std::ofstream;
using std::ifstream;

using byte = uint8_t;

//! Generates a random key
/*! 
  Generates a random key and stores it in a file, the key will have the size specified by key_size in bytes
  \param filename The name of the file where the key will be stored
  \param key_size The size in bytes of the key
*/
void generateKey(const string& filename, const int key_size);
//! Process an encryption/decryption request
/*! 
  Encrypts/Decrypts a file using the specified key with the specified block size
  \param fIn File for the input
  \param fOut File for the output
  \param key Byte array for the key
  \param block_size The block size
  \param encrypt Whether the function shall encrypt or decrypt
  \param operation_mode The operation mode
*/
void Process_Request(ifstream& fIn, ofstream& fOut,
		     const byte* key, const int block_size,
		     const bool encrypt, const string& operation_mode);
//! The operation mode CBC
/*! 
  Applies the operation mode CBC by making XOR of the origin with the previous ciphertext on the encryption operation and decrypting the ciphertext and making a result of this result with the previous ciphertext for the decryption operation
  \param origin The byte array to operate
  \param aux An auxiliar array used to handle the operations
  \param result The final result of the operation
  \param key The key used
  \param block_size The block size
  \param encrypt Whether the function shall encrypt or decrypt
*/
void CBC(const byte* origin, byte* aux, byte* result,
	 const byte* key, const int block_size, bool encrypt);
//! The operation mode CTR
/*! 
  Applies the operation mode CTR by encrypting the IV, then making XOR of this with the origin and then modifying the IV by adding one
  \param origin The byte array to operate
  \param IV The IV used for the operation
  \param result The final result of the operation
  \param key The key used
  \param block_size The block size
  \param encrypt Whether the function shall encrypt or decrypt
*/
void CTR(const byte* origin, byte* IV, byte* result,
	 const byte* key, const int block_size, bool encrypt);
//! 
/*! Adds a number to a byte array
  Adds a number to a byte array, the function is used in the CTR mode
  \param array The array to modify
  \param number The number to add
  \param array_size The size of the array
*/
void add(byte* array, char number, int array_size);
//! XOR a pair of arrays
/*! 
  Makes the XOR operation of two blocks of equal size
  \param argument1 The first block 
  \param argument2 The second block
  \param result The result block
  \param array_size The array size
*/
void XOR_Block(const byte* argument1, const byte* argument2,
	       byte* result, int array_size);
//! The cipher operation
/*! 
  Ciphers the origin using key and stores it in result. It also makes the decipher operation.
  \param origin The information to be ciphered/deciphered
  \param result The resulting information
  \param key The key to use
  \param block_size The block size
  \param encrypt Whether the function shall encrypt or decrypt
*/
void cipher(const byte* origin, byte* result, const byte* key,
	    const int block_size, bool encrypt);

#endif
