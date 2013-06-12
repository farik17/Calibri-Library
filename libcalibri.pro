TEMPLATE    = lib
CONFIG     += c++11 staticlib
CONFIG     -= app_bundle qt
TARGET      = calibri
DESTDIR     = lib

OBJECTS_DIR = obj

HEADERS    += \
    defines.h \
    datastream.h

include(tcpserver/tcpserver.pri)
include(socket/socket.pri)
include(eventdispatcher/eventdispatcher.pri)
include(ssl/ssl.pri)
include(crypto/crypto.pri)
include(settings/settings.pri)
include(datetime/datetime.pri)
include(uniqueid/uniqueid.pri)
include(filesystem/filesystem.pri)
include(utils/utils.pri)

win32 {
    INCLUDEPATH += \
        C:/openssl/include \
        C:/libevent/WIN32-Code \
        C:/libevent/include

    LIBS    += \
        -lWs2_32 \
        -lAdvapi32 \
        -lShell32 \
        -lRpcrt4 \
        -lKernel32 \
        -LC:/openssl/lib/vc -llibeay32MD \
        -LC:/openssl/lib/vc -lssleay32MD \
        -LC:/libevent -llibevent_core \
        -LC:/libevent -llibevent_extras \
        -LC:/libevent -llibevent_openssl
} else:unix {
    LIBS    += \
        -luuid \
        -levent_core \
        -levent_extra \
        -levent_openssl \
        -lcrypto \
        -lssl

    target.path     = /usr/lib/calibri
    headers.path    = /usr/include/calibri
    headers.files  += eventdispatcher/eventdispatcher.h \
        eventdispatcher/eventdispatcher_config.h \
        eventdispatcher/eventdispatcher_types.h \
        tcpserver/tcpserver.h \
        socket/tcpsocket.h \
        socket/sslsocket.h \
        ssl/ssl.h \
        crypto/crypto.h \
        settings/settings.h \
        datetime/datetime.h \
        uniqueid/uniqueid.h \
        filesystem/filesystem.h \
        utils/utils.h \
        datastream.h \
        defines.h

    QMAKE_PKGCONFIG_NAME        = calibri
    QMAKE_PKGCONFIG_DESCRIPTION = "Calibri Library"
    QMAKE_PKGCONFIG_LIBDIR      = $$target.path
    QMAKE_PKGCONFIG_INCDIR      = $$headers.path
    QMAKE_PKGCONFIG_DESTDIR     = pkgconfig

    INSTALLS += target headers

    QMAKE_CXXFLAGS_RELEASE     -= -O2
    QMAKE_CXXFLAGS_RELEASE     += -O3 \
        -march=native \
        -mtune=native \
        -funroll-loops
}
