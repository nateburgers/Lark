// lrkma_placement.h                                                  -*-C++-*-
#ifndef INCLUDED_LRKMA_PLACEMENT
#define INCLUDED_LRKMA_PLACEMENT

//@PURPOSE: Provide ...
//
//@TYPES:
//  lrkma::Placement:
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_LRKMF_TYPEUTIL
#include <lrkmf_typeutil.h>
#endif

#ifndef INCLUDED_LRKP_SIZE
#include <lrkp_size.h>
#endif

template <typename AUTHORIZATION_TYPE>
void *operator new(LarkCompiler::lrkp::Size  numBytes,
                   void                     *arena,
                   AUTHORIZATION_TYPE&&      authorization);

namespace LarkCompiler {
namespace lrkma {

                              // ===============
                              // class PLACEMENT
                              // ===============

template <typename OBJECT_TYPE>
class Placement {

  public:
    // TYPES
    using Object = OBJECT_TYPE;

  private:
    // PRIVATE TYPES
    struct PlacementNewAuthorization {
    };

    // FRIENDS
    template <typename AUTHORIZATION_TYPE>
    friend void *::operator new(LarkCompiler::lrkp::Size  numBytes,
                                void                     *arena,
                                AUTHORIZATION_TYPE&&      authorization);

    // DATA
    void *d_arena_p;

  public:
    // CREATORS
    Placement() = default;

    Placement(const Placement&  original) = default;
    Placement(      Placement&& original) = default;

    explicit Placement(void *arena);

    ~Placement() = default;

    // MANIPULATORS
    Placement& operator=(const Placement&  original) = default;
    Placement& operator=(      Placement&& original) = default;

    void setArena(void *arena);

    template <typename... CONSTRUCTOR_PARAMS>
    Object *operator()(CONSTRUCTOR_PARAMS&&... parameters) &&;

    // ACCESSORS
    const void *arena() const;
};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                              // ---------------
                              // class PLACEMENT
                              // ---------------

// CREATORS
template <typename OBJECT_TYPE> inline
Placement<OBJECT_TYPE>::Placement(void *arena)
    : d_arena_p(arena)
{
}

// MANIPULATORS
template <typename OBJECT_TYPE> inline
void Placement<OBJECT_TYPE>::setArena(void *arena)
{
    d_arena_p = arena;
}

template <typename    OBJECT_TYPE>
template <typename... CONSTRUCTOR_PARAMS> inline
OBJECT_TYPE *Placement<OBJECT_TYPE>::operator()(
                                         CONSTRUCTOR_PARAMS&&... parameters) &&
{
    // TODO(nate): forward the parameters
    return new (d_arena_p, PlacementNewAuthorization()) Object(parameters...);
}

// ACCESSORS
template <typename OBJECT_TYPE> inline
const void *Placement<OBJECT_TYPE>::arena() const
{
    return d_arena_p;
}

} // close namespace lrkma
} // close namespace LarkCompiler

template <typename AUTHORIZATION_TYPE> inline
void *operator new(LarkCompiler::lrkp::Size  numBytes,
                   void                     *arena,
                   AUTHORIZATION_TYPE&&      authorization)
{
    static_assert(LarkCompiler::lrkmf::TypeUtil::equals<
                  AUTHORIZATION_TYPE,
                  typename LarkCompiler::lrkma::Placement<int>::PlacementNewAuthorization>,
                  "");

    static_cast<void>(authorization);
    static_cast<void>(numBytes);
    return arena;
}

int main()
{
    int foo;
    int *bar = new (&foo, foo) int(3);
}

#endif // INCLUDED_LRKMA_PLACEMENT

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
