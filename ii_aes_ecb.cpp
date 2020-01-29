#include "ii_aes_ecb.h"

#include <iostream>

#include "cryptopp/osrng.h"
#include "cryptopp/ccm.h"
#include "cryptopp/hex.h"

#include "vlog.h"
#include "ii_casts.h"

using namespace CryptoPP;
using namespace std;
using namespace ii;


//=======================================================================================
ii_aes_ecb::ii_aes_ecb( const SecByteBlock& key )
{
    assert( key.size() == AES::DEFAULT_KEYLENGTH );
    enc.SetKey( key, key.size() );
    dec.SetKey( key, key.size() );
}
//=======================================================================================
std::string ii_aes_ecb::encode( const string& msg )
{
    assert( 0 == msg.size() % AES::DEFAULT_KEYLENGTH );

    std::string res;
    res.resize( msg.size() );

    enc.ProcessData( cast::mut_u8(res.data()), cast::u8(msg.data()), msg.size() );
    //dec.ProcessLastBlock()

    return res;
}
//=======================================================================================
string ii_aes_ecb::decode( const string& msg )
{
    assert( 0 == msg.size() % AES::DEFAULT_KEYLENGTH );

    std::string res;
    res.resize( msg.size() );

    dec.ProcessData( cast::mut_u8(res.data()), cast::u8(msg.data()), msg.size() );

    return res;
}
//=======================================================================================
ii_aes_ecb::ii_aes_ecb()
{
    AutoSeededRandomPool prng;

    SecByteBlock key( AES::DEFAULT_KEYLENGTH );
    prng.GenerateBlock( key, key.size() );

    enc.SetKey( key, key.size() );
    dec.SetKey( key, key.size() );
}
//=======================================================================================

/*
    AutoSeededRandomPool prng;

    SecByteBlock key(AES::DEFAULT_KEYLENGTH);
    prng.GenerateBlock( key, key.size() );

    string plain = "ECB Mode Test";
    string cipher, encoded, recovered;


    try
    {
        cout << "plain text: " << plain << endl;

        ECB_Mode< AES >::Encryption e;
        e.SetKey( key, key.size() );

        // The StreamTransformationFilter adds padding
        //  as required. ECB and CBC Mode must be padded
        //  to the block size of the cipher.
        StringSource ss1( plain, true,
            new StreamTransformationFilter( e,
                new StringSink( cipher )
            ) // StreamTransformationFilter
        ); // StringSource
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }


    // Pretty print cipher text
    StringSource ss2( cipher, true,
        new HexEncoder(
            new StringSink( encoded )
        ) // HexEncoder
    ); // StringSource
    cout << "cipher text: " << encoded << endl;


    try
    {
        ECB_Mode< AES >::Decryption d;
        // ECB Mode does not use an IV
        d.SetKey( key, key.size() );

        // The StreamTransformationFilter removes
        //  padding as required.
        StringSource ss3( cipher, true,
            new StreamTransformationFilter( d,
                new StringSink( recovered )
            ) // StreamTransformationFilter
        ); // StringSource

        cout << "recovered text: " << recovered << endl;
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << e.what() << endl;
        exit(1);
    }
    vdeb << "Recovered original message" << recovered;
*/
