#ifndef II_CASTS_H
#define II_CASTS_H

#include <stdint.h>

namespace ii
{
    class cast
    {
    public:
        static uint8_t* u8( char * d );

        static const uint8_t* u8( const char * d );

        static uint8_t* mut_u8( const char * d );
    };

}


#endif // II_CASTS_H
