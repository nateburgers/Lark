// lrkma_placementutil.h                                              -*-C++-*-
#ifndef INCLUDED_LRKMA_PLACEMENTUTIL
#define INCLUDED_LRKMA_PLACEMENTUTIL

//@PURPOSE: Provide ...
//
//@TYPES:
//  lrkma::PlacementUtil:
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_LRKMA_PLACEMENT
#include <lrkma_placement.h>
#endif

namespace LarkCompiler {
namespace lrkma {

                            // ====================
                            // struct PLACEMENTUTIL
                            // ====================

struct PlacementUtil {

    // CLASS METHODS
    template <typename OBJECT_TYPE>
    static Placement<OBJECT_TYPE> place(void *arena);

};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                            // --------------------
                            // struct PLACEMENTUTIL
                            // --------------------

// CLASS METHODS
template <typename OBJECT_TYPE> inline
Placement<OBJECT_TYPE> PlacementUtil::place(void *arena)
{
    return Placement<OBJECT_TYPE>(arena);
}

} // close namespace lrkma
} // close namespace LarkCompiler

#endif // INCLUDED_LRKMA_PLACEMENTUTIL

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
