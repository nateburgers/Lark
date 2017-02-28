// lrkpa_atomicutil.h                                                 -*-C++-*-
#ifndef INCLUDED_LRKPA_ATOMICUTIL
#define INCLUDED_LRKPA_ATOMICUTIL

//=============================================================================
// @PURPOSE:
// 
// @TYPES:
// 
// @SEE_ALSO:
// 
// @DESCRIPTION:
// 
//-----------------------------------------------------------------------------

#ifndef INCLUDED_LRKP_INTEGER
#include <lrkp_integer.h>
#endif
 
namespace LarkCompiler {
namespace lrkpa {

                              // =================
                              // struct ATOMICUTIL
                              // =================

struct AtomicUtil {
    // This utility 'struct' ...

    // TYPES
    enum class MemoryOrder {
        e_RELAXED,
        e_ACQUIRE,
        e_RELEASE,
        e_ACQUIRE_RELEASE,
        e_SEQUENTIAL_CONSISTENT,
    };

    // CLASS METHODS
    static lrkp::Integer64 fetchThenAdd(lrkp::Integer64 *output,
                                        lrkp::Integer64  value,
                                        MemoryOrder      orderingConstraint);

    static lrkp::Integer64 fetchThenSubtract(
                                          lrkp::Integer64 *output,
                                          lrkp::Integer64  value,
                                          MemoryOrder      orderingConstraint);

    static lrkp::Integer64 fetchThenOr(lrkp::Integer64 *output,
                                       lrkp::Integer64  value);

    static lrkp::Integer64 fetchThenAnd(lrkp::Integer64 *output,
                                        lrkp::Integer64  value);

    static lrkp::Integer64 fetchThenXor(lrkp::Integer64 *output,
                                        lrkp::Integer64  value);

    //static lrkp::Integer64 fetchThenNand
};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                              // -----------------
                              // struct ATOMICUTIL
                              // -----------------

// CLASS METHODS

} // close namespace lrkpa
} // close namespace LarkCompiler

#endif // INCLUDED_LRKPA_ATOMICUTIL

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
