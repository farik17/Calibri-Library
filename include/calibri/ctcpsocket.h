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

#ifndef CTCPSOCKET_H
#define CTCPSOCKET_H

//! CEventDispatcher Includes
#include "ceventdispatcher.h"

class CTcpSocket
{
public:
    CTcpSocket();
    virtual ~CTcpSocket();

    void setConnectedHandler(const std::function<void (socketinfo *)> &handler);
    void setConnectedHandler(std::function<void (socketinfo *)> &&handler);
    void setDisconnectedHandler(const std::function<void (socketinfo *)> &handler);
    void setDisconnectedHandler(std::function<void (socketinfo *)> &&handler);
    void setReadHandler(const std::function<void (socketinfo *)> &handler);
    void setReadHandler(std::function<void (socketinfo *)> &&handler);
    void setWriteHandler(const std::function<void (socketinfo *)> &handler);
    void setWriteHandler(std::function<void (socketinfo *)> &&handler);
    void setErrorHandler(const std::function<void (socketinfo *, const c_int32)> &handler);
    void setErrorHandler(std::function<void (socketinfo *, const c_int32)> &&handler);
    void connectToHost(const std::string &address, const c_uint16 port);
    void close(const bool force = false);

    std::string address() const;
    std::string errorString() const;

    const size_t bytesToRead() const;
    const size_t bytesToWrite() const;
    const size_t write(const char *data, const size_t len);
    const size_t read(char *data, const size_t len);

    const c_fdptr socketDescriptor() const;

    const c_int32 error() const;

    const c_uint16 port() const;

    const CSocketState state() const;

    const bool setSocketDescriptor(const c_fdptr fd);
    const bool setNoDelay(const c_uint32 flag);
    const bool setKeepAlive(const c_uint32 flag, const c_uint32 idle = 0, const c_uint32 interval = 0, const c_uint32 count = 0);

protected:
    socketinfo *m_socketinfo;

private:    
    C_DISABLE_COPY(CTcpSocket)
};

#endif // CTCPSOCKET_H
