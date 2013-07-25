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

#ifndef CSSLSOCKET_H
#define CSSLSOCKET_H

//! CSocket Includes
#include "ctcpsocket.h"

class CSslSocket : public CTcpSocket
{
public:
    CSslSocket();
    virtual ~CSslSocket();

    void setEncryptedHandler(const std::function<void (socketinfo *)> &handler);
    void setSslErrorHandler(const std::function<void (socketinfo *, const c_ulong)> &handler);
    void setSslProtocol(const CSSLProtocol sslProtocol);
    void setSslMode(const CSSLMode sslMode);
    void setSslPeerVerifyMode(const CSSLPeerVerifyMode sslPeerVerifyMode);
    void setSslCertificate(const std::string &certificatePath, const CSSLFileType fileType);
    void setSslPrivateKey(const std::string &privateKeyPath, const CSSLFileType fileType);

    std::string sslErrorString() const;

    const c_ulong sslError() const;

    const CSSLProtocol sslProtocol() const;
    const CSSLMode sslMode() const;
    const CSSLPeerVerifyMode sslPeerVerifyMode() const;

private:
    C_DISABLE_COPY(CSslSocket)
};

#endif // CSSLSOCKET_H
