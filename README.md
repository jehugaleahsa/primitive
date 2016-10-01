# primitive
Provide user-defined initialization semantics for arithmetic types.

## Overview
C++ does not default initialize primitive variables in functions and classes. The output of the following code may be completely random, depending on your platform:

    int i;
    std::cout << i << std::endl;

Most C++ developers are familiar with this, making sure to only initialize variables with values in functions and always doing member initialization in constructors. However, this is an easy mistake to make and can lead to surprising results for inexperienced programmers. Ininitialized arrays suffer the same problem. Consider:

    char unknown[100];  // uninitialized in local scope
    char zeroed[100] {};  // initialized to NUL (\0)
    primitive<char> constructed[100];  // initialized to NUL (\0)

For this reason, many organizations have policies in place that all variables must be initialized when defined. The purpose of this project is to enforce up-front initialization using C++ user-defined construction semantics. C++ guarantees that all user-defined types are constructed on creation.

This header provides the `primitive` class template, which is restricted to arithmetic types (types where `std::is_arithmetic<T>::value == true`). The following types are included:

* `bool`
* `char` (`char16_t`, `char32_t` and `wchar`)
* `signed char`
* `unsigned char`
* `short` (`signed` and `unsigned`)
* `int` (`signed` and `unsigned`)
* `long` (`signed` and `unsigned`)
* `long long` (`signed` and `unsigned`)
* `float`
* `double`
* `long double`
* Types defined in `<cstdint>`

Given `primitive<int> value;`, the variable `value` will hold the value `0`. Ideally, interactions with the `primitive` wrapper should perfectly match working with the underlying primitive. When the underlying primitive is needed, the `get` method will provide a copy of the underlying primitive. `primitive` also provides a `value_type` type definition to expose the underlying primitive type.

## Compile-time Friendly
The `primitive` class implements most of its functionality as `constexpr` to allow expressions to be calculated at compile-time. This allows you to use instances of `primitive` to build arrays and template arguments, e.g.:

    using UChar = primitive<unsigned char>;
    using Int = primitive<int>;
    contexpr Int BUFFER_SIZE = 1024;
    UChar buffer[BUFFER_SIZE * 4];

## Safer Promotions and Narrowing (Optional)
The `primitive` class includes member templates to limit which conversions are permitted among primitive types. In C++, some of the legal conversion are surprising and error prone. For example, `double` implicitly converts to `int` (`int three = 3.14;`). These types of implicit conversions are disabled as much as possible.

C++ allows signed and unsigned `char` and `short` values to be initialized from integer literals; the best you can hope for is a warning if the value would be truncated. In order to declare variables of these types, `primitive` provides a static `from` function to convert from `int` (e.g., `auto x = primitive<short>::from(123);`). Your compiler should provide the same level of warnings when using `from`.

Even `from` restricts which values `primitive`s can be initialized with. If you want to support additional conversions with the `from` function, provide a template specialization:

    template<> struct is_conversion<From, To> : std::true_type {};  // higher to lower precision

Here, `From` is the type you want to convert to type `To`. Note your compiler may still refuse your custom conversions. The absolute workaround is to `static_cast` the value beforehand.

Another restriction imposed by `primitive` is that signed and unsigned variables and value cannot be mixed. Unsigned variables must be initialized using unsigned literals (e.g., `primitive<unsigned int> x = 123u;`). Signed variables must be initialized from signed literals (e.g., `primitive<int> x = 123;`).

Additionally, `char` is often used as an 8-bit arithmetic type, but there are no guarantees that it is signed or unsigned. For that reason, `primitive` does not explicitly allow `char` to implicitly convert to other types; however, in many environments `char` is simply a typedef of a `signed char` or `unsigned char`, so the conversion must be permitted.

If you want to define your own promotions, you can define your own template specializations:

    template<> struct is_promotion<From, To> : std::true_type {};  // lower to higher precision

Here, `From` is the type you want to convert/promote to type `To`. This would be useful if working with `<cstdint>` and need to support promotion, e.g., `int32_t` to `int64_t`.

In cases where you are sure about the conversion, explicit conversions to other `primitive` types are supported via `static_cast`.

## Limiting Booleans (optional)
C++ programmers are accustom to treating booleans (`bool`) as arithmetic types. It is not uncommon to see a `bool` added to an `int`. However, most of the time, conversion to and from `bool` should be explicit through comparisons or logical negation (`!`). For that reason, it will be common to see the following when using `primitive<bool>`:

    primitive<bool> condition(true);
    if (condition.get()) {}
    if (condition == true) {}
    if (!!condition) {}

I find this overly verbose, but the only alternative is to make an implicit conversion from `primitive<bool>` to `bool`.
