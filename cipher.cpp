#include <string>
#include <iostream>
#include <stdio.h>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

using namespace std;



void DES_Cipher(CipherInterface *cipher, string key, string enc_dec, string inFile, string outFile) {
	cipher->setKey((unsigned char*)key.c_str());
	if(enc_dec == "ENC") {
		//unsigned char* ciphertext = cipher->encrypt(read(inFile));

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
	
	// The block size
	int blockSize = -1;
		
	/* Create an instance of the DES cipher */	
	CipherInterface* cipher = NULL; 
	
	if(cipherType == "DES") {
		cipher = new DES();
		blockSize = 8;
		cipher->setKey((unsigned char *)key.c_str());
	}
	else if(cipherType == "AES"){
		cipher = new AES();
		blockSize = 16;
		string prePendKey; 
		if(enc_dec == "ENC")
		{
			prePendKey = "0"+key;
			cipher->setKey((unsigned char *)prePendKey.c_str());
		}
		else if(enc_dec == "DEC")
		{
			prePendKey = "1"+key;
			cipher->setKey((unsigned char *)prePendKey.c_str());
		}
		else
		{
			cout<<"You need to enter ENC or DEC."<<endl;
		}
	}
	
	/* Error checks */
	if(!cipher)
	{

		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}	

	// A single block	
	unsigned char block[blockSize];

	// Open the input the file 
	FILE* inputFilePtr = fopen(inFile.c_str(), "rb");
	
	// Open the output file
	FILE* outputFilePtr = fopen(outFile.c_str(), "wb");
	
	// Sanity check for the input file
	if(!inputFilePtr)
	{
		perror("fopen() error on input");
		exit(-1);
	}

	// Sanity check for the output
	if(!outputFilePtr)
	{
		perror("fopen() error on output");
		exit(-1);
	}
	
	int bytesRead, bytesWrote;
	
	unsigned char * processedText = NULL;
 	
	// Read the entire file
	while(!feof(inputFilePtr))
	{
		// 1. Read one block using fread()
		bytesRead  = fread(block, 1, blockSize, inputFilePtr);
		
		// If we read something, we will process it
		if(bytesRead != 0)
		{
		
			// 2. If encrypting, padd it
			if(enc_dec == "ENC")
			{
				//|b|b|b| | | | | |
				//bytesRead => 3
				//block[bytesRead] = 'x';
				//
				for(int i=bytesRead; i<blockSize; i++)
				{
					block[i] = 'x';
				}

				processedText = cipher->encrypt((unsigned char *)block);
					
			}
			else
			{
				processedText = cipher->decrypt((unsigned char *) block);
			}
			
				
			// 3. Encrypt/Decrypt

			// 4. Write the block to the output file
			bytesWrote = fwrite(processedText, 1, blockSize, outputFilePtr);
			
			// Sanity check!	
			if(bytesWrote != blockSize)
			{
				perror("Unable to write bytes!\n");
				exit(-1);
			}
			
			// Free the memory	
			delete[] processedText;

		}
	}

	fclose(inputFilePtr);
	fclose(outputFilePtr);
	
		

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
