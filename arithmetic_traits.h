#ifndef ARITHMETIC_TRAITS_HPP
#define ARITHMETIC_TRAITS_HPP

template<typename TTo> struct promoted_alias_type { using type = TTo; };
template<typename TFrom, typename TTo> struct promote_arithmetic;
template<typename TFrom, typename TTo> using promote_arithmetic_t = typename promote_arithmetic<TFrom, TTo>::type;

template<> struct promote_arithmetic<signed char, short> : promoted_alias_type<short> {};

template<> struct promote_arithmetic<unsigned char, unsigned short> : promoted_alias_type<unsigned short> {};

template<> struct promote_arithmetic<signed char, int> : promoted_alias_type<int> {};
template<> struct promote_arithmetic<short, int> : promoted_alias_type<int> {};

template<> struct promote_arithmetic<unsigned char, unsigned int> : promoted_alias_type<unsigned int> {};
template<> struct promote_arithmetic<unsigned short, unsigned int> : promoted_alias_type<unsigned int> {};

template<> struct promote_arithmetic<signed char, long> : promoted_alias_type<long> {};
template<> struct promote_arithmetic<short, long> : promoted_alias_type<long> {};
template<> struct promote_arithmetic<int, long> : promoted_alias_type<long> {};

template<> struct promote_arithmetic<unsigned char, unsigned long> : promoted_alias_type<unsigned long> {};
template<> struct promote_arithmetic<unsigned short, unsigned long> : promoted_alias_type<unsigned long> {};
template<> struct promote_arithmetic<unsigned int, unsigned long> : promoted_alias_type<unsigned long> {};

template<> struct promote_arithmetic<signed char, long long> : promoted_alias_type<long long> {};
template<> struct promote_arithmetic<short, long long> : promoted_alias_type<long long> {};
template<> struct promote_arithmetic<int, long long> : promoted_alias_type<long long> {};
template<> struct promote_arithmetic<long, long long> : promoted_alias_type<long long> {};

template<> struct promote_arithmetic<unsigned char, unsigned long long> : promoted_alias_type<unsigned long long> {};
template<> struct promote_arithmetic<unsigned short, unsigned long long> : promoted_alias_type<unsigned long long> {};
template<> struct promote_arithmetic<unsigned int, unsigned long long> : promoted_alias_type<unsigned long long> {};
template<> struct promote_arithmetic<unsigned long, unsigned long long> : promoted_alias_type<unsigned long long> {};

template<> struct promote_arithmetic<signed char, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<unsigned char, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<short, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<unsigned short, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<int, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<unsigned int, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<long, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<unsigned long, double> : promoted_alias_type<double> {};
template<> struct promote_arithmetic<float, double> : promoted_alias_type<double> {};

template<> struct promote_arithmetic<signed char, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<unsigned char, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<short, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<unsigned short, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<int, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<unsigned int, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<long, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<unsigned long, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<long long, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<unsigned long long, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<float, long double> : promoted_alias_type<long double> {};
template<> struct promote_arithmetic<double, long double> : promoted_alias_type<long double> {};

#endif // ARITHMETIC_TRAITS_HPP
