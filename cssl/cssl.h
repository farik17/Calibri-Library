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

#ifndef CSSL_H
#define CSSL_H

//! Std Includes
#include <string>

//! OpenSSL Includes
#include <openssl/ssl.h>
#include <openssl/err.h>

//! Project Includes
#include "cdefines.h"

enum CSSLProtocol : c_uint8 {
    SSLv3_0         = 1,
    TLSv1_0         = 2,
    TLSv1_1         = 3,
    TLSv1_2         = 4
};

enum CSSLMode : c_uint8 {
    ClientMode      = 1,
    ServerMode      = 2
};

enum CSSLPeerVerifyMode : c_uint8 {
    VerifyNone      = 1,
    VerifyPeer      = 2
};

enum CSSLFileType : c_uint8 {
    PEM             = 1,
    ASN1            = 2
};

SSL_CTX *SSL_CTX_create(CSSLProtocol sslProtocol, CSSLMode sslMode, CSSLPeerVerifyMode sslPeerVerifyMode);

void SSL_init();
void SSL_CTX_set_certificate(SSL_CTX *ssl_ctx, const std::string &certificatePath, CSSLFileType fileType);
void SSL_CTX_set_private_key(SSL_CTX *ssl_ctx, const std::string &privateKeyPath, CSSLFileType fileType);
void SSL_CTX_set_protocol(SSL_CTX *ssl_ctx, CSSLProtocol sslProtocol, CSSLMode sslMode);
void SSL_CTX_set_peer_verify_mode(SSL_CTX *ssl_ctx, CSSLPeerVerifyMode sslPeerVerifyMode);

#endif // CSSL_H
