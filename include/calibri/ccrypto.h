#ifndef CCRYPTO_H
#define CCRYPTO_H

//! Std Includes
#include <string>

void MD4_hash(const std::string &data, unsigned char *hash);
void MD5_hash(const std::string &data, unsigned char *hash);
void SHA1_hash(const std::string &data, unsigned char *hash);
void SHA224_hash(const std::string &data, unsigned char *hash);
void SHA256_hash(const std::string &data, unsigned char *hash);
void SHA384_hash(const std::string &data, unsigned char *hash);
void SHA512_hash(const std::string &data, unsigned char *hash);

std::string AES256_cbc_encrypt(const std::string &data, const std::string &key, const std::string &iv = "aes_ivec");
std::string AES256_cbc_decrypt(const std::string &data, const std::string &key, const std::string &iv = "aes_ivec");

#endif // CCRYPTO_H
