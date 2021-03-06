// lrkp_real.h                                                        -*-C++-*-
#ifndef INCLUDED_LRKP_REAL
#define INCLUDED_LRKP_REAL

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

enum class FloatingPointType {
    e_FLOAT  =  0,
    e_DOUBLE =  1,

    e_ERROR  = -1,
};

            // ====================================================
            // struct FloatingPointWithType<FloatingPointType TYPE>
            // ====================================================

template <FloatingPointType TYPE>
struct FloatingPointWithType final {
    struct Type;
};

template <>
struct FloatingPointWithType<FloatingPointType::e_FLOAT> final {
    using Type = float;
};

template <>
struct FloatingPointWithType<FloatingPointType::e_DOUBLE> final {
    using Type = double;
};

                          // ========================
                          // struct FloatingPointUtil
                          // ========================

struct FloatingPointUtil {

    // CLASS METHODS
    static constexpr FloatingPointType typeWithSize(unsigned size)
    {
        if      (sizeof(float ) == size) {
            return FloatingPointType::e_FLOAT;
        }
        else if (sizeof(double) == size) {
            return FloatingPointType::e_DOUBLE;
        }
        else {
            return FloatingPointType::e_ERROR;
        }
    }

    // TYPES
    template <unsigned SIZE>
    using FloatingPointWithSize =
        typename FloatingPointWithType<typeWithSize(SIZE)>::Type;

};

}; // close unnamed namespace

                                  // =========
                                  // type REAL
                                  // =========

// TYPES
using Real32 = FloatingPointUtil::FloatingPointWithSize<4>;
using Real64 = FloatingPointUtil::FloatingPointWithSize<8>;
using Real   = FloatingPointUtil::FloatingPointWithSize<8>;

// STATIC ASSERTIONS
static_assert(4 == sizeof(Real32), "");
static_assert(8 == sizeof(Real64), "");
static_assert(8 == sizeof(Real  ), "");

static_assert(4 == alignof(Real32), "");
static_assert(8 == alignof(Real64), "");
static_assert(8 == alignof(Real  ), "");

} // close lrkp namespace
} // close LarkCompiler namespace

#endif // INCLUDED_LRKP_REAL

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
