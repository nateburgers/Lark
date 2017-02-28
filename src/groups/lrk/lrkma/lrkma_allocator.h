// lrkma_allocator.h                                                  -*-C++-*-
#ifndef INCLUDED_LRKMA_ALLOCATOR
#define INCLUDED_LRKMA_ALLOCATOR

//@PURPOSE: Provide ...
//
//@TYPES:
//  lrkma::Allocator:
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_LRKP_BOOLEAN
#include <lrkp_boolean.h>
#endif

#ifndef INCLUDED_LRKP_SIZE
#include <lrkp_size.h>
#endif

namespace LarkCompiler {
namespace lrkma {

                              // ===============
                              // class ALLOCATOR
                              // ===============

class Allocator {

  public:
    // CREATORS
    virtual ~Allocator() = 0;

    // MANIPULATORS
    virtual void *allocate(lrkp::Size size, lrkp::Size alignment) = 0;

    virtual void deallocate(void *memory) = 0;

};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                              // ---------------
                              // class ALLOCATOR
                              // ---------------

// CREATORS
inline
Allocator::~Allocator()
{
}

} // close namespace lrkma
} // close namespace LarkCompiler

#endif // INCLUDED_LRKMA_ALLOCATOR

// ----------------------------------------------------------------------------
// Copyright (c) 2017 Nathan Burgers
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
