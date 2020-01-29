#include "ii_nonces.h"

#include "cryptopp/osrng.h"

static thread_local CryptoPP::AutoSeededRandomPool rng;


static std::string rand_str( size_t size )
{
    assert(size <= 8);
    char buf[8];
    auto b2 = static_cast<CryptoPP::byte*>( static_cast<void*>(buf) );
    rng.GenerateBlock( b2, size );

    return { buf, size };
}


//  От единицы до нужного количества
Head_Nonce::Head_Nonce()
    : data( rand_str(8) )
{
    uint8_t real_size = 1 + (data[0] & 0x07);
    data.resize( real_size );
}

Head_Nonce::Head_Nonce( const std::string& d )
    : data( d )
{}


void Tail_Nonce::generate( size_t cur_size )
{
    auto new_size = cur_size + padding_size;
    new_size /= padding_size;
    new_size *= padding_size;
    new_size -= crc_size;

    assert( new_size >= cur_size );

    auto sz = new_size - cur_size;
    if (sz == 0) sz = padding_size;

    data = rand_str( sz );
    auto corr_len = data[0];
    corr_len &= 0x0F;
}
