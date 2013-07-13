TEMPLATE    = lib
CONFIG     += c++11 staticlib build_all
CONFIG     -= app_bundle qt
TARGET      = $$qtLibraryTarget(calibri)
DESTDIR     = lib

CONFIG(debug, debug|release) {
    DEFINES        += \
        DEBUG

    OBJECTS_DIR     = obj/debug
} else {
    OBJECTS_DIR     = obj/release
}

HEADERS    += \
    cdatastream.h \
    cdefines.h

include(ctcpserver/ctcpserver.pri)
include(csocket/csocket.pri)
include(ceventdispatcher/ceventdispatcher.pri)
include(cssl/cssl.pri)
include(ccrypto/ccrypto.pri)
include(csettings/csettings.pri)
include(cdatetime/cdatetime.pri)
include(cuniqueid/cuniqueid.pri)
include(cfilesystem/cfilesystem.pri)
include(cutils/cutils.pri)
include(celapsedtimer/celapsedtimer.pri)

win32 {
    DEFINES        += \
        NOMINMAX

    INCLUDEPATH    += \
        c:/openssl/include \
        c:/libevent/WIN32-Code \
        c:/libevent/include

    LIBS           += \
        -lWs2_32 \
        -lAdvapi32 \
        -lShell32 \
        -lRpcrt4 \
        -lKernel32 \
        -Lc:/openssl/lib/vc -llibeay32MD \
        -Lc:/openssl/lib/vc -lssleay32MD \
        -Lc:/libevent -llibevent_core \
        -Lc:/libevent -llibevent_extras \
        -Lc:/libevent -llibevent_openssl
} else:unix {
    CONFIG         += \
        create_pc \
        create_prl

    LIBS           += \
        -luuid \
        -levent_core \
        -levent_extra \
        -levent_openssl \
        -lcrypto \
        -lssl

    target.path     = /usr/lib/calibri
    headers.path    = /usr/include/calibri
    headers.files   = include/calibri/*.h

    QMAKE_PKGCONFIG_NAME            = calibri
    QMAKE_PKGCONFIG_DESCRIPTION     = "Calibri Library"
    QMAKE_PKGCONFIG_LIBDIR          = $$target.path
    QMAKE_PKGCONFIG_INCDIR          = $$headers.path
    QMAKE_PKGCONFIG_DESTDIR         = pkgconfig

    INSTALLS       += \
        target \
        headers

    QMAKE_CXXFLAGS_RELEASE     += \
        -O3 \
        -march=native \
        -mtune=native \
        -funroll-loops
}
