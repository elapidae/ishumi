#ifndef II_X25519_H
#define II_X25519_H

#include "cryptopp/xed25519.h"
#include "cryptopp/osrng.h"


class ii_x25519
{
public:
    static ii_x25519 generate();

private:
    ii_x25519( CryptoPP::AutoSeededRandomPool& p );
    CryptoPP::x25519 x;
};

#endif // II_X25519_H
