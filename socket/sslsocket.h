#ifndef SSLSOCKET_H
#define SSLSOCKET_H

//! Socket Includes
#include "tcpsocket.h"

class CSslSocket : public CTcpSocket
{
public:
    CSslSocket();
    virtual ~CSslSocket();

    void setEncryptedHandler(const std::function<void (socketinfo *)> &handler);
    void setSslErrorHandler(const std::function<void (socketinfo *, c_int32)> &handler);
    void unsetEncryptedHandler();
    void unsetSslErrorHandler();
    void setSslProtocol(SSLProtocol sslProtocol);
    void setSslMode(SSLMode sslMode);
    void setSslPeerVerifyMode(SSLPeerVerifyMode sslPeerVerifyMode);
    void setSslCertificate(const std::string &certificate);
    void setSslPrivateKey(const std::string &privateKey);

    std::string sslErrorString() const;

    c_ulong sslError() const;

    SSLProtocol sslProtocol() const;
    SSLMode sslMode() const;
    SSLPeerVerifyMode sslPeerVerifyMode() const;

private:
    C_DISABLE_COPY(CSslSocket)
};

#endif // SSLSOCKET_H
