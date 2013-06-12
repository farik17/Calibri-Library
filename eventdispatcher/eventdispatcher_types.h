#ifndef EVENTDISPATCHER_TYPES_H
#define EVENTDISPATCHER_TYPES_H

//! Std Includes
#include <functional>

//! Ssl Includes
#include "ssl.h"

//! Forward Declaration
struct timerinfo;
struct event;
struct sslinfo;
struct socketinfo;
struct bufferevent;
struct serverinfo;
struct evconnlistener;

/*! timerinfo */
timerinfo *timerinfo_new();
void timerinfo_free(timerinfo *timer_info);

void timerinfo_set_event(timerinfo *timer_info, event *ev);
event *timerinfo_get_event(const timerinfo *timer_info);

void timerinfo_set_context(timerinfo *timer_info, void *ctx);
void *timerinfo_get_context(const timerinfo *timer_info);

void timerinfo_set_timer_handler(timerinfo *timer_info, const std::function<void (timerinfo *)> &handler);
void timerinfo_unset_timer_handler(timerinfo *timer_info);
const std::function<void (timerinfo *)> &timerinfo_get_timer_handler(const timerinfo *timer_info);

/*! sslinfo */
sslinfo *sslinfo_new();
void sslinfo_free(sslinfo *ssl_info);

void sslinfo_set_ssl_ctx(sslinfo *ssl_info, SSL_CTX *ssl_ctx);
SSL_CTX *sslinfo_get_ssl_ctx(const sslinfo *ssl_info);

void sslinfo_set_ssl_protocol(sslinfo *ssl_info, SSLProtocol ssl_protocol);
SSLProtocol sslinfo_get_ssl_protocol(const sslinfo *ssl_info);

void sslinfo_set_ssl_mode(sslinfo *ssl_info, SSLMode ssl_mode);
SSLMode sslinfo_get_ssl_mode(const sslinfo *ssl_info);

void sslinfo_set_ssl_peer_verify_mode(sslinfo *ssl_info, SSLPeerVerifyMode ssl_peer_verify_mode);
SSLPeerVerifyMode sslinfo_get_ssl_peer_verify_mode(const sslinfo *ssl_info);

void sslinfo_set_encrypted_handler(sslinfo *ssl_info, const std::function<void (socketinfo *)> &handler);
void sslinfo_unset_encrypted_handler(sslinfo *ssl_info);
const std::function<void (socketinfo *)> &sslinfo_get_encrypted_handler(const sslinfo *ssl_info);

void sslinfo_set_ssl_error_handler(sslinfo *ssl_info, const std::function<void (socketinfo *, c_ulong)> &handler);
void sslinfo_unset_ssl_error_handler(sslinfo *ssl_info);
const std::function<void (socketinfo *, c_ulong)> &sslinfo_get_ssl_error_handler(const sslinfo *ssl_info);

/*! socketinfo */
enum SocketState : c_uint8 {
    Unconnected     = 1,
    Connecting      = 2,
    Connected       = 3,
    Closing         = 4
};

socketinfo *socketinfo_new();
void socketinfo_free(socketinfo *socket_info);

void socketinfo_set_bufferevent(socketinfo *socket_info, bufferevent *buffer_event);
bufferevent *socketinfo_get_bufferevent(const socketinfo *socket_info);

void socketinfo_set_context(socketinfo *socket_info, void *ctx);
void *socketinfo_get_context(const socketinfo *socket_info);

void socketinfo_set_sslinfo(socketinfo *socket_info, sslinfo *ssl_info);
sslinfo *socketinfo_get_sslinfo(const socketinfo *socket_info);

void socketinfo_set_socket_state(socketinfo *socket_info, SocketState socket_state);
SocketState socketinfo_get_socket_state(const socketinfo *socket_info);

void socketinfo_set_connected_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler);
void socketinfo_unset_connected_handler(socketinfo *socket_info);
const std::function<void (socketinfo *)> &socketinfo_get_connected_handler(const socketinfo *socket_info);

void socketinfo_set_disconnected_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler);
void socketinfo_unset_disconnected_handler(socketinfo *socket_info);
const std::function<void (socketinfo *)> &socketinfo_get_disconnected_handler(const socketinfo *socket_info);

void socketinfo_set_read_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler);
void socketinfo_unset_read_handler(socketinfo *socket_info);
const std::function<void (socketinfo *)> &socketinfo_get_read_handler(const socketinfo *socket_info);

void socketinfo_set_error_handler(socketinfo *socket_info, const std::function<void (socketinfo *, c_int32)> &handler);
void socketinfo_unset_error_handler(socketinfo *socket_info);
const std::function<void (socketinfo *, c_int32)> &socketinfo_get_error_handler(const socketinfo *socket_info);

/*! serverinfo */
serverinfo *serverinfo_new();
void serverinfo_free(serverinfo *server_info);

void serverinfo_set_evconnlistener(serverinfo *server_info, evconnlistener *ev_conn_listener);
evconnlistener *serverinfo_get_evconnlistener(const serverinfo *server_info);

void serverinfo_set_context(serverinfo *server_info, void *ctx);
void *serverinfo_get_context(const serverinfo *server_info);

void serverinfo_set_accept_handler(serverinfo *server_info, const std::function<void (serverinfo *, c_fdptr)> &handler);
void serverinfo_unset_accept_handler(serverinfo *server_info);
const std::function<void (serverinfo *, c_fdptr)> &serverinfo_get_accept_handler(const serverinfo *server_info);

void serverinfo_set_accept_error_handler(serverinfo *server_info, const std::function<void (serverinfo *, c_int32)> &handler);
void serverinfo_unset_accept_error_handler(serverinfo *server_info);
const std::function<void (serverinfo *, c_int32)> &serverinfo_get_accept_error_handler(const serverinfo *server_info);

#endif // EVENTDISPATCHER_TYPES_H
