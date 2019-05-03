#ifndef CRYPTO_NONE_HPP
#define CRYPTO_NONE_HPP

#include"Crypto.hpp"

class CryptoNone : public Crypto
{
public:
	CryptoNone(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
		       std::function<void(const uint8_t *data, uint32_t len)> decryptCallback);
	void genKeys();
	bool getKeys(uint8_t **pubKey, uint32_t &pubLen, 
				 uint8_t **priKey, uint32_t &priLen);
	void setKeys(const uint8_t *pubKey, uint32_t pubLen,
				 const uint8_t *priKey, uint32_t priLen);
	void destroyKeys();
	bool encrypt(const uint8_t *data, uint32_t len);
	bool decrypt(const uint8_t *data, uint32_t len);
};

#endif
