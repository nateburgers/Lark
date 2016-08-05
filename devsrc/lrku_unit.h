// lrku_unit.h                                                        -*-C++-*-
#ifndef INCLUDED_LRKU_UNIT
#define INCLUDED_LRKU_UNIT

//@PURPOSE:
//
//@TYPES:
//
//@SEE_ALSO:
//
//@DESCRIPTION:
//

#ifndef INCLUDED_LRKP_BOOLEAN
#include <lrkp_boolean.h>
#endif

namespace LarkCompiler {
namespace lrku {

                                 // ==========
                                 // class UNIT
                                 // ==========

class Unit {
    // ...

  public:
    // CREATORS
    explicit Unit() = default;

    explicit Unit(const Unit&  original) = default;
    explicit Unit(      Unit&& original) = default;

    ~Unit() = default;

    // MANIPULATORS
    Unit& operator=(const Unit&  original) = default;
    Unit& operator=(      Unit&& original) = default;
};

// FREE OPERATORS
lrkp::Boolean operator==(const Unit& lhs,
                         const Unit& rhs);

lrkp::Boolean operator!=(const Unit& lhs,
                         const Unit& rhs);

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                                 // ----------
                                 // class UNIT
                                 // ----------

// FREE OPERATORS
inline
lrkp::Boolean operator==(const Unit&,
                         const Unit&)
{
    return true;
}

inline
lrkp::Boolean operator!=(const Unit&,
                         const Unit&)
{
    return false;
}

} // close package namespace
} // close product namespace

#endif // INCLUDED_LRKU_UNIT

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
