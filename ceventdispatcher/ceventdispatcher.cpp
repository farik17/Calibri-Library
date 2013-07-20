/****************************************************************************
**
** Copyright (c) 2013 Calibri-Software <calibrisoftware@gmail.com>
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included in
** all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
** IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
** AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
** OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
** THE SOFTWARE.
**
****************************************************************************/

//! Self Includes
#include "ceventdispatcher.h"

//! Platform Includes
#if defined(_WIN32)
#   include <WS2tcpip.h>
#elif defined(__unix__) || defined(__linux__)
#   include <cstring>
#endif

//! Std Includes
#include <iostream>

//! LibEvent Includes
#include <event2/listener.h>
#include <event2/bufferevent_ssl.h>

//! CEventDispatcher Includes
#include "ceventdispatcher_types.h"
#include "ceventdispatcher_config.h"

//! Defines
#define AF_INET_LENGTH          16
#define AF_INET6_LENGTH         48

CEventDispatcher *CEventDispatcher::m_eventDispatcher = nullptr;

CEventDispatcher::~CEventDispatcher()
{
#if defined(_WIN32)
    WSACleanup();
#endif

    if (m_event_base)
        event_base_free(m_event_base);

    if (m_evdns_base)
        evdns_base_free(m_evdns_base, 1);
}

void CEventDispatcher::acceptSocket(socketinfo *socket_info, const c_fdptr fd)
{
    bufferevent *buffer_event = nullptr;

    sslinfo *ssl_info = socketinfo_get_sslinfo(socket_info);
    if (ssl_info) {
        SSL *ssl = SSL_new(sslinfo_get_ssl_ctx(ssl_info));
        if (!ssl) {
#if defined(DEBUG)
            C_DEBUG("failed to initialize ssl");
#endif
            return;
        }

        buffer_event = bufferevent_openssl_socket_new(m_event_base, fd, ssl, BUFFEREVENT_SSL_ACCEPTING, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
            SSL_free(ssl);
#if defined(DEBUG)
            C_DEBUG("failed to initialize events");
#endif
            return;
        }
    } else {
        buffer_event = bufferevent_socket_new(m_event_base, fd, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
#if defined(DEBUG)
            C_DEBUG("failed to initialize events");
#endif
            return;
        }
    }

    bufferevent_setcb(buffer_event, CEventDispatcher::readNotification, nullptr, CEventDispatcher::eventNotification, socket_info);

    c_int16 events = (EV_READ | EV_PERSIST);

    c_int32 features = event_base_get_features(m_event_base);
    if (features & EV_FEATURE_ET)
        events |= EV_ET;

    if (bufferevent_enable(buffer_event, events) != 0) {
        bufferevent_free(buffer_event);
#if defined(DEBUG)
        C_DEBUG("failed to enable events");
#endif
        return;
    }

    socketinfo_set_bufferevent(socket_info, buffer_event);
    socketinfo_set_socket_state(socket_info, Connected);
}

void CEventDispatcher::connectSocket(socketinfo *socket_info, const std::string &address, const c_uint16 port)
{
    bufferevent *buffer_event = nullptr;

    sslinfo *ssl_info = socketinfo_get_sslinfo(socket_info);
    if (ssl_info) {
        SSL *ssl = SSL_new(sslinfo_get_ssl_ctx(ssl_info));
        if (!ssl) {
#if defined(DEBUG)
            C_DEBUG("failed to initialize ssl");
#endif
            return;
        }

        buffer_event = bufferevent_openssl_socket_new(m_event_base, -1, ssl, BUFFEREVENT_SSL_CONNECTING, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
            SSL_free(ssl);
#if defined(DEBUG)
            C_DEBUG("failed to initialize events");
#endif
            return;
        }
    } else {
        buffer_event = bufferevent_socket_new(m_event_base, -1, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
#if defined(DEBUG)
            C_DEBUG("failed to initialize events");
#endif
            return;
        }
    }

    bufferevent_setcb(buffer_event, CEventDispatcher::readNotification, nullptr, CEventDispatcher::eventNotification, socket_info);

    c_int16 events = (EV_READ | EV_PERSIST);

    c_int32 features = event_base_get_features(m_event_base);
    if (features & EV_FEATURE_ET)
        events |= EV_ET;

    if (bufferevent_enable(buffer_event, events) != 0) {
        bufferevent_free(buffer_event);
#if defined(DEBUG)
        C_DEBUG("failed to enable events");
#endif
        return;
    }

    if (bufferevent_socket_connect_hostname(buffer_event, m_evdns_base, AF_UNSPEC, address.c_str(), port) != 0) {
        bufferevent_free(buffer_event);
#if defined(DEBUG)
        C_DEBUG("failed to connect");
#endif
        return;
    }

    socketinfo_set_bufferevent(socket_info, buffer_event);
    socketinfo_set_socket_state(socket_info, Connecting);
}

void CEventDispatcher::closeSocket(socketinfo *socket_info, const bool force)
{
    bufferevent *buffer_event = socketinfo_get_bufferevent(socket_info);

    if (force || evbuffer_get_length(bufferevent_get_output(buffer_event)) == 0) {
        bufferevent_free(buffer_event);

        socketinfo_set_bufferevent(socket_info, nullptr);
        socketinfo_set_socket_state(socket_info, Unconnected);

        const auto &disconnected_handler = socketinfo_get_disconnected_handler(socket_info);
        if (disconnected_handler)
            disconnected_handler(socket_info);
    } else {
        evbuffer_add_cb(bufferevent_get_output(buffer_event), CEventDispatcher::outputBufferNotification, socket_info);

        socketinfo_set_socket_state(socket_info, Closing);
    }
}

void CEventDispatcher::bindServer(serverinfo *server_info, const std::string &address, const c_uint16 port, const c_int32 backlog)
{
    evutil_addrinfo hints;
    memset(&hints, 0, sizeof(evutil_addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    evutil_addrinfo *addr_info = nullptr;

    if (evutil_getaddrinfo(address.c_str(), std::to_string(port).c_str(), &hints, &addr_info) != 0) {
#if defined(DEBUG)
        C_DEBUG("invalid address or port");
#endif
        return;
    }

    evconnlistener *ev_conn_listener = nullptr;

    switch (addr_info->ai_family) {
    case AF_INET:
        ev_conn_listener = evconnlistener_new_bind(m_event_base, CEventDispatcher::acceptNotification, server_info, (LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE), backlog, addr_info->ai_addr, static_cast<c_int32>(sizeof(sockaddr_in)));
        break;

    case AF_INET6:
        ev_conn_listener = evconnlistener_new_bind(m_event_base, CEventDispatcher::acceptNotification, server_info, (LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE), backlog, addr_info->ai_addr, static_cast<c_int32>(sizeof(sockaddr_in6)));
        break;

    default:
        evutil_freeaddrinfo(addr_info);
        return;
    }

    if (!ev_conn_listener) {
        evutil_freeaddrinfo(addr_info);
#if defined(DEBUG)
        C_DEBUG("failed to bind listener");
#endif
        return;
    }

    evutil_freeaddrinfo(addr_info);

    evconnlistener_set_error_cb(ev_conn_listener, CEventDispatcher::acceptErrorNotification);

    serverinfo_set_evconnlistener(server_info, ev_conn_listener);
}

void CEventDispatcher::closeServer(serverinfo *server_info)
{    
    evconnlistener_free(serverinfo_get_evconnlistener(server_info));

    serverinfo_set_evconnlistener(server_info, nullptr);
}

void CEventDispatcher::startTimer(timerinfo *timer_info, const c_uint32 msec, const bool repeat)
{
    c_int16 events = repeat ? (EV_TIMEOUT | EV_PERSIST) : EV_TIMEOUT;

    event *ev = event_new(m_event_base, -1, events, CEventDispatcher::timerNotification, timer_info);
    if (!ev) {
#if defined(DEBUG)
        C_DEBUG("failed to initialize timer");
#endif
        return;
    }

    timeval tv;
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    if (event_add(ev, &tv) != 0) {
        event_free(ev);
#if defined(DEBUG)
        C_DEBUG("invalid timer interval");
#endif
        return;
    }

    timerinfo_set_event(timer_info, ev);
}

void CEventDispatcher::restartTimer(timerinfo *timer_info, const c_uint32 msec, const bool repeat)
{
    killTimer(timer_info);
    startTimer(timer_info, msec, repeat);
}

void CEventDispatcher::killTimer(timerinfo *timer_info)
{
    event_free(timerinfo_get_event(timer_info));

    timerinfo_set_event(timer_info, nullptr);
}

const c_int32 CEventDispatcher::execute()
{
#if defined(DEBUG)
    int result = event_base_dispatch(m_event_base);
    if (result != 0)
        C_DEBUG("internal error");
    return result;
#else
    return event_base_dispatch(m_event_base);
#endif
}

const c_int32 CEventDispatcher::execute(const EventLoopFlag eventLoopFlag)
{
    c_int32 flag = 0;

    switch (eventLoopFlag) {
    case Once:
        flag = EVLOOP_ONCE;
        break;

    case NonBlock:
        flag = EVLOOP_NONBLOCK;
        break;

    case NoExitOnEmpty:
        flag = EVLOOP_NO_EXIT_ON_EMPTY;
        break;

    default:
#if defined(DEBUG)
        C_DEBUG("invalid event loop flag");
#endif
        return -1;
    }

#if defined(DEBUG)
    int result = event_base_loop(m_event_base, flag);
    if (result != 0)
        C_DEBUG("internal error");
    return result;
#else
    return event_base_loop(m_event_base, flag);
#endif
}

const c_int32 CEventDispatcher::terminate()
{
#if defined(DEBUG)
    int result = event_base_loopbreak(m_event_base);
    if (result != 0)
        C_DEBUG("internal error");
    return result;
#else
    return event_base_loopbreak(m_event_base);
#endif
}

void CEventDispatcher::initialize(CEventDispatcherConfig *config)
{
    if (!m_eventDispatcher)
        m_eventDispatcher = new CEventDispatcher(config);
}

const std::string CEventDispatcher::socketAddress(const c_fdptr fd)
{
    sockaddr_storage sa_stor;
    size_t sa_stor_len = sizeof(sockaddr_storage);
    memset(&sa_stor, 0, sa_stor_len);

#if defined(_WIN32)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sa_stor), reinterpret_cast<c_int32 *>(&sa_stor_len)) != 0)
#elif defined(__unix__) || defined(__linux__)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sa_stor), reinterpret_cast<c_uint32 *>(&sa_stor_len)) != 0)
#endif
        return std::string();

    switch (sa_stor.ss_family) {
    case AF_INET: {
        char addr[AF_INET_LENGTH];
        evutil_inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in *>(&sa_stor)->sin_addr, addr, AF_INET_LENGTH);
        return addr;
    }

    case AF_INET6: {
        char addr[AF_INET6_LENGTH];
        evutil_inet_ntop(AF_INET6, &reinterpret_cast<sockaddr_in6 *>(&sa_stor)->sin6_addr, addr, AF_INET6_LENGTH);
        return addr;
    }

    default:
        break;
    }

    return std::string();
}

CEventDispatcher *CEventDispatcher::instance()
{
    if (!m_eventDispatcher)
        m_eventDispatcher = new CEventDispatcher();

    return m_eventDispatcher;
}

const c_uint16 CEventDispatcher::socketPort(const c_fdptr fd)
{
    sockaddr_storage sa_stor;
    size_t sa_stor_len = sizeof(sockaddr_storage);
    memset(&sa_stor, 0, sa_stor_len);

#if defined(_WIN32)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sa_stor), reinterpret_cast<c_int32 *>(&sa_stor_len)) != 0)
#elif defined(__unix__) || defined(__linux__)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sa_stor), reinterpret_cast<c_uint32 *>(&sa_stor_len)) != 0)
#endif
        return 0;

    switch (sa_stor.ss_family) {
    case AF_INET:
        return ntohs(reinterpret_cast<sockaddr_in *>(&sa_stor)->sin_port);

    case AF_INET6:
        return ntohs(reinterpret_cast<sockaddr_in6 *>(&sa_stor)->sin6_port);

    default:
        break;
    }

    return 0;
}

CEventDispatcher::CEventDispatcher()
    : m_event_base(nullptr)
    , m_evdns_base(nullptr)
{
#if defined(_WIN32)
    initializeWSA();
#endif

    m_event_base = event_base_new();
    if (m_event_base) {
        m_evdns_base = evdns_base_new(m_event_base, 1);
        if (!m_evdns_base) {
            event_base_free(m_event_base);
#if defined(DEBUG)
            C_DEBUG("failed to initialize");
#endif
        }
    }
#if defined(DEBUG)
    else {
        C_DEBUG("failed to initialize");
    }
#endif
}

CEventDispatcher::CEventDispatcher(CEventDispatcherConfig *config)
    : m_event_base(nullptr)
    , m_evdns_base(nullptr)
{
#if defined(_WIN32)
    initializeWSA();
#endif

    m_event_base = event_base_new_with_config(config->m_event_config);
    if (m_event_base) {
        m_evdns_base = evdns_base_new(m_event_base, 1);
        if (!m_evdns_base) {
            event_base_free(m_event_base);
#if defined(DEBUG)
            C_DEBUG("failed to initialize");
#endif
        }
    }
#if defined(DEBUG)
    else {
        C_DEBUG("failed to initialize");
    }
#endif
}

#if defined(_WIN32)
void CEventDispatcher::initializeWSA()
{
    WORD version = MAKEWORD(2, 2);
    WSADATA wsaData;

    c_int32 error = WSAStartup(version, &wsaData);
    if (error != 0) {
        WSACleanup();
#if defined(DEBUG)
        C_DEBUG("failed with code " + std::to_string(error));
#endif
    }
}
#endif

void CEventDispatcher::acceptNotification(evconnlistener *listener, const c_fdptr fd, sockaddr *address, const c_int32 socklen, void *ctx)
{
    C_UNUSED(listener);
    C_UNUSED(address);
    C_UNUSED(socklen);

    serverinfo *server_info = reinterpret_cast<serverinfo *>(ctx);

    const auto &accep_handler = serverinfo_get_accept_handler(server_info);
    if (accep_handler)
        accep_handler(server_info, fd);
}

void CEventDispatcher::acceptErrorNotification(evconnlistener *listener, void *ctx)
{
    C_UNUSED(listener);

    serverinfo *server_info = reinterpret_cast<serverinfo *>(ctx);

    const auto &accept_error_handler = serverinfo_get_accept_error_handler(server_info);
    if (accept_error_handler)
        accept_error_handler(server_info, evutil_socket_geterror(evconnlistener_get_fd(listener)));
}

void CEventDispatcher::readNotification(bufferevent *buffer_event, void *ctx)
{
    C_UNUSED(buffer_event);

    socketinfo *socket_info = reinterpret_cast<socketinfo *>(ctx);

    const auto &read_handler = socketinfo_get_read_handler(socket_info);
    if (read_handler)
        read_handler(socket_info);
}

void CEventDispatcher::eventNotification(bufferevent *buffer_event, const c_int16 events, void *ctx)
{
    socketinfo *socket_info = reinterpret_cast<socketinfo *>(ctx);

    if (events & BEV_EVENT_CONNECTED) {
        socketinfo_set_socket_state(socket_info, Connected);

        sslinfo *ssl_info = socketinfo_get_sslinfo(socket_info);
        if (ssl_info) {
            const auto &encrypted_handler = sslinfo_get_encrypted_handler(ssl_info);
            if (encrypted_handler)
                encrypted_handler(socket_info);
        } else {
            const auto &connected_handler = socketinfo_get_connected_handler(socket_info);
            if (connected_handler)
                connected_handler(socket_info);
        }
        return;
    }

    if (events & BEV_EVENT_ERROR) {
        c_int32 error = evutil_socket_geterror(bufferevent_getfd(buffer_event));
        if (error != 0) {
            const auto &error_handler = socketinfo_get_error_handler(socket_info);
            if (error_handler)
                error_handler(socket_info, error);
        }

        sslinfo *ssl_info = socketinfo_get_sslinfo(socket_info);
        if (ssl_info) {
            c_ulong ssl_error = bufferevent_get_openssl_error(buffer_event);
            if (ssl_error != 0) {
                const auto &ssl_error_handler = sslinfo_get_ssl_error_handler(ssl_info);
                if (ssl_error_handler)
                    ssl_error_handler(socket_info, ssl_error);
            }
        }
    }

    if (events & BEV_EVENT_EOF) {
        bufferevent_free(buffer_event);

        socketinfo_set_bufferevent(socket_info, nullptr);
        socketinfo_set_socket_state(socket_info, Unconnected);

        const auto &disconnected_handler = socketinfo_get_disconnected_handler(socket_info);
        if (disconnected_handler)
            disconnected_handler(socket_info);
    }
}

void CEventDispatcher::timerNotification(const c_fdptr fd, const c_int16 events, void *ctx)
{
    C_UNUSED(fd);
    C_UNUSED(events);

    timerinfo *timer_info = reinterpret_cast<timerinfo *>(ctx);

    const auto &timer_handler = timerinfo_get_timer_handler(timer_info);
    if (timer_handler)
        timer_handler(timer_info);
}

void CEventDispatcher::outputBufferNotification(evbuffer *buffer, const evbuffer_cb_info *info, void *ctx)
{
    C_UNUSED(info);

    socketinfo *socket_info = reinterpret_cast<socketinfo *>(ctx);

    if (socketinfo_get_socket_state(socket_info) != Closing)
        return;

    if (evbuffer_get_length(buffer) != 0)
        return;

    bufferevent_free(socketinfo_get_bufferevent(socket_info));

    socketinfo_set_bufferevent(socket_info, nullptr);
    socketinfo_set_socket_state(socket_info, Unconnected);

    const auto &disconnected_handler = socketinfo_get_disconnected_handler(socket_info);
    if (disconnected_handler)
        disconnected_handler(socket_info);
}
