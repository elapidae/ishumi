
#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include "cryptlib.h"
using CryptoPP::Exception;

#include "hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include "filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include "aes.h"
using CryptoPP::AES;

#include "modes.h"
using CryptoPP::ECB_Mode;

#include "ii_aes_ecb.h"

using namespace CryptoPP;

#include "vlog.h"
#include "vbyte_buffer.h"

int main(int argc, char* argv[])
{
    SecByteBlock key( ii_aes_ecb::block_size );
    key.Assign( (u_char*)"0123456789abcdef", 16 );

    ii_aes_ecb e( key );
    auto ch = e.encode("0123456789abcdef");
    vdeb << vbyte_buffer(ch).to_hex();
    vdeb << e.encode(ch).size();
    vdeb << e.decode(ch);
    return 0;
}

/*
#include "mainwindow.h"


#include <QApplication>

#include "vlog.h"
#include "cryptopp/rsa.h"
#include "cryptopp/base64.h"
#include <QFile>
#include "cryptopp/osrng.h"
#include "cryptopp/dsa.h"
#include <QCryptographicHash>


#include <iostream>
#include <stdexcept>
#include <string>

#include "cryptopp/cryptlib.h"
#include "cryptopp/xed25519.h"
#include "cryptopp/filters.h"
#include "cryptopp/osrng.h"
#include "cryptopp/files.h"
#include "cryptopp/hex.h"
#include "cryptopp/sha3.h"

#include "vbyte_buffer.h"
#include "ii_sha3_256.h"
#include "ii_aes_ecb.h"


using namespace CryptoPP;


int main( int argc, char* argv[] )
{
    AutoSeededRandomPool rndA, rndB;
    SecByteBlock key( ii_aes_ecb::block_size );
    key.Assign( (uchar*)"0123456789abcdef", 16 );

    ii_aes_ecb e( key );
    auto ch = e.encode("0123456789abcdef");
    ch = e.encode("0123456789abcdef");
    auto ch2 = e.encode(ch);
    vdeb << vbyte_buffer(ch).to_hex();
    vdeb << e.decode(ch2);
    vdeb << e.encode(ch).size();

    return 0;

//    AutoSeededRandomPool rndA, rndB;
    x25519 ecdhA(rndA), ecdhB(rndB);

    std::string rr;
    StringSink sink( rr );

   // ed25519 ed;
   // ed.
    //BufferedTransformation bt;
    //ecdhA.DEREncode( rr );
    //////////////////////////////////////////////////////////////

    SecByteBlock privA( ecdhA.PrivateKeyLength() );
    SecByteBlock pubA( ecdhA.PublicKeyLength() );
    ecdhA.GenerateKeyPair( rndA, privA, pubA );

    SecByteBlock privB( ecdhB.PrivateKeyLength() );
    SecByteBlock pubB( ecdhB.PublicKeyLength() );
    ecdhB.GenerateKeyPair( rndB, privB, pubB );

    //////////////////////////////////////////////////////////////

    SecByteBlock sharedA(ecdhA.AgreedValueLength());
    SecByteBlock sharedB(ecdhB.AgreedValueLength());

    if(ecdhA.AgreedValueLength() != ecdhB.AgreedValueLength())
        throw std::runtime_error("Shared secret size mismatch");

    if(!ecdhA.Agree(sharedA, privA, pubB))
        throw std::runtime_error("Failed to reach shared secret (1)");

    if(!ecdhB.Agree(sharedB, privB, pubA))
        throw std::runtime_error("Failed to reach shared secret (2)");

    size_t len = std::min(ecdhA.AgreedValueLength(), ecdhB.AgreedValueLength());
    if(!len || !VerifyBufsEqual(sharedA.BytePtr(), sharedB.BytePtr(), len))
        throw std::runtime_error("Failed to reach shared secret (3)");

    //////////////////////////////////////////////////////////////

    HexEncoder encoder(new FileSink(std::cout));

    std::cout << "Shared secret (A): ";
    StringSource(sharedA, sharedA.size(), true, new Redirector(encoder));
    std::cout << std::endl;

    std::cout << "Shared secret (B): ";
    StringSource(sharedB, sharedB.size(), true, new Redirector(encoder));
    std::cout << std::endl;

    return 0;
}

/*
//  https://www.cryptopp.com/wiki/Base64Decoder
//  https://www.cryptopp.com/wiki/Elliptic_curve_diffie-hellman
//  AES
//  http://www.cyberforum.ru/cpp-beginners/thread1300736.html

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <stdexcept>
using std::runtime_error;

#include <cstdlib>
using std::exit;

#include "cryptopp/osrng.h"
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::AutoSeededX917RNG;

#include "cryptopp/aes.h"
using CryptoPP::AES;

#include "cryptopp/eccrypto.h"
using CryptoPP::ECP;
using CryptoPP::ECDH;

#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

#include "cryptopp/oids.h"
using CryptoPP::OID;

// ASN1 is a namespace, not an object
#include "cryptopp/asn.h"
using namespace CryptoPP::ASN1;

#include "cryptopp/integer.h"
using CryptoPP::Integer;

#include "cryptopp/xed25519.h"
using namespace CryptoPP;

#include "cryptopp/cryptlib.h"
#include "cryptopp/xed25519.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"
#include "cryptopp/osrng.h"
#include "cryptopp/hex.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <exception>

#define USE_PIPELINE 1

int main (int argc, char* argv[])
{
    using namespace CryptoPP;

    AutoSeededRandomPool prng;

    x25519 x(prng);
    x.Agree()


    HexEncoder encoder(new FileSink(std::cout));

    //FileSource fs1("private.key.bin", true);
    //FileSource fs1("private.key.bin", true);
    ed25519::Signer signer(prng);
    //signer.AccessPrivateKey().GenerateRandom(prng);

    bool valid = signer.GetPrivateKey().Validate(prng, 3);
    if (valid == false)
        throw std::runtime_error("Invalid private key");

    //FileSource fs2("public.key.bin", true);
    ed25519::Verifier verifier(signer);
    //verifier.AccessPublicKey() =


    valid = verifier.GetPublicKey().Validate(prng, 3);
    if (valid == false)
        throw std::runtime_error("Invalid private key");

    std::cout << "Keys are valid\n" << std::endl;

    ////////////////////////////////////////////////////////////

    std::string message = "Yoda said, Do or do not. There is no try.";
    std::string signature;

#if USE_PIPELINE
    StringSource(message, true, new SignerFilter(NullRNG(), signer, new StringSink(signature)));
#else
    // Determine maximum size, allocate a string with the maximum size
    size_t siglen = signer.MaxSignatureLength();
    signature.resize(siglen);

    // Sign, and trim signature to actual size
    siglen = signer.SignMessage(NullRNG(), (const byte*)&message[0], message.size(),
                                (byte*)&signature[0]);
    signature.resize(siglen);
#endif

    std::cout << "Signature: ";
    StringSource(signature, true, new Redirector(encoder));
    std::cout << "\n" << std::endl;

    ////////////////////////////////////////////////////////////

#if USE_PIPELINE
    StringSource(signature+message, true, new SignatureVerificationFilter(verifier,
                 new ArraySink((byte*)&valid, sizeof(valid))));
#else
    valid = verifier.VerifyMessage((const byte*)&message[0], message.size(),
                                   (const byte*)&signature[0], signature.size());
#endif

    if (valid == false)
        throw std::runtime_error("Invalid signature over message");

    std::cout << "Verified signature over message\n" << std::endl;

    return 0;
}

int main1( int, char** )
{

    //ed25519::Verifier verifier(signer);

//    const ed25519PublicKey& pubKey = dynamic_cast<const ed25519PublicKey&>(verifier.GetPublicKey());
//    const Integer& y = pubKey.GetPublicElement();
//    std::cout << std::hex << y << std::endl;
    OID CURVE = secp256r1();
    //OID CURVE = x25519();
    AutoSeededX917RNG<AES> rng;
    ECDH < ECP >::Domain dhA( CURVE ), dhB( CURVE );

    // Don't worry about point compression. Its amazing that Certicom got
    // a patent for solving an algebraic equation....
    // dhA.AccessGroupParameters().SetPointCompression(true);
    // dhB.AccessGroupParameters().SetPointCompression(true);

    SecByteBlock privA(dhA.PrivateKeyLength()), pubA(dhA.PublicKeyLength());
    SecByteBlock privB(dhB.PrivateKeyLength()), pubB(dhB.PublicKeyLength());

    dhA.GenerateKeyPair(rng, privA, pubA);
    dhB.GenerateKeyPair(rng, privB, pubB);

    if(dhA.AgreedValueLength() != dhB.AgreedValueLength())
    throw runtime_error("Shared secret size mismatch");

    SecByteBlock sharedA(dhA.AgreedValueLength()), sharedB(dhB.AgreedValueLength());

    const bool rtn1 = dhA.Agree(sharedA, privA, pubB);
    const bool rtn2 = dhB.Agree(sharedB, privB, pubA);
    if(!rtn1 || !rtn2)
    throw runtime_error("Failed to reach shared secret (A)");

    const bool rtn3 = sharedA.size() == sharedB.size();
    if(!rtn3)
    throw runtime_error("Failed to reach shared secret (B)");

    Integer a, b;

    a.Decode(sharedA.BytePtr(), sharedA.SizeInBytes());
    cout << "(A): " << std::hex << a << endl;

    b.Decode(sharedB.BytePtr(), sharedB.SizeInBytes());
    cout << "(B): " << std::hex << b << endl;

    const bool rtn4 = a == b;
    if(!rtn4)
    throw runtime_error("Failed to reach shared secret (C)");

    cout << "Agreed to shared secret" << endl;

    return 0;
}

/*

using namespace CryptoPP;
using namespace std;

int main( int argc, char *argv[] )
{

    ///////////////////////////////////////
    // Pseudo Random Number Generator
    AutoSeededRandomPool rng;

    ///////////////////////////////////////
    // Generate Parameters
    InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 3072);

    ///////////////////////////////////////
    // Generated Parameters
    const Integer& n = params.GetModulus();
    const Integer& p = params.GetPrime1();
    const Integer& q = params.GetPrime2();
    const Integer& d = params.GetPrivateExponent();
    const Integer& e = params.GetPublicExponent();

    ///////////////////////////////////////
    // Dump
    vdeb << "RSA Parameters:";
    vdeb << " n: " << n;
    vdeb << " p: " << p;
    vdeb << " q: " << q;
    vdeb << " d: " << d;
    vdeb << " e: " << e;


    ///////////////////////////////////////
    // Create Keys
    RSA::PrivateKey privateKey(params);
    RSA::PublicKey publicKey(params);

    return 0;

    QApplication app( argc,argv );

    QFile f( "/home/el/.ssh/id_rsa.pub" );
    Q_ASSERT( f.open(QIODevice::ReadOnly) );
    auto data = f.readAll();
    auto code = data.split(' ');

    vdeb << data;



    string encoded = "/+7dzLuqmYh3ZlVEMyIRAA==";
    string decoded;

    Base64Decoder decoder;
    decoder.Put( (byte*)encoded.data(), encoded.size() );
    decoder.MessageEnd();

    word64 size = decoder.MaxRetrievable();
    if(size && size <= SIZE_MAX)
    {
        decoded.resize(size);
        decoder.Get((byte*)&decoded[0], decoded.size());
    }
}
*/
