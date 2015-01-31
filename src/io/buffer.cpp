//! Self includes
#include "buffer.hpp"

//! Calibri-Library includes
#include "global/compilerdetection.hpp"

namespace Calibri {

namespace Constants {

constexpr char endOfLine { '\n' };

} // end namespace Constants

auto Buffer::read(sizeinfo size, bool *ok) noexcept -> ByteArray
{
    try {
        ByteArray data { size };

        bool success {};

        auto processedBytes = read(data, size, &success);

        if (ok)
            *ok = success;

        if (UNLIKELY(!success))
            return {};

        data.resize(processedBytes);

        return data;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

auto Buffer::readLine(sizeinfo size, bool *ok) noexcept -> ByteArray
{
    try {
        ByteArray data { size };

        bool success {};

        auto processedBytes = readLine(data, size, &success);

        if (ok)
            *ok = success;

        if (UNLIKELY(!success))
            return {};

        data.resize(processedBytes);

        return data;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

auto Buffer::write(const ByteArray &data, bool *ok) noexcept -> sizeinfo
{
    return write(data, data.size(), ok);
}

auto Buffer::canReadLine() const noexcept -> bool
{
    try {
        return std::find(std::next(std::begin(m_byteArray), pos()), std::end(m_byteArray), Constants::endOfLine) != std::end(m_byteArray);
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        return false;
    }
}

auto Buffer::atEnd() const noexcept -> bool
{
    return pos() == m_byteArray.size();
}

auto Buffer::readData(char *data, sizeinfo size, bool *ok) noexcept -> sizeinfo
{
    try {
        size = std::min<decltype(size)>(m_byteArray.size() - pos(), size);

        std::copy_n(std::next(std::begin(m_byteArray), pos()), size, data);

        setPos(pos() + size);

        if (ok)
            *ok = true;

        return size;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return 0;
    }
}

auto Buffer::writeData(const char *data, sizeinfo size, bool *ok) noexcept -> sizeinfo
{
    try {
        auto nextPos = pos() + size;

        if (nextPos > m_byteArray.size())
            m_byteArray.resize(nextPos);

        std::copy_n(data, size, std::next(std::begin(m_byteArray), pos()));

        setPos(nextPos);

        if (ok)
            *ok = true;

        return size;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return 0;
    }
}

auto Buffer::readLineData(char *data, sizeinfo size, bool *ok) noexcept -> sizeinfo
{
    try {
        size = std::min<decltype(size)>(m_byteArray.size() - pos(), size);

        auto begin = std::next(std::begin(m_byteArray), pos());
        auto endOfLineIt = std::find(begin, std::end(m_byteArray), Constants::endOfLine);

        if (endOfLineIt != std::end(m_byteArray))
            size = std::min<decltype(size)>(std::distance(begin, endOfLineIt) + sizeof(Constants::endOfLine), size);

        std::copy_n(begin, size, data);

        setPos(pos() + size);

        if (ok)
            *ok = true;

        return size;
    } catch (const std::exception &ex) {
        std::cerr << __func__ << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return 0;
    }
}

auto Buffer::seekData(sizeinfo pos) noexcept -> bool
{
    if (UNLIKELY(pos > m_byteArray.size()))
        return false;

    setPos(pos);

    return true;
}

} // end namespace Calibri
