#ifndef DISABLECOPY_H
#define DISABLECOPY_H

namespace Calibri
{

class DisableCopy
{
public:
    constexpr explicit DisableCopy() noexcept = default;

private:
    DisableCopy(const DisableCopy &) = delete;
    DisableCopy &operator =(const DisableCopy &) = delete;
};

}

#endif // DISABLECOPY_H
