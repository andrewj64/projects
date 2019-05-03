#include "Crypto.hpp"
#include "CryptoNone.hpp"
#include"CryptoCaesar.hpp"
#include <iostream>

/**
 * @brief Constructor
 *
 * This function creates/initializes this object.
 * The callbacks are used by the underlying
 * algorithm to pass back processed data to the using logic.
 *
 * NOTE: There is no correlation between the amount of data passed into the algorithm
 * and the amount returned from it.  Likewise, there is no required correlation between
 * the number of times data is passed into the algorithm and the number of times callbacks
 * are called.
 *
 * @param encryptCallback Callback function for returning encrypted data
 * @param decryptCallback Callback function for returning decrypted data
 */
Crypto::Crypto(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
               std::function<void(const uint8_t *data, uint32_t len)> decryptCallback)
{
	std::cout << "This should prolly do nothing" << std::endl;
	m_encryptCallback = encryptCallback;
	m_decryptCallback = decryptCallback;
}

/**
 * @brief Create a Crypto object using the correct transform
 *
 * @param encryptCallback Callback function for returning encrypted data
 * @param decryptCallback Callback function for returning decrypted data
 * @param algorithm Enum indicationg which transform should be used
 * @return shared_ptr to newly constructed heap object
 */
std::shared_ptr<Crypto> Crypto::cryptoFactory(std::function<void(const uint8_t *data, uint32_t len)> encryptCallback,
                                              std::function<void(const uint8_t *data, uint32_t len)> decryptCallback,
                                              Algorithm algorithm)
{
	if (algorithm == Algorithm::eNONE)
	{
		std::shared_ptr<Crypto> pNone(new CryptoNone(encryptCallback, decryptCallback));
		return pNone;
	}
	else if (algorithm == Algorithm::eCAESAR)
	{
		std::shared_ptr<Crypto> pCaesar(new CryptoCaesar(encryptCallback, decryptCallback));
		return pCaesar;
	}
	else
	{
		std::cout << "You done messed up A-Aron!" << std::endl;
		exit(1);
	}	
}
