#include "CryptoAES.hpp"
#include "Crypto.hpp"
#include <iostream>
#include <ctime>
#include <cstring>

#define BLOCK_SIZE 16
#define BUFF_SIZE 15
#define DEBUG 0

CryptoAES::CryptoAES(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
                           std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
: Crypto(encryptCallback, decryptCallback)
{
	td = mcrypt_module_open("rijndael-128", NULL, "cbc", NULL);
	key = new uint8_t[keyLen];
	IV = new uint8_t[IVLen];
}

void CryptoAES::genKeys()
{
	// Do some stuff to get a random number and shift the stuff
	// Generate a random array/vector key. Size?
	std::srand(std::time(NULL));
	
	for (int i = 0; i < keyLen; i++)
	{
	    key[i] = (std::rand() % 256);
	   
	}
	for (int i = 0; i < IVLen; i++)
	{
	    IV[i] = (std::rand() % 256);
	   
	}
	mcrypt_generic_init(td, key, keyLen, IV);
	keyGenerated = true;
}

bool CryptoAES::getKeys(uint8_t ** pubKey, uint32_t & pubLen, uint8_t ** 
priKey, uint32_t & priLen)
{
	if (!keyGenerated)
	{
		//std::cout << "No keys were generated!" << std::endl;
		return false;
	}
	else 
	{
		*priKey = new uint8_t[2 * BLOCK_SIZE];
		std::memcpy(*priKey, key, BLOCK_SIZE);
		std::memcpy(*priKey + BLOCK_SIZE, IV, BLOCK_SIZE);
		priLen = BLOCK_SIZE * 2;
	}
	return true;
}

void CryptoAES::setKeys(const uint8_t * pubKey, uint32_t pubLen, const uint8_t * priKey, uint32_t priLen)
{
	std::memcpy(key, priKey, keyLen);
	std::memcpy(IV, priKey + BLOCK_SIZE, BLOCK_SIZE);
	mcrypt_generic_init(td, key, keyLen, IV);
	keyGenerated = true;
}

void CryptoAES::destroyKeys()
{
	delete [] key;
	delete [] IV;
	key = NULL;
	IV = NULL;
	keyGenerated = false;
}


bool CryptoAES::encrypt(const uint8_t * data, uint32_t len)
{
	if (!keyGenerated)
	{
		//std::cout << "No key has been initialized" << std::endl;
		return false;
	}
	
	uint8_t block[16];
	if (len == 0 && inBuff > 0)
	{
		
		if (DEBUG) std::cout << "flushing buffers and encrypting." << std::endl;
		block[15] = inBuff;
		buff.read((char *)block, inBuff);
		mcrypt_generic(td, block, BLOCK_SIZE);
		m_encryptCallback(block, BLOCK_SIZE);
		inBuff = 0;
		return true;
	}
	buff.write((char *)data, len);
	inBuff += len;
	
	while (inBuff >= BUFF_SIZE)
	{
		buff.read((char *)block, BUFF_SIZE);
		inBuff -= BUFF_SIZE;
		block[15] = BUFF_SIZE;
		mcrypt_generic(td, block, BLOCK_SIZE);

		m_encryptCallback(block, BLOCK_SIZE);	
		//std::cout << "in encrypt loop" << std::endl;
	}
	
	return true;
}

bool CryptoAES::decrypt(const uint8_t * data, uint32_t len)
{
	
	if (!keyGenerated)
	{
		//std::cout << "No key has been initialized" << std::endl;
		return false;
	}
	uint8_t block[16];
	if (len == 0 && inBuff > 0)
	{
		if (DEBUG) std::cout << "flushing buffers and decrypting." << std::endl;
		buff.read((char *)block, BUFF_SIZE);
		mdecrypt_generic(td, block, BLOCK_SIZE);
		buffLen = block[15];
		m_decryptCallback(block, buffLen);
		return true;
	}
	buff.write((char *)data, len);
	inBuff += len;
	
	while (inBuff >= BLOCK_SIZE)
	{
		buff.read((char *)block, BLOCK_SIZE);
		mdecrypt_generic(td, block, BLOCK_SIZE);
		inBuff -= BLOCK_SIZE;
		m_decryptCallback(block, block[15]);	
	}
	

	return true;
}

CryptoAES::~CryptoAES()
{
	mcrypt_generic_deinit (td);
	mcrypt_module_close(td);
}
