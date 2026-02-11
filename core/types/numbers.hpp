#pragma once
#include <type_traits>

template<typename T>
concept Arithmatic = std::is_arithmetic_v<T>;