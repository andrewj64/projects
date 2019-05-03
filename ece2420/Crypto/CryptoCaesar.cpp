#include "CryptoCaesar.hpp"
#include <iostream>
#include <ctime>

CryptoCaesar::CryptoCaesar(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
                           std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
: Crypto(encryptCallback, decryptCallback)
{
}

void CryptoCaesar::genKeys()
{
	// Do some stuff to get a random number and shift the stuff

	std::srand(std::time(NULL));				// for some reason, key is always null after this function. shouldn't it initialize it in the class and stay there even when it is beyond the scope of this function?
	
	k = (uint8_t) (std::rand() % 256);
	key = &k;
	length = 1;
}

bool CryptoCaesar::getKeys(uint8_t ** pubKey, uint32_t & pubLen, uint8_t ** 
priKey, uint32_t & priLen)
{
	if (!key || !length)
	{
		std::cout << "No keys were generated!" << std::endl;
		return false;
	}
	else 
	{
		pubKey = &key;
		pubLen = length;
	}
	
	// set length!!!
	return true;
}

void CryptoCaesar::setKeys(const uint8_t * pubKey, uint32_t pubLen, const uint8_t * priKey, uint32_t priLen)
{
	key = (uint8_t *) pubKey;
	length = pubLen;
}

void CryptoCaesar::destroyKeys()
{
	key = NULL;
	length = 0;
}

bool CryptoCaesar::encrypt(const uint8_t * data, uint32_t len)
{
	uint8_t * edata = (uint8_t *) data;
	//std::default_random_engine generator;
	//std::uniform_int_distribution<int> distribution(1, sizeof((*data) - 1);
	//int rand = distribution(generator);
	// get random number
	// shift numbers + rand % len;
	if (key == NULL)
	{
		std::cout << "No key has been initialized" << std::endl;
		return false;
	}
	for (uint32_t i = 0; i < len; i++)			// Cycle through data and shift by amount specified by key
	{
		edata[i] += *key;		//because of wraparound logic of uin8_t, if statement is not needed	
		/*if (edata[i] > 255)
		{
			edata[i] -= 255;
		}*/
	}
	m_encryptCallback(edata, len);
	
	return true;
}

bool CryptoCaesar::decrypt(const uint8_t * data, uint32_t len)
{
	uint8_t * edata = (uint8_t *) data;
	if (key == NULL || !len)
	{
		std::cout << "No key has been initialized" << std::endl;
		return false;
	}
	for (uint32_t i = 0; i < len; i++)			// Cycle through data and shift by amount specified by key
	{
			edata[i] -= *key;
	}
	m_decryptCallback(edata, len);
	return true;
}
