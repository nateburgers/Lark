// m_lrkbld_cursor.h
#ifndef INCLUDED_M_LRKBLD_CURSOR
#define INCLUDED_M_LRKBLD_CURSOR

//@PURPOSE: Provide a mechanism for iterating over a temporary sequence.
// 
//@CLASSES:
//  Cursor:  
//
//@DESCRIPTION:
//

#ifndef INCLUDED_MEMORY
#include <memory>
#define INCLUDED_MEMORY
#endif

#ifndef INCLUDED_UTILITY
#include <utility>
#define INCLUDED_UTILITY
#endif

namespace LarkCompiler {
namespace m_lrkbld {

template <typename ELEMENT_TYPE>
class VirtualCursor {
    // This mechanism implementation..
  public:
    // TYPES
    using ElementType = ELEMENT_TYPE;

  public:
    // CREATORS
    virtual ~VirtualCursor() = 0;

    // MANIPULATORS
    virtual void advance() = 0;

    // ACCESSORS
    virtual void element(ElementType *output) const = 0; 

    virtual bool done() const = 0;
};

template <typename ELEMENT_TYPE>
class Cursor final {
    // This mechanism provides 

  public:
    // TYPES
    using ElementType    = ELEMENT_TYPE;
    using Implementation = VirtualCursor<ElementType>;

  private:
    // DATA
    std::unique_ptr<Implementation> d_impl;

  public:
    // CREATORS
    Cursor() = default;

    Cursor(std::unique_ptr<Implementation>&& impl);

    Cursor(const Cursor&  source) = delete;
    Cursor(      Cursor&& source) = default;

   ~Cursor() = default;

    // MANIPULATORS
    Cursor& operator=(const Cursor&  source) = delete;
    Cursor& operator=(      Cursor&& source) = default;

    void reset(std::unique_ptr<Implementation>&& impl);

    void advance();

    // ACCESSORS
    void element(ElementType *output) const;

    bool done() const;
};

struct CursorUtil {
    // This 'struct' provides a namespace for utility functions acting on
    // 'Cursor' objects.

    // CLASS ACCESSORS
    template <typename ELEMENT_TYPE,
              typename CLOSURE_TYPE>
    static void forEach(Cursor<ELEMENT_TYPE> *cursor,
                        CLOSURE_TYPE&&        closure);
        // Invoke the specified 'closure' on each element in the specified
        // 'cursor'.
};

// ============================================================================
//                           INLINE DEFINITIONS
// ============================================================================

                        // -----------------
                        // struct CursorUtil
                        // -----------------
 
// CREATORS
template <typename ELEMENT_TYPE>
Cursor<ELEMENT_TYPE>::Cursor(
                  std::unique_ptr<Cursor<ELEMENT_TYPE>::Implementation>&& impl)
    : d_impl(std::move(impl))
{
}

// MANIPULATORS
template <typename ELEMENT_TYPE>
void Cursor<ELEMENT_TYPE>::reset(
                  std::unique_ptr<Cursor<ELEMENT_TYPE>::Implementation>&& impl)
{
    d_impl = std::move(impl);
}

template <typename ELEMENT_TYPE>
void Cursor<ELEMENT_TYPE>::advance()
{
    d_impl->advance();
}

// ACCESSORS
template <typename ELEMENT_TYPE>
void Cursor<ELEMENT_TYPE>::element(ELEMENT_TYPE *output) const
{
    d_impl->element(output);
}

template <typename ELEMENT_TYPE>
bool Cursor<ELEMENT_TYPE>::done() const
{
    return d_impl->done();
}

                        // -----------------
                        // struct CursorUtil
                        // -----------------

// CLASS ACCESSORS
template <typename ELEMENT_TYPE,
          typename CLOSURE_TYPE>
void CursorUtil::forEach(Cursor<ELEMENT_TYPE> *cursor,
                         CLOSURE_TYPE&&        closure)
{
    while (!cursor->done()) {
        ELEMENT_TYPE element;
        cursor->element(&element);
        closure(std::move(element));
        cursor->advance();
    }
}

} // close package namespace
} // close product namespace

#endif // INCLUDED_M_LRKBLD_CURSOR
