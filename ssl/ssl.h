#ifndef SSL_H
#define SSL_H

//! OpenSSL Includes
#include <openssl/ssl.h>
#include <openssl/err.h>

//! Project Includes
#include "defines.h"

enum SSLProtocol : c_uint8 {
    SSLv3_0         = 1,
    TLSv1_0         = 2,
    TLSv1_1         = 3,
    TLSv1_2         = 4
};

enum SSLMode : c_uint8 {
    ClientMode      = 1,
    ServerMode      = 2
};

enum SSLPeerVerifyMode : c_uint8 {
    VerifyNone      = 1,
    VerifyPeer      = 2
};

enum SSLFileType : c_uint8 {
    PEM             = 1,
    ASN1            = 2
};

SSL_CTX *SSL_CTX_create(SSLProtocol sslProtocol, SSLMode sslMode, SSLPeerVerifyMode sslPeerVerifyMode);

void SSL_init();
void SSL_CTX_set_certificate(SSL_CTX *ssl_ctx, const std::string &certificatePath, SSLFileType fileType);
void SSL_CTX_set_private_key(SSL_CTX *ssl_ctx, const std::string &privateKeyPath, SSLFileType fileType);
void SSL_CTX_set_protocol(SSL_CTX *ssl_ctx, SSLProtocol sslProtocol, SSLMode sslMode);
void SSL_CTX_set_peer_verify_mode(SSL_CTX *ssl_ctx, SSLPeerVerifyMode sslPeerVerifyMode);

#endif // SSL_H
