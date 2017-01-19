// lrkp_integer.h                                                     -*-C++-*-
#ifndef INCLUDED_LRKP_INTEGER
#define INCLUDED_LRKP_INTEGER

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

                               // ============
                               // type INTEGER
                               // ============

// TODO(nate): put the below type machinery into a utility.
template <unsigned SIZE, typename... TYPES>
struct IntegerSearch;

template <bool CONDITION, unsigned SIZE, typename TYPE, typename... TYPES>
struct IntegerSearchCondition;

template <unsigned SIZE, typename TYPE, typename... TYPES>
struct IntegerSearchCondition<true, SIZE, TYPE, TYPES...> {
    using Type = TYPE;
};

template <unsigned SIZE, typename TYPE, typename... TYPES>
struct IntegerSearchCondition<false, SIZE, TYPE, TYPES...> {
    using Type = typename IntegerSearch<SIZE, TYPES...>::Type;
};

template <unsigned SIZE, typename TYPE, typename... TYPES>
struct IntegerSearch<SIZE, TYPE, TYPES...> {
    using Type =
        typename IntegerSearchCondition<
            SIZE == sizeof(TYPE),
            SIZE,
            TYPE,
            TYPES...
        >::Type;
};

template <unsigned SIZE, typename TYPE>
struct IntegerSearch<SIZE, TYPE> {

    static_assert(SIZE == sizeof(TYPE),
                  "None of the specified 'TYPES' had the specified 'SIZE'.");

    using Type = TYPE;
};

template <unsigned SIZE, typename... TYPES>
using FirstTypeWithSize = typename IntegerSearch<SIZE, TYPES...>::Type;

// TODO(nate): put the above into a utility.

template <unsigned SIZE>
using SizedInteger = FirstTypeWithSize<SIZE,
    signed char,
    signed short int,
    signed int,
    signed long int,
    signed long long int
>;

// TYPES
using Integer8  = SizedInteger<1>;
using Integer16 = SizedInteger<2>;
using Integer32 = SizedInteger<4>;
using Integer64 = SizedInteger<8>;
using Integer   = SizedInteger<8>;

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

} // close package namespace
} // close product namespace

#endif // INCLUDED_LRKP_TEMPLATE

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
