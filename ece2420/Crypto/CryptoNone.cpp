#include "CryptoNone.hpp"
#include <iostream>

CryptoNone::CryptoNone(std::function<void(const uint8_t*data, uint32_t len)> encryptCallback,
					   std::function<void(const uint8_t*data, uint32_t len)> decryptCallback)
: Crypto(encryptCallback, decryptCallback)
{
	std::cout << "Well, nothing to see here" << std::endl;
}

void CryptoNone::genKeys()
{

	std::cout << "Do some stuff" << std::endl;
}

bool CryptoNone::getKeys(uint8_t ** pubKey, uint32_t & pubLen, uint8_t ** priKey, uint32_t & priLen)
{
	std::cout << "You are using the CryptoNone method of encryption. There are no keys." << std::endl;
	return true;
}

void CryptoNone::setKeys(const uint8_t * pubKey, uint32_t pubLen, const uint8_t * priKey, uint32_t priLen)
{

}

void CryptoNone::destroyKeys()
{
}

bool CryptoNone::encrypt(const uint8_t * data, uint32_t len)
{
	// call the encrypt callback
	m_encryptCallback(data, len);
	return true;
}

bool CryptoNone::decrypt(const uint8_t * data, uint32_t len)
{
	// call the decrypt callback
	m_decryptCallback(data, len);
	return true;
}
