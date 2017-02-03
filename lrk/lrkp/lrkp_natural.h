// lrkp_natural.h                                                     -*-C++-*-
#ifndef INCLUDED_LRKP_NATURAL
#define INCLUDED_LRKP_NATURAL

//@PURPOSE:
//
//@TYPES:
//
//@SEE_ALSO:
//
//@DESCRIPTION:
//

namespace LarkCompiler {
namespace lrkp {
namespace {

enum class UnsignedType {
    e_UNSIGNED_CHAR          =  0,
    e_UNSIGNED_SHORT_INT     =  1,
    e_UNSIGNED_INT           =  2,
    e_UNSIGNED_LONG_INT      =  3,
    e_UNSIGNED_LONG_LONG_INT =  4,

    e_ERROR                  = -1,
};

                 // ==========================================
                 // struct UnsignedWithType<UnsignedType TYPE>
                 // ==========================================

template <UnsignedType TYPE>
struct UnsignedWithType final {
    struct Type;
};

template <>
struct UnsignedWithType<UnsignedType::e_UNSIGNED_CHAR> final {
    using Type = unsigned char;
};

template <>
struct UnsignedWithType<UnsignedType::e_UNSIGNED_SHORT_INT> final {
    using Type = unsigned short int;
};

template <>
struct UnsignedWithType<UnsignedType::e_UNSIGNED_INT> final {
    using Type = unsigned int;
};

template <>
struct UnsignedWithType<UnsignedType::e_UNSIGNED_LONG_INT> final {
    using Type = unsigned long int;
};

template <>
struct UnsignedWithType<UnsignedType::e_UNSIGNED_LONG_LONG_INT> final {
    using Type = unsigned long long int;
};

                             // ===================
                             // struct UnsignedUtil
                             // ===================

struct UnsignedUtil {

    // CLASS METHODS
    static constexpr UnsignedType typeWithSize(unsigned size)
    {
        if      (sizeof(unsigned char         ) == size) {
            return UnsignedType::e_UNSIGNED_CHAR;
        }
        else if (sizeof(unsigned short int    ) == size) {
            return UnsignedType::e_UNSIGNED_SHORT_INT;
        }
        else if (sizeof(unsigned int          ) == size) {
            return UnsignedType::e_UNSIGNED_INT;
        }
        else if (sizeof(unsigned long int     ) == size) {
            return UnsignedType::e_UNSIGNED_LONG_INT;
        }
        else if (sizeof(unsigned long long int) == size) {
            return UnsignedType::e_UNSIGNED_LONG_LONG_INT;
        }
        else {
            return UnsignedType::e_ERROR;
        }
    }

    // TYPES
    template <unsigned SIZE>
    using UnsignedWithSize =
        typename UnsignedWithType<typeWithSize(SIZE)>::Type;

};

} // close unnamed namespace


                               // ============
                               // type NATURAL
                               // ============

// TYPES
using Natural8  = UnsignedUtil::UnsignedWithSize<1>;
using Natural16 = UnsignedUtil::UnsignedWithSize<2>;
using Natural32 = UnsignedUtil::UnsignedWithSize<4>;
using Natural64 = UnsignedUtil::UnsignedWithSize<8>;
using Natural   = UnsignedUtil::UnsignedWithSize<8>;

// STATIC ASSERTIONS
static_assert(1 == sizeof(Natural8 ), "");
static_assert(2 == sizeof(Natural16), "");
static_assert(4 == sizeof(Natural32), "");
static_assert(8 == sizeof(Natural64), "");
static_assert(8 == sizeof(Natural  ), "");

static_assert(1 == alignof(Natural8 ), "");
static_assert(2 == alignof(Natural16), "");
static_assert(4 == alignof(Natural32), "");
static_assert(8 == alignof(Natural64), "");
static_assert(8 == alignof(Natural  ), "");

} // close lrkp namespace
} // close LarkCompiler namespace

#endif // INCLUDED_LRKP_NATURAL

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
