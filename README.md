# primitive
Provide user-defined initialization semantics for arithmetic types.

## Overview
C++ does not default initialize primitive variables in functions and classes. The output of the following code may be completely random, depending on your platform:

    int i;
    std::cout << i << std::endl;
    
Most C++ developers are familiar with this, making sure to only initialize variables with values in functions and always doing member initialization in constructors. However, this is an easy mistake to make and can lead to surprising results for inexperienced programmers.

Many C programmers are familiar with this issue; a common bug is to forget to NUL (`\0`) terminate C strings. This leads to errors (overflows) because primitives in arrays are not initialized either.

    char text[6] = { 'H', 'E', 'L', 'L', 'O' };  // Potentially missing NUL terminator
    
For this reason, many organizations have policies in place that all variables must be initialized when defined. The purpose of this project is to enforce up-front initialization using C++ user-defined construction semantics. C++ guarantees that all user-defined types are constructed on creation.

This header provides the `primitive` class template, which is restricted to arithmetic types (types where `std::is_arithmetic<T>::value == true`). The following types are included:

* bool
* char (char16_t, char32_t and wchar) 
* signed char
* unsigned char
* short (signed and unsigned)
* int (signed and unsigned)
* long (signed and unsigned)
* long long (signed and unsigned)
* float
* double
* long double
* Types defined in `<cstdint>

Given `primitive<int> value;`, the variable `value` will hold the value `0`. Ideally, interactions with the `primitive` wrapper should perfectly match working with the underlying primitive. When the underlying primitive is needed, the `get` method will provide a copy of the underlying primitive. `primitive` also provides a `value_type` type definition to expose the underlying primitive type.

## Compile-time Friendly
The `primitive` class implements most of its functionality as `constexpr` to allow expressions to be calculated at compile-time. This allows you to use instances of `primitive` to build arrays and template arguments, e.g.:

    using UChar = primitive<unsigned char>;
    using Int = primitive<int>;
    contexpr Int BUFFER_SIZE = 1024; 
    UChar buffer[BUFFER_SIZE * 4];
    
## Underflow/Overflow-Safe Implicit Conversions (Optional)
The `primitive` class includes member templates to limit which conversions are permitted among primitive types. In C++, some of the legal conversion are surprising and error prone. For example, `double` implicitly converts to `int` (`int three = 3.14;`). Additionally, `char` is often used as an 8-bit arithmetic type, but there are no guarantees that it is signed or unsigned. For that reason, `primitive` does not allow `char` to implicitly convert to other types.

In cases where you are sure about the conversion, explicit conversions via `static_cast` are permitted.

## Limiting Booleans (optional)
C++ programmers are accustom to treating booleans (`bool`) as arithmetic types. It is not uncommon to see a `bool` added to an `int`. However, most of the time, conversion to and from `bool` should be explicit through comparisons or logical negation (`!`). Consider the following code:

    bool isTeacherNeeded = true;
    int students = 21;
    int participants = students + isTeacherNeeded;  // 22
    
With the restrictions placed on `primitive<bool>`, the code would need to be rewritten as:

    using Boolean = primitive<bool>;
    using Integer = primitive<int>;
    Boolean isTeacherNeeded = true;
    Integer students = 21;
    Integer participants = students + (isTeacherNeeded == true ? 1 : 0);
    
Instead of comparing to `true`, `get` could have been called, as well. I find this overly verbose, but the only alternative is to make an implicit conversion from `primitive<bool>` to `bool`.
