//! Self Includes
#include "ssl.h"

//! Std Includes
#include <iostream>

//! OpenSSL Includes
#include <openssl/rand.h>

SSL_CTX *SSL_CTX_create(SSLProtocol sslProtocol, SSLMode sslMode, SSLPeerVerifyMode sslPeerVerifyMode)
{
    SSL_CTX *ssl_ctx = nullptr;

    switch (sslProtocol) {
    case SSLv3_0:
        switch (sslMode) {
        case SSLServerMode:
            ssl_ctx = SSL_CTX_new(SSLv3_server_method());
            break;

        case SSLClientMode:
            ssl_ctx = SSL_CTX_new(SSLv3_client_method());
            break;

        default:
            std::cout << "SSL_CTX_create error: invalid ssl mode" << std::endl;
            return nullptr;
        }

        break;

    case TLSv1_0:
        switch (sslMode) {
        case SSLServerMode:
            ssl_ctx = SSL_CTX_new(TLSv1_server_method());
            break;

        case SSLClientMode:
            ssl_ctx = SSL_CTX_new(TLSv1_client_method());
            break;

        default:
            std::cout << "SSL_CTX_create error: invalid ssl mode" << std::endl;
            return nullptr;
        }

        break;

    case TLSv1_1:
        switch (sslMode) {
        case SSLServerMode:
            ssl_ctx = SSL_CTX_new(TLSv1_1_server_method());
            break;

        case SSLClientMode:
            ssl_ctx = SSL_CTX_new(TLSv1_1_client_method());
            break;

        default:
            std::cout << "SSL_CTX_create error: invalid ssl mode" << std::endl;
            return nullptr;
        }

        break;

    case TLSv1_2:
        switch (sslMode) {
        case SSLServerMode:
            ssl_ctx = SSL_CTX_new(TLSv1_2_server_method());
            break;

        case SSLClientMode:
            ssl_ctx = SSL_CTX_new(TLSv1_2_client_method());
            break;

        default:
            std::cout << "SSL_CTX_create error: invalid ssl mode" << std::endl;
            return nullptr;
        }

        break;

    default:
        std::cout << "SSL_CTX_create error: invalid ssl protocol" << std::endl;
        return nullptr;
    }

    if (!ssl_ctx) {
        std::cout << "SSL_CTX_create error: failed to initialize ssl context" << std::endl;
        return nullptr;
    }

    SSL_CTX_set_peer_verify_mode(ssl_ctx, sslPeerVerifyMode);

    return ssl_ctx;
}

void SSL_init()
{
    SSL_load_error_strings();
    SSL_library_init();

    if (RAND_poll() != 1)
        std::cout << "initialize error: failed ssl rand poll" << std::endl;
}

void SSL_CTX_set_certificate(SSL_CTX *ssl_ctx, const std::string &certificate)
{
    if (SSL_CTX_use_certificate_file(ssl_ctx, certificate.c_str(), SSL_FILETYPE_PEM) != 1)
        std::cout << "SSL_CTX_set_certificate error: invalid certificate path" << std::endl;
}

void SSL_CTX_set_private_key(SSL_CTX *ssl_ctx, const std::string &privateKey)
{
    if (SSL_CTX_use_PrivateKey_file(ssl_ctx, privateKey.c_str(), SSL_FILETYPE_PEM) != 1)
        std::cout << "SSL_CTX_set_private_key error: invalid private key path" << std::endl;
}

void SSL_CTX_set_protocol(SSL_CTX *ssl_ctx, SSLProtocol sslProtocol, SSLMode sslMode)
{
    switch (sslProtocol) {
    case SSLv3_0:
        switch (sslMode) {
        case SSLServerMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, SSLv3_server_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        case SSLClientMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, SSLv3_client_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        default:
            std::cout << "SSL_CTX_set_protocol error: invalid ssl mode" << std::endl;
            break;
        }

        break;

    case TLSv1_0:
        switch (sslMode) {
        case SSLServerMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_server_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        case SSLClientMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_client_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        default:
            std::cout << "SSL_CTX_set_protocol error: invalid ssl mode" << std::endl;
            break;
        }

        break;

    case TLSv1_1:
        switch (sslMode) {
        case SSLServerMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_1_server_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        case SSLClientMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_1_client_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        default:
            std::cout << "SSL_CTX_set_protocol error: invalid ssl mode" << std::endl;
            break;
        }

        break;

    case TLSv1_2:
        switch (sslMode) {
        case SSLServerMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_2_server_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        case SSLClientMode:
            if (SSL_CTX_set_ssl_version(ssl_ctx, TLSv1_2_client_method()) != 1)
                std::cout << "SSL_CTX_set_protocol error: failed to set ssl context protocol" << std::endl;
            break;

        default:
            std::cout << "SSL_CTX_set_protocol error: invalid ssl mode" << std::endl;
            break;
        }

        break;

    default:
        std::cout << "SSL_CTX_set_protocol error: invalid ssl protocol" << std::endl;
        break;
    }
}

void SSL_CTX_set_peer_verify_mode(SSL_CTX *ssl_ctx, SSLPeerVerifyMode sslPeerVerifyMode)
{
    switch (sslPeerVerifyMode) {
    case SSLVerifyNone:
        SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_NONE, nullptr);
        break;

    case SSLVerifyPeer:
        SSL_CTX_set_verify(ssl_ctx, SSL_VERIFY_PEER, nullptr);
        break;

    default:
        std::cout << "SSL_CTX_set_peer_verify_mode error: invalid ssl peer verify mode" << std::endl;
        break;
    }
}
