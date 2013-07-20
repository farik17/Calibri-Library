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
#include "ctcpsocket.h"

//! Platform Includes
#if defined(__unix__) || defined(__linux__)
#   include <netinet/tcp.h>
#endif

//! LibEvent Includes
#include <event2/bufferevent.h>

CTcpSocket::CTcpSocket()
    : m_socketinfo(socketinfo_new())
{
    socketinfo_set_context(m_socketinfo, this);
}

CTcpSocket::~CTcpSocket()
{
    close(true);

    socketinfo_free(m_socketinfo);
}

void CTcpSocket::setConnectedHandler(const std::function<void (socketinfo *)> &handler)
{
    socketinfo_set_connected_handler(m_socketinfo, handler);
}

void CTcpSocket::setDisconnectedHandler(const std::function<void (socketinfo *)> &handler)
{
    socketinfo_set_disconnected_handler(m_socketinfo, handler);
}

void CTcpSocket::setReadHandler(const std::function<void (socketinfo *)> &handler)
{
    socketinfo_set_read_handler(m_socketinfo, handler);
}

void CTcpSocket::setErrorHandler(const std::function<void (socketinfo *, const c_int32)> &handler)
{
    socketinfo_set_error_handler(m_socketinfo, handler);
}

void CTcpSocket::connectToHost(const std::string &address, const c_uint16 port)
{
    if (state() != Unconnected)
        return;

    CEventDispatcher::instance()->connectSocket(m_socketinfo, address, port);
}

void CTcpSocket::close(const bool force)
{    
    if (state() != Connected)
        return;

    CEventDispatcher::instance()->closeSocket(m_socketinfo, force);
}

const std::string CTcpSocket::address() const
{
    return CEventDispatcher::socketAddress(socketDescriptor());
}

const std::string CTcpSocket::errorString() const
{
    return evutil_socket_error_to_string(error());
}

const size_t CTcpSocket::bytesAvailable() const
{
    if (state() != Connected)
        return 0;

    return evbuffer_get_length(bufferevent_get_input(socketinfo_get_bufferevent(m_socketinfo)));
}

const size_t CTcpSocket::write(const char *data, const size_t len)
{
    if (state() != Connected)
        return 0;

    if (bufferevent_write(socketinfo_get_bufferevent(m_socketinfo), data, len) != 0)
        return 0;

    return len;
}

const size_t CTcpSocket::read(char *data, const size_t len)
{
    if (state() != Connected)
        return 0;

    return bufferevent_read(socketinfo_get_bufferevent(m_socketinfo), data, len);
}

const c_fdptr CTcpSocket::socketDescriptor() const
{
    if (state() != Connected)
        return 0;

    return bufferevent_getfd(socketinfo_get_bufferevent(m_socketinfo));
}

const c_int32 CTcpSocket::error() const
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return 0;

    return evutil_socket_geterror(fd);
}

const c_uint16 CTcpSocket::port() const
{
    return CEventDispatcher::socketPort(socketDescriptor());
}

const CSocketState CTcpSocket::state() const
{
    return socketinfo_get_socket_state(m_socketinfo);
}

const bool CTcpSocket::atEnd() const
{
    return bytesAvailable() == 0;
}

const bool CTcpSocket::setSocketDescriptor(const c_fdptr fd)
{
    if (state() != Unconnected)
        return false;

    CEventDispatcher::instance()->acceptSocket(m_socketinfo, fd);

    if (state() != Connected)
        return false;

    return true;
}

const bool CTcpSocket::setNoDelay(const c_uint32 flag)
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return false;

#if defined(_WIN32)
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char *>(&flag), sizeof(c_uint32)) != 0)
#elif defined(__unix__) || defined(__linux__)
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(c_uint32)) != 0)
#endif
        return false;

    return true;
}

const bool CTcpSocket::setKeepAlive(const c_uint32 flag, const c_uint32 idle, const c_uint32 interval, const c_uint32 count)
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return false;

#if defined(_WIN32)
    C_UNUSED(flag);
    C_UNUSED(idle);
    C_UNUSED(interval);
    C_UNUSED(count);

    return false;
#elif defined(__unix__) || defined(__linux__)
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &flag, sizeof(c_uint32)) != 0)
        return false;

    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(c_uint32)) != 0)
        return false;

    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(c_uint32)) != 0)
        return false;

    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, sizeof(c_uint32)) != 0)
        return false;

    return true;
#endif
}
