#ifndef II_AES_ECB_H
#define II_AES_ECB_H


#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
//#include "cryptopp/ec

class ii_aes_ecb
{
public:
    enum { block_size = CryptoPP::AES::DEFAULT_KEYLENGTH };

    ii_aes_ecb();
    ii_aes_ecb( const CryptoPP::SecByteBlock& key );

    std::string encode( const std::string& msg );
    std::string decode( const std::string& msg );

private:
    CryptoPP::ECB_Mode<CryptoPP::AES>::Encryption enc;
    CryptoPP::ECB_Mode<CryptoPP::AES>::Decryption dec;
};

#endif // II_AES_ECB_H
