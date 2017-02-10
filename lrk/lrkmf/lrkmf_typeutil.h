// lrkmf_typeutil.h                                                   -*-C++-*-
#ifndef INCLUDED_LRKMF_TYPEUTIL
#define INCLUDED_LRKMF_TYPEUTIL

//@PURPOSE: Provide ...
//
//@TYPES:
//  lrkmf::TypeUtil:
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_LRKP_BOOLEAN
#include <lrkp_boolean.h>
#endif

namespace LarkCompiler {
namespace lrkmf {

             // ==================================================
             // struct TypeUtil_EqualsImplUtil<LHS_TYPE, RHS_TYPE>
             // ==================================================

template <typename LHS_TYPE, typename RHS_TYPE>
struct TypeUtil_EqualsImplUtil {
    static constexpr lrkp::Boolean value = false;
};

template <typename TYPE>
struct TypeUtil_EqualsImplUtil<TYPE, TYPE> {
    static constexpr lrkp::Boolean value = true;
};

                               // ===============
                               // struct TYPEUTIL
                               // ===============

struct TypeUtil {

    // CLASS DATA
    template <typename LHS_TYPE, typename RHS_TYPE>
    static constexpr lrkp::Boolean equals =
        TypeUtil_EqualsImplUtil<LHS_TYPE, RHS_TYPE>::value;

};

static_assert(TypeUtil::equals<int, int>, "");

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                               // --------------
                               // class TYPEUTIL
                               // --------------

// CREATORS

// MANIPULATORS

// ACCESSORS

// FREE OPERATORS

} // close namespace lrkmf
} // close namespace LarkCompiler

#endif // INCLUDED_LRKMF_TYPEUTIL

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
