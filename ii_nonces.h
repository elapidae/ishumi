#ifndef II_NONCES_H
#define II_NONCES_H

#include <vector>

#include "s11n.h"
#include "ii_aes_ecb.h"


class Head_Nonce
{
public:
    Head_Nonce();
    Head_Nonce( const std::string& d );

    std::string data;
};


class Tail_Nonce
{
public:
    enum { padding_size = ii_aes_ecb::block_size, crc_size = 4 };

    //  Сделает хвост такой длины, чтобы после добавления crc размер был
    //  кратным padding_size;
    void generate( size_t cur_size );

    std::string data;
};


template<>
struct s11n::Serial<Head_Nonce>
{
    //static constexpr auto name_of_type = "std::string";

    static void write( const Head_Nonce& n, impl_s11n::Writer* writer )
    {
        using namespace s11n::impl_s11n;
        writer->write_str( n.data );
    }

    static Head_Nonce read( impl_s11n::Reader* reader )
    {
        using namespace s11n::impl_s11n;
        auto first_byte = decode<uint8_t>( reader );
        size_t sz = (first_byte & 0x07);
        return reader->read_str( sz );
    }
};



template<>
struct s11n::Serial<Tail_Nonce>
{
    //static constexpr auto name_of_type = "std::string";

    static void write( const Tail_Nonce& n, impl_s11n::Writer* writer )
    {
        using namespace s11n::impl_s11n;
        writer->write_str( n.data );
    }

    static Tail_Nonce read( impl_s11n::Reader* reader )
    {
        using namespace s11n::impl_s11n;
        auto first_byte = decode<uint8_t>( reader );
        size_t sz = (first_byte & 0x07);
        //return reader->read_str( sz );
    }
};

#endif // II_NONCES_H
