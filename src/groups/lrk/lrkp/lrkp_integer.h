// lrkp_integer.h                                                     -*-C++-*-
#ifndef INCLUDED_LRKP_INTEGER
#define INCLUDED_LRKP_INTEGER

//@PURPOSE: Provide a set of integer types specified by size.
//
//@TYPES:
//  lrkp::Integer8:   8-bit signed integer
//  lrkp::Integer16: 16-bit signed integer
//  lrkp::Integer32: 32-bit signed integer
//  lrkp::Integer64: 64-bit signed integer
//  lrkp::Integer:   64-bit signed integer
//
//@SEE_ALSO: lrkp_natural, lrkp_real
//
//@DESCRIPTION: This component
//

namespace LarkCompiler {
namespace lrkp {
namespace {

                              // ================
                              // enum IntegerType
                              // ================

enum class IntegerType {
    e_SIGNED_CHAR          =  0,
    e_SIGNED_SHORT_INT     =  1,
    e_SIGNED_INT           =  2,
    e_SIGNED_LONG_INT      =  3,
    e_SIGNED_LONG_LONG_INT =  4,

    e_ERROR                = -1,
};

                  // ========================================
                  // struct IntegerWithType<IntegerType TYPE>
                  // ========================================

template <IntegerType TYPE>
struct IntegerWithType final {
    struct Type;
};

template <>
struct IntegerWithType<IntegerType::e_SIGNED_CHAR> final {
    using Type = signed char;
};

template <>
struct IntegerWithType<IntegerType::e_SIGNED_SHORT_INT> final {
    using Type = signed short int;
};

template <>
struct IntegerWithType<IntegerType::e_SIGNED_INT> final {
    using Type = signed int;
};

template <>
struct IntegerWithType<IntegerType::e_SIGNED_LONG_INT> final {
    using Type = signed long int;
};

template <>
struct IntegerWithType<IntegerType::e_SIGNED_LONG_LONG_INT> final {
    using Type = signed long long int;
};

                             // ==================
                             // struct IntegerUtil
                             // ==================

struct IntegerUtil {

    // CLASS METHODS
    static constexpr IntegerType typeWithSize(unsigned size)
    {
        if      (sizeof(signed char         ) == size) {
            return IntegerType::e_SIGNED_CHAR;
        }
        else if (sizeof(signed short int    ) == size) {
            return IntegerType::e_SIGNED_SHORT_INT;
        }
        else if (sizeof(signed int          ) == size) {
            return IntegerType::e_SIGNED_INT;
        }
        else if (sizeof(signed long int     ) == size) {
            return IntegerType::e_SIGNED_LONG_INT;
        }
        else if (sizeof(signed long long int) == size) {
            return IntegerType::e_SIGNED_LONG_LONG_INT;
        }
        else {
            return IntegerType::e_ERROR;
        }
    }

    // TYPES
    template <unsigned SIZE>
    using IntegerWithSize = typename IntegerWithType<typeWithSize(SIZE)>::Type;
};

} // close unnamed namespace

// TYPES
using Integer8  = IntegerUtil::IntegerWithSize<1>;
using Integer16 = IntegerUtil::IntegerWithSize<2>;
using Integer32 = IntegerUtil::IntegerWithSize<4>;
using Integer64 = IntegerUtil::IntegerWithSize<8>;
using Integer   = IntegerUtil::IntegerWithSize<8>;

// STATIC ASSERTIONS
static_assert(1 == sizeof(Integer8 ), "");
static_assert(2 == sizeof(Integer16), "");
static_assert(4 == sizeof(Integer32), "");
static_assert(8 == sizeof(Integer64), "");
static_assert(8 == sizeof(Integer  ), "");

static_assert(1 == alignof(Integer8 ), "");
static_assert(2 == alignof(Integer16), "");
static_assert(4 == alignof(Integer32), "");
static_assert(8 == alignof(Integer64), "");
static_assert(8 == alignof(Integer  ), "");

} // close lrkp namespace
} // close LarkCompiler namespace

#endif // INCLUDED_LRKP_INTEGER

// ----------------------------------------------------------------------------
// Copyright (c) 2016 Nathan Burgers
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ------------------------------ END-OF-FILE ---------------------------------
