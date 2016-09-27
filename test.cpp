#include <iostream>
#include <sstream>
#include <type_traits>
#include <cassert>
#include <utility>
#include "primitive.hpp"

int main() {
    using std::is_same;
    using std::move;

    using Boolean = primitive<bool>;
    using Char = primitive<char>;
    using SChar = primitive<signed char>;
    using UChar = primitive<unsigned char>;
    using Short = primitive<short>;
    using UShort = primitive<unsigned short>;
    using Int = primitive<int>;
    using UInt = primitive<unsigned int>;
    using Long = primitive<long>;
    using ULong = primitive<unsigned long>;
    using Long_Long = primitive<long long>;
    using ULong_Long = primitive<unsigned long long>;
    using Float = primitive<float>;
    using Double = primitive<double>;
    using Long_Double = primitive<long double>;

    // Guarantee there is no overhead
    static_assert(sizeof(Int) == sizeof(int), "The wrapper has overhead.");

    // Verify the underlying type is exposed by the value_type member.
    static_assert(is_same< int, typename primitive<int>::value_type >::value, "Value type not exposed.");

    // Without providing a value, primitives should be zeroed out.
    Int uninitialized;
    assert(uninitialized.get() == 0);
    static_assert(Int().get() == 0, "The value was not default-initialized from the default ctor.");

    // Check the provided value is stored.
    static_assert(Int(42).get() == 42, "The value was not initialized from a value.");

    // Check the copy ctor copies the underlying value.
    constexpr Int source(42);
    static_assert(Int(source).get() == 42, "The value was not copied in the copy ctor.");

    // Check the move ctor moves the underlying value.
    static_assert(Int(move(Int(42))).get() == 42, "The value was not moved in the move ctor.");

    // Check the copy operator copies the underlying value.
    Int copyDestination;
    copyDestination = Int(33);
    assert(copyDestination.get() == 33);

    // Check the move operator moves the underlying value.__construct_from_string_literal
    Int moveDestination;
    moveDestination = move(Int(33));
    assert(moveDestination.get() == 33);

    // Unary operators
    constexpr Int pos(3);
    constexpr Int pos_res = +pos;
    static_assert(pos.get() == pos_res.get(), "The + unary operator did not return the primitive.");

    constexpr Int neg(5);
    constexpr Int neg_res = -neg;
    static_assert(-neg.get() == neg_res.get(), "The - unary operator did not negate the number.");

    constexpr Int bitneg(10);
    constexpr Int bitneg_res = ~bitneg;
    static_assert(~bitneg.get() == bitneg_res.get(), "The ~ unary operator did not bitwise negate the number.");

    constexpr Boolean logicalneg(false);
    constexpr Boolean logicalneg_res = !logicalneg;
    static_assert(!logicalneg.get() == logicalneg_res.get(), "The ! unary operator did not logically negate the value.");

    Int preinc(4);
    ++preinc;
    assert(preinc.get() == 5);

    Int postinc(4);
    Int postinc_res = postinc++;
    assert(postinc.get() == 5);
    assert(postinc_res.get() == 4);

    Int predec(4);
    --predec;
    assert(predec.get() == 3);

    Int postdec(4);
    Int postdec_res = postdec--;
    assert(postdec.get() == 3);
    assert(postdec_res.get() == 4);

    // Assignment operators
    Int add(5);
    add += 4;
    assert(add.get() == 9);

    Int add_self(5);
    add_self += Char(4);
    assert(add_self.get() == 9);

    Int substract(5);
    substract -= 4;
    assert(substract.get() == 1);

    Int substract_self(5);
    substract_self -= Char(4);
    assert(substract_self.get() == 1);

    Int multiply(5);
    multiply *= 4;
    assert(multiply.get() == 20);

    Int multiply_self(5);
    multiply_self *= Char(4);
    assert(multiply_self.get() == 20);

    Int divide(20);
    divide /= 4;
    assert(divide.get() == 5);

    Int divide_self(20);
    divide_self /= Char(4);
    assert(divide_self.get() == 5);

    Int modulus(21);
    modulus %= 4;
    assert(modulus.get() == 1);

    Int modulus_self(21);
    modulus_self %= Char(4);
    assert(modulus_self.get() == 1);

    Int shiftleft(2);
    shiftleft <<= 1;
    assert(shiftleft.get() == 4);

    Int shiftleft_self(2);
    shiftleft_self <<= 1;
    assert(shiftleft_self.get() == 4);

    Int shiftright(4);
    shiftright >>= 1;
    assert(shiftright.get() == 2);

    Int shiftright_self(4);
    shiftright_self >>= 1;
    assert(shiftright_self.get() == 2);

    Int bit_and(5);
    bit_and &= 1;
    assert(bit_and.get() == 1);

    Int bitand_self(5);
    bitand_self &= 1;
    assert(bitand_self.get() == 1);

    Int bit_or(5);
    bit_or |= 2;
    assert(bit_or.get() == 7);

    Int bitor_self(5);
    bitor_self |= 2;
    assert(bitor_self.get() == 7);

    Int bitxor(7);
    bitxor ^= 2;
    assert(bitxor.get() == 5);

    Int bitxor_self(7);
    bitxor_self ^= 2;
    assert(bitxor_self.get() == 5);

    // Implicit conversions
    constexpr Short schar2shortconv(SChar(12));
    static_assert(schar2shortconv.get() == 12, "A signed char was not converted to a short.");
    constexpr UShort uchar2ushortconv(UChar(12));
    static_assert(uchar2ushortconv.get() == 12, "An unsigned char was not converted to an unsigned short.");

    constexpr Int schar2intconv(SChar(12));
    static_assert(schar2intconv.get() == 12, "A signed char was not converted to an int.");
    constexpr Int short2intconv(Short(12));
    static_assert(short2intconv.get() == 12, "A signed short was not converted to an int.");

    constexpr UInt uchar2uintconv(UChar(12));
    static_assert(uchar2uintconv.get() == 12, "An unsigned char was not converted to an unsigned int.");
    constexpr UInt ushort2uintconv(Short(12));
    static_assert(ushort2uintconv.get() == 12, "An unsigned short was not converted to an unsigned int.");

    constexpr Long schar2longconv(SChar(12));
    static_assert(schar2longconv.get() == 12, "A signed char was not converted to a long.");
    constexpr Long short2longconv(Short(12));
    static_assert(short2longconv.get() == 12, "A signed short was not converted to a long.");
    constexpr Long int2longconv(Int(12));
    static_assert(int2longconv.get() == 12, "A signed int was not converted to a long.");

    constexpr ULong uchar2ulongconv(UChar(12));
    static_assert(uchar2ulongconv.get() == 12, "An unsigned char was not converted to an unsigned long.");
    constexpr ULong ushort2ulongconv(UShort(12));
    static_assert(ushort2ulongconv.get() == 12, "An unsigned short was not converted to an unsigned long.");
    constexpr ULong uint2ulongconv(UInt(12));
    static_assert(uint2ulongconv.get() == 12, "An unsigned int was not converted to an unsigned long.");

    constexpr Long_Long schar2longlongconv(SChar(12));
    static_assert(schar2longlongconv.get() == 12, "A signed char was not converted to a long long.");
    constexpr Long_Long short2longlongconv(Short(12));
    static_assert(short2longlongconv.get() == 12, "A signed short was not converted to a long long.");
    constexpr Long_Long int2longlongconv(Int(12));
    static_assert(int2longlongconv.get() == 12, "A signed int was not converted to a long long.");
    constexpr Long_Long long2longlongconv(Long(12));
    static_assert(long2longlongconv.get() == 12, "A signed long was not converted to a long long.");

    constexpr ULong_Long uchar2ulonglongconv(UChar(12));
    static_assert(uchar2ulonglongconv.get() == 12, "An unsigned char was not converted to an unsigned long long.");
    constexpr ULong_Long ushort2ulonglongconv(UShort(12));
    static_assert(ushort2ulonglongconv.get() == 12, "An unsigned short was not converted to an unsigned long long.");
    constexpr ULong_Long uint2ulonglongconv(UInt(12));
    static_assert(uint2ulonglongconv.get() == 12, "An unsigned int was not converted to an unsigned long long.");
    constexpr ULong_Long ulong2ulonglongconv(ULong(12));
    static_assert(ulong2ulonglongconv.get() == 12, "An unsigned long was not converted to an unsigned long long.");

    constexpr Double schar2doubleconv(SChar(-12));
    static_assert(schar2doubleconv.get() == -12.0, "A signed char was not converted to a double.");
    constexpr Double uchar2doubleconv(UChar(12));
    static_assert(uchar2doubleconv.get() == 12.0, "An unsigned char was not converted to a double.");
    constexpr Double short2doubleconv(Short(-12));
    static_assert(short2doubleconv.get() == -12.0, "A signed short was not converted to a double.");
    constexpr Double ushort2doubleconv(UShort(12));
    static_assert(ushort2doubleconv.get() == 12.0, "An unsigned short was not converted to a double.");
    constexpr Double int2doubleconv(Int(-12));
    static_assert(int2doubleconv.get() == -12.0, "A signed int was not converted to a double.");
    constexpr Double uint2doubleconv(UInt(12));
    static_assert(uint2doubleconv.get() == 12.0, "An unsigned int was not converted to a double.");
    constexpr Double long2doubleconv(Long(-12));
    static_assert(long2doubleconv.get() == -12.0, "A signed long was not converted to a double.");
    constexpr Double ulong2doubleconv(ULong(12));
    static_assert(ulong2doubleconv.get() == 12.0, "An unsigned long was not converted to a double.");
    constexpr Double float2doubleconv(Float(-12));
    static_assert(float2doubleconv.get() == -12.0, "A signed long was not converted to a double.");

    constexpr Long_Double schar2longdoubleconv(SChar(-12));
    static_assert(schar2longdoubleconv.get() == -12.0, "A signed char was not converted to a long double.");
    constexpr Long_Double uchar2longdoubleconv(UChar(12));
    static_assert(uchar2longdoubleconv.get() == 12.0, "An unsigned char was not converted to a long double.");
    constexpr Long_Double short2longdoubleconv(Short(-12));
    static_assert(short2longdoubleconv.get() == -12.0, "A signed short was not converted to a long double.");
    constexpr Long_Double ushort2longdoubleconv(UShort(12));
    static_assert(ushort2longdoubleconv.get() == 12.0, "An unsigned short was not converted to a long double.");
    constexpr Long_Double int2longdoubleconv(Int(-12));
    static_assert(int2longdoubleconv.get() == -12.0, "A signed int was not converted to a long double.");
    constexpr Long_Double uint2longdoubleconv(UInt(12));
    static_assert(uint2longdoubleconv.get() == 12.0, "An unsigned signed int was not converted to a long double.");
    constexpr Long_Double long2longdoubleconv(Long(-12));
    static_assert(long2longdoubleconv.get() == -12.0, "A signed long was not converted to a long double.");
    constexpr Long_Double ulong2longdoubleconv(ULong(12));
    static_assert(ulong2longdoubleconv.get() == 12.0, "An unsigned signed long was not converted to a long double.");
    constexpr Long_Double float2longdoubleconv(Float(-12));
    static_assert(float2longdoubleconv.get() == -12.0, "A float was not converted to a long double.");
    constexpr Long_Double double2longdoubleconv(Double(-12));
    static_assert(double2longdoubleconv.get() == -12.0, "A double was not converted to a long double.");

    // Explicit conversions
    constexpr Float double2float = static_cast<Float>(Double(12));
    static_assert(double2float.get() == 12, "A double was not converted explicitly to a float.");

    // Binary Operators
    static_assert((Int(1) + 1).get() == 2, "Binary + failed.");
    static_assert((1 + Int(1)).get() == 2, "Binary + failed.");
    static_assert((Int(1) + Int(1)).get() == 2, "Binary + failed.");

    static_assert((Int(2) - 1).get() == 1, "Binary - failed.");
    static_assert((2 - Int(1)).get() == 1, "Binary - failed.");
    static_assert((Int(2) - Int(1)).get() == 1, "Binary - failed.");

    static_assert((Int(2) * 3).get() == 6, "Binary * failed.");
    static_assert((2 * Int(3)).get() == 6, "Binary * failed.");
    static_assert((Int(2) * Int(3)).get() == 6, "Binary * failed.");

    static_assert((Int(6) / 3).get() == 2, "Binary / failed.");
    static_assert((6 / Int(3)).get() == 2, "Binary / failed.");
    static_assert((Int(6) / Int(3)).get() == 2, "Binary / failed.");

    static_assert((Int(6) % 5).get() == 1, "Binary % failed.");
    static_assert((6 % Int(5)).get() == 1, "Binary % failed.");
    static_assert((Int(6) % Int(5)).get() == 1, "Binary % failed.");

    static_assert((Int(5) & 3).get() == 1, "Binary & failed.");
    static_assert((5 & Int(3)).get() == 1, "Binary & failed.");
    static_assert((Int(5) & Int(3)).get() == 1, "Binary & failed.");

    static_assert((Int(5) | 2).get() == 7, "Binary | failed.");
    static_assert((5 | Int(2)).get() == 7, "Binary | failed.");
    static_assert((Int(5) | Int(2)).get() == 7, "Binary | failed.");

    static_assert((Int(7) ^ 2).get() == 5, "Binary ^ failed.");
    static_assert((7 ^ Int(2)).get() == 5, "Binary ^ failed.");
    static_assert((Int(7) ^ Int(2)).get() == 5, "Binary ^ failed.");

    static_assert((Int(2) << 1).get() == 4, "Binary << failed.");
    static_assert((2 << Int(1)).get() == 4, "Binary << failed.");
    static_assert((Int(2) << Int(1)).get() == 4, "Binary << failed.");

    static_assert((Int(4) >> 1).get() == 2, "Binary >> failed.");
    static_assert((4 >> Int(1)).get() == 2, "Binary >> failed.");
    static_assert((Int(4) >> Int(1)).get() == 2, "Binary >> failed.");

    static_assert(!(Boolean(true) && false).get(), "Binary && failed.");
    static_assert(!(true && Boolean(false)).get(), "Binary && failed.");
    static_assert(!(Boolean(true) && Boolean(false)).get(), "Binary && failed.");

    static_assert((Boolean(true) || false).get(), "Binary || failed.");
    static_assert((true || Boolean(false)).get(), "Binary || failed.");
    static_assert((Boolean(true) || Boolean(false)).get(), "Binary || failed.");

    static_assert(Int(1) == 1, "Binary == failed.");
    static_assert(1 == Int(1), "Binary == failed.");
    static_assert(Int(1) == Int(1), "Binary == failed.");

    static_assert(Int(1) != 2, "Binary != failed.");
    static_assert(1 != Int(2), "Binary != failed.");
    static_assert(Int(1) != Int(2), "Binary != failed.");

    static_assert(Int(1) < 2, "Binary < failed.");
    static_assert(1 < Int(2), "Binary < failed.");
    static_assert(Int(1) < Int(2), "Binary < failed.");

    static_assert(Int(1) <= 2, "Binary <= failed.");
    static_assert(1 <= Int(2), "Binary <= failed.");
    static_assert(Int(1) <= Int(2), "Binary <= failed.");

    static_assert(Int(3) > 2, "Binary > failed.");
    static_assert(3 > Int(2), "Binary > failed.");
    static_assert(Int(3) > Int(2), "Binary > failed.");

    static_assert(Int(3) >= 2, "Binary >= failed.");
    static_assert(3 >= Int(2), "Binary >= failed.");
    static_assert(Int(3) >= Int(2), "Binary >= failed.");

    // Test iostreams
    Int cinned;
    std::istringstream input("123");
    input >> cinned;
    assert(cinned == 123);

    constexpr Int couted(123);
    std::ostringstream output;
    output << couted;
    assert(output.str() == "123");

    constexpr Int expanded = Short(123);
    static_assert(expanded.get() == 123, "Could not convert from short to int.");

    static_assert(Int(1), "The value did not convert to true.");
    static_assert(!Int(0), "The value did convert to false.");
}