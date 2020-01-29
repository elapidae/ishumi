#include "ii_x25519.h"


ii_x25519 ii_x25519::generate()
{
    CryptoPP::AutoSeededRandomPool rng;
    return ii_x25519( rng );
}

ii_x25519::ii_x25519( CryptoPP::AutoSeededRandomPool &p )
    : x( p )
{}
