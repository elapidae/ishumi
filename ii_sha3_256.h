#ifndef II_SHA3_256_H
#define II_SHA3_256_H

#include "cryptopp/sha3.h"


namespace ii
{
    class sha3_256
    {
    public:

        void update( const std::string& data );

        std::string final();

    private:
        CryptoPP::SHA3_256 sha;
    };
}

#endif // II_SHA3_256_H
