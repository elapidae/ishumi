#ifndef FORM_CRYPTO_PRI_H
#define FORM_CRYPTO_PRI_H

#include <QString>
#include <QFile>
#include <QSet>
#include "vlog.h"

//=======================================================================================

bool omit_header( QString name )
{
    if ( name.contains("_simd") ) return true;
    if ( name.contains("_avx") ) return true;

    if ( name == "ariatab" ) return true;
    if ( name == "bfinit" ) return true;
    if ( name == "casts" ) return true;
    if ( name == "dessp" ) return true;
    if ( name == "kalynatab" ) return true;
    if ( name == "keccak_core" ) return true;
    if ( name == "marss" ) return true;
    if ( name == "rdtables" ) return true;
    if ( name == "squaretb" ) return true;
    if ( name == "sharkbox" ) return true;
    if ( name == "tigertab" ) return true;
    if ( name == "adhoc" ) return true;
    if ( name == "fipsalgt" ) return true;
    if ( name == "tftables" ) return true;
    if ( name == "" ) return true;
    if ( name == "" ) return true;

    return false;
}

//=======================================================================================

extern const char* compiles;

void form_crypto_pri()
{
    QString comp = compiles;

    auto lines = comp.split( "\n" );

    QSet<QString> cxx_flags;
    QString files;
    QString del_line = "g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe ";
    for ( auto l: lines )
    {
        if ( l.isEmpty() ) continue;

        if ( !l.startsWith(del_line) )throw verror;
        l.remove( 0, del_line.size() );

        if ( l.contains("adhoc") )   continue; // is test
        if ( l.contains("test") )    continue;
        if ( l.contains("validat") ) continue;
        if ( l.contains("bench") )   continue;

        auto args = l.split( ' ' );
        //vdeb << args << l;
        Q_ASSERT( args.size() > 1 );
        auto sname = args.takeLast();

        for (auto a:args)
            cxx_flags.insert( a );

        files += "    SOURCES     += $$CRYPTOPP_DIR/" + sname + "\n";
        sname.chop(4);

        if ( omit_header(sname) )
        {
            files += "\n";
            continue;
        }
        files += "    HEADERS     += $$CRYPTOPP_DIR/" + sname + ".h\n\n";
    }

    QFile f( "../ishumi/cryptopp/cryptopp.pri" );

    if ( !f.open(QIODevice::WriteOnly) ) throw verror;
    f.write( "\nisEmpty(qi_cryptopp) {\n    qi_cryptopp = 1\n\n"
             "    INCLUDEPATH += $$CRYPTOPP_DIR\n\n" );

    for (auto x: cxx_flags)
    {
        if (x == "-c") continue;
        f.write( "    QMAKE_CXXFLAGS += " );
        f.write( x.toLatin1() + "\n" );
    }
    f.write("\n\n");
    f.write( files.toLatin1() );
    f.write( "}\n" );
}

const char* compiles =
R"(
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cryptlib.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cpu.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c integer.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c 3way.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c adler32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c algebra.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c algparam.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c allocate.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c arc4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c aria.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c aria_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ariatab.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c asn.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c authenc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c base32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c base64.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c basecode.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bfinit.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c blake2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c blake2b_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c blake2s_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c blowfish.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c blumshub.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c camellia.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cast.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c casts.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cbcmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ccm.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c chacha.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mavx2 -c chacha_avx.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse2 -c chacha_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c chachapoly.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cham.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c cham_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c channels.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c crc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.2 -c crc_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c darn.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c default.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c des.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dessp.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dh.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dh2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dll.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c donna_32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c donna_64.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse2 -c donna_sse.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dsa.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c eax.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ec2n.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c eccrypto.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ecp.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c elgamal.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c emsa2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c eprecomp.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c esign.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c files.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c filters.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c fips140.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c fipstest.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gcm.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -mpclmul -c gcm_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gf256.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gf2_32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gf2n.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mpclmul -c gf2n_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gfpcrypt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gost.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gzip.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hc128.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hc256.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hex.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hight.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hrtimer.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ida.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c idea.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c iterhash.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c kalyna.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c kalynatab.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c keccak.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c keccak_core.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c keccak_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c lea.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c lea_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c luc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c mars.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c marss.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c md2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c md4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c md5.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c misc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c modes.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c mqueue.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c mqv.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c nbtheory.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c oaep.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c osrng.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c padlkrng.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c panama.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c pkcspad.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c poly1305.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c polynomi.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c pssr.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c pubkey.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c queue.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rabbit.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rabin.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c randpool.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rc2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rc5.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rc6.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rdrand.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rdtables.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rijndael.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -maes -c rijndael_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ripemd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rng.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rsa.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rw.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c safer.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c salsa.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c scrypt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c seal.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c seed.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c serpent.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sha.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sha3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.2 -msha -c sha_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c shacal2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.2 -msha -c shacal2_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c shake.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c shark.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sharkbox.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c simeck.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c simeck_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c simon.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c simon128_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c simon64_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c skipjack.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sm3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sm4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -maes -c sm4_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sosemanuk.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c speck.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c speck128_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c speck64_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c square.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c squaretb.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse2 -c sse_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c strciphr.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tea.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tftables.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c threefish.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tiger.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tigertab.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ttmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tweetnacl.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c twofish.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c vmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c wake.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c whrlpool.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xed25519.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xtr.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xtrcrypt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xts.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c zdeflate.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c zinflate.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c zlib.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c adhoc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c test.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bench1.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bench2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bench3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c datatest.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dlltest.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c fipsalgt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat0.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat1.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat5.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat6.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat7.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat8.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat9.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat10.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest1.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest4.cpp
)";


/*
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cryptlib.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cpu.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c integer.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c 3way.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c adler32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c algebra.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c algparam.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c allocate.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c arc4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c aria.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c aria_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ariatab.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c asn.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c authenc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c base32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c base64.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c basecode.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bfinit.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c blake2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c blake2b_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c blake2s_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c blowfish.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c blumshub.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c camellia.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cast.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c casts.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cbcmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ccm.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c chacha.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mavx2 -c chacha_avx.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse2 -c chacha_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c chachapoly.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cham.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c cham_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c channels.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c cmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c crc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.2 -c crc_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c darn.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c default.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c des.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dessp.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dh.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dh2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dll.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c donna_32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c donna_64.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse2 -c donna_sse.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dsa.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c eax.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ec2n.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c eccrypto.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ecp.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c elgamal.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c emsa2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c eprecomp.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c esign.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c files.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c filters.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c fips140.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c fipstest.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gcm.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -mpclmul -c gcm_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gf256.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gf2_32.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gf2n.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mpclmul -c gf2n_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gfpcrypt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gost.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c gzip.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hc128.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hc256.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hex.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hight.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c hrtimer.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ida.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c idea.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c iterhash.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c kalyna.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c kalynatab.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c keccak.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c keccak_core.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c keccak_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c lea.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c lea_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c luc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c mars.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c marss.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c md2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c md4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c md5.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c misc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c modes.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c mqueue.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c mqv.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c nbtheory.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c oaep.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c osrng.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c padlkrng.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c panama.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c pkcspad.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c poly1305.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c polynomi.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c pssr.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c pubkey.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c queue.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rabbit.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rabin.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c randpool.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rc2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rc5.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rc6.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rdrand.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rdtables.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rijndael.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -maes -c rijndael_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ripemd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rng.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rsa.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c rw.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c safer.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c salsa.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c scrypt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c seal.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c seed.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c serpent.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sha.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sha3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.2 -msha -c sha_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c shacal2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.2 -msha -c shacal2_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c shake.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c shark.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sharkbox.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c simeck.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c simeck_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c simon.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c simon128_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c simon64_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c skipjack.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sm3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sm4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -maes -c sm4_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c sosemanuk.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c speck.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -mssse3 -c speck128_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse4.1 -c speck64_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c square.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c squaretb.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -msse2 -c sse_simd.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c strciphr.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tea.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tftables.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c threefish.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tiger.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tigertab.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c ttmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c tweetnacl.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c twofish.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c vmac.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c wake.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c whrlpool.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xed25519.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xtr.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xtrcrypt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c xts.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c zdeflate.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c zinflate.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c zlib.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c adhoc.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c test.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bench1.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bench2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c bench3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c datatest.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c dlltest.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c fipsalgt.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat0.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat1.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat4.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat5.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat6.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat7.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat8.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat9.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c validat10.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest1.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest2.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest3.cpp
g++ -DNDEBUG -g2 -O3 -fPIC -pthread -pipe -c regtest4.cpp
ar r libcryptopp.a cryptlib.o cpu.o integer.o 3way.o adler32.o algebra.o algparam.o allocate.o arc4.o aria.o aria_simd.o ariatab.o asn.o authenc.o base32.o base64.o basecode.o bfinit.o blake2.o blake2b_simd.o blake2s_simd.o blowfish.o blumshub.o camellia.o cast.o casts.o cbcmac.o ccm.o chacha.o chacha_avx.o chacha_simd.o chachapoly.o cham.o cham_simd.o channels.o cmac.o crc.o crc_simd.o darn.o default.o des.o dessp.o dh.o dh2.o dll.o donna_32.o donna_64.o donna_sse.o dsa.o eax.o ec2n.o eccrypto.o ecp.o elgamal.o emsa2.o eprecomp.o esign.o files.o filters.o fips140.o fipstest.o gcm.o gcm_simd.o gf256.o gf2_32.o gf2n.o gf2n_simd.o gfpcrypt.o gost.o gzip.o hc128.o hc256.o hex.o hight.o hmac.o hrtimer.o ida.o idea.o iterhash.o kalyna.o kalynatab.o keccak.o keccak_core.o keccak_simd.o lea.o lea_simd.o luc.o mars.o marss.o md2.o md4.o md5.o misc.o modes.o mqueue.o mqv.o nbtheory.o oaep.o osrng.o padlkrng.o panama.o pkcspad.o poly1305.o polynomi.o pssr.o pubkey.o queue.o rabbit.o rabin.o randpool.o rc2.o rc5.o rc6.o rdrand.o rdtables.o rijndael.o rijndael_simd.o ripemd.o rng.o rsa.o rw.o safer.o salsa.o scrypt.o seal.o seed.o serpent.o sha.o sha3.o sha_simd.o shacal2.o shacal2_simd.o shake.o shark.o sharkbox.o simeck.o simeck_simd.o simon.o simon128_simd.o simon64_simd.o skipjack.o sm3.o sm4.o sm4_simd.o sosemanuk.o speck.o speck128_simd.o speck64_simd.o square.o squaretb.o sse_simd.o strciphr.o tea.o tftables.o threefish.o tiger.o tigertab.o ttmac.o tweetnacl.o twofish.o vmac.o wake.o whrlpool.o xed25519.o xtr.o xtrcrypt.o xts.o zdeflate.o zinflate.o zlib.o
ar: creating libcryptopp.a
ranlib libcryptopp.a
g++ -o cryptest.exe -DNDEBUG -g2 -O3 -fPIC -pthread -pipe adhoc.o test.o bench1.o bench2.o bench3.o datatest.o dlltest.o fipsalgt.o validat0.o validat1.o validat2.o validat3.o validat4.o validat5.o validat6.o validat7.o validat8.o validat9.o validat10.o regtest1.o regtest2.o regtest3.o regtest4.o ./libcryptopp.a
*/

#endif // FORM_CRYPTO_PRI_H
