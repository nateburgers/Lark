// lrkma_mallocfreeallocator.h                                        -*-C++-*-
#ifndef INCLUDED_LRKMA_MALLOCFREEALLOCATOR
#define INCLUDED_LRKMA_MALLOCFREEALLOCATOR

//@PURPOSE: Provide ...
//
//@TYPES:
//  lrkma::MallocFreeAllocator:
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_CSTDLIB
#include <cstdlib>
#define INCLUDED_CSTDLIB
#endif

#ifndef INCLUDED_LRKMA_ALLOCATOR
#include <lrkma_allocator.h>
#endif

#ifndef INCLUDED_LRKP_SIZE
#include <lrkp_size.h>
#endif

namespace LarkCompiler {
namespace lrkma {

                         // =========================
                         // class MALLOCFREEALLOCATOR
                         // =========================

class MallocFreeAllocator : public Allocator {

  public:
    // CREATORS
    MallocFreeAllocator() = default;

    MallocFreeAllocator(const MallocFreeAllocator&  original) = delete;
    MallocFreeAllocator(      MallocFreeAllocator&& original) = delete;

    ~MallocFreeAllocator() override = default;

    // MANIPULATORS
    MallocFreeAllocator& operator=(
                                 const MallocFreeAllocator& original) = delete;
    MallocFreeAllocator& operator=(MallocFreeAllocator&& original) = delete;

                          // lrkma::Allocator protocol

    void *allocate(lrkp::Size numBytes, lrkp::Size alignment) override;

    void deallocate(void *memory) override;

};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                         // -------------------------
                         // class MALLOCFREEALLOCATOR
                         // -------------------------

// MANIPULATORS
inline
void *MallocFreeAllocator::allocate(lrkp::Size numBytes, lrkp::Size alignment)
{
    static_cast<void>(alignment);
    return std::malloc(numBytes);
}

inline
void MallocFreeAllocator::deallocate(void *memory)
{
    std::free(memory);
}

} // close namespace lrkma
} // close namespace LarkCompiler

#endif // INCLUDED_LRKMA_MALLOCFREEALLOCATOR

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
