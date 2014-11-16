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

enum class DigestType : uint8 {
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
template<DigestType Type,
         typename std::enable_if<Type == DigestType::MD2>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md2();
}
#endif

#if !defined(OPENSSL_NO_MD4)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::MD4>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md4();
}
#endif

#if !defined(OPENSSL_NO_MD5)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::MD5>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md5();
}
#endif

#if !defined(OPENSSL_NO_SHA)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::SHA>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha();
}

template<DigestType Type,
         typename std::enable_if<Type == DigestType::SHA1>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha1();
}

template<DigestType Type,
         typename std::enable_if<Type == DigestType::DSS>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_dss();
}

template<DigestType Type,
         typename std::enable_if<Type == DigestType::DSS1>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_dss1();
}

template<DigestType Type,
         typename std::enable_if<Type == DigestType::ECDSA>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_ecdsa();
}
#endif

#if !defined(OPENSSL_NO_SHA256)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::SHA224>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha224();
}

template<DigestType Type,
         typename std::enable_if<Type == DigestType::SHA256>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha256();
}
#endif

#if !defined(OPENSSL_NO_SHA512)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::SHA384>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha384();
}

template<DigestType Type,
         typename std::enable_if<Type == DigestType::SHA512>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_sha512();
}
#endif

#if !defined(OPENSSL_NO_MDC2)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::MDC2>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_mdc2();
}
#endif

#if !defined(OPENSSL_NO_RIPEMD)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::RipeMD160>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_ripemd160();
}
#endif

#if !defined(OPENSSL_NO_WHIRLPOOL)
template<DigestType Type,
         typename std::enable_if<Type == DigestType::Whirlpool>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_whirlpool();
}
#endif

template<DigestType Type,
         typename std::enable_if<Type == DigestType::Null>::type... Enabler>
auto digestAlgorithm() noexcept -> const EVP_MD *
{
    return EVP_md_null();
}

} // end namespace Internal

template<DigestType Type>
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
