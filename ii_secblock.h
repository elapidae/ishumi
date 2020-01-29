#ifndef II_SECBLOCK_H
#define II_SECBLOCK_H

#include "cryptopp/secblock.h"

class ii_secbyteblock
{
public:

    CryptoPP::SecByteBlock& block();

private:
    CryptoPP::SecByteBlock _block;
};


#endif // II_SECBLOCK_H
