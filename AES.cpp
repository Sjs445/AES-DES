#include "AES.h"

/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	// Whether we are doing encryption/decryption
	char type = keyArray[0];	

	// The index of the key
	int keyIndex = 0;
	
	// if keyArray's size is 34 proceed
	if(strlen((char *)keyArray)!=33)
	{
		fprintf(stderr, "Key should be 128 bits!\n");
		return false;
	}

	//	Create new char array for twoCharToHexByte conversion
	unsigned char hexArray [16];

	// convert keyArray to the hex array
	for (int i = 1; i < 32; i+=2)
	{
		
		hexArray[keyIndex] = twoCharToHexByte((unsigned char *)keyArray + i);

		// Go to the index key index
		++keyIndex;
	}
	
	if(keyArray[0]=='0')
	{
		cerr << "Setting encryption key!" << endl;
		// Set the encryption key	
		if(AES_set_encrypt_key(hexArray, 128, &enc_key)!=0)
		{
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			return false;
		}
		return true;	
	}
	else	// Otherwise we use set_decrypt_key
	{
		cerr << "Setting decryption key!" << endl;
		//	Set the decryption key
		if(AES_set_decrypt_key(hexArray, 128, &dec_key)!=0)
		{
			fprintf(stderr, "AES_SET_decrypt_key() failed!\n");
			return false;
		}
			return true;
	}
	
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	
	//TODO: 1. Dynamically allocate a block to store the ciphertext.
	unsigned char * enc_out = new unsigned char [16];
	//	2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	AES_ecb_encrypt(plainText, enc_out, &enc_key, AES_ENCRYPT);
	// 	3. Return the pointer to the ciphertext

	return enc_out;	
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	
	//TODO: 1. Dynamically allocate a block to store the plaintext.
	unsigned char* dec_out = new unsigned char [16];
	//	2. Use AES_ecb_encrypt(...) to decrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	AES_ecb_encrypt(cipherText, dec_out, &dec_key, AES_DECRYPT);
	// 	3. Return the pointer to the plaintext
		
	return dec_out;
}

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char AES::charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */	
	if(character >= '0' && character <= '9')	
		/* Convert the character to hex */
		return character - '0';
	/* It the first digit a letter 'a' - 'f'? */
	else if(character >= 'a' && character <= 'f')
		/* Conver the cgaracter to hex */
		return (character - 97) + 10;	
	/* Invalid character */
	else return 'z';
}


unsigned char AES::twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;
	
	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if((singleByte = charToHex(twoChars[0])) == 'z') 
	{
		/* Invalid digit */
		return 'z';
	}
	
	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);
	
	/* Conver the second character */
	if((secondChar = charToHex(twoChars[1])) == 'z')
		return 'z'; 
	
	/* Insert the second value into the lower nibble */	
	singleByte |= secondChar;

	return singleByte;
}
