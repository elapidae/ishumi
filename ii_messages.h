#ifndef II_MESSAGES_H
#define II_MESSAGES_H

#include "s11n.h"

//=======================================================================================

namespace ii
{
    //-----------------------------------------------------------------------------------
    struct GeneralBody_1
    {
        std::string nonce_heap;

        uint64_t    alice;
        uint64_t    bob;

        uint32_t    aim;

        std::string data;

        std::string nonce_tail;

        template<typename T>
        void encode( const T& val );
    };
    //-----------------------------------------------------------------------------------
    struct GeneralMessage_0
    {
        uint64_t    sid;
        std::string data;
        uint32_t    crc;

        void fill( const GeneralBody_1& body );
    };
    //-----------------------------------------------------------------------------------
    struct Msg_Ping_2
    {
        uint32_t id;
    };
    //-----------------------------------------------------------------------------------
    struct Msg_Pong_3
    {
        uint32_t id;
    };
    //-----------------------------------------------------------------------------------
} // namespace ii
//=======================================================================================

template<>
struct s11n::Serial<ii::GeneralMessage_0>
{
    static auto to_tuple( const ii::GeneralMessage_0& msg )
    {
        return std::make_tuple( msg.sid, msg.data, msg.crc );
    }
};

//=======================================================================================

template<>
struct s11n::Serial<ii::GeneralBody_1>
{
    static auto to_tuple( const ii::GeneralBody_1& msg )
    {
        return std::make_tuple( msg.nonce_heap,
                                msg.alice,
                                msg.bob,
                                msg.aim,
                                msg.data,
                                msg.nonce_tail
                              );
    }
};

//=======================================================================================

template<>
struct s11n::Serial<ii::Msg_Ping_2>
{
    static auto to_tuple( const ii::Msg_Ping_2& msg )
    {
        return std::make_tuple( msg.id );
    }
};

//=======================================================================================

template<>
struct s11n::Serial<ii::Msg_Pong_3>
{
    static auto to_tuple( const ii::Msg_Pong_3& msg )
    {
        return std::make_tuple( msg.id );
    }
};

//=======================================================================================

namespace ii
{
    template<typename T>
    void GeneralBody_1::encode( const T& val )
    {
        data = s11n::encode( val );
        aim  = s11n::signature_crc<T>();
        //fill nonces.
    }
}



#endif // II_MESSAGES_H
