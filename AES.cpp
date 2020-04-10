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
	// Assuming we add 00 to the beginning of keyArray in cipher.cpp

	cout << strlen((char *)keyArray) << endl;
	
	// if keyArray's size is 17 proceed
	if(strlen((char *)keyArray)!=17)
	{
		fprintf(stderr, "Key should be 128 bits!\n");
		return false;
	}

	unsigned char * hexArray=(unsigned char *)keyArray;

	// convert keyArray to the hex array
	for (int i = 0; i < 17; i+=2)
	{
		hexArray[i]=twoCharToHexByte((unsigned char *)keyArray[i]);
	}

	// Removing the first byte 
	unsigned char * originalKey;
	strncpy((char *)originalKey, (char*)keyArray+1, 16);

	if(keyArray[0]==0x00)
	{
		// Set the encryption key	
		if(AES_set_encrypt_key(originalKey, 128, &enc_key)!=0)
		{
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			return false;
		}
		return true;	
	}
	else	// Otherwise we use set_decrypt_key
	{
		//	Set the decryption key
		if(AES_set_decrypt_key(originalKey, 128, &dec_key)!=0)
		{
			fprintf(stderr, "AES_SET_decrypt_key() failed!\n");
			return false;
		}
		return true;
	}
		
	// TODO: AES implementation of openssl cares about whether
	// you are encrypting or decrypting when setting the key.
	// That is, when encrypting you use function AES_set_encrypt_key(...)
	// and when decrypting AES_set_decrypt_key(...).
	//
	// One way to solve this problem is to pass in a 17 byte key, where
	// the first byte is used to indicate whether we are encrypting or
	// decrypting. E.g., if the first byte is 0, then use AES_set_encrypt_key(...).
	// Otherwise, use AES_set_decrypt_key(...).  The rest of the bytes in the
	// array indicate the 16 bytes of the 128-bit AES key.
	//
	// Both functions return 0 on success and other values on faliure.
	// For documentation, please see https://boringssl.googlesource.com/boringssl/+/2623/include/openssl/aes.h
	// and aes.cpp example provided with the assignment.

	// Check the type of key being passed in
	char type = keyArray[0];

	// Create a temp key variable to ensure original key isnt altered
	unsigned char *newKey = new unsigned char[16];

	// Pass over key values
	for(int i = 0; i < 16; i++)	{
		newKey[i] = keyArray[i + 1];
	}

	// Assign return value for SetKey()
	bool returnValue =  true;

	// Check if the key has passed or failed and return the result
	if (type == '0')	{
		if(AES_set_encrypt_key(newKey, 128, &this->enc_key) != 0)	{
			cerr << "AES_set_encrypt_key() has failed!\n" << endl;
			returnValue = false;
		}
	}
	else
	{
		if(AES_set_decrypt_key(newKey, 128, &this->dec_key) != 0)	{
			cerr << "AES_set_decrypt_key() has failed!\n" << endl;
			returnValue = false;
		}
	}
	
	
	
	
	return returnValue;
	
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
