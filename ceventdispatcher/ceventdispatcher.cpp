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

void CEventDispatcher::initialize(CEventDispatcherConfig *config)
{
    if (!m_eventDispatcher)
        m_eventDispatcher = new CEventDispatcher(config);
}

CEventDispatcher *CEventDispatcher::instance()
{
    if (!m_eventDispatcher)
        m_eventDispatcher = new CEventDispatcher();

    return m_eventDispatcher;
}

void CEventDispatcher::execute()
{
    if (event_base_dispatch(m_event_base) != 0)
        std::cout << "CEventDispatcher::execute error: internal error" << std::endl;
}

void CEventDispatcher::execute(EventLoopFlag flag)
{
    c_int32 result = 0;

    switch (flag) {
    case Once:
        result = EVLOOP_ONCE;
        break;

    case Nonblock:
        result = EVLOOP_NONBLOCK;
        break;

    case NoExitOnEmpty:
        result = EVLOOP_NO_EXIT_ON_EMPTY;
        break;

    default:
        std::cout << "CEventDispatcher::execute error: invalid event loop flag" << std::endl;
        return;
    }

    if (event_base_loop(m_event_base, result) != 0)
        std::cout << "CEventDispatcher::execute error: internal error" << std::endl;
}

void CEventDispatcher::terminate()
{
    if (event_base_loopbreak(m_event_base) != 0)
        std::cout << "CEventDispatcher::terminate error: internal error" << std::endl;
}

void CEventDispatcher::acceptSocket(socketinfo *socket_info, c_fdptr fd)
{
    bufferevent *buffer_event = nullptr;

    sslinfo *ssl_info = socketinfo_get_sslinfo(socket_info);
    if (ssl_info) {
        SSL *ssl = SSL_new(sslinfo_get_ssl_ctx(ssl_info));
        if (!ssl) {
            std::cout << "CEventDispatcher::dispatchSocket error: failed to initialize ssl" << std::endl;
            return;
        }

        buffer_event = bufferevent_openssl_socket_new(m_event_base, fd, ssl, BUFFEREVENT_SSL_ACCEPTING, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
            SSL_free(ssl);
            std::cout << "CEventDispatcher::dispatchSocket error: failed to initialize events" << std::endl;
            return;
        }
    } else {
        buffer_event = bufferevent_socket_new(m_event_base, fd, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
            std::cout << "CEventDispatcher::dispatchSocket error: failed to initialize events" << std::endl;
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
        std::cout << "CEventDispatcher::dispatchSocket error: failed to enable events" << std::endl;
        return;
    }

    socketinfo_set_bufferevent(socket_info, buffer_event);
    socketinfo_set_socket_state(socket_info, Connected);
}

void CEventDispatcher::connectSocket(socketinfo *socket_info, const std::string &address, c_uint16 port)
{
    bufferevent *buffer_event = nullptr;

    sslinfo *ssl_info = socketinfo_get_sslinfo(socket_info);
    if (ssl_info) {
        SSL *ssl = SSL_new(sslinfo_get_ssl_ctx(ssl_info));
        if (!ssl) {
            std::cout << "CEventDispatcher::dispatchSocket error: failed to initialize ssl" << std::endl;
            return;
        }

        buffer_event = bufferevent_openssl_socket_new(m_event_base, -1, ssl, BUFFEREVENT_SSL_CONNECTING, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
            SSL_free(ssl);
            std::cout << "CEventDispatcher::dispatchSocket error: failed to initialize events" << std::endl;
            return;
        }
    } else {
        buffer_event = bufferevent_socket_new(m_event_base, -1, BEV_OPT_CLOSE_ON_FREE);
        if (!buffer_event) {
            std::cout << "CEventDispatcher::dispatchSocket error: failed to initialize events" << std::endl;
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
        std::cout << "CEventDispatcher::dispatchSocket error: failed to enable events" << std::endl;
        return;
    }

    if (bufferevent_socket_connect_hostname(buffer_event, m_evdns_base, AF_UNSPEC, address.c_str(), port) != 0) {
        bufferevent_free(buffer_event);
        std::cout << "CEventDispatcher::dispatchSocket error: failed to connect" << std::endl;
        return;
    }

    socketinfo_set_bufferevent(socket_info, buffer_event);
    socketinfo_set_socket_state(socket_info, Connecting);
}

void CEventDispatcher::closeSocket(socketinfo *socket_info, bool force)
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
        socketinfo_set_socket_state(socket_info, Closing);
    }
}

void CEventDispatcher::bindServer(serverinfo *server_info, const std::string &address, c_uint16 port, c_int32 backlog)
{
    char port_cstr[6];
    evutil_snprintf(port_cstr, 6, "%d", static_cast<c_int32>(port));

    evutil_addrinfo hints;
    memset(&hints, 0, sizeof(evutil_addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    evutil_addrinfo *addr_info = nullptr;

    if (evutil_getaddrinfo(address.c_str(), port_cstr, &hints, &addr_info) != 0) {
        std::cout << "CEventDispatcher::bindServer error: invalid address or port" << std::endl;
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
        std::cout << "CEventDispatcher::bindListener error: failed to bind listener" << std::endl;
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

void CEventDispatcher::startTimer(timerinfo *timer_info, c_uint32 msec, bool repeat)
{
    c_int16 events = repeat ? (EV_TIMEOUT | EV_PERSIST) : EV_TIMEOUT;

    event *ev = event_new(m_event_base, -1, events, CEventDispatcher::timerNotification, timer_info);
    if (!ev) {
        std::cout << "CEventDispatcher::startTimer error: failed to initialize timer" << std::endl;
        return;
    }

    timeval tv;
    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    if (event_add(ev, &tv) != 0) {
        event_free(ev);
        std::cout << "CEventDispatcher::startTimer error: invalid timer interval" << std::endl;
        return;
    }

    timerinfo_set_event(timer_info, ev);
}

void CEventDispatcher::restartTimer(timerinfo *timer_info, c_uint32 msec, bool repeat)
{
    killTimer(timer_info);
    startTimer(timer_info, msec, repeat);
}

void CEventDispatcher::killTimer(timerinfo *timer_info)
{
    event_free(timerinfo_get_event(timer_info));

    timerinfo_set_event(timer_info, nullptr);
}

std::string CEventDispatcher::socketAddress(c_fdptr fd) const
{
    sockaddr_storage sock_addr_stor;
    size_t sock_addr_stor_len = sizeof(sockaddr_storage);
    memset(&sock_addr_stor, 0, sock_addr_stor_len);

#if defined(_WIN32)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sock_addr_stor), reinterpret_cast<c_int32 *>(&sock_addr_stor_len)) != 0)
#elif defined(__unix__) || defined(__linux__)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sock_addr_stor), reinterpret_cast<c_uint32 *>(&sock_addr_stor_len)) != 0)
#endif
        return std::string();

    switch (sock_addr_stor.ss_family) {
    case AF_INET: {
        char addr[16];
        evutil_inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in *>(&sock_addr_stor)->sin_addr, addr, 16);
        return addr;
    }

    case AF_INET6: {
        char addr[48];
        evutil_inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in6 *>(&sock_addr_stor)->sin6_addr, addr, 48);
        return addr;
    }

    default:
        break;
    }

    return std::string();
}

c_uint16 CEventDispatcher::socketPort(c_fdptr fd) const
{
    sockaddr_storage sock_addr_stor;
    size_t sock_addr_stor_len = sizeof(sockaddr_storage);
    memset(&sock_addr_stor, 0, sock_addr_stor_len);

#if defined(_WIN32)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sock_addr_stor), reinterpret_cast<c_int32 *>(&sock_addr_stor_len)) != 0)
#elif defined(__unix__) || defined(__linux__)
    if (getpeername(fd, reinterpret_cast<sockaddr *>(&sock_addr_stor), reinterpret_cast<c_uint32 *>(&sock_addr_stor_len)) != 0)
#endif
        return 0;

    switch (sock_addr_stor.ss_family) {
    case AF_INET:
        return ntohs(reinterpret_cast<sockaddr_in *>(&sock_addr_stor)->sin_port);

    case AF_INET6:
        return ntohs(reinterpret_cast<sockaddr_in6 *>(&sock_addr_stor)->sin6_port);

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
    if (!m_event_base)
        std::cout << "CEventDispatcher::CEventDispatcher error: failed to initialize EventDispatcher" << std::endl;
    else
        m_evdns_base = evdns_base_new(m_event_base, 1);

    if (!m_evdns_base) {
        event_base_free(m_event_base);
        std::cout << "CEventDispatcher::CEventDispatcher error: failed to initialize EventDispatcher" << std::endl;
    }
}

CEventDispatcher::CEventDispatcher(CEventDispatcherConfig *config)
    : m_event_base(nullptr)
    , m_evdns_base(nullptr)
{
#if defined(_WIN32)
    initializeWSA();
#endif

    m_event_base = event_base_new_with_config(config->m_event_config);
    if (!m_event_base)
        std::cout << "CEventDispatcher::CEventDispatcher error: failed to initialize EventDispatcher" << std::endl;
    else
        m_evdns_base = evdns_base_new(m_event_base, 1);

    if (!m_evdns_base) {
        event_base_free(m_event_base);
        std::cout << "CEventDispatcher::CEventDispatcher error: failed to initialize EventDispatcher" << std::endl;
    }
}

#if defined(_WIN32)
void CEventDispatcher::initializeWSA()
{
    WORD version = MAKEWORD(2, 2);
    WSADATA wsaData;

    c_int32 error = WSAStartup(version, &wsaData);
    if (error != 0) {
        WSACleanup();
        std::cout << "CEventDispatcher::initializeWSA error: failed with code " << error << std::endl;
    }
}
#endif

CEventDispatcher *CEventDispatcher::m_eventDispatcher = nullptr;

void CEventDispatcher::acceptNotification(evconnlistener *listener, c_fdptr fd, sockaddr *address, c_int32 socklen, void *ctx)
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

void CEventDispatcher::eventNotification(bufferevent *buffer_event, c_int16 events, void *ctx)
{
    socketinfo *socket_info = reinterpret_cast<socketinfo *>(ctx);

    if (events & BEV_EVENT_CONNECTED) {
        evbuffer_add_cb(bufferevent_get_output(socketinfo_get_bufferevent(socket_info)), CEventDispatcher::outputBufferNotification, socket_info);

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

    bool finished = false;

    if (events & BEV_EVENT_EOF)
        finished = true;

    if (events & BEV_EVENT_ERROR) {
        finished = true;

        c_int32 error = evutil_socket_geterror(bufferevent_getfd(buffer_event));
        if (error != 0) {
            const auto &error_handler = socketinfo_get_error_handler(socket_info);
            if (error_handler)
                error_handler(socket_info, error);
        } else {
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
    }

    if (finished) {
        bufferevent_free(buffer_event);

        socketinfo_set_bufferevent(socket_info, nullptr);
        socketinfo_set_socket_state(socket_info, Unconnected);

        const auto &disconnected_handler = socketinfo_get_disconnected_handler(socket_info);
        if (disconnected_handler)
            disconnected_handler(socket_info);
    }
}

void CEventDispatcher::timerNotification(c_fdptr fd, c_int16 events, void *ctx)
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