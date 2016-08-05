// lrku_nullablevaluebuffer.h                                         -*-C++-*-
#ifndef INCLUDED_LRKU_NULLABLEVALUEBUFFER
#define INCLUDED_LRKU_NULLABLEVALUEBUFFER

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

#ifndef INCLUDED_LRKP_BYTE
#include <lrkp_byte.h>
#endif

#ifndef INCLUDED_LRKP_SIZE
#include <lrkp_size.h>
#endif

#ifndef INCLUDED_LRKP_PLACEMENTNEW
#include <lrkp_placementnew.h>
#endif

template <typename AUTHORIZATION_TAG>
void *operator new(unsigned int, void *data, AUTHORIZATION_TAG);

namespace LarkCompiler {
namespace lrku {

template <lrkp::Size SIZE>
using ByteArray = lrkp::Byte[SIZE];

template <typename OBJECT_TYPE>
class ObjectStorage {
  public:
    using Object = OBJECT_TYPE;
    using Buffer = ByteArray<sizeof(Object)>;

  private:
    alignas(Object) Buffer d_buffer;

    static constexpr void checkInvariants()
    {
        static_assert( sizeof(Object) ==  sizeof(ObjectStorage));
        static_assert(alignof(Object) == alignof(ObjectStorage));
    }

  public:
    constexpr ObjectStorage() = default;
    constexpr ObjectStorage(const ObjectStorage&  original) = default;
    constexpr ObjectStorage(      ObjectStorage&& original) = default;

    ~ObjectStorage() = default;

    constexpr Buffer& buffer() &
    {
        checkInvariants();
        return d_buffer;
    }

    constexpr Buffer&& buffer() &&
    {
        checkInvariants();
        return d_buffer;
    }

    constexpr const Buffer& buffer() const &
    {
        checkInvariants();
        return d_buffer;
    }
};

// TODO(nate): Array specializations for this
template <typename OBJECT_TYPE>
class Placement {

  public:
    // TYPES
    using Object = OBJECT_TYPE;

  private:
    struct Authorization { };

    template <typename AUTH>
    friend void* (::operator new) (long unsigned int, void *, AUTH);

    void *d_memory_p;

  public:
    Placement() = delete;

    //Placement(void *data);

    template <lrkp::Size NUM_BYTES>
    Placement(ByteArray<NUM_BYTES> *memory)
        : d_memory_p(memory)
    {
        static_assert(sizeof(Object) == NUM_BYTES);
    }

    template <typename... CONSTRUCTOR_ARGUMENTS>
    Object *operator()(CONSTRUCTOR_ARGUMENTS&&... arguments) &&
    {
        // TODO(nate): forward
        return new (d_memory_p) Object(arguments...);
    }
};

template <typename OBJECT_TYPE>
class ValuePlacement {
  public:
    // TYPES
    using Object = OBJECT_TYPE;

  private:
    // DATA
    Placement<Object> d_placement;

  public:
    // CREATORS
    template <typename lrkp::Size NUM_BYTES>
    ValuePlacement(ByteArray<NUM_BYTES> *memory)
        : d_placement(memory)
    {
    }

    // MANIPULATORS
    template <typename... CONSTRUCTOR_ARGUMENTS>
    Object& operator()(CONSTRUCTOR_ARGUMENTS&&... arguments) &&
    {
        return *static_cast<Placement<Object>&&>(d_placement)(arguments...);
    }
};

struct PlacementUtil {
    template <typename OBJECT_TYPE, lrkp::Size NUM_BYTES>
    static Placement<OBJECT_TYPE> place(ByteArray<NUM_BYTES> *memory)
    {
        return Placement<OBJECT_TYPE>(memory);
    }

    template <typename OBJECT_TYPE>
    static Placement<OBJECT_TYPE> place(ObjectStorage<OBJECT_TYPE> *storage)
    {
        return Placement<OBJECT_TYPE>(&storage->buffer());
    }

    template <typename OBJECT_TYPE>
    static ValuePlacement<OBJECT_TYPE> placeValue(
                                          ObjectStorage<OBJECT_TYPE> *storage)
    {
        return ValuePlacement<OBJECT_TYPE>(&storage->buffer());
    }

    // TODO(nate): placeUnique, placeShared, etc...
};


template <typename CONSTRUCTOR_SIGNATURE>
class Constructor;

template <typename OBJECT_TYPE>
using DefaultConstructor = Constructor<OBJECT_TYPE()>;

template <typename OBJECT_TYPE>
using CopyConstructor = Constructor<OBJECT_TYPE(const OBJECT_TYPE&)>;

template <typename OBJECT_TYPE>
using MoveConstructor = Constructor<OBJECT_TYPE(OBJECT_TYPE&&)>;

template <typename    OBJECT_TYPE,
          typename... CONSTRUCTOR_ARGUMENTS>
class Constructor<OBJECT_TYPE(CONSTRUCTOR_ARGUMENTS...)> {

  public:
    using Function = OBJECT_TYPE(CONSTRUCTOR_ARGUMENTS...);
  private:
    Function *d_constructor;

    static OBJECT_TYPE construct(CONSTRUCTOR_ARGUMENTS... arguments)
    {
        // TODO(nate): forward
        return OBJECT_TYPE(arguments...);
    }

  public:
    constexpr explicit Constructor()
        : d_constructor(&construct)
    {
    }

    constexpr explicit Constructor(Function *constructor)
        : d_constructor(constructor)
    {
    }

    OBJECT_TYPE operator()(CONSTRUCTOR_ARGUMENTS... arguments) const
    {
        // TODO(nate): forward
        return d_constructor(arguments...);
    }
};

template <typename OBJECT_TYPE>
class Destructor {
  public:
    using Object   = OBJECT_TYPE;
    using Function = void(Object *);

  private:
    Function *d_destructor;

    static void destroy(Object *object)
    {
        object->~Object();
    }

  public:
    explicit Destructor()
        : d_destructor(&destroy)
    {
    }

    constexpr explicit Destructor(Function *destructor)
        : d_destructor(destructor)
    {
    }

    void operator()(Object *object) const
    {
        d_destructor(object);
    }
};

template <typename SIGNATURE_TYPE>
struct Method;

template <typename    HOST_TYPE,
          typename    RETURN_TYPE,
          typename... ARGUMENT_TYPES>
class Method<RETURN_TYPE(HOST_TYPE, ARGUMENT_TYPES...)>
{
  public:
    // TYPES
    using Pointer = RETURN_TYPE (HOST_TYPE::*)(ARGUMENT_TYPES...);

  private:
    Pointer  d_method_p;

  public:
    Method (Pointer method)
        : d_method_p(method)
    {
    }

    RETURN_TYPE operator()(HOST_TYPE           *host, 
                           ARGUMENT_TYPES&&...  arguments) const
    {
        return (host->*d_method_p)(arguments...);
    }

    Pointer operator Pointer() const
    {
        return d_method_p;
    }
};

struct ObjectUtil 
{
    template <typename    OBJECT_TYPE,
              typename... CONSTRUCTOR_ARGUMENTS>
    static OBJECT_TYPE construct(CONSTRUCTOR_ARGUMENTS&&... arguments)
    {
        // TODO(nate): forward
        return OBJECT_TYPE(arguments...);
    }

    template <typename OBJECT_TYPE>
    static void destroy(OBJECT_TYPE *object)
    {
        object->~OBJECT_TYPE();
    }
};


static_assert(alignof(int) == alignof(ObjectStorage<int>));

void test() {
    struct Empty { };
    CopyConstructor<int> makeEmpty;
    Destructor<Empty> destroy;
    int empty = makeEmpty(2);
    (void)empty;
    // Destructor<int> d = ObjectUtil::destructor<int>;
    // Method<Class, int(int, int)> m = &int::doSomething;
    ObjectStorage<int> storage;
    int& foo = PlacementUtil::placeValue<int>(&storage) (3);
    ObjectUtil::destroy(&foo);

    int bar = ObjectUtil::construct<int>(3);
    (void)bar;
}

template <lrkp::Boolean ENABLE, typename TYPE = void>
struct EnableIfImpUtil
{
};

template <lrkp::Boolean ENABLE, typename TYPE>
struct EnableIfImpUtil<true, TYPE>
{
    using Type = TYPE;
}

template lrkp::Boolean ENABLE, typename TYPE>
using EnableIf = EnableIfImpUtil<ENABLE, TYPE>::Type;

}
}

template <typename AUTHORIZATION_TAG>
EnableIf<
    lrkmf::TypeUtil::isSame<Placement::Authorization, AUTHORIZATION_TAG>,
    void *
> operator new(unsigned long, void *data, AUTHORIZATION_TAG)
{
    // TODO(nate): Use enable_if to only allow this template to
    //             participate in overload resolution if the authorization
    //             tag is the same as Placement::Authorization.
    return data;
}


namespace LarkCompiler {
namespace lrku {

                       // ===============================
                       // class NULLABLEVALUEBUFFER<TYPE>
                       // ===============================

template <typename VALUE_TYPE>
class NullableValueBuffer {
    // ...

  public:
    // TYPES
    using Value = VALUE_TYPE;

  private:
    // DATA
    alignas(Value) lrkp::Byte d_buffer[sizeof(Value)];

  public:
    // CREATORS
    explicit NullableValueBuffer() = default;

    explicit NullableValueBuffer(const NullableValueBuffer& ) = default;
    explicit NullableValueBuffer(      NullableValueBuffer&&) = default;

    ~NullableValueBuffer() = default;

    template <typename... CONSTRUCTOR_ARGUMENTS>
    Value& construct(CONSTRUCTOR_ARGUMENTS&&... arguments);

    // MANIPULATORS
    NullableValueBuffer& operator=(const NullableValueBuffer& ) = default;
    NullableValueBuffer& operator=(      NullableValueBuffer&&) = default;
};

template <typename VALUE_TYPE>
class NullableValue {
    // ...

  public:
    using Value = VALUE_TYPE;

  private:
    Value                      *d_value_p;
    NullableValueBuffer<Value>  d_buffer;

  public:
    // CREATORS
    explicit NullableValue();

    explicit NullableValue(const NullableValue&  original);
    explicit NullableValue(      NullableValue&& original);

    template <typename... CONSTRUCTOR_ARGUMENTS>
    explicit NullableValue(CONSTRUCTOR_ARGUMENTS&&... arguments);

    ~NullableValue();

    // MANIPULATORS
    NullableValue& operator=(const NullableValue&  original);
    NullableValue& operator=(      NullableValue&& original);

    template <typename OTHER_VALUE_TYPE>
    NullableValue& operator=(const NullableValue<OTHER_VALUE_TYPE>&  original);

    template <typename OTHER_VALUE_TYPE>
    NullableValue& operator=(      NullableValue<OTHER_VALUE_TYPE>&& original);

    NullableValue& operator=(const Value&  value);
    NullableValue& operator=(      Value&& value);

    template <typename... CONSTRUCTOR_ARGUMENTS>
    void construct(CONSTRUCTOR_ARGUMENTS&&... arguments);

    void destroy();

    template <typename... CONSTRUCTOR_ARGUMENTS>
    void reconstruct(CONSTRUCTOR_ARGUMENTS&&... arguments);

    Value& value();

    // ACCESSORS
    lrkp::Boolean isNull() const;

    const Value& value() const;
};

// FREE OPERATORS
template <typename LHS_TYPE,
          typename RHS_TYPE>
lrkp::Boolean operator==(const NullableValue<LHS_TYPE>& lhs,
                         const NullableValue<RHS_TYPE>& rhs);

template <typename LHS_TYPE,
          typename RHS_TYPE>
lrkp::Boolean operator!=(const NullableValue<LHS_TYPE>& lhs,
                         const NullableValue<RHS_TYPE>& rhs);

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                       // -------------------------------
                       // class NULLABLEVALUEBUFFER<TYPE>
                       // -------------------------------

// CREATORS
template <typename    VALUE_TYPE>
template <typename... CONSTRUCTOR_ARGUMENTS>
inline
VALUE_TYPE& NullableValueBuffer<VALUE_TYPE>::construct(
                                          CONSTRUCTOR_ARGUMENTS&&... arguments)
{
    return *new (d_buffer) Value(arguments...);
}

// LOCAL FUNCTIONS
static inline
void destroyValueIfAny(NullableValue *value)
{
    if (!value->isNull()) {
        value->destroy();
    }
}

// CREATORS
template <typename VALUE_TYPE>
inline
NullableValue<VALUE_TYPE>::NullableValue()
    : d_value_p(nullptr)
{
}

template <typename VALUE_TYPE>
inline
NullableValue<VALUE_TYPE>::NullableValue(const NullableValue& original)
{
    if (original.isNull()) {
        d_value_p = nullptr;
    }
    else {
        construct(original.value());
    }
}

template <typename VALUE_TYPE>
inline
NullableValue<VALUE_TYPE>::NullableValue(NullableValue&& original)
{
    if (original.isNull()) {
        d_value_p = nullptr;
    }
    else {
        // TODO(nate): move
        construct(original.value());
    }
}

template <typename    VALUE_TYPE>
template <typename... CONSTRUCTOR_ARGUMENTS>
inline
NullableValue<VALUE_TYPE>::NullableValue(CONSTRUCTOR_ARGUMENTS&&... arguments)
{
    d_value_p = &d_buffer.construct(arguments...);
}

template <typename VALUE_TYPE>
inline
NullableValue<VALUE_TYPE>::~NullableValue()
{
    destroyValueIfAny(this);
}

template <typename    VALUE_TYPE>
template <typename... CONSTRUCTOR_ARGUMENTS>
inline
void NullableValue<VALUE_TYPE>::construct(CONSTRUCTOR_ARGUMENTS&&... arguments)
{
    destroyValueIfAny(this);
    d_value_p = &d_buffer.construct(arguments...);
}

template <typename VALUE_TYPE>
inline
void NullableValue<VALUE_TYPE>::destroy()
{
    d_value_p->~Value();
    d_value_p = nullptr;
}

// MANIPULATORS
template <typename VALUE_TYPE>
inline
NullableValue<VALUE_TYPE>& NullableValue<VALUE_TYPE>::operator=(
                                                 const NullableValue& original)
{
    destroyValueIfAny(this);
    if (!original.isNull()) {
        d_value_p = &d_buffer.construct(original.value());
    }
    return *this;
}

template <typename VALUE_TYPE>
inline
NullableValue<VALUE_TYPE>& NullableValue<VALUE_TYPE>::operator=(
                                                      NullableValue&& original)
{
    destroyValueIfAny(this);
    if (!original.isNull()) {
        // TODO(nate): move semantics
        d_value_p = &d_buffer.construct(original.value());
    }
    return *this;
}

template <typename VALUE_TYPE>
inline
VALUE_TYPE& NullableValue<VALUE_TYPE>::value()
{
    return *d_value_p;
}

// ACCESSORS
template <typename VALUE_TYPE>
inline
const VALUE_TYPE& NullableValue<VALUE_TYPE>::value() const
{
    return *d_value_p;
}

} // close package namespace
} // close product namespace

#endif // INCLUDED_LRKU_NULLABLEVALUEBUFFER

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
