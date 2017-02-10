// lrkma_allocatorutil.h                                              -*-C++-*-
#ifndef INCLUDED_LRKMA_ALLOCATORUTIL
#define INCLUDED_LRKMA_ALLOCATORUTIL

//@PURPOSE: Provide ...
//
//@TYPES:
//  lrkma::AllocatorUtil:
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_LRKP_BOOLEAN
#include <lrkp_boolean.h>
#endif

namespace LarkCompiler {

namespace lrkma { class Allocator; }

namespace lrkma {

                            // ====================
                            // struct ALLOCATORUTIL
                            // ====================

struct AllocatorUtil {

    // CLASS METHODS
    template <typename OBJECT_TYPE>
    static void deleteObject(OBJECT_TYPE *object, Allocator *allocator);

};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                            // -------------------
                            // class ALLOCATORUTIL
                            // -------------------

// CLASS METHODS
template <typename OBJECT_TYPE>
void AllocatorUtil::deleteObject(OBJECT_TYPE *object, Allocator *allocator)
{
    object->~OBJECT_TYPE();
    allocator->deallocate(dynamic_cast<OBJECT_TYPE *>(allocator));
}

} // close namespace lrkma
} // close namespace LarkCompiler

#endif // INCLUDED_LRKMA_ALLOCATORUTIL

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
