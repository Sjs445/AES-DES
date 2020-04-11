#include <string>
#include <iostream>
#include <fstream>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;

// Reads the file and returns a string containing contents
string read(string file) {
	ifstream infile(file.c_str());
	string contents;
	char character;

	if(infile.is_open()) {
		while(infile >> character) {
			contents = contents + character;
		}
	}
	return contents;
}

void DES_Cipher(CipherInterface *cipher, string key, string enc_dec, string inFile, string outFile) {
	cipher->setKey((unsigned char*)key.c_str());
	if(enc_dec == "ENC") {
		//unsigned char* ciphertext = cipher->encrypt(read(inFile));

	}
}

void AES_Cipher(CipherInterface *cipher, string key, string enc_dec, string inFile, string outFile){
	if(enc_dec == "ENC")	{
		string paddedKey = "0"+key;
		cipher->setKey((unsigned char*)paddedKey.c_str());
		unsigned char* ciphertext = cipher->encrypt((unsigned char*)read(inFile).c_str());
		cout << ciphertext << endl;
	}
	else{
		string paddedKey = "1"+key;
		cipher->setKey((unsigned char*)paddedKey.c_str());
		unsigned char* ciphertext = cipher->encrypt((unsigned char *)read(inFile).c_str());
		cout << ciphertext << endl;
}
}

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	with your code which can SWITCH
	 * between DES and AES and encrypt files. DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 *
	 * NOTE: due to the incomplete skeleton, the code may crash or
	 * misbehave.
	 */
	

	//Example run command:
	//cipher AES "00112233445566778899aabbccddeeff" ENC in.txt out.txt

	// Map the arguments to strings
	string cipherType = argv[1];
	string key = argv[2];
	string enc_dec = argv[3];
	string inFile = argv[4];
	string outFile = argv[5];
	if(cipherType == "DES") {
		CipherInterface* cipher = new DES();
		DES_Cipher(cipher, key, enc_dec, inFile, outFile);
	}
	else if(cipherType == "AES"){
		CipherInterface* cipher = new AES();
		AES_Cipher(cipher, key, enc_dec, inFile, outFile);
	}
	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL; 
	/* Error checks */
	if(!cipher)
	{

		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
	// cipher->setKey((unsigned char*)"0123456789abcdef");
	
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);	
	
	return 0;
}
