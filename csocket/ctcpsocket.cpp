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
    close();

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

void CTcpSocket::setErrorHandler(const std::function<void (socketinfo *, c_int32)> &handler)
{
    socketinfo_set_error_handler(m_socketinfo, handler);
}

void CTcpSocket::unsetConnectedHandler()
{
    socketinfo_unset_connected_handler(m_socketinfo);
}

void CTcpSocket::unsetDisconnectedHandler()
{
    socketinfo_unset_disconnected_handler(m_socketinfo);
}

void CTcpSocket::unsetReadHandler()
{
    socketinfo_unset_read_handler(m_socketinfo);
}

void CTcpSocket::unsetErrorHandler()
{
    socketinfo_unset_error_handler(m_socketinfo);
}

void CTcpSocket::connectToHost(const std::string &address, c_uint16 port)
{
    if (state() != Unconnected)
        return;

    CEventDispatcher::instance()->connectSocket(m_socketinfo, address, port);
}

void CTcpSocket::close(bool force)
{    
    if (state() != Connected)
        return;

    CEventDispatcher::instance()->closeSocket(m_socketinfo, force);
}

std::string CTcpSocket::address() const
{
    return CEventDispatcher::instance()->socketAddress(socketDescriptor());
}

std::string CTcpSocket::errorString() const
{
    return evutil_socket_error_to_string(error());
}

size_t CTcpSocket::bytesAvailable() const
{
    if (state() != Connected)
        return 0;

    return evbuffer_get_length(bufferevent_get_input(socketinfo_get_bufferevent(m_socketinfo)));
}

size_t CTcpSocket::write(const char *data, size_t len)
{
    if (state() != Connected)
        return 0;

    if (bufferevent_write(socketinfo_get_bufferevent(m_socketinfo), data, len) != 0)
        return 0;

    return len;
}

size_t CTcpSocket::read(char *data, size_t len)
{
    if (state() != Connected)
        return 0;

    return bufferevent_read(socketinfo_get_bufferevent(m_socketinfo), data, len);
}

c_fdptr CTcpSocket::socketDescriptor() const
{
    if (state() != Connected)
        return 0;

    return bufferevent_getfd(socketinfo_get_bufferevent(m_socketinfo));
}

c_int32 CTcpSocket::error() const
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return 0;

    return evutil_socket_geterror(fd);
}

c_uint16 CTcpSocket::port() const
{
    return CEventDispatcher::instance()->socketPort(socketDescriptor());
}

CSocketState CTcpSocket::state() const
{
    return socketinfo_get_socket_state(m_socketinfo);
}

bool CTcpSocket::atEnd() const
{
    return bytesAvailable() == 0;
}

bool CTcpSocket::setSocketDescriptor(c_fdptr fd)
{
    if (state() != Unconnected)
        return false;

    CEventDispatcher::instance()->acceptSocket(m_socketinfo, fd);

    if (state() != Connected)
        return false;

    return true;
}

bool CTcpSocket::setNoDelay(c_uint32 flag)
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return false;

#if defined(_WIN32)
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<const char *>(&flag), 4) != 0)
#elif defined(__unix__) || defined(__linux__)
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &flag, 4) != 0)
#endif
        return false;

    return true;
}

bool CTcpSocket::setKeepAlive(c_uint32 flag, c_uint32 idle, c_uint32 interval, c_uint32 count)
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
    if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &flag, 4) != 0)
        return false;

    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE, &idle, 4) != 0)
        return false;

    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL, &interval, 4) != 0)
        return false;

    if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT, &count, 4) != 0)
        return false;

    return true;
#endif
}