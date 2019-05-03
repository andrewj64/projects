#include "Crypto.hpp"
#include <iostream>
#include "CryptoCaesar.hpp"
#include "CryptoNone.hpp"
#include <string>
#include <sstream>


int main()
{
	std::ostringstream ctOss;
	std::ostringstream ptOss;

	std::function<void(const uint8_t *data, uint32_t len)> ctFunc = [&ctOss](const uint8_t *buf, uint32_t len) {
		ctOss.write((char *)buf, len);
	};
	std::function<void(const uint8_t *data, uint32_t len)> ptFunc = [&ptOss](const uint8_t *buf, uint32_t len) {
	
		ptOss.write((char *)buf, len);
	};

	// AES test
	ctOss.str("");
	ptOss.str("");
	auto pCrypto = Crypto::cryptoFactory(ctFunc, ptFunc, Algorithm::eAES);
	pCrypto->genKeys();
	std::string test = "Testing AES transform\n";
	pCrypto->encrypt((uint8_t *)test.c_str(), test.size());
	pCrypto->encrypt(nullptr, 0);
	std::cout << "CT:" << ctOss.str() << std::endl;
	pCrypto ->decrypt((uint8_t *)(ctOss.str().c_str()), ctOss.str().size());
	std::cout << "PT: " << ptOss.str() << std::endl;
	
	/*//None test
	ctOss.str("");
	ptOss.str("");
	auto pCrypto = Crypto::cryptoFactory(ctFunc, ptFunc, Algorithm::eNONE);
	pCrypto->genKeys();
	std::string test = "Testing NONE transform\n";
	pCrypto->encrypt((uint8_t *)test.c_str(), test.size());
	pCrypto->encrypt(nullptr, 0);
	std::cout << "CT:" << ctOss.str() << std::endl;
	pCrypto ->decrypt((uint8_t *)(ctOss.str().c_str()), ctOss.str().size());
	std::cout << "PT: " << ptOss.str() << std::endl;

	//Caesar test
	ctOss.str("");
	ptOss.str("");
	pCrypto = Crypto::cryptoFactory(ctFunc, ptFunc, Algorithm::eCAESAR);
	pCrypto->genKeys();
	test = "Testing CAESAR transform\n";
	pCrypto->encrypt((uint8_t *)test.c_str(), test.size());
	std::cout << "CT: " << ctOss.str() << std::endl;
	//pCrypto->encrypt(nullptr, 0);
	pCrypto->decrypt((uint8_t *)(ctOss.str().c_str()), ctOss.str().size());
	std::cout << "PT: " << ptOss.str() << std::endl;
	std::cin.ignore();
	*/
	return 0;
}

