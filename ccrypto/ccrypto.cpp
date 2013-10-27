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
#include "ccrypto.h"

//! OpenSSL Includes
#include <openssl/aes.h>
#include <openssl/evp.h>

//! Project Includes
#include "cdefines.h"

//! Defines
#define SHA1_DIGEST_LENGTH              20

void MD4_hash(const std::string &data, unsigned char *hash)
{
    MD4_CTX md4_ctx;
    MD4_Init(&md4_ctx);
    MD4_Update(&md4_ctx, data.c_str(), data.size());
    MD4_Final(hash, &md4_ctx);
}

void MD5_hash(const std::string &data, unsigned char *hash)
{
    MD5_CTX md5_ctx;
    MD5_Init(&md5_ctx);
    MD5_Update(&md5_ctx, data.c_str(), data.size());
    MD5_Final(hash, &md5_ctx);
}

void SHA1_hash(const std::string &data, unsigned char *hash)
{
    SHA_CTX sha_ctx;
    SHA1_Init(&sha_ctx);
    SHA1_Update(&sha_ctx, data.c_str(), data.size());
    SHA1_Final(hash, &sha_ctx);
}

void SHA224_hash(const std::string &data, unsigned char *hash)
{
    SHA256_CTX sha256_ctx;
    SHA224_Init(&sha256_ctx);
    SHA224_Update(&sha256_ctx, data.c_str(), data.size());
    SHA224_Final(hash, &sha256_ctx);
}

void SHA256_hash(const std::string &data, unsigned char *hash)
{
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, data.c_str(), data.size());
    SHA256_Final(hash, &sha256_ctx);
}

void SHA384_hash(const std::string &data, unsigned char *hash)
{
    SHA512_CTX sha512_ctx;
    SHA384_Init(&sha512_ctx);
    SHA384_Update(&sha512_ctx, data.c_str(), data.size());
    SHA384_Final(hash, &sha512_ctx);
}

void SHA512_hash(const std::string &data, unsigned char *hash)
{
    SHA512_CTX sha512_ctx;
    SHA512_Init(&sha512_ctx);
    SHA512_Update(&sha512_ctx, data.c_str(), data.size());
    SHA512_Final(hash, &sha512_ctx);
}

std::string AES256_cbc_encrypt(const std::string &data, const std::string &key, const std::string &iv)
{
    const auto in_len = static_cast<c_int32>(data.size());
    c_int32 out_len = 0;
    c_int32 total_len = 0;
    auto *encrypted_data = new unsigned char[static_cast<size_t>(in_len + AES_BLOCK_SIZE - 1)];
    unsigned char key_hash[SHA256_DIGEST_LENGTH];
    unsigned char iv_hash[SHA256_DIGEST_LENGTH];

    SHA256_hash(key, key_hash);
    SHA256_hash(iv, iv_hash);

    EVP_CIPHER_CTX evp_cipher_ctx;
    EVP_CIPHER_CTX_init(&evp_cipher_ctx);
    EVP_EncryptInit(&evp_cipher_ctx, EVP_aes_256_cbc(), key_hash, iv_hash);
    EVP_EncryptUpdate(&evp_cipher_ctx, encrypted_data, &out_len, reinterpret_cast<const unsigned char *>(data.c_str()), in_len);
    total_len += out_len;
    EVP_EncryptFinal(&evp_cipher_ctx, reinterpret_cast<unsigned char *>(encrypted_data + total_len), &out_len);
    total_len += out_len;
    EVP_CIPHER_CTX_cleanup(&evp_cipher_ctx);

    std::string encrypted(reinterpret_cast<const char *>(encrypted_data), total_len);

    delete[] encrypted_data;

    return encrypted;
}

std::string AES256_cbc_decrypt(const std::string &data, const std::string &key, const std::string &iv)
{
    const auto in_len = static_cast<c_int32>(data.size());
    c_int32 out_len = 0;
    c_int32 total_len = 0;
    auto *decrypted_data = new unsigned char[static_cast<size_t>(in_len)];
    unsigned char key_hash[SHA256_DIGEST_LENGTH];
    unsigned char iv_hash[SHA256_DIGEST_LENGTH];

    SHA256_hash(key, key_hash);
    SHA256_hash(iv, iv_hash);

    EVP_CIPHER_CTX evp_cipher_ctx;
    EVP_CIPHER_CTX_init(&evp_cipher_ctx);
    EVP_DecryptInit(&evp_cipher_ctx, EVP_aes_256_cbc(), key_hash, iv_hash);
    EVP_DecryptUpdate(&evp_cipher_ctx, decrypted_data, &out_len, reinterpret_cast<const unsigned char *>(data.c_str()), in_len);
    total_len += out_len;
    EVP_DecryptFinal(&evp_cipher_ctx, reinterpret_cast<unsigned char *>(decrypted_data + total_len), &out_len);
    total_len += out_len;
    EVP_CIPHER_CTX_cleanup(&evp_cipher_ctx);

    std::string decrypted(reinterpret_cast<const char *>(decrypted_data), total_len);

    delete[] decrypted_data;

    return decrypted;
}
