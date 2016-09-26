// lrkp_union.h                                                       -*-C++-*-
#ifndef INCLUDED_LRKP_UNION
#define INCLUDED_LRKP_UNION

//@PURPOSE: Provide a value-semantic union representation for complex types.
//
//@CLASSES:
//    lrkp::Union: A value-semantic union representation for complex types.
//
//@DESCRIPTION:
//

#ifndef INCLUDED_TYPE_TRAITS
#include <type_traits>
#define INCLUDED_TYPE_TRAITS
#endif

#ifndef INCLUDED_UTILITY
#include <utility>
#define INCLUDED_UTILITY
#endif

namespace LarkCompiler {
namespace lrkp {

                        // =================
                        // class TaggedUnion
                        // =================

template <typename... TYPES>
class TaggedUnion final {

  public:
    // TYPES
    using Tag   = unsigned char;
    using Union = Union<TYPES...> Union;

    // CLASS ACCESSORS
    template <typename REQUESTED_TYPE>
    static constexpr Tag tag();

  private:
    // DATA
    Tag   d_tag;
    Union d_union;

  public:
    // CREATORS
    TaggedUnion() = delete;

    template <typename REQUESTED_TYPE>
    explicit TaggedUnion(const REQUESTED_TYPE& value);

    template <typename REQUESTED_TYPE>
    explicit TaggedUnion(REQUESTED_TYPE&& value);

    TaggedUnion(const TaggedUnion&  other);
    TaggedUnion(      TaggedUnion&& other);

   ~TaggedUnion();

    // MANIPULATORS
    TaggedUnion& operator=(const TaggedUnion&  other);
    TaggedUnion& operator=(      TaggedUnion&& other);

    template <typename REQUESTED_TYPE>
    REQUESTED_TYPE& as();

    // ACCESSORS
    template <typename REQUESTED_TYPE>
    const REQUESTED_TYPE& as() const;

    const Tag tag() const;
};

                        // ===========
                        // class Union
                        // ===========

template <typename... TYPES>
union Union final {
    // This 'union'

    // CREATORS
    Union() = delete;

    template <typename REQUESTED_TYPE>
    explicit Union(const REQUESTED_TYPE& value);

    template <typename REQUESTED_TYPE>
    explicit Union(REQUESTED_TYPE&& value);

    Union(const Union&  other) = delete;
    Union(      Union&& other) = delete;

   ~Union();

    template <typename REQUESTED_TYPE>
    void destroy();

    // MANIPULATORS
    Union& operator=(const Union&  other) = delete;
    Union& operator=(      Union&& other) = delete;

    template <typename REQUESTED_TYPE>
    REQUESTED_TYPE& as();

    // ACCESSORS
    template <typename REQUESTED_TYPE>
    const REQUESTED_TYPE& as() const;
};

// ============================================================================
//                             SPECIALIZATIONS
// ============================================================================

template <typename    FIRST_TYPE,
          typename... REMAINING_TYPES>
union Union<FIRST_TYPE, REMAINING_TYPES...> final {
    // This value-semantic class..

  private:
    // PRIVATE TYPES
    using HeadType = FIRST_TYPE;
    using TailType = Union<REMAINING_TYPES...>;

    // DATA
    HeadType                  d_head;
    Union<REMAINING_TYPES...> d_tail;

    // PRIVATE MANIPULATORS
    HeadType& head();

    template <typename REQUESTED_TYPE>
    REQUESTED_TYPE& tail();

    // PRIVATE ACCESSORS
    const HeadType& head() const;

    template <typename REQUESTED_TYPE>
    const REQUESTED_TYPE& tail() const;

  public:
    // CREATORS
    Union() = delete;

    template <typename REQUESTED_TYPE>
    explicit Union(const REQUESTED_TYPE& object);

    template <typename REQUESTED_TYPE>
    explicit Union(REQUESTED_TYPE&& object);

    Union(const Union&  other) = delete;
    Union(      Union&& other) = delete;

   ~Union();

    template<typename REQUESTED_TYPE>
    void destroy();

    // MANIPULATORS
    Union& operator=(const Union&  other) = delete;
    Union& operator=(      Union&& other) = delete;

    template <typename REQUESTED_TYPE>
    REQUESTED_TYPE& as();

    // ACCESSORS
    template <typename REQUESTED_TYPE>
    const REQUESTED_TYPE& as() const;
};

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
union Union<FIRST_TYPE, SECOND_TYPE> final {
    // This value-semantic class..

  public:
    // TYPES
    using FirstType  = FIRST_TYPE;
    using SecondType = SECOND_TYPE;

  private:
    // DATA
    FirstType  d_first;
    SecondType d_second;

  public:
    // CREATORS
    Union() = delete;
        // Disallow default construction of this union.

    explicit Union(const FirstType& first);

    explicit Union(FirstType&& first);

    explicit Union(const SecondType& second);

    explicit Union(SecondType&& second);

    Union(const Union&  other) = delete;
    Union(      Union&& other) = delete;
        // Disallow copy and move construction of this union.

   ~Union();
        // Destroy this union object without destroying the object occupying
        // this union.  Note that to destroy the object occupying this union,
        // one must call one of: 'destroy', 'destroyFirst', or 'destroySecond'
        // on this union.

    template <typename REQUESTED_TYPE>
    void destroy();
        // Call the destructor of the object occupying the slot for the
        // specified 'REQUESTED_TYPE' of this union.  The behavior is undefined
        // unless this union was constructed with an object of type
        // 'REQUESTED_TYPE'.  The function will fail to compile unless the
        // specified 'REQUESTED_TYPE' is equal to the specified 'FIRST_TYPE' or
        // the specified 'SECOND_TYPE'.

    void destroyFirst();
        // Call the destructor of the object occupying the slot for the
        // specified 'FIRST_TYPE' of this union.  The behavior is undefined
        // unless this union was constructed with an object of type
        // 'FIRST_TYPE'.

    void destroySecond();
        // Call the destructor of the object occupying the slot for the
        // specified 'SECOND_TYPE' of this union.  The behavior is undefined
        // unless this union was constructed with an object of type
        // 'SECOND_TYPE'.

    // MANIPULATORS
    Union& operator=(const Union&  other) = delete;
    Union& operator=(      Union&& other) = delete;
        // Disallow copy and move assignment of this union.

    template <typename REQUESTED_TYPE>
    REQUESTED_TYPE& as();

    FirstType& first();

    SecondType& second();

    // ACCESSORS
    template <typename REQUESTED_TYPE>
    const REQUESTED_TYPE& as() const;

    const FirstType& first() const;

    const SecondType& second() const;
};

// ============================================================================
//                            INLINE DEFINITIONS
// ============================================================================

namespace {
template <bool CONDITION,
          typename TRUE_TYPE,  TRUE_TYPE  TRUE_VALUE,
          typename FALSE_TYPE, FALSE_TYPE FALSE_VALUE>
struct ConditionalValueImp;

template <typename TRUE_TYPE,  TRUE_TYPE  TRUE_VALUE,
          typename FALSE_TYPE, FALSE_TYPE FALSE_VALUE>
struct ConditionalValueImp<true,
                           TRUE_TYPE,  TRUE_VALUE,
                           FALSE_TYPE, FALSE_VALUE> {
    static constexpr TRUE_TYPE value = TRUE_VALUE;
};

template <typename TRUE_TYPE,  TRUE_TYPE  TRUE_VALUE,
          typename FALSE_TYPE, FALSE_TYPE FALSE_VALUE>
struct ConditionalValueImp<false,
                           TRUE_TYPE,  TRUE_VALUE,
                           FALSE_TYPE, FALSE_VALUE> {
    static constexpr FALSE_TYPE value = FALSE_VALUE;
};

template <bool CONDITION,
          typename TRUE_TYPE,  TRUE_TYPE  TRUE_VALUE,
          typename FALSE_TYPE, FALSE_TYPE FALSE_VALUE>
constexpr auto ConditionalValue = ConditionalValueImp<CONDITION,
                                                      TRUE_TYPE,
                                                      TRUE_VALUE,
                                                      FALSE_TYPE,
                                                      FALSE_VALUE>::value;
}; // close anonymous namespace

                        // ----------------------
                        // class Union (Variadic)
                        // ----------------------

                        // -----------
                        // class Union
                        // -----------

// CREATORS
template <typename FIRST_TYPE,
          typename SECOND_TYPE>
Union<FIRST_TYPE, SECOND_TYPE>::Union(const FIRST_TYPE& first)
    : d_first(first)
{
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
Union<FIRST_TYPE, SECOND_TYPE>::Union(FIRST_TYPE&& first)
    : d_first(std::forward<FIRST_TYPE>(first))
{
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
Union<FIRST_TYPE, SECOND_TYPE>::Union(const SECOND_TYPE& second)
    : d_second(second)
{
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
Union<FIRST_TYPE, SECOND_TYPE>::Union(SECOND_TYPE&& second)
    : d_second(std::forward<SECOND_TYPE>(second))
{
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
Union<FIRST_TYPE, SECOND_TYPE>::~Union()
{
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
template <typename REQUESTED_TYPE>
void Union<FIRST_TYPE, SECOND_TYPE>::destroy()
{
    static_assert(std::is_same<REQUESTED_TYPE, FIRST_TYPE >::value ||
                  std::is_same<REQUESTED_TYPE, SECOND_TYPE>::value,
                  "The specified 'REQUESTED_TYPE' must be equal to the"
                  " specified 'FIRST_TYPE' or the specified 'SECOND_TYPE'");

    constexpr bool IsFirstType = std::is_same<REQUESTED_TYPE,
                                              FIRST_TYPE>::value;
    using Destructor = void (Union::*)();
    (this->*ConditionalValue<IsFirstType,
                             Destructor, &Union::destroyFirst,
                             Destructor, &Union::destroySecond>)();

}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
void Union<FIRST_TYPE, SECOND_TYPE>::destroyFirst()
{
    d_first.~FirstType();
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
void Union<FIRST_TYPE, SECOND_TYPE>::destroySecond()
{
    d_second.~SecondType();
}

// MANIPULATORS

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
template <typename REQUESTED_TYPE>
REQUESTED_TYPE& Union<FIRST_TYPE, SECOND_TYPE>::as()
{
    static_assert(std::is_same<REQUESTED_TYPE, FIRST_TYPE >::value ||
                  std::is_same<REQUESTED_TYPE, SECOND_TYPE>::value,
                  "The specified 'REQUESTED_TYPE' must be equal to the"
                  " specified 'FIRST_TYPE' or the specified 'SECOND_TYPE'");
    using FirstManipulator  = FirstType&  (Union::*)();
    using SecondManipulator = SecondType& (Union::*)();
    constexpr bool IsFirstType = std::is_same<REQUESTED_TYPE,
                                              FIRST_TYPE>::value;
    return (this->*ConditionalValue<IsFirstType,
                                    FirstManipulator,  &Union::first,
                                    SecondManipulator, &Union::second>)();
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
FIRST_TYPE& Union<FIRST_TYPE, SECOND_TYPE>::first()
{
    return d_first;
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
SECOND_TYPE& Union<FIRST_TYPE, SECOND_TYPE>::second()
{
    return d_second;
}

// ACCESSORS
template <typename FIRST_TYPE,
          typename SECOND_TYPE>
template <typename REQUESTED_TYPE>
const REQUESTED_TYPE& Union<FIRST_TYPE, SECOND_TYPE>::as() const
{
    static_assert(std::is_same<REQUESTED_TYPE, FIRST_TYPE >::value ||
                  std::is_same<REQUESTED_TYPE, SECOND_TYPE>::value,
                  "The specified 'REQUESTED_TYPE' must be equal to the"
                  " specified 'FIRST_TYPE' or the specified 'SECOND_TYPE'");

    using FirstAccessor  = const FirstType&  (Union::*)() const;
    using SecondAccessor = const SecondType& (Union::*)() const;
    constexpr bool IsFirstType = std::is_same<REQUESTED_TYPE,
                                              FIRST_TYPE>::value;
    return (this->*ConditionalValue<IsFirstType,
                                    FirstAccessor,  &Union::first,
                                    SecondAccessor, &Union::second>)();
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
const FIRST_TYPE& Union<FIRST_TYPE, SECOND_TYPE>::first() const
{
    return d_first;
}

template <typename FIRST_TYPE,
          typename SECOND_TYPE>
const SECOND_TYPE& Union<FIRST_TYPE, SECOND_TYPE>::second() const
{
    return d_second;
}

}; // close package namespace
}; // close product namespace

#endif // INCLUDED_LRKP_UNION
