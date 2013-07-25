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
#include "ctcpserver.h"

//! LibEvent Includes
#include <event2/listener.h>

CTcpServer::CTcpServer()
    : m_serverinfo(serverinfo_new())
{
    serverinfo_set_context(m_serverinfo, this);
}

CTcpServer::~CTcpServer()
{
    close();

    serverinfo_free(m_serverinfo);
}

void CTcpServer::setAcceptHandler(const std::function<void (serverinfo *, const c_fdptr)> &handler)
{
    serverinfo_set_accept_handler(m_serverinfo, handler);
}

void CTcpServer::setAcceptErrorHandler(const std::function<void (serverinfo *, const c_int32)> &handler)
{
    serverinfo_set_accept_error_handler(m_serverinfo, handler);
}

void CTcpServer::setEnable(const bool enable)
{
    if (!isListening())
        return;

    if (enable)
        evconnlistener_enable(serverinfo_get_evconnlistener(m_serverinfo));
    else
        evconnlistener_disable(serverinfo_get_evconnlistener(m_serverinfo));
}

const bool CTcpServer::isListening() const
{
    return serverinfo_get_evconnlistener(m_serverinfo) != nullptr;
}

const bool CTcpServer::listen(const std::string &address, const c_uint16 port, const c_int32 backlog)
{
    if (isListening())
        return false;

    CEventDispatcher::instance()->bindServer(m_serverinfo, address, port, backlog);

    return isListening();
}

const bool CTcpServer::close()
{
    if (!isListening())
        return false;

    CEventDispatcher::instance()->closeServer(m_serverinfo);

    return isListening();
}

std::string CTcpServer::address() const
{
    return CEventDispatcher::instance()->socketAddress(socketDescriptor());
}

std::string CTcpServer::errorString() const
{
    return evutil_socket_error_to_string(error());
}

const c_fdptr CTcpServer::socketDescriptor() const
{
    if (!isListening())
        return 0;

    return evconnlistener_get_fd(serverinfo_get_evconnlistener(m_serverinfo));
}

const c_int32 CTcpServer::error() const
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return 0;

    return evutil_socket_geterror(fd);
}

const c_uint16 CTcpServer::port() const
{
    return CEventDispatcher::instance()->socketPort(socketDescriptor());
}
