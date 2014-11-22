#ifndef DIGEST_H
#define DIGEST_H

//! Std includes
#include <type_traits>

//! OpenSSL includes
#include <openssl/evp.h>

//! Calibri-Library includes
#include "tools/bytearray.h"
#include "tools/metacast.h"

namespace Calibri {

//! Enumerations
enum class DigestAlgorithm : uint8 {
#if !defined(OPENSSL_NO_MD2)
    MD2,
#endif

#if !defined(OPENSSL_NO_MD4)
    MD4,
#endif

#if !defined(OPENSSL_NO_MD5)
    MD5,
#endif

#if !defined(OPENSSL_NO_SHA)
    SHA,
    SHA1,
    DSS,
    DSS1,
    ECDSA,
#endif

#if !defined(OPENSSL_NO_SHA256)
    SHA224,
    SHA256,
#endif

#if !defined(OPENSSL_NO_SHA512)
    SHA384,
    SHA512,
#endif

#if !defined(OPENSSL_NO_MDC2)
    MDC2,
#endif

#if !defined(OPENSSL_NO_RIPEMD)
    RipeMD160,
#endif

#if !defined(OPENSSL_NO_WHIRLPOOL)
    Whirlpool,
#endif

    Null
};

namespace Internal {

#if !defined(OPENSSL_NO_MD2)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MD2>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md2();
}
#endif

#if !defined(OPENSSL_NO_MD4)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MD4>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md4();
}
#endif

#if !defined(OPENSSL_NO_MD5)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MD5>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md5();
}
#endif

#if !defined(OPENSSL_NO_SHA)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha();
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA1>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha1();
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::DSS>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_dss();
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::DSS1>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_dss1();
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::ECDSA>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_ecdsa();
}
#endif

#if !defined(OPENSSL_NO_SHA256)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA224>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha224();
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA256>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha256();
}
#endif

#if !defined(OPENSSL_NO_SHA512)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA384>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha384();
}

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::SHA512>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha512();
}
#endif

#if !defined(OPENSSL_NO_MDC2)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::MDC2>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_mdc2();
}
#endif

#if !defined(OPENSSL_NO_RIPEMD)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::RipeMD160>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_ripemd160();
}
#endif

#if !defined(OPENSSL_NO_WHIRLPOOL)
template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::Whirlpool>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_whirlpool();
}
#endif

template<DigestAlgorithm Algorithm,
         typename std::enable_if<Algorithm == DigestAlgorithm::Null>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md_null();
}

} // end namespace Internal

template<DigestAlgorithm Type>
auto digest(const ByteArray &data, bool *ok = nullptr) noexcept -> ByteArray
{
    auto digestAlgorithm = Internal::digestAlgorithm<Type>();
    ByteArray digestData { metaCast<size_t>(EVP_MD_size(digestAlgorithm)) };

    EVP_MD_CTX digestContext;
    EVP_MD_CTX_init(&digestContext);

    if (EVP_DigestInit(&digestContext, digestAlgorithm) != 1) {
        EVP_MD_CTX_cleanup(&digestContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_DigestUpdate(&digestContext, reinterpret_cast<const unsigned char *>(data.data()), data.size()) != 1) {
        EVP_MD_CTX_cleanup(&digestContext);

        if (ok)
            *ok = false;

        return {};
    }

    if (EVP_DigestFinal(&digestContext, reinterpret_cast<unsigned char *>(digestData.data()), nullptr) != 1) {
        EVP_MD_CTX_cleanup(&digestContext);

        if (ok)
            *ok = false;

        return {};
    }

    EVP_MD_CTX_cleanup(&digestContext);

    if (ok)
        *ok = true;

    return digestData;
}

} // end namespace Calibri

#endif // DIGEST_H
