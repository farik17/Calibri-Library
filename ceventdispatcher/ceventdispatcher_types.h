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

#ifndef CEVENTDISPATCHER_TYPES_H
#define CEVENTDISPATCHER_TYPES_H

//! Std Includes
#include <functional>

//! CSsl Includes
#include "cssl.h"

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
void timerinfo_set_timer_handler(timerinfo *timer_info, std::function<void (timerinfo *)> &&handler);
const std::function<void (timerinfo *)> &timerinfo_get_timer_handler(const timerinfo *timer_info);

/*! sslinfo */
sslinfo *sslinfo_new();
void sslinfo_free(sslinfo *ssl_info);

void sslinfo_set_ssl_protocol(sslinfo *ssl_info, const CSSLProtocol ssl_protocol);
const CSSLProtocol sslinfo_get_ssl_protocol(const sslinfo *ssl_info);

void sslinfo_set_ssl_mode(sslinfo *ssl_info, const CSSLMode ssl_mode);
const CSSLMode sslinfo_get_ssl_mode(const sslinfo *ssl_info);

void sslinfo_set_ssl_peer_verify_mode(sslinfo *ssl_info, const CSSLPeerVerifyMode ssl_peer_verify_mode);
const CSSLPeerVerifyMode sslinfo_get_ssl_peer_verify_mode(const sslinfo *ssl_info);

void sslinfo_set_ssl_context(sslinfo *ssl_info, SSL_CTX *ssl_ctx);
SSL_CTX *sslinfo_get_ssl_context(const sslinfo *ssl_info);

void sslinfo_set_encrypted_handler(sslinfo *ssl_info, const std::function<void (socketinfo *)> &handler);
void sslinfo_set_encrypted_handler(sslinfo *ssl_info, std::function<void (socketinfo *)> &&handler);
const std::function<void (socketinfo *)> &sslinfo_get_encrypted_handler(const sslinfo *ssl_info);

void sslinfo_set_ssl_error_handler(sslinfo *ssl_info, const std::function<void (socketinfo *, const c_ulong)> &handler);
void sslinfo_set_ssl_error_handler(sslinfo *ssl_info, std::function<void (socketinfo *, const c_ulong)> &&handler);
const std::function<void (socketinfo *, const c_ulong)> &sslinfo_get_ssl_error_handler(const sslinfo *ssl_info);

/*! socketinfo */
enum CSocketState : c_uint8 {
    Unconnected = 1,
    Connecting,
    Connected,
    Closing
};

socketinfo *socketinfo_new();
void socketinfo_free(socketinfo *socket_info);

void socketinfo_set_socket_state(socketinfo *socket_info, const CSocketState socket_state);
const CSocketState socketinfo_get_socket_state(const socketinfo *socket_info);

void socketinfo_set_bufferevent(socketinfo *socket_info, bufferevent *buffer_event);
bufferevent *socketinfo_get_bufferevent(const socketinfo *socket_info);

void socketinfo_set_context(socketinfo *socket_info, void *ctx);
void *socketinfo_get_context(const socketinfo *socket_info);

void socketinfo_set_sslinfo(socketinfo *socket_info, sslinfo *ssl_info);
sslinfo *socketinfo_get_sslinfo(const socketinfo *socket_info);

void socketinfo_set_connected_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler);
void socketinfo_set_connected_handler(socketinfo *socket_info, std::function<void (socketinfo *)> &&handler);
const std::function<void (socketinfo *)> &socketinfo_get_connected_handler(const socketinfo *socket_info);

void socketinfo_set_disconnected_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler);
void socketinfo_set_disconnected_handler(socketinfo *socket_info, std::function<void (socketinfo *)> &&handler);
const std::function<void (socketinfo *)> &socketinfo_get_disconnected_handler(const socketinfo *socket_info);

void socketinfo_set_read_handler(socketinfo *socket_info, const std::function<void (socketinfo *)> &handler);
void socketinfo_set_read_handler(socketinfo *socket_info, std::function<void (socketinfo *)> &&handler);
const std::function<void (socketinfo *)> &socketinfo_get_read_handler(const socketinfo *socket_info);

void socketinfo_set_error_handler(socketinfo *socket_info, const std::function<void (socketinfo *, const c_int32)> &handler);
void socketinfo_set_error_handler(socketinfo *socket_info, std::function<void (socketinfo *, const c_int32)> &&handler);
const std::function<void (socketinfo *, const c_int32)> &socketinfo_get_error_handler(const socketinfo *socket_info);

/*! serverinfo */
serverinfo *serverinfo_new();
void serverinfo_free(serverinfo *server_info);

void serverinfo_set_evconnlistener(serverinfo *server_info, evconnlistener *ev_conn_listener);
evconnlistener *serverinfo_get_evconnlistener(const serverinfo *server_info);

void serverinfo_set_context(serverinfo *server_info, void *ctx);
void *serverinfo_get_context(const serverinfo *server_info);

void serverinfo_set_accept_handler(serverinfo *server_info, const std::function<void (serverinfo *, const c_fdptr)> &handler);
void serverinfo_set_accept_handler(serverinfo *server_info, std::function<void (serverinfo *, const c_fdptr)> &&handler);
const std::function<void (serverinfo *, const c_fdptr)> &serverinfo_get_accept_handler(const serverinfo *server_info);

void serverinfo_set_accept_error_handler(serverinfo *server_info, const std::function<void (serverinfo *, const c_int32)> &handler);
void serverinfo_set_accept_error_handler(serverinfo *server_info, std::function<void (serverinfo *, const c_int32)> &&handler);
const std::function<void (serverinfo *, const c_int32)> &serverinfo_get_accept_error_handler(const serverinfo *server_info);

#endif // CEVENTDISPATCHER_TYPES_H
