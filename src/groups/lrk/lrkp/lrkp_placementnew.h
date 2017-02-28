// lrkp_placementnew.h                                                -*-C++-*-
#ifndef INCLUDED_LRKP_PLACEMENTNEW
#define INCLUDED_LRKP_PLACEMENTNEW

#ifndef INCLUDED_LRKP_SIZE
#include <lrkp_size.h>
#endif

//@PURPOSE:
//
//@SEE_ALSO:
//
//@DESCRIPTION:
//

void *operator new(LarkCompiler::lrkp::Size  size,
                   void                     *storage) noexcept;

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

inline
void *operator new(LarkCompiler::lrkp::Size,
                   void                      *storage) noexcept
    // Note that this function cannot be placed in a namespace.
{
    return storage;
}

#endif // INCLUDED_LRKP_PLACEMENTNEW

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
