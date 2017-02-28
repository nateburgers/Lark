// lrkp_byte.h                                                        -*-C++-*-
#ifndef INCLUDED_LRKP_BYTE
#define INCLUDED_LRKP_BYTE

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

                               // =========
                               // type BYTE
                               // =========

// TYPES
using Byte = unsigned char;

// STATIC ASSERTIONS
static_assert(1 == sizeof(Byte),
              "The size of the 'Byte' type is 1.");

} // close package namespace
} // close product namespace

#endif // INCLUDED_LRKP_BYTE

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
