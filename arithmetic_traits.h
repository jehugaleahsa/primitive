#ifndef ARITHMETIC_TRAITS_HPP
#define ARITHMETIC_TRAITS_HPP

#include <type_traits>

template<typename TFrom, typename TTo> struct is_promotion : std::false_type {};
template<typename TFrom, typename TTo> struct is_conversion : std::false_type {};

template<> struct is_conversion<int, signed char> : std::true_type {};
template<> struct is_conversion<unsigned int, unsigned char> : std::true_type {};
template<> struct is_conversion<int, short> : std::true_type {};
template<> struct is_conversion<unsigned int, unsigned short> : std::true_type {};

template<> struct is_promotion<signed char, short> : std::true_type {};

template<> struct is_promotion<unsigned char, unsigned short> : std::true_type {};

template<> struct is_promotion<signed char, int> : std::true_type {};
template<> struct is_promotion<short, int> : std::true_type {};

template<> struct is_promotion<unsigned char, unsigned int> : std::true_type {};
template<> struct is_promotion<unsigned short, unsigned int> : std::true_type {};

template<> struct is_promotion<signed char, long> : std::true_type {};
template<> struct is_promotion<short, long> : std::true_type {};
template<> struct is_promotion<int, long> : std::true_type {};

template<> struct is_promotion<unsigned char, unsigned long> : std::true_type {};
template<> struct is_promotion<unsigned short, unsigned long> : std::true_type {};
template<> struct is_promotion<unsigned int, unsigned long> : std::true_type {};

template<> struct is_promotion<signed char, long long> : std::true_type {};
template<> struct is_promotion<short, long long> : std::true_type {};
template<> struct is_promotion<int, long long> : std::true_type {};
template<> struct is_promotion<long, long long> : std::true_type {};

template<> struct is_promotion<unsigned char, unsigned long long> : std::true_type {};
template<> struct is_promotion<unsigned short, unsigned long long> : std::true_type {};
template<> struct is_promotion<unsigned int, unsigned long long> : std::true_type {};
template<> struct is_promotion<unsigned long, unsigned long long> : std::true_type {};

template<> struct is_promotion<signed char, double> : std::true_type {};
template<> struct is_promotion<unsigned char, double> : std::true_type {};
template<> struct is_promotion<short, double> : std::true_type {};
template<> struct is_promotion<unsigned short, double> : std::true_type {};
template<> struct is_promotion<int, double> : std::true_type {};
template<> struct is_promotion<unsigned int, double> : std::true_type {};
template<> struct is_promotion<long, double> : std::true_type {};
template<> struct is_promotion<unsigned long, double> : std::true_type {};
template<> struct is_promotion<float, double> : std::true_type {};

template<> struct is_promotion<signed char, long double> : std::true_type {};
template<> struct is_promotion<unsigned char, long double> : std::true_type {};
template<> struct is_promotion<short, long double> : std::true_type {};
template<> struct is_promotion<unsigned short, long double> : std::true_type {};
template<> struct is_promotion<int, long double> : std::true_type {};
template<> struct is_promotion<unsigned int, long double> : std::true_type {};
template<> struct is_promotion<long, long double> : std::true_type {};
template<> struct is_promotion<unsigned long, long double> : std::true_type {};
template<> struct is_promotion<long long, long double> : std::true_type {};
template<> struct is_promotion<unsigned long long, long double> : std::true_type {};
template<> struct is_promotion<float, long double> : std::true_type {};
template<> struct is_promotion<double, long double> : std::true_type {};

#endif // ARITHMETIC_TRAITS_HPP
