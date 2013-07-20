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
#include "csslsocket.h"

//! LibEvent Includes
#include <event2/bufferevent_ssl.h>

CSslSocket::CSslSocket()
    : CTcpSocket()
{
    sslinfo *ssl_info = sslinfo_new();
    sslinfo_set_ssl_ctx(ssl_info, SSL_CTX_create(sslinfo_get_ssl_protocol(ssl_info), sslinfo_get_ssl_mode(ssl_info), sslinfo_get_ssl_peer_verify_mode(ssl_info)));

    socketinfo_set_sslinfo(m_socketinfo, ssl_info);
    socketinfo_set_context(m_socketinfo, this);
}

CSslSocket::~CSslSocket()
{
    sslinfo_free(socketinfo_get_sslinfo(m_socketinfo));
}

void CSslSocket::setEncryptedHandler(const std::function<void (socketinfo *)> &handler)
{
    sslinfo_set_encrypted_handler(socketinfo_get_sslinfo(m_socketinfo), handler);
}

void CSslSocket::setSslErrorHandler(const std::function<void (socketinfo *, const c_ulong)> &handler)
{
    sslinfo_set_ssl_error_handler(socketinfo_get_sslinfo(m_socketinfo), handler);
}

void CSslSocket::setSslProtocol(const CSSLProtocol sslProtocol)
{
    sslinfo *ssl_info = socketinfo_get_sslinfo(m_socketinfo);

    if (sslinfo_get_ssl_protocol(ssl_info) == sslProtocol)
        return;

    sslinfo_set_ssl_protocol(ssl_info, sslProtocol);

    SSL_CTX_set_protocol(sslinfo_get_ssl_ctx(ssl_info), sslinfo_get_ssl_protocol(ssl_info), sslinfo_get_ssl_mode(ssl_info));
}

void CSslSocket::setSslMode(const CSSLMode sslMode)
{
    sslinfo *ssl_info = socketinfo_get_sslinfo(m_socketinfo);

    if (sslinfo_get_ssl_mode(ssl_info) == sslMode)
        return;

    sslinfo_set_ssl_mode(ssl_info, sslMode);

    SSL_CTX_set_protocol(sslinfo_get_ssl_ctx(ssl_info), sslinfo_get_ssl_protocol(ssl_info), sslinfo_get_ssl_mode(ssl_info));
}

void CSslSocket::setSslPeerVerifyMode(const CSSLPeerVerifyMode sslPeerVerifyMode)
{
    sslinfo *ssl_info = socketinfo_get_sslinfo(m_socketinfo);

    if (sslinfo_get_ssl_peer_verify_mode(ssl_info) == sslPeerVerifyMode)
        return;

    sslinfo_set_ssl_peer_verify_mode(ssl_info, sslPeerVerifyMode);

    SSL_CTX_set_peer_verify_mode(sslinfo_get_ssl_ctx(ssl_info), sslinfo_get_ssl_peer_verify_mode(ssl_info));
}

void CSslSocket::setSslCertificate(const std::string &certificatePath, const CSSLFileType fileType)
{
    SSL_CTX_set_certificate(sslinfo_get_ssl_ctx(socketinfo_get_sslinfo(m_socketinfo)), certificatePath, fileType);
}

void CSslSocket::setSslPrivateKey(const std::string &privateKeyPath, const CSSLFileType fileType)
{
    SSL_CTX_set_private_key(sslinfo_get_ssl_ctx(socketinfo_get_sslinfo(m_socketinfo)), privateKeyPath, fileType);
}

const std::string CSslSocket::sslErrorString() const
{
    return ERR_error_string(sslError(), nullptr);
}

const c_ulong CSslSocket::sslError() const
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return 0;

    return bufferevent_get_openssl_error(socketinfo_get_bufferevent(m_socketinfo));
}

const CSSLProtocol CSslSocket::sslProtocol() const
{
    return sslinfo_get_ssl_protocol(socketinfo_get_sslinfo(m_socketinfo));
}

const CSSLMode CSslSocket::sslMode() const
{
    return sslinfo_get_ssl_mode(socketinfo_get_sslinfo(m_socketinfo));
}

const CSSLPeerVerifyMode CSslSocket::sslPeerVerifyMode() const
{
    return sslinfo_get_ssl_peer_verify_mode(socketinfo_get_sslinfo(m_socketinfo));
}
