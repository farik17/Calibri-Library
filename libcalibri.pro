TEMPLATE    = lib
CONFIG     += c++11 staticlib
CONFIG     -= app_bundle qt
TARGET      = calibri
DESTDIR     = lib

OBJECTS_DIR = obj

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

win32 {
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
    headers.files  += \
        include/calibri/ceventdispatcher.h \
        include/calibri/ceventdispatcher_config.h \
        include/calibri/ceventdispatcher_types.h \
        include/calibri/ctcpserver.h \
        include/calibri/ctcpsocket.h \
        include/calibri/csslsocket.h \
        include/calibri/cssl.h \
        include/calibri/ccrypto.h \
        include/calibri/csettings.h \
        include/calibri/cdatetime.h \
        include/calibri/cuniqueid.h \
        include/calibri/cfilesystem.h \
        include/calibri/cutils.h \
        include/calibri/cdatastream.h \
        include/calibri/cdefines.h

    QMAKE_PKGCONFIG_NAME            = calibri
    QMAKE_PKGCONFIG_DESCRIPTION     = "Calibri Library"
    QMAKE_PKGCONFIG_LIBDIR          = $$target.path
    QMAKE_PKGCONFIG_INCDIR          = $$headers.path
    QMAKE_PKGCONFIG_DESTDIR         = pkgconfig

    INSTALLS       += target headers

    QMAKE_CXXFLAGS_RELEASE     += \
        -O3 \
        -march=native \
        -mtune=native \
        -funroll-loops
}
