#include "ii_sha3_256.h"

#include "ii_casts.h"


//=======================================================================================
void ii::sha3_256::update( const std::string& msg )
{
    if ( msg.empty() ) return;
    sha.Update( cast::u8(msg.data()), msg.size() );
}
//=======================================================================================
std::string ii::sha3_256::final()
{
    std::string res;

    res.resize( sha.DigestSize() );

    sha.Final( cast::mut_u8(res.data()) );

    return res;
}
//=======================================================================================
