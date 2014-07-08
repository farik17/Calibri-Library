#ifndef REPEATER_H
#define REPEATER_H

//! Std Includes
#include <cstddef>

//! CalibriLibrary Includes
#include "disablecopy.h"

namespace Calibri
{

template<size_t Count>
class Repeater : private DisableCopy
{
public:
    template<typename Predicate, typename... Arguments>
    static void run(Predicate predicate, Arguments... arguments) {
        predicate(arguments...);
        Repeater<Count - 1>::run(predicate, arguments...);
    }

private:
    Repeater() noexcept = default;
};

template<>
class Repeater<0> : private DisableCopy
{
public:
    template<typename Predicate, typename... Arguments>
    static void run(Predicate , Arguments...) {}

private:
    Repeater<0>() noexcept = default;
};

} // namespace Calibri

#endif // REPEATER_H
