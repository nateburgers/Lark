// lrkt_union.h                                                       -*-C++-*-
#ifndef INCLUDED_LRKT_UNION
#define INCLUDED_LRKT_UNION

//@PURPOSE:
//
//@CLASSES:
//
//@SEE_ALSO:
//
//@DESCRIPTION:
//

// ============================================================================
// Project Plan:
//
// TODO(nate):
//  o Implement variadic lrku::Union union
//  o Implement variadic lrkmf::TypeList struct
//  o Implement variadic lrku::Visitor protocol
//  o Implement variadic lrku::VisitorAdapter adapter
//  o Implement variadic lrku::TaggedUnion value
//    `- required for making algebraic data types
//  o Implement template lrku::IndirectValue value
//    |- required for making recursive, but value-semantic AST's
//    `- should be a 'fast-moving' data type, ie a pointer to implementation.
// ============================================================================

                                // placement new


                               // ===============
                               // class ALLOCATOR
                               // ===============

class Allocator {
    // This protocol class..

  public:
    // CREATORS
    virtual ~Allocator();

    // MANIPULATORS
    virtual void *allocate(int numBytes) = 0;

    virtual void deallocate(void *address) = 0;
};

namespace LarkCompiler {
namespace lrku {

                          // =========================
                          // class INDIRECTVALUE<TYPE>
                          // =========================

template <typename VALUE_TYPE>
class IndirectValue final {
    // This ..

  public:
    // TYPES
    using Value = VALUE_TYPE;

  private:
    // DATA
    Value *d_value_p;
    //! lrkma::Allocator *d_allocator_p;

  public:
    // CREATORS
    explicit IndirectValue();

    explicit IndirectValue(const IndirectValue&  original);
    explicit IndirectValue(      IndirectValue&& original);

    template <typename... VALUE_CONSTRUCTOR_ARGUMENTS>
    explicit IndirectValue(VALUE_CONSTRUCTOR_ARGUMENTS&&... arguments);

    ~IndirectValue();

    // MANIPULATORS
    IndirectValue& operator=(const IndirectValue&  original);
    IndirectValue& operator=(      IndirectValue&& original);

    Value& operator*();

    Value *operator->();

    Value& value();

    // ACCESSORS
    const Value& operator*() const;

    const Value *operator->() const;

    const Value& value() const;
};

// ============================================================================
//                              INLINE DEFINITIONS
// ============================================================================

                          // -------------------------
                          // class INDIRECTVALUE<TYPE>
                          // -------------------------

// CREATORS
template <typename VALUE_TYPE>
IndirectValue<VALUE_TYPE>::IndirectValue()
    : d_value_p(new VALUE_TYPE())
{
}

template <typename VALUE_TYPE>
IndirectValue<VALUE_TYPE>::IndirectValue(
                                     const IndirectValue<VALUE_TYPE>& original)
    : d_value_p(new VALUE_TYPE(*original.d_value_p))
{
}

template <typename VALUE_TYPE>
IndirectValue<VALUE_TYPE>::IndirectValue(IndirectValue<VALUE_TYPE>&& original)
    : d_value_p(original.d_value_p)
{
    original.d_value_p = nullptr;
}

template <typename    VALUE_TYPE>
template <typename... VALUE_CONSTRUCTOR_ARGUMENTS>
IndirectValue<VALUE_TYPE>::IndirectValue(
                                    VALUE_CONSTRUCTOR_ARGUMENTS&&... arguments)
    : d_value_p(new VALUE_TYPE(arguments...))
{
}

template <typename VALUE_TYPE>
IndirectValue<VALUE_TYPE>::~IndirectValue()
{
    delete d_value_p;
}

// MANIPULATORS
template <typename VALUE_TYPE>
IndirectValue<VALUE_TYPE>& IndirectValue<VALUE_TYPE>::operator=(
                                     const IndirectValue<VALUE_TYPE>& original)
{
    *d_value_p = *original.d_value_p;
}

template <typename VALUE_TYPE>
IndirectValue<VALUE_TYPE>& IndirectValue<VALUE_TYPE>::operator=(
                                          IndirectValue<VALUE_TYPE>&& original)
{
    d_value_p          = original.d_value_p;
    original.d_value_p = nullptr;
}

template <typename VALUE_TYPE>
VALUE_TYPE& IndirectValue<VALUE_TYPE>::operator*()
{
    return *d_value_p;
}

template <typename VALUE_TYPE>
VALUE_TYPE *IndirectValue<VALUE_TYPE>::operator->()
{
    return d_value_p;
}

template <typename VALUE_TYPE>
VALUE_TYPE& IndirectValue<VALUE_TYPE>::value()
{
    return *d_value_p;
}

// ACCESSORS
template <typename VALUE_TYPE>
const VALUE_TYPE& IndirectValue<VALUE_TYPE>::operator*() const
{
    return *d_value_p;
}

template <typename VALUE_TYPE>
const VALUE_TYPE *IndirectValue<VALUE_TYPE>::operator->() const
{
    return d_value_p;
}

template <typename VALUE_TYPE>
const VALUE_TYPE& IndirectValue<VALUE_TYPE>::value() const
{
    return *d_value_p;
}

} // close package namespace
} // close product namespace

                               // namespace lrkmf

                            // component lrkmf::False

namespace LarkCompiler {
namespace lrkmf {

struct False {
    // This 'struct'

    // CLASS DATA
    constexpr static lrkp::Boolean value = false;
};

} // close package namespace
} // close product namespace


                            // component lrkmf::True

namespace LarkCompiler {
namespace lrkmf {

struct True {
    // This 'struct'

    // CLASS DATA
    constexpr static lrkp::Boolean value = true;
};

} // close package namespace
} // close product namespace


                        // component lrkmf::TemplateUtil

namespace LarkCompiler {
namespace lrkmf {

template <lrkp::Boolean CONDITION,
          template <typename...> class TRUE_CHOICE,
          template <typename...> class FALSE_CHOICE>
struct TemplateUtil_SelectImpUtil;


template <template <typename...> class TRUE_CHOICE,
          template <typename...> class FALSE_CHOICE>
struct TemplateUtil_SelectImpUtil<true, TRUE_CHOICE, FALSE_CHOICE> {
    template <typename... TYPES>
    using Type = TRUE_CHOICE<TYPES...>;
};

template <template <typename...> class TRUE_CHOICE,
          template <typename...> class FALSE_CHOICE>
struct TemplateUtil_SelectImpUtil<false, TRUE_CHOICE, FALSE_CHOICE> {
    template <typename... TYPES>
    using Type = FALSE_CHOICE<TYPES...>;
};

struct TemplateUtil {
    template <lrkp::Boolean CONDITION,
              template <typename...> class TRUE_CHOICE,
              template <typename...> class FALSE_CHOICE>
    using Select = TemplateUtil_SelectImpUtil<CONDITION,
                                              TRUE_CHOICE,
                                              FALSE_CHOICE>;
};

} // close package namespace
} // close product namespace

                          // component lrkmf::TypeUtil

namespace LarkCompiler {
namespace lrkmf {

                             // ConditionalImpUtil

template <lrkp::Boolean CONDITION,
          typename      TRUE_TYPE,
          typename      FALSE_TYPE>
struct TypeUtil_ConditionalImpUtil;

template <typename TRUE_TYPE,
          typename FALSE_TYPE>
struct TypeUtil_ConditionalImpUtil<true, TRUE_TYPE, FALSE_TYPE> {
    // TYPES
    using Type = TRUE_TYPE;
};

template <typename TRUE_TYPE,
          typename FALSE_TYPE>
struct TypeUtil_ConditionalImpUtil<false, TRUE_TYPE, FALSE_TYPE> {
    // TYPES
    using Type = FALSE_TYPE;
};

                                // IsSameImpUtil

template <typename LHS_TYPE,
          typename RHS_TYPE>
struct TypeUtil_IsSameImpUtil : public lrkmf::False {
};

template <typename TYPE>
struct TypeUtil_IsSameImpUtil<TYPE, TYPE> : public lrkmf::True {
};

                               // IdentityImpUtil

template <typename TYPE>
struct TypeUtil_IdentityImpUtil {
    using Type = TYPE;
};

                           // RemoveReferenceImpUtil

template <typename TYPE>
struct TypeUtil_RemoveReferenceImpUtil {
    using Type = TYPE;
};

template <typename TYPE>
struct TypeUtil_RemoveReferenceImpUtil<TYPE&> {
    using Type = TYPE;
};

template <typename TYPE>
struct TypeUtil_RemoveReferenceImpUtil<TYPE&&> {
    using Type = TYPE;
};

                                  // TypeUtil

struct TypeUtil {
    // This 'struct'..

    // TYPES
    template <lrkp::Boolean CONDITION,
              typename      TRUE_TYPE,
              typename      FALSE_TYPE>
    using Conditional =
        typename TypeUtil_ConditionalImpUtil<CONDITION,
                                             TRUE_TYPE,
                                             FALSE_TYPE>::Type;

    template <typename TYPE>
    using Identity = typename TypeUtil_IdentityImpUtil<TYPE>::Type;

    template <typename TYPE>
    using RemoveReference =
                          typename TypeUtil_RemoveReferenceImpUtil<TYPE>::Type;

    // CLASS METAFUNCTIONS
    template <typename LHS_TYPE,
              typename RHS_TYPE>
    static constexpr lrkp::Boolean isSame =
                             TypeUtil_IsSameImpUtil<LHS_TYPE, RHS_TYPE>::value;
};

} // close package namespace
} // close product namespace

                          // component lrkmf::TypeList

namespace LarkCompiler {
namespace lrkmf {

                               // ==============
                               // class TYPELIST
                               // ==============

template <typename... TYPES>
struct TypeList;

template <>
struct TypeList<> {
    // CLASS DATA
    static constexpr lrkp::Integer size = 0;

    template <typename TYPE>
    static constexpr lrkp::Boolean has = false;
};

template <typename HEAD_TYPE, typename... TAIL_TYPES>
struct TypeList<HEAD_TYPE, TAIL_TYPES...> {
    // This utility 'struct'..

    // TYPES
    using Head = HEAD_TYPE;
    using Tail = TypeList<TAIL_TYPES...>;

    template <lrkp::Integer INDEX>
    using Element =
        TypeUtil::Conditional<0 == INDEX,
                              Head,
                              typename Tail::template index<INDEX - 1>>;

    // CLASS DATA
    static constexpr lrkp::Integer size = 1 + Tail::size;

    template <typename TYPE>
    static constexpr lrkp::Boolean has =
                                       lrkmf::TypeUtil::isSame<HEAD_TYPE, TYPE>
                                       ? true
                                       : Tail::template has<TYPE>;

    template <typename TYPE>
    static constexpr lrkp::Integer indexOf =
                                       lrkmf::TypeUtil::isSame<HEAD_TYPE, TYPE>
                                       ? 0
                                       : 1 + Tail::template indexOf<TYPE>;
};

} // close package namespace
} // close product namespace

                         // component lrkmf::Signature

namespace LarkCompiler {
namespace lrkmf {

template <typename TYPE>
constexpr TYPE declval;

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES>
struct Signature;

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES>
struct Signature<RETURN_TYPE(PARAMETER_TYPES...)> {
    // This utility...

    // TYPES
    using Return     = RETURN_TYPE;
    using Parameters = TypeList<PARAMETER_TYPES...>;

    using Function   = RETURN_TYPE (*)(PARAMETER_TYPES...);

    template <typename HOST_TYPE>
    using Method     = RETURN_TYPE (HOST_TYPE::*)(PARAMETER_TYPES...);

    // CLASS METHODS
    static constexpr Function overload(Function function)
    {
        return function;
    }

    template <typename HOST_TYPE>
    static constexpr Method<HOST_TYPE> overload(Method<HOST_TYPE> method)
    {
        return method;
    }

    static constexpr lrkp::Boolean test(void (*))
    {
        return false;
    }
};

template <typename TYPE>
struct SignatureOf;

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES>
struct SignatureOf<RETURN_TYPE(PARAMETER_TYPES...)> {
    // TYPES
    using Type = Signature<RETURN_TYPE(PARAMETER_TYPES...)>;
};

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES>
struct SignatureOf<RETURN_TYPE(*)(PARAMETER_TYPES...)> {
    // TYPES
    using Type = Signature<RETURN_TYPE(PARAMETER_TYPES...)>;
};

template <typename TYPE>
struct Instance {
    // CREATORS
    Instance(TYPE);

    template <typename OTHER_TYPE>
    Instance(OTHER_TYPE) = delete;
};

template <typename    RETURN_TYPE,
          typename... PARAMETER_TYPES>
struct Instance<RETURN_TYPE(PARAMETER_TYPES...)> {
    // CREATORS
    Instance(RETURN_TYPE(PARAMETER_TYPES...));

    template <typename HOST_TYPE>
    Instance(RETURN_TYPE(HOST_TYPE::*)(PARAMETER_TYPES...));
};


struct AllocatorAware {

    template <typename TYPE>
    using Requirements = decltype(
        Instance< lrku::Allocator *(void) >(&TYPE::allocator)
    );

};

struct ValueSemantic {

    template <typename TYPE>
    using Requirements = decltype(
        Instance< TYPE >(TYPE(declval<TYPE>)) // copy constructable
    );
};

template <typename... TYPES>
using Void = void;

template <typename CONCEPT, typename = void>
struct ModelsConceptImp : False {
};

template <typename CONCEPT, typename... TYPES>
struct ModelsConceptImp<
              CONCEPT(TYPES...),
              Void<typename CONCEPT::template Requirements<TYPES...>>> : True {
};

template <typename MODEL_TYPE>
constexpr lrkp::Boolean models = ModelsConceptImp<MODEL_TYPE>::value;

struct Foo {
    lrku::Allocator& allocator();
};

static_assert(models<AllocatorAware(Foo)>, "");

} // close package namespace
} // close product namespace

                               // namespace lrku

                          // component lrku::ValueUtil

namespace LarkCompiler {
namespace lrku {

struct ValueUtil {
    // This 'struct'..

    // CLASS METHDOS
    template <typename TYPE>
    static TYPE&& forward(lrkmf::TypeUtil::RemoveReference<TYPE>& object);

    template <typename TYPE>
    static TYPE&& forward(lrkmf::TypeUtil::RemoveReference<TYPE>&& object);

    template <typename TYPE>
    static typename lrkmf::TypeUtil::RemoveReference<TYPE>&& move(TYPE&& object);
};

template <typename TYPE>
TYPE&& ValueUtil::forward(lrkmf::TypeUtil::RemoveReference<TYPE>& object)
{
    return static_cast<TYPE&&>(object);
}

template <typename TYPE>
TYPE&& ValueUtil::forward(lrkmf::TypeUtil::RemoveReference<TYPE>&& object)
{
    return static_cast<TYPE&&>(object);
}

template <typename TYPE>
typename lrkmf::TypeUtil::RemoveReference<TYPE>&& ValueUtil::move(
                                                                 TYPE&& object)
{
    using RValueReference = typename lrkmf::TypeUtil::RemoveReference<TYPE>&&;
    return static_cast<RValueReference>(object);
}

} // close package namespace
} // close product namespace

                               // namespace lrkt

                        // component lrkt::Uninitialized

namespace LarkCompiler {
namespace lrkt {

    // TODO(nate): make this thing behave like nullablevalue,

                             // ===================
                             // class UNINITIALIZED
                             // ===================

template <typename ELEMENT_TYPE>
class Uninitialized {

    // TODO(nate): Give this thing pointer-like operators.

  public:
    using Element = ELEMENT_TYPE;

  private:
    union {
        // lrku::Unit d_unit;
        Element    d_element;
    };
};

} // close package namespace
} // close product namespace

                            // component lrkt::Union

namespace LarkCompiler {
namespace lrkt {

                                 // ===========
                                 // union UNION
                                 // ===========

template <typename... CHOICE_TYPES>
union Union;

template <typename CHOICE_TYPE>
union Union<CHOICE_TYPE> {
    // This 'union'..

  public:
    // TYPES
    using Choice = CHOICE_TYPE;

  private:
    // DATA
    Choice d_choice;

  public:
    // CREATORS
    explicit Union();

    explicit Union(const Union&  original);
    explicit Union(      Union&& original);

    explicit Union(const Choice&  choice);
    explicit Union(      Choice&& choice);

    template <typename OTHER_TYPE>
    explicit Union(OTHER_TYPE&&) = delete;

    ~Union();

    // MANIPULATORS
    Union& operator=(const Union&  original);
    Union& operator=(      Union&& original);

    Union& operator=(const Choice&  choice);
    Union& operator=(      Choice&& choice);

    template <typename OTHER_TYPE>
    Union& operator=(OTHER_TYPE&&) = delete;

    template <typename OTHER_TYPE>
    void destroy();

    template <typename    OTHER_TYPE,
              typename... OTHER_TYPE_CONSTRUCTOR_ARGUMENTS>
    void createInPlace(OTHER_TYPE_CONSTRUCTOR_ARGUMENTS&&... arguments);

    template <typename OTHER_TYPE>
    OTHER_TYPE& as();

    // ACCESSORS
    template <typename OTHER_TYPE>
    const OTHER_TYPE& as() const;

    // OPERATORS
    lrkp::Boolean operator==(const Union& rhs) const;
    lrkp::Boolean operator!=(const Union& rhs) const;
};

template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
union Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...> {
    // This 'union'..

  public:
    // TYPES
    using Choices      = lrkmf::TypeList<FIRST_CHOICE_TYPE,
                                         OTHER_CHOICE_TYPES...>;
    using FirstChoice  = FIRST_CHOICE_TYPE;
    using OtherChoices = lrkmf::TypeList<OTHER_CHOICE_TYPES...>;

  private:
    // FRIENDS
    template <typename CHOICE_TYPE>
    friend struct Union_FirstChoiceImpUtil;

    template <typename CHOICE_TYPE>
    friend struct Union_OtherChoiceImpUtil;

    // DATA
    FirstChoice                  d_firstChoice;
    Union<OTHER_CHOICE_TYPES...> d_otherChoices;

  public:
    // CREATORS
    explicit Union() = delete;

    explicit Union(const Union&  original) = delete;
    explicit Union(      Union&& original) = delete;

    explicit Union(const FirstChoice&  original);
    explicit Union(      FirstChoice&& original);

    template <typename CHOICE_TYPE>
    explicit Union(CHOICE_TYPE&& original);

    ~Union();

    template <typename CHOICE_TYPE>
    void destroy();

    // MANIPULATORS
    Union& operator=(const Union&  original) = delete;
    Union& operator=(      Union&& original) = delete;

    template <typename    CHOICE_TYPE,
              typename    NEW_CHOICE_TYPE,
              typename... NEW_CHOICE_TYPE_CONSTRUCTOR_ARGUMENTS>
    void replace(NEW_CHOICE_TYPE_CONSTRUCTOR_ARGUMENTS&&... arguments);

    template <typename CHOICE_TYPE>
    CHOICE_TYPE& as();

    // ACCCESSORS
    template <typename CHOICE_TYPE>
    const CHOICE_TYPE& as() const;
};

                       // ==============================
                       // class UNION_FIRSTCHOICEIMPUTIL
                       // ==============================

template <typename CHOICE_TYPE>
struct Union_FirstChoiceImpUtil {
    // This 'struct'...

    // CLASS METHODS
    template <typename... CHOICE_TYPES>
    static CHOICE_TYPE& as(Union<CHOICE_TYPES...> *self);

    template <typename... CHOICE_TYPES>
    static const CHOICE_TYPE& as(const Union<CHOICE_TYPES...>& self);
};

                       // ==============================
                       // class UNION_OTHERCHOICEIMPUTIL
                       // ==============================

template <typename CHOICE_TYPE>
struct Union_OtherChoiceImpUtil {
    // This 'struct'...

    // CLASS METHODS
    template <typename... CHOICE_TYPES>
    static CHOICE_TYPE& as(Union<CHOICE_TYPES...> *self);

    template <typename... CHOICE_TYPES>
    static const CHOICE_TYPE& as(const Union<CHOICE_TYPES...>& self);
};


// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                                 // -----------
                                 // union UNION
                                 // -----------

// CREATORS
template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>::Union()
    : d_choice()
{
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>::Union(const Union<CHOICE_TYPE>& original)
    : d_choice(original.d_choice)
{
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>::Union(Union<CHOICE_TYPE>&& original)
    : d_choice(lrku::ValueUtil::forward<CHOICE_TYPE>(original.d_choice))
{
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>::Union(const CHOICE_TYPE& choice)
    : d_choice(choice)
{
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>::Union(CHOICE_TYPE&& choice)
    : d_choice(lrku::ValueUtil::forward<CHOICE_TYPE>(choice))
{
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>::~Union()
{
}

// MANIPULATORS
template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>& Union<CHOICE_TYPE>::operator=(
                                            const Union<CHOICE_TYPE>& original)
{
    d_choice = original.d_choice;
    return *this;
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>& Union<CHOICE_TYPE>::operator=(
                                                 Union<CHOICE_TYPE>&& original)
{
    d_choice = lrku::ValueUtil::move(original.d_choice);
    return *this;
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>& Union<CHOICE_TYPE>::operator=(const CHOICE_TYPE& choice)
{
    d_choice = choice;
    return *this;
}

template <typename CHOICE_TYPE>
Union<CHOICE_TYPE>& Union<CHOICE_TYPE>::operator=(CHOICE_TYPE&& choice)
{
    d_choice = lrku::ValueUtil::move(choice);
    return *this;
}

template <typename CHOICE_TYPE>
template <typename OTHER_TYPE>
void Union<CHOICE_TYPE>::destroy()
{
    static_assert(lrkmf::TypeUtil::isSame<CHOICE_TYPE, OTHER_TYPE>,
                  "The specified 'OTHER_TYPE' must be the same type as the"
                  " specified 'CHOICE_TYPE'");

    d_choice.~CHOICE_TYPE();
}

template <typename CHOICE_TYPE>
template <typename    OTHER_TYPE,
          typename... OTHER_TYPE_CONSTRUCTOR_ARGUMENTS>
void Union<CHOICE_TYPE>::createInPlace(
                               OTHER_TYPE_CONSTRUCTOR_ARGUMENTS&&... arguments)
{
    static_assert(lrkmf::TypeUtil::isSame<CHOICE_TYPE, OTHER_TYPE>,
                  "The specified 'OTHER_TYPE' must be the same type as the"
                  " specified 'CHOICE_TYPE'");

    this->destroy<CHOICE_TYPE>();

    new (&d_choice) CHOICE_TYPE(
     lrku::ValueUtil::forward<OTHER_TYPE_CONSTRUCTOR_ARGUMENTS>(arguments)...);
}

template <typename CHOICE_TYPE>
template <typename OTHER_TYPE>
OTHER_TYPE& Union<CHOICE_TYPE>::as()
{
    static_assert(lrkmf::TypeUtil::isSame<CHOICE_TYPE, OTHER_TYPE>,
                  "The specified 'OTHER_TYPE' must be the same type as the"
                  " specified 'CHOICE_TYPE'");

    return d_choice;
}

// ACCESSORS
template <typename CHOICE_TYPE>
template <typename OTHER_TYPE>
const OTHER_TYPE& Union<CHOICE_TYPE>::as() const
{
    static_assert(lrkmf::TypeUtil::isSame<CHOICE_TYPE, OTHER_TYPE>,
                  "The specified 'OTHER_TYPE' must be the same type as the"
                  " specified 'CHOICE_TYPE'");

    return d_choice;
}

                                 // -----------
                                 // union UNION
                                 // -----------

// CREATORS
template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...>::Union(
                                             const FIRST_CHOICE_TYPE& original)
    : d_firstChoice(original)
{
}

template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...>::Union(
                                                  FIRST_CHOICE_TYPE&& original)
    : d_firstChoice(lrku::ValueUtil::move(original))
{
}

template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
template <typename    CHOICE_TYPE>
Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...>::Union(CHOICE_TYPE&& original)
    : d_otherChoices(lrku::ValueUtil::forward<CHOICE_TYPE>(original))
{
}

template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
template <typename    CHOICE_TYPE>
void Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...>::destroy()
{
    as<CHOICE_TYPE>().~CHOICE_TYPE();
}

// MANIPULATORS
template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
template <typename    CHOICE_TYPE>
CHOICE_TYPE& Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...>::as()
{
    using ChoiceList = lrkmf::TypeList<FIRST_CHOICE_TYPE,
                                       OTHER_CHOICE_TYPES...>;
    static_assert(ChoiceList::template has<CHOICE_TYPE>,
                  "you don't have it!");

    using ImpUtil = typename lrkmf::TemplateUtil::Select<
                       lrkmf::TypeUtil::isSame<FIRST_CHOICE_TYPE, CHOICE_TYPE>,
                       Union_FirstChoiceImpUtil,
                       Union_OtherChoiceImpUtil>::template Type<CHOICE_TYPE>;
    return ImpUtil::as(this);
}

template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
template <typename    CHOICE_TYPE,
          typename    NEW_CHOICE_TYPE,
          typename... NEW_CHOICE_TYPE_CONSTRUCTOR_ARGUMENTS>
void Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...>::replace(
                          NEW_CHOICE_TYPE_CONSTRUCTOR_ARGUMENTS&&... arguments)
{
    destroy<CHOICE_TYPE>();
    new (&as<NEW_CHOICE_TYPE>()) NEW_CHOICE_TYPE(
               lrku::ValueUtil::forward<NEW_CHOICE_TYPE_CONSTRUCTOR_ARGUMENTS>(
                                                                arguments)...);
}

// ACCESSORS
template <typename    FIRST_CHOICE_TYPE,
          typename... OTHER_CHOICE_TYPES>
template <typename    CHOICE_TYPE>
const CHOICE_TYPE& Union<FIRST_CHOICE_TYPE, OTHER_CHOICE_TYPES...>::as() const
{
    using ImpUtil = typename lrkmf::TemplateUtil::Select<
                       lrkmf::TypeUtil::isSame<FIRST_CHOICE_TYPE, CHOICE_TYPE>,
                       Union_FirstChoiceImpUtil,
                       Union_OtherChoiceImpUtil>::template Type<CHOICE_TYPE>;
    return ImpUtil::as(*this);
}


                       // ------------------------------
                       // class UNION_FIRSTCHOICEIMPUTIL
                       // ------------------------------

// CLASS METHODS
template <typename    CHOICE_TYPE>
template <typename... ALL_CHOICE_TYPES>
CHOICE_TYPE& Union_FirstChoiceImpUtil<CHOICE_TYPE>::as(
                                              Union<ALL_CHOICE_TYPES...> *self)
{
    using Union       = Union<ALL_CHOICE_TYPES...>;
    using FirstChoice = typename Union::FirstChoice;
    static_assert(lrkmf::TypeUtil::isSame<CHOICE_TYPE, FirstChoice>,
                  "The specified 'CHOICE_TYPE' must be the same as"
                  " 'Union<ALL_CHOICE_TYPES...>::FirstChoice'.");

    return self->d_firstChoice;
}

template <typename    CHOICE_TYPE>
template <typename... ALL_CHOICE_TYPES>
const CHOICE_TYPE& Union_FirstChoiceImpUtil<CHOICE_TYPE>::as(
                                        const Union<ALL_CHOICE_TYPES...>& self)
{
    using Union       = Union<ALL_CHOICE_TYPES...>;
    using FirstChoice = typename Union::FirstChoice;
    static_assert(lrkmf::TypeUtil::isSame<CHOICE_TYPE, FirstChoice>,
                  "The specified 'CHOICE_TYPE' must be the same as the first"
                  " choice type of the specified 'self' Union.");

    return self.d_firstChoice;
}

                       // ------------------------------
                       // class UNION_OTHERCHOICEIMPUTIL
                       // ------------------------------

// CLASS METHODS
template <typename    CHOICE_TYPE>
template <typename... ALL_CHOICE_TYPES>
CHOICE_TYPE& Union_OtherChoiceImpUtil<CHOICE_TYPE>::as(
                                              Union<ALL_CHOICE_TYPES...> *self)
{
    return self->d_otherChoices.template as<CHOICE_TYPE>();
}

template <typename    CHOICE_TYPE>
template <typename... ALL_CHOICE_TYPES>
const CHOICE_TYPE& Union_OtherChoiceImpUtil<CHOICE_TYPE>::as(
                                        const Union<ALL_CHOICE_TYPES...>& self)
{
    return self.d_otherChoices.template as<CHOICE_TYPE>();
}

} // close package namespace
} // close product namespace

#endif // INCLUDED_LRKT_UNION
