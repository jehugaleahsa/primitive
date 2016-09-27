#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include <type_traits>
#include <iosfwd>

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

template<typename T, typename = std::enable_if_t< std::is_arithmetic<T>::value >>
class primitive final {
    T m_value;

public:
    using value_type = T;

    constexpr primitive() noexcept: m_value() {}
    constexpr primitive(T const& value) noexcept: m_value(value) {}

    template<typename U, typename = promote_arithmetic_t<U, T>>
    constexpr primitive(primitive<U> const& other) noexcept : m_value(other.get()) {}

    primitive(primitive const&) = default;
    primitive(primitive &&) = default;

    primitive& operator=(primitive const&) = default;
    primitive& operator=(primitive &&) = default;
    template<typename U, typename = promote_arithmetic_t<T, U>>
    primitive& operator=(primitive<U> const& other) noexcept { m_value = other.get(); }

    constexpr T const& get() const noexcept { return m_value; }

    template<typename U = T, typename = std::enable_if_t< !std::is_same<U, bool>::value  >>
    constexpr primitive const& operator+() const noexcept { return *this; }
    template<typename U = T, typename = std::enable_if_t< !std::is_same<U, bool>::value  >>
    constexpr primitive operator-() const noexcept { return -m_value; }

    template<typename U = T, typename = std::enable_if_t< std::is_integral<U>::value && !std::is_same<U, bool>::value >>
    constexpr primitive operator~() const noexcept { return ~m_value; }

    constexpr primitive<bool> operator!() const noexcept { return !m_value; }

    primitive& operator++() noexcept { 
        ++m_value; 
        return *this; 
    }
    primitive operator++(int) noexcept { 
        return m_value++;
    }

    primitive& operator--() noexcept { 
        --m_value; 
        return *this; 
    }
    primitive operator--(int) noexcept { 
        return m_value--;
    }

    template<typename U>
    primitive& operator+=(U const& other) noexcept {
        m_value += other;
        return *this;
    }
    template<typename U>
    primitive& operator+=(primitive<U> const& other) noexcept {
        m_value += other.get();
        return *this;
    }

    template<typename U>
    primitive& operator-=(U const& other) noexcept {
        m_value -= other;
        return *this;
    }
    template<typename U>
    primitive& operator-=(primitive<U> const& other) noexcept {
        m_value -= other.get();
        return *this;
    }

    template<typename U>
    primitive& operator*=(U const& other) noexcept {
        m_value *= other;
        return *this;
    }
    template<typename U>
    primitive& operator*=(primitive<U> const& other) noexcept {
        m_value *= other.get();
        return *this;
    }

    template<typename U>
    primitive& operator/=(U const& other) noexcept {
        m_value /= other;
        return *this;
    }
    template<typename U>
    primitive& operator/=(primitive<U> const& other) noexcept {
        m_value /= other.get();
        return *this;
    }

    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator%=(U const& other) noexcept {
        m_value %= other;
        return *this;
    }
    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator%=(primitive<U> const& other) noexcept {
        m_value %= other.get();
        return *this;
    }

    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator<<=(U const& other) noexcept {
        m_value <<= other;
        return *this;
    }
    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator<<=(primitive<U> const& other) noexcept {
        m_value <<= other.get();
        return *this;
    }

    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator>>=(U const& other) noexcept {
        m_value >>= other;
        return *this;
    }
    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator>>=(primitive<U> const& other) noexcept {
        m_value >>= other.get();
        return *this;
    }

    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator&=(U const& other) noexcept {
        m_value &= other;
        return *this;
    }
    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator&=(primitive<U> const& other) noexcept {
        m_value &= other.get();
        return *this;
    }

    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator|=(U const& other) noexcept {
        m_value |= other;
        return *this;
    }
    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator|=(primitive<U> const& other) noexcept {
        m_value |= other.get();
        return *this;
    }

    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator^=(U const& other) noexcept {
        m_value ^= other;
        return *this;
    }
    template<typename U, typename = std::enable_if_t< std::is_integral<T>::value && std::is_integral<U>::value >>
    primitive& operator^=(primitive<U> const& other) noexcept {
        m_value ^= other.get();
        return *this;
    }

    template<typename U>
    constexpr explicit operator primitive<U>() const noexcept { return static_cast<U>(m_value); }

    friend std::istream& operator>>(std::istream& lhs, primitive<T> & rhs) { return lhs >> rhs.m_value; }
};

template<typename T>
constexpr primitive<T> operator+(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() + rhs; }
template<typename T>
constexpr primitive<T> operator+(T const& lhs, primitive<T> const& rhs) noexcept { return lhs + rhs.get(); }
template<typename T1, typename T2>
constexpr auto operator+(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() + rhs.get())> {
    return lhs.get() + rhs.get();
}

template<typename T>
constexpr primitive<T> operator-(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() - rhs; }
template<typename T>
constexpr primitive<T> operator-(T const& lhs, primitive<T> const& rhs) noexcept { return lhs - rhs.get(); }
template<typename T1, typename T2>
constexpr auto operator-(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() - rhs.get())> {
    return lhs.get() - rhs.get();
}

template<typename T>
constexpr primitive<T> operator*(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() * rhs; }
template<typename T>
constexpr primitive<T> operator*(T const& lhs, primitive<T> const& rhs) noexcept { return lhs * rhs.get(); }
template<typename T1, typename T2>
constexpr auto operator*(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() * rhs.get())> {
    return lhs.get() * rhs.get();
}

template<typename T>
constexpr primitive<T> operator/(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() / rhs; }
template<typename T>
constexpr primitive<T> operator/(T const& lhs, primitive<T> const& rhs) noexcept { return lhs / rhs.get(); }
template<typename T1, typename T2>
constexpr auto operator/(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() / rhs.get())> {
    return lhs.get() / rhs.get();
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator%(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() % rhs; }
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator%(T const& lhs, primitive<T> const& rhs) noexcept { return lhs % rhs.get(); }
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator%(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() % rhs.get())> {
    return lhs.get() % rhs.get();
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator&(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() & rhs; }
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator&(T const& lhs, primitive<T> const& rhs) noexcept { return lhs & rhs.get(); }
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator&(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() & rhs.get())> {
    return lhs.get() & rhs.get();
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator|(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() | rhs; }
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator|(T const& lhs, primitive<T> const& rhs) noexcept { return lhs | rhs.get(); }
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator|(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() | rhs.get())> {
    return lhs.get() | rhs.get();
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator^(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() ^ rhs; }
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator^(T const& lhs, primitive<T> const& rhs) noexcept { return lhs ^ rhs.get(); }
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator^(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() ^ rhs.get())>  {
    return lhs.get() ^ rhs.get();
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator<<(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() << rhs; }
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator<<(T const& lhs, primitive<T> const& rhs) noexcept { return lhs << rhs.get(); }
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator<<(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() << rhs.get())> {
    return lhs.get() << rhs.get();
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator>>(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() >> rhs; }
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator>>(T const& lhs, primitive<T> const& rhs) noexcept { return lhs >> rhs.get(); }
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator>>(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept -> primitive<decltype(lhs.get() >> rhs.get())> {
    return lhs.get() >> rhs.get();
}

constexpr primitive<bool> operator&&(primitive<bool> const& lhs, bool const& rhs) noexcept { return lhs.get() && rhs; }
constexpr primitive<bool> operator&&(bool const& lhs, primitive<bool> const& rhs) noexcept { return lhs && rhs.get(); }
constexpr primitive<bool> operator&&(primitive<bool> const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs.get() && rhs.get();
}

constexpr primitive<bool> operator||(primitive<bool> const& lhs, bool const& rhs) noexcept { return lhs.get() || rhs; }
constexpr primitive<bool> operator||(bool const& lhs, primitive<bool> const& rhs) noexcept { return lhs || rhs.get(); }
constexpr primitive<bool> operator||(primitive<bool> const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs.get() || rhs.get();
}

template<typename T>
constexpr bool operator==(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() == rhs; }
template<typename T>
constexpr bool operator==(T const& lhs, primitive<T> const& rhs) noexcept { return lhs == rhs.get(); }
template<typename T1, typename T2>
constexpr bool operator==(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() == rhs.get();
}

template<typename T>
constexpr bool operator!=(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() != rhs; }
template<typename T>
constexpr bool operator!=(T const& lhs, primitive<T> const& rhs) noexcept { return lhs != rhs.get(); }
template<typename T1, typename T2>
constexpr bool operator!=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() != rhs.get();
}

template<typename T>
constexpr bool operator<(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() < rhs; }
template<typename T>
constexpr bool operator<(T const& lhs, primitive<T> const& rhs) noexcept { return lhs < rhs.get(); }
template<typename T1, typename T2>
constexpr bool operator<(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() < rhs.get();
}

template<typename T>
constexpr bool operator<=(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() <= rhs; }
template<typename T>
constexpr bool operator<=(T const& lhs, primitive<T> const& rhs) noexcept { return lhs <= rhs.get(); }
template<typename T1, typename T2>
constexpr bool operator<=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() <= rhs.get();
}

template<typename T>
constexpr bool operator>(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() > rhs; }
template<typename T>
constexpr bool operator>(T const& lhs, primitive<T> const& rhs) noexcept { return lhs > rhs.get(); }
template<typename T1, typename T2>
constexpr bool operator>(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() > rhs.get();
}

template<typename T>
constexpr bool operator>=(primitive<T> const& lhs, T const& rhs) noexcept { return lhs.get() >= rhs; }
template<typename T>
constexpr bool operator>=(T const& lhs, primitive<T> const& rhs) noexcept { return lhs >= rhs.get(); }
template<typename T1, typename T2>
constexpr bool operator>=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() >= rhs.get();
}

template<typename T>
std::ostream& operator<<(std::ostream& lhs, primitive<T> const& rhs) { return lhs << rhs.get(); }

#endif