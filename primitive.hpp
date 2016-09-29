#ifndef PRIMITIVE_HPP
#define PRIMITIVE_HPP

#include "arithmetic_traits.h"
#include <iosfwd>

template<typename T, typename = std::enable_if_t< std::is_arithmetic<T>::value >>
class primitive final {
    T m_value;

public:
    using value_type = T;

    constexpr primitive() noexcept: m_value() {}

    template<typename U, typename = std::enable_if_t<
         std::is_same<T, U>::value || is_promotion<U, T>::value
    >>
    constexpr primitive(U const& value) noexcept : m_value(value) {}

    template<typename U, typename = std::enable_if_t< is_promotion<U, T>::value >>
    constexpr primitive(primitive<U> const& other) noexcept : m_value(other.get()) {}

    template<typename U, typename = std::enable_if_t< is_conversion<U, T>::value >>
    constexpr static primitive from(U const& other) noexcept {
        return primitive(static_cast<T>(other));
    }

    primitive(primitive const&) = default;
    primitive(primitive &&) = default;

    primitive& operator=(primitive const&) = default;
    primitive& operator=(primitive &&) = default;

    constexpr T const& get() const noexcept { return m_value; }

    template<typename U = T, typename = std::enable_if_t< !std::is_same<U, bool>::value  >>
    constexpr primitive const& operator+() const noexcept {
        return *this;
    }
    template<typename U = T, typename = std::enable_if_t< !std::is_same<U, bool>::value  >>
    constexpr primitive operator-() const noexcept {
        return primitive(-m_value);
    }

    template<typename U = T, typename = std::enable_if_t< std::is_integral<U>::value && !std::is_same<U, bool>::value >>
    constexpr primitive operator~() const noexcept {
        return primitive(~m_value);
    }

    template<typename U = T, typename = std::enable_if_t< std::is_same<U, bool>::value >>
    constexpr bool operator!() const noexcept {
        return !m_value;
    }

    primitive& operator++() noexcept {
        ++m_value;
        return *this;
    }
    primitive operator++(int) noexcept {
        return primitive(m_value++);
    }

    primitive& operator--() noexcept {
        --m_value;
        return *this;
    }
    primitive operator--(int) noexcept {
        return primitive(m_value--);
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
    constexpr explicit operator primitive<U>() const noexcept {
        return primitive<U>(static_cast<U>(m_value));
    }

    friend std::istream& operator>>(std::istream& lhs, primitive<T> & rhs) {
        return lhs >> rhs.m_value;
    }
};

template<typename T>
constexpr primitive<T> operator+(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() + rhs);
}
template<typename T>
constexpr primitive<T> operator+(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs + rhs.get());
}
template<typename T1, typename T2>
constexpr auto operator+(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() + rhs.get())>(lhs.get() + rhs.get());
}

template<typename T>
constexpr primitive<T> operator-(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() - rhs);
}
template<typename T>
constexpr primitive<T> operator-(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs - rhs.get());
}
template<typename T1, typename T2>
constexpr auto operator-(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() - rhs.get())>(lhs.get() - rhs.get());
}

template<typename T>
constexpr primitive<T> operator*(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() * rhs);
}
template<typename T>
constexpr primitive<T> operator*(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs * rhs.get());
}
template<typename T1, typename T2>
constexpr auto operator*(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() * rhs.get())>(lhs.get() * rhs.get());
}

template<typename T>
constexpr primitive<T> operator/(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() / rhs);
}
template<typename T>
constexpr primitive<T> operator/(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs / rhs.get());
}
template<typename T1, typename T2>
constexpr auto operator/(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() / rhs.get())>(lhs.get() / rhs.get());
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator%(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() % rhs);
}
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator%(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs % rhs.get());
}
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator%(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() % rhs.get())>(lhs.get() % rhs.get());
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator&(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() & rhs);
}
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator&(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs & rhs.get());
}
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator&(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() & rhs.get())>(lhs.get() & rhs.get());
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator|(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() | rhs);
}
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator|(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs | rhs.get());
}
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator|(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() | rhs.get())>(lhs.get() | rhs.get());
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator^(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() ^ rhs);
}
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator^(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs ^ rhs.get());
}
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator^(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept  {
    return primitive<decltype(lhs.get() ^ rhs.get())>(lhs.get() ^ rhs.get());
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator<<(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() << rhs);
}
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator<<(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs << rhs.get());
}
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator<<(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() << rhs.get())>(lhs.get() << rhs.get());
}

template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator>>(primitive<T> const& lhs, T const& rhs) noexcept {
    return primitive<T>(lhs.get() >> rhs);
}
template<typename T, typename = std::enable_if_t< std::is_integral<T>::value >>
constexpr primitive<T> operator>>(T const& lhs, primitive<T> const& rhs) noexcept {
    return primitive<T>(lhs >> rhs.get());
}
template<typename T1, typename T2, typename = std::enable_if_t< std::is_integral<T1>::value && std::is_integral<T2>::value >>
constexpr auto operator>>(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return primitive<decltype(lhs.get() >> rhs.get())>(lhs.get() >> rhs.get());
}

constexpr bool operator&&(primitive<bool> const& lhs, bool const& rhs) noexcept {
    return lhs.get() && rhs;
}
constexpr bool operator&&(bool const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs && rhs.get();
}
constexpr bool operator&&(primitive<bool> const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs.get() && rhs.get();
}

constexpr bool operator||(primitive<bool> const& lhs, bool const& rhs) noexcept {
    return lhs.get() || rhs;
}
constexpr bool operator||(bool const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs || rhs.get();
}
constexpr bool operator||(primitive<bool> const& lhs, primitive<bool> const& rhs) noexcept {
    return lhs.get() || rhs.get();
}

template<typename T>
constexpr bool operator==(primitive<T> const& lhs, T const& rhs) noexcept {
    return lhs.get() == rhs;
}
template<typename T>
constexpr bool operator==(T const& lhs, primitive<T> const& rhs) noexcept {
    return lhs == rhs.get();
}
template<typename T1, typename T2>
constexpr bool operator==(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() == rhs.get();
}

template<typename T>
constexpr bool operator!=(primitive<T> const& lhs, T const& rhs) noexcept {
    return lhs.get() != rhs;
}
template<typename T>
constexpr bool operator!=(T const& lhs, primitive<T> const& rhs) noexcept {
    return lhs != rhs.get();
}
template<typename T1, typename T2>
constexpr bool operator!=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() != rhs.get();
}

template<typename T>
constexpr bool operator<(primitive<T> const& lhs, T const& rhs) noexcept {
    return lhs.get() < rhs;
}
template<typename T>
constexpr bool operator<(T const& lhs, primitive<T> const& rhs) noexcept {
    return lhs < rhs.get();
}
template<typename T1, typename T2>
constexpr bool operator<(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() < rhs.get();
}

template<typename T>
constexpr bool operator<=(primitive<T> const& lhs, T const& rhs) noexcept {
    return lhs.get() <= rhs;
}
template<typename T>
constexpr bool operator<=(T const& lhs, primitive<T> const& rhs) noexcept {
    return lhs <= rhs.get();
}
template<typename T1, typename T2>
constexpr bool operator<=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() <= rhs.get();
}

template<typename T>
constexpr bool operator>(primitive<T> const& lhs, T const& rhs) noexcept {
    return lhs.get() > rhs;
}
template<typename T>
constexpr bool operator>(T const& lhs, primitive<T> const& rhs) noexcept {
    return lhs > rhs.get();
}
template<typename T1, typename T2>
constexpr bool operator>(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() > rhs.get();
}

template<typename T>
constexpr bool operator>=(primitive<T> const& lhs, T const& rhs) noexcept {
    return lhs.get() >= rhs;
}
template<typename T>
constexpr bool operator>=(T const& lhs, primitive<T> const& rhs) noexcept {
    return lhs >= rhs.get();
}
template<typename T1, typename T2>
constexpr bool operator>=(primitive<T1> const& lhs, primitive<T2> const& rhs) noexcept {
    return lhs.get() >= rhs.get();
}

template<typename T>
std::ostream& operator<<(std::ostream& lhs, primitive<T> const& rhs) {
    return lhs << rhs.get();
}

#endif
