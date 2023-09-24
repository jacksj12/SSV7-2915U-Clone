#pragma once // Avoid multiple header links.
#include "main.h"


/// @brief 
/// @tparam T A temporary datatype, which allows any datatype to be parsed.
/// @param val The value that needs to be determined.
/// @return -1, 0, 1
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}