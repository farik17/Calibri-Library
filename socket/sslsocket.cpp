//! Self Includes
#include "sslsocket.h"

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

void CSslSocket::setSslErrorHandler(const std::function<void (socketinfo *, c_int32)> &handler)
{
    sslinfo_set_ssl_error_handler(socketinfo_get_sslinfo(m_socketinfo), handler);
}

void CSslSocket::unsetEncryptedHandler()
{
    sslinfo_unset_encrypted_handler(socketinfo_get_sslinfo(m_socketinfo));
}

void CSslSocket::unsetSslErrorHandler()
{
    sslinfo_unset_ssl_error_handler(socketinfo_get_sslinfo(m_socketinfo));
}

void CSslSocket::setSslProtocol(SSLProtocol sslProtocol)
{
    sslinfo *ssl_info = socketinfo_get_sslinfo(m_socketinfo);

    if (sslinfo_get_ssl_protocol(ssl_info) == sslProtocol)
        return;

    sslinfo_set_ssl_protocol(ssl_info, sslProtocol);

    SSL_CTX_set_protocol(sslinfo_get_ssl_ctx(ssl_info), sslinfo_get_ssl_protocol(ssl_info), sslinfo_get_ssl_mode(ssl_info));
}

void CSslSocket::setSslMode(SSLMode sslMode)
{
    sslinfo *ssl_info = socketinfo_get_sslinfo(m_socketinfo);

    if (sslinfo_get_ssl_mode(ssl_info) == sslMode)
        return;

    sslinfo_set_ssl_mode(ssl_info, sslMode);

    SSL_CTX_set_protocol(sslinfo_get_ssl_ctx(ssl_info), sslinfo_get_ssl_protocol(ssl_info), sslinfo_get_ssl_mode(ssl_info));
}

void CSslSocket::setSslPeerVerifyMode(SSLPeerVerifyMode sslPeerVerifyMode)
{
    sslinfo *ssl_info = socketinfo_get_sslinfo(m_socketinfo);

    if (sslinfo_get_ssl_peer_verify_mode(ssl_info) == sslPeerVerifyMode)
        return;

    sslinfo_set_ssl_peer_verify_mode(ssl_info, sslPeerVerifyMode);

    SSL_CTX_set_peer_verify_mode(sslinfo_get_ssl_ctx(ssl_info), sslinfo_get_ssl_peer_verify_mode(ssl_info));
}

void CSslSocket::setSslCertificate(const std::string &certificate)
{
    SSL_CTX_set_certificate(sslinfo_get_ssl_ctx(socketinfo_get_sslinfo(m_socketinfo)), certificate);
}

void CSslSocket::setSslPrivateKey(const std::string &privateKey)
{
    SSL_CTX_set_private_key(sslinfo_get_ssl_ctx(socketinfo_get_sslinfo(m_socketinfo)), privateKey);
}

std::string CSslSocket::sslErrorString() const
{
    return ERR_error_string(sslError(), nullptr);
}

c_ulong CSslSocket::sslError() const
{
    c_fdptr fd = socketDescriptor();
    if (fd == 0)
        return 0;

    return bufferevent_get_openssl_error(socketinfo_get_bufferevent(m_socketinfo));
}

SSLProtocol CSslSocket::sslProtocol() const
{
    return sslinfo_get_ssl_protocol(socketinfo_get_sslinfo(m_socketinfo));
}

SSLMode CSslSocket::sslMode() const
{
    return sslinfo_get_ssl_mode(socketinfo_get_sslinfo(m_socketinfo));
}

SSLPeerVerifyMode CSslSocket::sslPeerVerifyMode() const
{
    return sslinfo_get_ssl_peer_verify_mode(socketinfo_get_sslinfo(m_socketinfo));
}
