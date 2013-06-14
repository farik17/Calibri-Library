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
    void setSslErrorHandler(const std::function<void (socketinfo *, c_int32)> &handler);
    void unsetEncryptedHandler();
    void unsetSslErrorHandler();
    void setSslProtocol(CSSLProtocol sslProtocol);
    void setSslMode(CSSLMode sslMode);
    void setSslPeerVerifyMode(CSSLPeerVerifyMode sslPeerVerifyMode);
    void setSslCertificate(const std::string &certificatePath, CSSLFileType fileType);
    void setSslPrivateKey(const std::string &privateKeyPath, CSSLFileType fileType);

    std::string sslErrorString() const;

    c_ulong sslError() const;

    CSSLProtocol sslProtocol() const;
    CSSLMode sslMode() const;
    CSSLPeerVerifyMode sslPeerVerifyMode() const;

private:
    C_DISABLE_COPY(CSslSocket)
};

#endif // CSSLSOCKET_H
