#ifndef CRYPTO_AES_HPP
#define CRYPTO_AES_HPP

#include"Crypto.hpp"
#include<iostream>
#include <mcrypt.h>
#include <sstream>

class CryptoAES : public Crypto
{
public:
	CryptoAES(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
                 std::function<void(const uint8_t *data, uint32_t len)> decryptCallback);
	~CryptoAES();
	void genKeys();
	bool getKeys(uint8_t **pubKey, uint32_t &pubLen,
                 uint8_t **priKey, uint32_t &priLen);
	void setKeys(const uint8_t *pubKey, uint32_t pubLen,
                 const uint8_t *priKey, uint32_t priLen);
	void destroyKeys();
	bool encrypt(const uint8_t *data, uint32_t len);
	bool decrypt(const uint8_t *data, uint32_t len);
	
protected:
	uint8_t * key;
	const uint32_t keyLen = 16;
	bool keyGenerated = false;
	uint8_t * IV;
	const uint32_t IVLen = 16;
	std::stringstream buff;
	uint32_t buffLen;
	uint32_t inBuff = 0;
	MCRYPT td;
};

#endif
