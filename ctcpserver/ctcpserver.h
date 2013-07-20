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

#ifndef CTCPSERVER_H
#define CTCPSERVER_H

//! CEventDispatcher Includes
#include "ceventdispatcher.h"

class CTcpServer
{
public:
    CTcpServer();
    virtual ~CTcpServer();

    void setAcceptHandler(const std::function<void (serverinfo *, const c_fdptr)> &handler);
    void setAcceptErrorHandler(const std::function<void (serverinfo *, const c_int32)> &handler);
    void setEnable(const bool enable = true);

    const bool isListening() const;
    const bool listen(const std::string &address, const c_uint16 port, const c_int32 backlog = -1);
    const bool close();

    const std::string address() const;
    const std::string errorString() const;

    const c_fdptr socketDescriptor() const;

    const c_int32 error() const;

    const c_uint16 port() const;

private:    
    C_DISABLE_COPY(CTcpServer)

    serverinfo *m_serverinfo;
};

#endif // CTCPSERVER_H
