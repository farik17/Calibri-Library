#ifndef CIPHER_H
#define CIPHER_H

//! Std includes
#include <type_traits>

//! OpenSSL includes
#include <openssl/evp.h>

//! Calibri-Library includes
#include "tools/bytearray.h"

namespace Calibri {

//! Enumerations
enum class CipherAlgorithm : uint8 {
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

#if !defined(OPENSSL_NO_RC4)
    RC4,
#endif

#if !defined(OPENSSL_NO_IDEA)
    IDEAecb,
    IDEAcbc,
    IDEAcfb,
    IDEAofb,
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

#if !defined(OPENSSL_NO_RC5)
    RC5ecb,
    RC5cbc,
    RC5cfb,
    RC5ofb,
#endif

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

#if !defined(OPENSSL_NO_DES)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DESecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DEScbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DEScfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DESofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DoubleDESecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DoubleDEScbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DoubleDEScfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DoubleDESofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::TripleDESecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede3_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::TripleDEScbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede3_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::TripleDEScfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede3_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::TripleDESofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_des_ede3_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::DESXcbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_desx_cbc();
}
#endif

#if !defined(OPENSSL_NO_RC4)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC4>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc4();
}
#endif

#if !defined(OPENSSL_NO_IDEA)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_idea_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAcbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_idea_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAcfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_idea_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::IDEAofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_idea_ofb();
}
#endif

#if !defined(OPENSSL_NO_RC2)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc2_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc2_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc2_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC2ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc2_ofb();
}
#endif

#if !defined(OPENSSL_NO_BF)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_bf_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFcbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_bf_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFcfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_bf_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::BFofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_bf_ofb();
}
#endif

#if !defined(OPENSSL_NO_CAST)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_cast5_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_cast5_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_cast5_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAST5ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_cast5_ofb();
}
#endif

#if !defined(OPENSSL_NO_RC5)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc5_32_12_16_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc5_32_12_16_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc5_32_12_16_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::RC5ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_rc5_32_12_16_ofb();
}
#endif

#if !defined(OPENSSL_NO_AES)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_128_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_128_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_128_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_128_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES128ctr>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_128_ctr();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_192_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_192_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_192_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_192_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES192ctr>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_192_ctr();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_256_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_256_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_256_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_256_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::AES256ctr>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_aes_256_ctr();
}
#endif

#if !defined(OPENSSL_NO_CAMELLIA)
template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_128_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_128_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_128_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA128ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_128_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_192_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_192_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_192_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA192ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_192_ofb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256ecb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_256_ecb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256cbc>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_256_cbc();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256cfb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_256_cfb();
}

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::CAMELLIA256ofb>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_camellia_256_ofb();
}
#endif

template<CipherAlgorithm Algorithm,
         typename std::enable_if<Algorithm == CipherAlgorithm::Null>::type... Enabler>
auto cipherAlgorithm() noexcept -> const EVP_CIPHER *
{
    return EVP_enc_null();
}

} // end namespace Internal

template<CipherAlgorithm Type,
         CipherMode Mode,
         typename std::enable_if<Mode == CipherMode::Encrypt>::type... Enabler>
auto cipher(const ByteArray &data, const ByteArray &key, const ByteArray &iv, bool *ok = nullptr) noexcept -> ByteArray
{
    int32 processedBytes {};
    int32 encryptedBytes {};

    auto cipherAlgorithm = Internal::cipherAlgorithm<Type>();
    ByteArray encryptedData { data.size() + EVP_CIPHER_block_size(cipherAlgorithm) - 1 };

    EVP_CIPHER_CTX cipherContext;
    EVP_CIPHER_CTX_init(&cipherContext);

    if (EVP_EncryptInit(&cipherContext, cipherAlgorithm, reinterpret_cast<const uchar *>(key.data()), reinterpret_cast<const uchar *>(iv.data())) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_EncryptUpdate(&cipherContext, reinterpret_cast<uchar *>(encryptedData.data()), &processedBytes, reinterpret_cast<const uchar *>(data.data()), data.size()) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    encryptedBytes += processedBytes;

    if (EVP_EncryptFinal(&cipherContext, reinterpret_cast<uchar *>(encryptedData.data() + encryptedBytes), &processedBytes) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    encryptedBytes += processedBytes;

    EVP_CIPHER_CTX_cleanup(&cipherContext);

    encryptedData.resize(encryptedBytes);

    if (ok)
        *ok = true;

    return encryptedData;
}

template<CipherAlgorithm Type,
         CipherMode Mode,
         typename std::enable_if<Mode == CipherMode::Decrypt>::type... Enabler>
auto cipher(const ByteArray &data, const ByteArray &key, const ByteArray &iv, bool *ok = nullptr) noexcept -> ByteArray
{
    int32 processedBytes {};
    int32 decryptedBytes {};

    auto cipherAlgorithm = Internal::cipherAlgorithm<Type>();
    ByteArray decryptedData { data.size() + EVP_CIPHER_block_size(cipherAlgorithm) };

    EVP_CIPHER_CTX cipherContext;
    EVP_CIPHER_CTX_init(&cipherContext);

    if (EVP_DecryptInit(&cipherContext, cipherAlgorithm, reinterpret_cast<const uchar *>(key.data()), reinterpret_cast<const uchar *>(iv.data())) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_DecryptUpdate(&cipherContext, reinterpret_cast<uchar *>(decryptedData.data()), &processedBytes, reinterpret_cast<const uchar *>(data.data()), data.size()) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    decryptedBytes += processedBytes;

    if (EVP_DecryptFinal(&cipherContext, reinterpret_cast<uchar *>(decryptedData.data() + decryptedBytes), &processedBytes) != 1) {
        EVP_CIPHER_CTX_cleanup(&cipherContext);

        if (ok)
            *ok = false;

        return {};
    }

    decryptedBytes += processedBytes;

    EVP_CIPHER_CTX_cleanup(&cipherContext);

    decryptedData.resize(decryptedBytes);

    if (ok)
        *ok = true;

    return decryptedData;
}

} // end namespace Calibri

#endif // CIPHER_H
