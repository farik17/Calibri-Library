#ifndef CIPHER_H
#define CIPHER_H

//! Std Includes
#include <type_traits>

//! OpenSSL Includes
#include <openssl/evp.h>

//! Calibri-Library Includes
#include "tools/buffer.h"

namespace Calibri {

enum class CipherType : uint8 {
#if !defined(OPENSSL_NO_AES)
    AES128ecb,
    AES128cbc,
    AES128cfb,
    AES128ofb,
    AES128ctr,
    AES192ecb,
    AES192cbc,
    AES192cfb,
    AES192ofb,
    AES192ctr,
    AES256ecb,
    AES256cbc,
    AES256cfb,
    AES256ofb,
    AES256ctr,
#endif

#if !defined(OPENSSL_NO_DES)
    DESecb,
    DEScbc,
    DEScfb,
    DESofb,
    DoubleDESecb,
    DoubleDEScbc,
    DoubleDEScfb,
    DoubleDESofb,
    TripleDESecb,
    TripleDEScbc,
    TripleDEScfb,
    TripleDESofb,
    DESXcbc,
#endif

#if !defined(OPENSSL_NO_IDEA)
    IDEAecb,
    IDEAcbc,
    IDEAcfb,
    IDEAofb,
#endif

#if !defined(OPENSSL_NO_RC5)
    RC5ecb,
    RC5cbc,
    RC5cfb,
    RC5ofb,
#endif

#if !defined(OPENSSL_NO_RC4)
    RC4,
#endif

#if !defined(OPENSSL_NO_RC2)
    RC2ecb,
    RC2cbc,
    RC2cfb,
    RC2ofb,
#endif

#if !defined(OPENSSL_NO_BF)
    BFecb,
    BFcbc,
    BFcfb,
    BFofb,
#endif

#if !defined(OPENSSL_NO_CAST)
    CAST5ecb,
    CAST5cbc,
    CAST5cfb,
    CAST5ofb,
#endif

#if !defined(OPENSSL_NO_CAMELLIA)
    CAMELLIA128ecb,
    CAMELLIA128cbc,
    CAMELLIA128cfb,
    CAMELLIA128ofb,
    CAMELLIA192ecb,
    CAMELLIA192cbc,
    CAMELLIA192cfb,
    CAMELLIA192ofb,
    CAMELLIA256ecb,
    CAMELLIA256cbc,
    CAMELLIA256cfb,
    CAMELLIA256ofb,
#endif

    Null
};

enum class CipherMode : uint8 {
    Encrypt,
    Decrypt
};

namespace Internal {

#if !defined(OPENSSL_NO_AES)
template<CipherType Type, typename std::enable_if<Type == CipherType::AES128ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_128_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES128cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_128_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES128cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_128_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES128ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_128_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES128ctr>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_128_ctr(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES192ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_192_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES192cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_192_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES192cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_192_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES192ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_192_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES192ctr>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_192_ctr(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES256ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_256_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES256cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_256_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES256cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_256_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES256ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_256_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::AES256ctr>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_aes_256_ctr(); }
#endif

#if !defined(OPENSSL_NO_DES)
template<CipherType Type, typename std::enable_if<Type == CipherType::DESecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DEScbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DEScfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DESofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DoubleDESecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DoubleDEScbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DoubleDEScfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DoubleDESofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::TripleDESecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede3_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::TripleDEScbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede3_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::TripleDEScfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede3_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::TripleDESofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_des_ede3_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::DESXcbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_desx_cbc(); }
#endif

#if !defined(OPENSSL_NO_IDEA)
template<CipherType Type, typename std::enable_if<Type == CipherType::IDEAecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_idea_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::IDEAcbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_idea_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::IDEAcfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_idea_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::IDEAofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_idea_ofb(); }
#endif

#if !defined(OPENSSL_NO_RC5)
template<CipherType Type, typename std::enable_if<Type == CipherType::RC5ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc5_32_12_16_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::RC5cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc5_32_12_16_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::RC5cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc5_32_12_16_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::RC5ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc5_32_12_16_ofb(); }
#endif

#if !defined(OPENSSL_NO_RC4)
template<CipherType Type, typename std::enable_if<Type == CipherType::RC4>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc4(); }
#endif

#if !defined(OPENSSL_NO_RC2)
template<CipherType Type, typename std::enable_if<Type == CipherType::RC2ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc2_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::RC2cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc2_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::RC2cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc2_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::RC2ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_rc2_ofb(); }
#endif

#if !defined(OPENSSL_NO_BF)
template<CipherType Type, typename std::enable_if<Type == CipherType::BFecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_bf_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::BFcbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_bf_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::BFcfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_bf_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::BFofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_bf_ofb(); }
#endif

#if !defined(OPENSSL_NO_CAST)
template<CipherType Type, typename std::enable_if<Type == CipherType::CAST5ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_cast5_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAST5cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_cast5_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAST5cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_cast5_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAST5ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_cast5_ofb(); }
#endif

#if !defined(OPENSSL_NO_CAMELLIA)
template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA128ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_128_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA128cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_128_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA128cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_128_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA128ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_128_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA192ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_192_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA192cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_192_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA192cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_192_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA192ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_192_ofb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA256ecb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_256_ecb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA256cbc>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_256_cbc(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA256cfb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_256_cfb(); }

template<CipherType Type, typename std::enable_if<Type == CipherType::CAMELLIA256ofb>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_camellia_256_ofb(); }
#endif

template<CipherType Type, typename std::enable_if<Type == CipherType::Null>::type... Enabler>
auto cipherAlgorithm() -> const EVP_CIPHER * { return EVP_enc_null(); }

} // namespace Internal

template<CipherType Type, CipherMode Mode, typename std::enable_if<Mode == CipherMode::Encrypt>::type... Enabler>
auto cipher(const Buffer &data, Buffer &key, const Buffer &iv = "iv") -> Buffer
{
    const auto dataBytes = static_cast<int32>(data.size());
    int32 processedBytes {};
    int32 encryptedBytes {};

    auto cipherAlgorithm = Internal::cipherAlgorithm<Type>();
    Buffer encryptedData(dataBytes + EVP_CIPHER_block_size(cipherAlgorithm) - 1);

    EVP_CIPHER_CTX cipherContext;
    EVP_CIPHER_CTX_init(&cipherContext);
    EVP_EncryptInit(&cipherContext, cipherAlgorithm, reinterpret_cast<const unsigned char *>(key.data()), reinterpret_cast<const unsigned char *>(iv.data()));
    EVP_EncryptUpdate(&cipherContext, reinterpret_cast<unsigned char *>(encryptedData.data()), &processedBytes, reinterpret_cast<const unsigned char *>(data.data()), dataBytes);
    encryptedBytes += processedBytes;
    EVP_EncryptFinal(&cipherContext, reinterpret_cast<unsigned char *>(encryptedData.data() + encryptedBytes), &processedBytes);
    encryptedBytes += processedBytes;
    EVP_CIPHER_CTX_cleanup(&cipherContext);

    encryptedData.resize(encryptedBytes);

    return encryptedData;
}

template<CipherType Type, CipherMode Mode, typename std::enable_if<Mode == CipherMode::Decrypt>::type... Enabler>
auto cipher(const Buffer &data, const Buffer &key, const Buffer &iv = "iv") -> Buffer
{
    const auto dataBytes = static_cast<int32>(data.size());
    int32 processedBytes {};
    int32 decryptedBytes {};

    auto cipherAlgorithm = Internal::cipherAlgorithm<Type>();
    Buffer decryptedData(dataBytes + EVP_CIPHER_block_size(cipherAlgorithm));

    EVP_CIPHER_CTX cipherContext;
    EVP_CIPHER_CTX_init(&cipherContext);
    EVP_DecryptInit(&cipherContext, cipherAlgorithm, reinterpret_cast<const unsigned char *>(key.data()), reinterpret_cast<const unsigned char *>(iv.data()));
    EVP_DecryptUpdate(&cipherContext, reinterpret_cast<unsigned char *>(decryptedData.data()), &processedBytes, reinterpret_cast<const unsigned char *>(data.data()), dataBytes);
    decryptedBytes += processedBytes;
    EVP_DecryptFinal(&cipherContext, reinterpret_cast<unsigned char *>(decryptedData.data() + decryptedBytes), &processedBytes);
    decryptedBytes += processedBytes;
    EVP_CIPHER_CTX_cleanup(&cipherContext);

    decryptedData.resize(decryptedBytes);

    return decryptedData;
}

} // namespace Calibri

#endif // CIPHER_H
