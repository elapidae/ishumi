#include "ii_messages.h"

using namespace ii;

void ii::GeneralMessage_0::fill( const ii::GeneralBody_1& body )
{
    data = s11n::encode( body );
}
