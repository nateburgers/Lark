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

} // close unnamed namespace


                               // ============
                               // type NATURAL
                               // ============

// TYPES
using Natural8  = unsigned           char;
using Natural16 = unsigned     short  int;
using Natural32 = unsigned      long  int;
using Natural64 = unsigned long long  int;
using Natural   = unsigned long long  int;

// STATIC ASSERTIONS
static_assert(1 == sizeof(Natural8 ), "");
static_assert(2 == sizeof(Natural16), "");
static_assert(4 == sizeof(Natural32), "");
static_assert(8 == sizeof(Natural64), "");
static_assert(8 == sizeof(Natural  ), "");

} // close package namespace
} // close product namespace

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
