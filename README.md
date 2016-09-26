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
* char
* wchar
* signed char
* unsigned char
* short (signed and unsigned)
* int (signed and unsigned)
* long (signed and unsigned)
* long long (signed and unsigned)
* float
* double
* long double
* Types defined in <cstdint>

Given `primitive<int> value;`, the variable `value` will hold the value `0`. Ideally, interactions with the `primitive` wrapper should perfectly match working with the underlying primitive. When the underlying primitive is needed, the `get` method will provide a copy of the underlying primitive. `primitive` also provides a `value_type` type definition to expose the underlying primitive type.

## Compile-time Friendly
The `primitive` class implements most of its functionality as `constexpr` to allow expressions to be calculated at compile-time. This allows you to use instances of `primitive` to build arrays and template arguments, e.g.:

    using UChar = primitive<unsigned char>;
    using Int = primitive<int>;
    contexpr Int BUFFER_SIZE = 1024; 
    UChar buffer[BUFFER_SIZE * 4];
    
## Underflow/Overflow-Safe Implicit Conversions (Optional)
