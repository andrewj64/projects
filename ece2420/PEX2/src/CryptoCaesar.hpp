#ifndef CRYPTO_CAESAR_HPP
#define CRYPTO_CAESAR_HPP

#include"Crypto.hpp"

class CryptoCaesar : public Crypto
{
public:
	CryptoCaesar(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
                 std::function<void(const uint8_t *data, uint32_t len)> decryptCallback);
	void genKeys();
	bool getKeys(uint8_t **pubKey, uint32_t &pubLen,
                 uint8_t **priKey, uint32_t &priLen);
	void setKeys(const uint8_t *pubKey, uint32_t pubLen,
                 const uint8_t *priKey, uint32_t priLen);
	void destroyKeys();
	bool encrypt(const uint8_t *data, uint32_t len);
	bool decrypt(const uint8_t *data, uint32_t len);
	uint8_t k;
	uint8_t * key;
	uint32_t length = 0;
	uint8_t * data;
};

#endif
