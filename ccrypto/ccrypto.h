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

#ifndef CCRYPTO_H
#define CCRYPTO_H

//! Std Includes
#include <string>

//! OpenSSL Includes
#include <openssl/md4.h>
#include <openssl/md5.h>
#include <openssl/sha.h>

void MD4_hash(const std::string &data, unsigned char *hash);
void MD5_hash(const std::string &data, unsigned char *hash);
void SHA1_hash(const std::string &data, unsigned char *hash);
void SHA224_hash(const std::string &data, unsigned char *hash);
void SHA256_hash(const std::string &data, unsigned char *hash);
void SHA384_hash(const std::string &data, unsigned char *hash);
void SHA512_hash(const std::string &data, unsigned char *hash);

const std::string AES256_cbc_encrypt(const std::string &data, const std::string &key, const std::string &iv = "aes_ivec");
const std::string AES256_cbc_decrypt(const std::string &data, const std::string &key, const std::string &iv = "aes_ivec");

#endif // CCRYPTO_H
