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
#include "cssl.h"

//! OpenSSL Includes
#include <openssl/rand.h>

void SSL_CTX_set_peer_verify_mode(SSL_CTX *ssl_ctx, const CSSLPeerVerifyMode sslPeerVerifyMode)
{
    switch (sslPeerVerifyMode) {
    case VerifyNone:
        SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_NONE, nullptr);

        break;

    case VerifyPeer:
        SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, nullptr);

        break;

    default:
#if defined(DEBUG)
        C_DEBUG("invalid ssl peer verify mode");
#endif
        break;
    }
}

SSL_CTX *SSL_CTX_create(const CSSLProtocol sslProtocol, const CSSLMode sslMode, const CSSLPeerVerifyMode sslPeerVerifyMode)
{
    SSL_CTX *ssl_ctx = nullptr;

    switch (sslProtocol) {
    case SSLv3_0:
        switch (sslMode) {
        case ServerMode:
            ssl_ctx = SSL_CTX_new(SSLv3_server_method());

            break;

        case ClientMode:
            ssl_ctx = SSL_CTX_new(SSLv3_client_method());

            break;

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            return nullptr;
        }

        break;

    case TLSv1_0:
        switch (sslMode) {
        case ServerMode:
            ssl_ctx = SSL_CTX_new(TLSv1_server_method());

            break;

        case ClientMode:
            ssl_ctx = SSL_CTX_new(TLSv1_client_method());

            break;

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            return nullptr;
        }

        break;

    case TLSv1_1:
        switch (sslMode) {
        case ServerMode:
            ssl_ctx = SSL_CTX_new(TLSv1_1_server_method());

            break;

        case ClientMode:
            ssl_ctx = SSL_CTX_new(TLSv1_1_client_method());

            break;

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            return nullptr;
        }

        break;

    case TLSv1_2:
        switch (sslMode) {
        case ServerMode:
            ssl_ctx = SSL_CTX_new(TLSv1_2_server_method());

            break;

        case ClientMode:
            ssl_ctx = SSL_CTX_new(TLSv1_2_client_method());

            break;

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            return nullptr;
        }

        break;

    default:
#if defined(DEBUG)
        C_DEBUG("invalid ssl protocol");
#endif
        return nullptr;
    }

    if (!ssl_ctx) {
#if defined(DEBUG)
        C_DEBUG("failed to initialize ssl context");
#endif
        return nullptr;
    }

    SSL_CTX_set_peer_verify_mode(ssl_ctx, sslPeerVerifyMode);

    return ssl_ctx;
}

const c_int32 SSL_init()
{
    SSL_load_error_strings();
    SSL_library_init();

#if defined(DEBUG)
    const auto result = RAND_poll();

    if (result != 1)
        C_DEBUG("failed ssl rand poll");

    return result;
#else
    return RAND_poll();
#endif
}

const c_int32 SSL_CTX_set_certificate(SSL_CTX *ssl_ctx, const std::string &certificatePath, const CSSLFileType fileType)
{
    switch (fileType) {
    case PEM: {
#if defined(DEBUG)
        const auto result = SSL_CTX_use_certificate_file(ssl_ctx, certificatePath.c_str(), SSL_FILETYPE_PEM);

        if (result != 1)
            C_DEBUG("invalid certificate path");

        return result;
#else
        return SSL_CTX_use_certificate_file(ssl_ctx, certificatePath.c_str(), SSL_FILETYPE_PEM);
#endif
    }

    case ASN1: {
#if defined(DEBUG)
        const auto result = SSL_CTX_use_certificate_file(ssl_ctx, certificatePath.c_str(), SSL_FILETYPE_ASN1);

        if (result != 1)
            C_DEBUG("invalid certificate path");

        return result;
#else
        return SSL_CTX_use_certificate_file(ssl_ctx, certificatePath.c_str(), SSL_FILETYPE_ASN1);
#endif
    }

    default:
#if defined(DEBUG)
        C_DEBUG("invalid file type");
#endif
        break;
    }

    return 0;
}

const c_int32 SSL_CTX_set_private_key(SSL_CTX *ssl_ctx, const std::string &privateKeyPath, const CSSLFileType fileType)
{
    switch (fileType) {
    case PEM: {
#if defined(DEBUG)
        const auto result = SSL_CTX_use_PrivateKey_file(ssl_ctx, privateKeyPath.c_str(), SSL_FILETYPE_PEM);

        if (result != 1)
            C_DEBUG("invalid private key path");

        return result;
#else
        return SSL_CTX_use_PrivateKey_file(ssl_ctx, privateKeyPath.c_str(), SSL_FILETYPE_PEM);
#endif
    }

    case ASN1: {
#if defined(DEBUG)
        const auto result = SSL_CTX_use_PrivateKey_file(ssl_ctx, privateKeyPath.c_str(), SSL_FILETYPE_ASN1);

        if (result != 1)
            C_DEBUG("invalid private key path");

        return result;
#else
        return SSL_CTX_use_PrivateKey_file(ssl_ctx, privateKeyPath.c_str(), SSL_FILETYPE_ASN1);
#endif
    }

    default:
#if defined(DEBUG)
        C_DEBUG("invalid file type");
#endif
        break;
    }

    return 0;
}

const c_int32 SSL_CTX_set_protocol(SSL_CTX *ssl_ctx, const CSSLProtocol sslProtocol, const CSSLMode sslMode)
{
    switch (sslProtocol) {
    case SSLv3_0:
        switch (sslMode) {
        case ServerMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, SSLv3_server_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, SSLv3_server_method());
#endif
        }

        case ClientMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, SSLv3_client_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, SSLv3_client_method());
#endif
        }

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            break;
        }

        break;

    case TLSv1_0:
        switch (sslMode) {
        case ServerMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_server_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_server_method());
#endif
        }

        case ClientMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_client_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_client_method());
#endif
        }

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            break;
        }

        break;

    case TLSv1_1:
        switch (sslMode) {
        case ServerMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_1_server_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_1_server_method());
#endif
        }

        case ClientMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_1_client_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_1_client_method());
#endif
        }

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            break;
        }

        break;

    case TLSv1_2:
        switch (sslMode) {
        case ServerMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_2_server_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_2_server_method());
#endif
        }

        case ClientMode: {
#if defined(DEBUG)
            const auto result = SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_2_client_method());

            if (result != 1)
                C_DEBUG("failed to set ssl context protocol");

            return result;
#else
            return SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_2_client_method());
#endif
        }

        default:
#if defined(DEBUG)
            C_DEBUG("invalid ssl mode");
#endif
            break;
        }

        break;

    default:
#if defined(DEBUG)
        C_DEBUG("invalid ssl protocol");
#endif
        break;
    }

    return 0;
}
