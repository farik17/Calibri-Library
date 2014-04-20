#ifndef REPEATER_H
#define REPEATER_H

//! Std Includes
#include <cstddef>

//! Project Includes
#include "global.h"

template<size_t Count>
class Repeater
{
public:
    template<typename Predicate, typename... Arguments>
    static void run(Predicate predicate, Arguments... arguments) {
        predicate(arguments...);
        Repeater<Count - 1>::run(predicate, arguments...);
    }

private:
    DISABLE_COPY(Repeater)

    Repeater() DECL_NOEXCEPT {}
};

template<>
class Repeater<0>
{
public:
    template<typename Predicate, typename... Arguments>
    static void run(Predicate , Arguments...) {}

private:
    DISABLE_COPY(Repeater<0>)

    Repeater<0>() DECL_NOEXCEPT {}
};

#endif // REPEATER_H
