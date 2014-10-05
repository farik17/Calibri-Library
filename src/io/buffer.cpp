//! Self Includes
#include "buffer.h"

namespace Calibri {

namespace Constants {

constexpr char endOfLine { '\n' };

} // namespace Constants

inline auto Buffer::read(size_t size, bool *ok) noexcept -> ByteArray
{
    try {
        ByteArray data { size };

        bool success {};

        auto processedBytes = IORandomAccessInterface::read(data, size, &success);

        if (ok)
            *ok = success;

        if (!success)
            return {};

        data.resize(processedBytes);

        return data;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return {};
    }
}

inline auto Buffer::write(const ByteArray &data, bool *ok) noexcept -> size_t
{
    return IORandomAccessInterface::write(data, data.size(), ok);
}

auto Buffer::canReadLine() const noexcept -> bool
{
    try {
        return std::find(std::next(std::begin(m_byteArray), pos()), std::end(m_byteArray), Constants::endOfLine) != std::end(m_byteArray);
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        return false;
    }
}

auto Buffer::atEnd() const noexcept -> bool
{
    return pos() == m_byteArray.size();
}

auto Buffer::readData(char *data, size_t size, bool *ok) noexcept -> size_t
{
    try {
        auto nextPos = pos() + size;

        if (nextPos > m_byteArray.size()) {
            size -= nextPos - m_byteArray.size();
            nextPos = m_byteArray.size();
        }

        std::copy_n(std::next(std::begin(m_byteArray), pos()), size, data);

        setPos(nextPos);

        if (ok)
            *ok = true;

        return size;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return 0;
    }
}

auto Buffer::writeData(const char *data, size_t size, bool *ok) noexcept -> size_t
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
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return 0;
    }
}

auto Buffer::readLineData(char *data, size_t size, bool *ok) noexcept -> size_t
{
    try {
        size = std::min<decltype(size)>(m_byteArray.size() - pos(), size);

        auto begin = std::next(std::begin(m_byteArray), pos());
        auto endOfLineIt = std::find(begin, std::end(m_byteArray), Constants::endOfLine);

        if (endOfLineIt != std::end(m_byteArray))
            size = std::min<decltype(size)>(std::distance(begin, endOfLineIt), size);

        std::copy_n(begin, size, data);

        setPos(pos() + size);

        if (ok)
            *ok = true;

        return size;
    } catch (const std::exception &ex) {
        std::cerr << FUNC_INFO << " : " << ex.what() << std::endl;

        if (ok)
            *ok = false;

        return 0;
    }
}

auto Buffer::seekData(size_t pos) noexcept -> bool
{
    if (pos > m_byteArray.size())
        return false;

    setPos(pos);

    return true;
}

} // namespace Calibri
