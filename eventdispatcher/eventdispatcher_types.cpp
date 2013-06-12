//! Self Includes
#include "eventdispatcher_types.h"

/*! timerinfo */
struct timerinfo
{
    event *ev;
    void *ctx;
    std::function<void (timerinfo *)> timer_handler;
};

timerinfo *timerinfo_new()
{
    timerinfo *timer_info = new timerinfo;
    timer_info->ev = nullptr;
    timer_info->ctx = nullptr;
    timer_info->timer_handler = nullptr;
    return timer_info;
}

void timerinfo_free(timerinfo *timer_info)
{
    delete timer_info;
}

void timerinfo_set_event(timerinfo *timer_info, event *ev)
{
    timer_info->ev = ev;
}

event *timerinfo_get_event(const timerinfo *timer_info)
{
    return timer_info->ev;
}

void timerinfo_set_context(timerinfo *timer_info, void *ctx)
{
    timer_info->ctx = ctx;
}

void *timerinfo_get_context(const timerinfo *timer_info)
{
    return timer_info->ctx;
}

void timerinfo_set_timer_handler(timerinfo *timer_info, const std::function<void (timerinfo *)> &handler)
{
    timer_info->timer_handler = handler;
}

void timerinfo_unset_timer_handler(timerinfo *timer_info)
{
    timer_info->timer_handler = nullptr;
}

const std::function<void (timerinfo *)> &timerinfo_get_timer_handler(const timerinfo *timer_info)
{
    return timer_info->timer_handler;
}

/*! sslinfo */
struct sslinfo
{
    SSL_CTX *ssl_ctx;
    SSLProtocol ssl_protocol;
    SSLMode ssl_mode;
    SSLPeerVerifyMode ssl_peer_verify_mode;
    std::function<void (socketinfo *)> encrypted_handler;
    std::function<void (socketinfo *, c_ulong)> ssl_error_handler;
};

sslinfo *sslinfo_new()
{
    sslinfo *ssl_info = new sslinfo;
    ssl_info->ssl_ctx = nullptr;
    ssl_info->ssl_protocol = SSLv3_0;
    ssl_info->ssl_mode = SSLClientMode;
    ssl_info->ssl_peer_verify_mode = SSLVerifyPeer;
    ssl_info->encrypted_handler = nullptr;
    ssl_info->ssl_error_handler = nullptr;
    return ssl_info;
}

void sslinfo_free(sslinfo *ssl_info)
{
    delete ssl_info;
}

void sslinfo_set_ssl_ctx(sslinfo *ssl_info, SSL_CTX *ssl_ctx)
{
    ssl_info->ssl_ctx = ssl_ctx;
}

SSL_CTX *sslinfo_get_ssl_ctx(const sslinfo *ssl_info)
{
    return ssl_info->ssl_ctx;
}

void sslinfo_set_ssl_protocol(sslinfo *ssl_info, SSLProtocol ssl_protocol)
{
    ssl_info->ssl_protocol = ssl_protocol;
}

SSLProtocol sslinfo_get_ssl_protocol(const sslinfo *ssl_info)
{
    return ssl_info->ssl_protocol;
}

void sslinfo_set_ssl_mode(sslinfo *ssl_info, SSLMode ssl_mode)
{
    ssl_info->ssl_mode = ssl_mode;
}

SSLMode sslinfo_get_ssl_mode(const sslinfo *ssl_info)
{
    return ssl_info->ssl_mode;
}

void sslinfo_set_ssl_peer_verify_mode(sslinfo *ssl_info, SSLPeerVerifyMode ssl_peer_verify_mode)
{
    ssl_info->ssl_peer_verify_mode = ssl_peer_verify_mode;
}

SSLPeerVerifyMode sslinfo_get_ssl_peer_verify_mode(const sslinfo *ssl_info)
{
    return ssl_info->ssl_peer_verify_mode;
}

void sslinfo_set_encrypted_handler(sslinfo *ssl_info, const std::function<void (socketinfo *)> &handler)
{
    ssl_info->encrypted_handler = handler;
}

void sslinfo_unset_encrypted_handler(sslinfo *ssl_info)
{
    ssl_info->encrypted_handler = nullptr;
}

const std::function<void (socketinfo *)> &sslinfo_get_encrypted_handler(const sslinfo *ssl_info)
{
    return ssl_info->encrypted_handler;
}

void sslinfo_set_ssl_error_handler(sslinfo *ssl_info, const std::function<void (socketinfo *, c_ulong)> &handler)
{
    ssl_info->ssl_error_handler = handler;
}

void sslinfo_unset_ssl_error_handler(sslinfo *ssl_info)
{
    ssl_info->ssl_error_handler = nullptr;
}

const std::function<void (socketinfo *, c_ulong)> &sslinfo_get_ssl_error_handler(const sslinfo *ssl_info)
{
    return ssl_info->ssl_error_handler;
}

/*! socketinfo */
struct socketinfo
{
    bufferevent *buffer_event;
    void *ctx;
    sslinfo *ssl_info;
    SocketState socket_state;
    std::function<void (socketinfo *)> connected_handler;
    std::function<void (socketinfo *)> disconnected_handler;
    std::function<void (socketinfo *)> read_handler;
    std::function<void (socketinfo *, c_int32)> error_handler;
};

socketinfo *socketinfo_new()
{
    socketinfo *socket_info = new socketinfo;
    socket_info->buffer_event = nullptr;
    socket_info->ctx = nullptr;
    socket_info->ssl_info = nullptr;
    socket_info->socket_state = Unconnected;
    socket_info->connected_handler = nullptr;
    socket_info->disconnected_handler = nullptr;
    socket_info->read_handler = nullptr;
    socket_info->error_handler = nullptr;
    return socket_info;
}

void socketinfo_free(socketinfo *socket_info)
{
    delete socket_info;
}

void socketinfo_set_bufferevent(socketinfo *socket_info, bufferevent *buffer_event)
{
    socket_info->buffer_event = buffer_event;
}

bufferevent *socketinfo_get_bufferevent(const socketinfo *socket_info)
{
    return socket_info->buffer_event;
}

void socketinfo_set_context(socketinfo *socket_info, void *ctx)
{
    socket_info->ctx = ctx;
}

void *socketinfo_get_context(const socketinfo *socket_info)
{
    return socket_info->ctx;
}

void socketinfo_set_sslinfo(socketinfo *socket_info, sslinfo *ssl_info)
{
    socket_info->ssl_info = ssl_info;
}

sslinfo *socketinfo_get_sslinfo(const socketinfo *socket_info)
{
    return socket_info->ssl_info;
}

void socketinfo_set_socket_state(socketinfo *socket_info, SocketState socket_state)
{
    socket_info->socket_state = socket_state;
}

SocketState socketinfo_get_socket_state(const socketinfo *socket_info)
{
    return socket_info->socket_state;
}

void socketinfo_set_connected_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler)
{
    socket_info->connected_handler = handler;
}

void socketinfo_unset_connected_handler(socketinfo *socket_info)
{
    socket_info->connected_handler = nullptr;
}

const std::function<void (socketinfo *)> &socketinfo_get_connected_handler(const socketinfo *socket_info)
{
    return socket_info->connected_handler;
}

void socketinfo_set_disconnected_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler)
{
    socket_info->disconnected_handler = handler;
}

void socketinfo_unset_disconnected_handler(socketinfo *socket_info)
{
    socket_info->disconnected_handler = nullptr;
}

const std::function<void (socketinfo *)> &socketinfo_get_disconnected_handler(const socketinfo *socket_info)
{
    return socket_info->disconnected_handler;
}

void socketinfo_set_read_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler)
{
    socket_info->read_handler = handler;
}

void socketinfo_unset_read_handler(socketinfo *socket_info)
{
    socket_info->read_handler = nullptr;
}

const std::function<void (socketinfo *)> &socketinfo_get_read_handler(const socketinfo *socket_info)
{
    return socket_info->read_handler;
}

void socketinfo_set_error_handler(socketinfo *socket_info, const std::function<void (socketinfo *, c_int32)> &handler)
{
    socket_info->error_handler = handler;
}

void socketinfo_unset_error_handler(socketinfo *socket_info)
{
    socket_info->error_handler = nullptr;
}

const std::function<void (socketinfo *, c_int32)> &socketinfo_get_error_handler(const socketinfo *socket_info)
{
    return socket_info->error_handler;
}

/*! serverinfo */
struct serverinfo
{
    evconnlistener *ev_conn_listener;
    void *ctx;
    std::function<void (serverinfo *, c_fdptr)> accept_handler;
    std::function<void (serverinfo *, c_int32)> accept_error_handler;
};

serverinfo *serverinfo_new()
{
    serverinfo *server_info = new serverinfo;
    server_info->ev_conn_listener = nullptr;
    server_info->ctx = nullptr;
    server_info->accept_handler = nullptr;
    server_info->accept_error_handler = nullptr;
    return server_info;
}

void serverinfo_free(serverinfo *server_info)
{
    delete server_info;
}

void serverinfo_set_evconnlistener(serverinfo *server_info, evconnlistener *ev_conn_listener)
{
    server_info->ev_conn_listener = ev_conn_listener;
}

evconnlistener *serverinfo_get_evconnlistener(const serverinfo *server_info)
{
    return server_info->ev_conn_listener;
}

void serverinfo_set_context(serverinfo *server_info, void *ctx)
{
    server_info->ctx = ctx;
}

void *serverinfo_get_context(const serverinfo *server_info)
{
    return server_info->ctx;
}

void serverinfo_set_accept_handler(serverinfo *server_info, const std::function<void (serverinfo *, c_fdptr)> &handler)
{
    server_info->accept_handler = handler;
}

void serverinfo_unset_accept_handler(serverinfo *server_info)
{
    server_info->accept_handler = nullptr;
}

const std::function<void (serverinfo *, c_fdptr)> &serverinfo_get_accept_handler(const serverinfo *server_info)
{
    return server_info->accept_handler;
}

void serverinfo_set_accept_error_handler(serverinfo *server_info, const std::function<void (serverinfo *, c_int32)> &handler)
{
    server_info->accept_error_handler = handler;
}

void serverinfo_unset_accept_error_handler(serverinfo *server_info)
{
    server_info->accept_error_handler = nullptr;
}

const std::function<void (serverinfo *, c_int32)> &serverinfo_get_accept_error_handler(const serverinfo *server_info)
{
    return server_info->accept_error_handler;
}
