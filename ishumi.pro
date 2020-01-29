QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
#    casts.cpp \
    form_crypto_pri.cpp \
    ii_aes_ecb.cpp \
    ii_casts.cpp \
    ii_secblock.cpp \
    ii_sha3_256.cpp \
    ii_x25519.cpp \
    main.cpp \
    mainwindow.cpp \
    ii_nonces.cpp

HEADERS += \
#    casts.h \
    form_crypto_pri.h \
    ii_aes_ecb.h \
    ii_casts.h \
    ii_secblock.h \
    ii_sha3_256.h \
    ii_x25519.h \
    mainwindow.h \
    ii_nonces.h


FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CRYPTOPP_DIR = $$PWD/cryptopp
include( cryptopp/cryptopp.pri )


VLIBS_DIR = $$PWD/../../vlibs2
include( $$VLIBS_DIR/qmake/vlog.pri )
include( $$VLIBS_DIR/qmake/vbyte_buffer.pri )


S11N_DIR = $$PWD/../../s11n_dev
include( $$S11N_DIR/s11n.pri )
