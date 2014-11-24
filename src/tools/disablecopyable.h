#ifndef DISABLECOPYABLE_H
#define DISABLECOPYABLE_H

namespace Calibri {

/*!
 *  DisableCopyable class
 */
class DisableCopyable
{
public:
    constexpr DisableCopyable() noexcept = default;

private:
    DisableCopyable(const DisableCopyable &) = delete;
    DisableCopyable &operator =(const DisableCopyable &) = delete;
};

} // end namespace Calibri

#endif // DISABLECOPYABLE_H
