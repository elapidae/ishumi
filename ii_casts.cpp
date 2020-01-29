#include "ii_casts.h"


using namespace ii;

template <typename Res, typename From >
static Res* cc( From* f )
{
    return static_cast<Res*>( static_cast<void*>(f) );
}

template <typename Res, typename From >
static const Res* c_cc( const From* f )
{
    return static_cast<const Res*>( static_cast<const void*>(f) );
}


uint8_t *ii::cast::u8( char *d )
{
    return cc<uint8_t>( d );
}

const uint8_t* cast::u8( const char* d )
{
    return c_cc<uint8_t>( d );
}

uint8_t *cast::mut_u8(const char *d)
{
    return const_cast<uint8_t*>( c_cc<uint8_t>(d) );
}
