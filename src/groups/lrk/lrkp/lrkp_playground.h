// lrkp_playground.h                                           -*-JavaScript-*-

//@PURPOSE: Provide a scratchpad for experimenting with compiler design
//
//@CLASSES:
//
// ---------
// UTILITIES
// ---------
// UniquePtrUtil:
//
// -----------
// IDENTIFIERS
// -----------
// Identifier:
//
// -----
// TYPES
// -----
// MonomorphicTypeVariant:
// MonomorphicType:
// FunctionType:
// IntegerType:
// VariableType:
// MonomorphicTypeConstVisitor:
//
// ------------
// TYPE SCHEMES
// ------------
// TypeSchemeVariant:
// TypeScheme:
// MonomorphicTypeScheme:
// PolymorphicTypeScheme:
// TypeSchemeConstVisitor:
// TypeSchemeFreeVariableVisitor:
// TypeSchemeUtil:
//
// ----------
// PRIMITIVES
// ----------
// Primitive:
//
// -----------
// EXPRESSIONS
// -----------
// ExpressionVariant:
// Expression:
// ApplicationExpression:
// FunctionExpression:
// IdentifierExpression:
// IntegerExpression:
// LetExpression:
// PrimitiveExpression:
// ExpressionVisitor:
// ExpressionConstVisitor:
// ExpressionConstFunctorVisitor:
// ExpressionUtil:

#ifndef INCLUDED_CSTDDEF
#include <stddef.h>
#define INCLUDED_CSTDDEF
#endif

#ifndef INCLUDED_MEMORY
#include <memory> // for std::unique_ptr
#define INCLUDED_MEMORY
#endif

#ifndef INCLUDED_UTILITY
#include <utility> // for std::forward
#define INCLUDED_UTILITY
#endif

namespace BloombergLP {
namespace lrkp {

class UniquePtrUtil final {
    // This utility class..

    template <typenane    RESULT,
              typename    ALLOCATOR,
              typename... CONSTRUCTOR_ARGUMENTS>
    static std::unique_ptr<RESULT> allocate(
                              const ALLOCATOR&           allocator,
                              CONSTRUCTOR_ARGUMENTS&&... constructorArguments);
        // ...

    template <typename RESULT>
    static std::unique_ptr<RESULT> copy(const RESULT& source);
        // ...

    template <typename RESULT>
    static std::unique_ptr<RESULT> copy(const std::unique_ptr<RESULT>& source);
        // ...

    template <typename RESULT,
              typename ALLOCATOR>
    static std::unique_ptr<RESULT> copy(const RESULT&    source,
                                        const ALLOCATOR& allocator);
        // ...

    template <typename RESULT,
              typename ALLOCATOR>
    static std::unique_ptr<RESULT> copy(
                                     const std::unique_ptr<RESULT>& source,
                                     const ALLOCATOR&               allocator);
        // ...

    template <typename RESULT,
              typename... CONSTRUCTOR_ARGUMENTS>
    static std::unique_ptr<RESULT> make(
                              CONSTRUCTOR_ARGUMENTS&&... constructorArguments);
        // ...

    template <typename RESULT>
    static std::unique_ptr<RESULT> move(RESULT&& source);
        // ...
};

class Identifier final {
  public:
    // TYPES
    typedef Identifier Type;

  private:
    // DATA
    uint64_t d_value;

    // FRIENDS
    friend bool operator==(const Type& lhs,
                           const Type& rhs);

    friend bool operator!=(const Type& lhs,
                           const Type& rhs);

    friend bool operator<(const Type& lhs,
                          const Type& rhs);

    friend bool operator<=(const Type& lhs,
                           const Type& rhs);

    friend bool operator>(const Type& lhs,
                          const Type& rhs);

    friend bool operator>=(const Type& lhs,
                           const Type& rhs);

  public:
    // CREATORS
    Identifier() = default;

    inline explicit
    Identifier(uint64_t value);

    Identifier(const Type&  source) = default;
    Identifier(      Type&& source) = default;

   ~Identifier() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;
};

class MonomorphicTypeVariant final {
  public:
    // TYPES
    typedef TypeVariant Type;

    // CLASS METHODS
    static constexpr Type        function();

    static constexpr Type        integer();

    static constexpr Type        variable();

    static constexpr std::size_t numberOfVariants();

  private:
    // PRIVATE TYPES
    enum Value {
        e_FUNCTION,
        e_INTEGER,
        e_VARIABLE,

        e_NUMBER_OF_VARIANTS,
    };

    // DATA
    Value d_value;

    // FRIENDS
    friend constexpr
    bool operator==(const Type& lhs,
                    const Type& rhs);

    friend constexpr
    bool operator!=(const Type& lhs,
                    const Type& rhs);

    // PRIVATE CREATORS
    constexpr MonomorphicTypeVariant(Value value);
};

class MonomorphicType {
  public:
    // TYPES
    typedef MonomorphicType        Type;
    typedef MonomorphicTypeVariant Variant;

  private:
    // DATA
    MonomorphicTypeVariant d_variant;

  public:
    // CREATORS
    MonomorphicTypeVariant() = delete;

    inline explicit
    MonomorphicTypeVariant(Variant variant);

    MonomorphicTypeVariant(const Type&  source) = default;
    MonomorphicTypeVariant(      Type&& source) = default;

    virtual
   ~MonomorphicTypeVariant() = 0;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    // ACCESSORS
    Variant variant() const;
};

class FunctionType final : public MonomorphicType {
  public:
    // TYPES
    typedef FunctionType Type;

  private:
    // DATA
    std::unique_ptr<MonomorphicType> d_domain;
    std::unique_ptr<MonomorphicType> d_codomain;

  public:
    // CREATORS
    FunctionType() = delete;

    FunctionType(const MonomorphicType& domain,
                 const MonomorphicType& codomain);

    FunctionType(MonomorphicType&& domain,
                 MonomorphicType&& codomain);

    FunctionType(const Type&  source);
    FunctionType(      Type&& source) = default;

    virtual override
   ~FunctionType() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source);
    Type& operator=(      Type&& source) = default;

    void setDomain(const MonomorphicType&  domain);
    void setDomain(      MonomorphicType&& domain);

    void setCodomain(const Monomorphictype&  codomain);
    void setCodomain(      MonomorphicType&& codomain);

    // ACCESSORS
    const MonomorphicType& domain() const;

    const MonomorphicType& codomain() const;
};

class IntegerType final : public MonomorphicType {
  public:
    // TYPES
    typedef IntegerType Type;

  public:
    // CREATORS
    IntegerType() = default;

    IntegerType(const IntegerType&  source) = default;
    IntegerType(      IntegerType&& source) = default;

    virtual override
   ~IntegerType();

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;
};

class VariableType final : public MonomorphicType {
  public:
    // TYPES
    typedef VariableType Type;

  private:
    // DATA
    Identifier d_identifier;

  public:
    // CREATORS
    VariableType() = delete;

    explicit
    VariableType(const Identifier& identifier);

    VariableType(const Type&  source) = default;
    VariableType(      Type&& source) = default;

    virtual override
   ~VariableType() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    void setIdentifier(const Identifier&  identifier);
    void setIdentifier(      Identifier&& identifier);

    // ACCESSORS
    const Identifier& identifier() const;
};

template <typename RESULT_TYPE>
class MonomorphicTypeConstVisitor {
  public:
    // TYPES
    typedef MonomorphicTypeVisitor Type;

    // CREATORS
    MonomorphicTypeVisitor() = default;

    MonomorphicTypeVisitor(const Type&  source) = default;
    MonomorphicTypeVisitor(      Type&& source) = default;

    virtual
   ~MonomorphicTypeVisitor() = 0;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    // ACCESSORS
    void operator()(RESULT_TYPE            *result,
                    const MonomorphicType&  type);

    virtual
    void operator()(RESULT_TYPE         *result,
                    const FunctionType&  type) = 0;

    virtual
    void operator()(RESULT_TYPE        *result,
                    const IntegerType&  type) = 0;

    virtual
    void operator()(RESULT_TYPE         *result,
                    const VariableType&  type) = 0;
};

class TypeSchemeVariant final {
  public:
    // TYPES
    typedef TypeSchemeVariant Type;

    // CLASS METHODS
    static constexpr Type        monomorphic();

    static constexpr Type        polymorphic();

    static constexpr std::size_t numberOfVariants();

  private:
    // PRIVATE TYPES
    enum Value {
        e_MONOMORPHIC,
        e_POLYMORPHIC,

        e_NUMBER_OF_VARIANTS,
    };

    // FRIENDS
    friend constexpr
    bool operator==(const Type& lhs,
                    const Type& rhs);

    friend constexpr
    bool operator!=(const Type& lhs,
                    const Type& rhs);

    // DATA
    Value d_value;

    // PRIVATE CREATORS
    constexpr TypeSchemeVariant(Value value);
};

class TypeScheme {
  public:
    // TYPES
    typedef TypeScheme        Type;
    typedef TypeSchemeVariant Variant;

  private:
    // DATA
    Variant d_variant;

  public:
    // CREATORS
    TypeScheme() = delete;

    TypeScheme(Variant variant);

    TypeScheme(const Type&  source) = default;
    TypeScheme(      Type&& source) = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    // ACCESSORS
    const Variant& variant() const;
};

class MonomorphicTypeScheme final : public TypeScheme {
  public:
    // TYPES
    typedef MonomorphicTypeScheme Type;

  private:
    // DATA
    MonomorphicType d_type;

  public:
    // CREATORS
    MonomorphicTypeScheme() = delete;

    MonomorphicTypeScheme(const MonomorphicType&  type);
    MonomorphicTypeScheme(      MonomorphicType&& type);

    MonomorphicTypeScheme(const Type&  source) = default;
    MonomorphicTypeScheme(      Type&& source) = default;

    virtual override
   ~MonomorphicTypeScheme() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    void setType(const MonomorphicType&  type);
    void setType(      MonomorphicType&& type);

    // ACCESSORS
    const MonormophicType& type() const;
};

class PolymorphicTypeScheme final : public TypeScheme {
  public:
    // TYPES
    typedef PolymorphicTypeScheme Type;

  private:
    // DATA
    Identifier                  d_qualifiedVariable;
    std::unique_ptr<TypeScheme> d_qualifiedBody;

  public:
    // CREATORS
    PolymorphicTypeScheme() = delete;

    PolymorphicTypeScheme(const Identifier& qualifiedVariable,
                          const TypeScheme& qualifiedBody);

    PolymorphicTypeScheme(Identifier&& qualifiedVariable,
                          Identifier&& qualifiedBody);

    PolymorphicTypeScheme(const Type&  source);
    PolymorphicTypeScheme(      Type&& source) = default;

    // MANIPULATORS
    Type& operator=(const Type&  source);
    Type& operator=(      Type&& source) = default;

    void setQualifiedVariable(const Identifier&  qualifiedVariable);
    void setQualifiedVariable(      Identifier&& qualifiedVariable);

    void setQualifiedBody(const TypeScheme&  qualifiedBody);
    void setQualifiedBody(      TypeScheme&& qualifiedBody);

    // ACCESSORS
    const Identifier& qualifiedVariable() const;

    const TypeScheme& qualifiedBody() const;
};

template <typename RESULT_TYPE>
class TypeSchemeConstVisitor {
  public:
    // TYPES
    typedef TypeSchemeConstVisitor Type;

    // CREATORS
    TypeSchemeConstVisitor() = default;

    TypeSchemeConstVisitor(const Type&  source) = default;
    TypeSchemeConstVisitor(      Type&& source) = default;

    virtual
   ~TypeSchemeConstVisitor() = 0;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(const Type&& source) = default;

    // ACCESSORS
    void operator()(RESULT_TYPE       *result,
                    const TypeScheme&  typeScheme) const;

    virtual
    void operator()(RESULT_TYPE                  *result,
                    const MonomorphicTypeScheme&  typeScheme) const = 0;

    virtual
    void operator()(RESULT_TYPE                  *result,
                    const PolymorphicTypeScheme&  typeScheme) const = 0;
};

class TypeSchemeFreeVariableVisitor
: public TypeSchemeConstVisitor<std::set<Identifier>> {
        // This value-semantic visitor class..

  public:
    // TYPES
    typedef TypeSchemeFreeVariableVisitor Type;
    typedef std::set<Identifier>          IdentifierSet;

  private:
    IdentifierSet d_boundVariables;

  public:
    // CREATORS
    TypeSchemeFreeVariableVisitor() = default;

    TypeSchemeFreeVariableVisitor(const IdentifierSet&  boundVariables);
    TypeSchemeFreeVariableVisitor(      IdentifierSet&& boundVariables);

    TypeSchemeFreeVariableVisitor(const Type&  source) = default;
    TypeSchemeFreeVariableVisitor(      Type&& source) = default;

    virtual override
   ~TypeSchemeFreeVariableVisitor() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    // ACCESSORS
    virtual override
    void operator()(TypeSchemeContext            *context,
                    const MonomorphicTypeScheme&  typeScheme) const;

    virtual override
    void operator()(TypeSchemeContext            *context,
                    const PolymorphicTypeScheme&  typeScheme) const;
}

struct TypeSchemeUtil {
    // This utility-semantic class..

    // TYPES
    typedef std::set<Identifier>             IdentifierSet;
    typedef std::map<Identifier, TypeScheme> TypeSchemeContext;

    // CLASS METHODS
    static void freeVariables(IdentifierSet     *freeVariables,
                              const TypeScheme&  typeScheme);
};

class Primitive final {
  public:
    // CLASS METHODS
    static constexpr Primitive   integerAddition();
        // ...

    static constexpr Primitive   integerSubtraction();
        // ...

    static constexpr Primitive   integerMultiplication();
        // ...

    static constexpr Primitive   integerDivision();
        // ...

    static constexpr std::size_t numberOfPrimitives();
        // ...

  private:
    // PRIVATE TYPES
    enum Value {
        e_INTEGER_ADDITION,
        e_INTEGER_SUBTRACTION,
        e_INTEGER_MULTIPLICATION,
        e_INTEGER_DIVISION,

        e_NUMBER_OF_VARIANTS,
    };

    // DATA
    Value d_value;

    // FRIENDS
    friend constexpr
    bool operator==(const Primitive& lhs,
                    const Primitive& rhs);

    friend constexpr
    bool operator!=(const Primitive& lhs,
                    const Primitive& rhs);

    // PRIVATE CREATORS
    constexpr Primitive(Value value);
};


class ExpressionVariant final {
  public:
    // CLASS METHODS
    static constexpr ExpressionVariant application();
        // Return the expression variant value that denotes the application
        // of a function to an argument.

    static constexpr ExpressionVariant function();
        // ...

    static constexpr ExpressionVariant identifier();
        // ...

    static constexpr ExpressionVariant integer();
        // ...

    static constexpr ExpressionVariant let();
        // ...

    static constexpr ExpressionVariant primitive();
        // ...

    static constexpr std::size_t       numberOfVariants();
        // ...

  private:
    // PRIVATE TYPES
    enum Value {
        e_APPLICATION,
        e_FUNCTION,
        e_IDENTIFIER,
        e_INTEGER,
        e_LET,
        e_PRIMITIVE,

        e_NUMBER_OF_VARIANTS,
    };

    // DATA
    Value d_value;

    // FRIENDS
    friend constexpr
    bool operator==(const ExpressionVariant& lhs,
                    const ExpressionVariant& rhs);

    friend constexpr
    bool operator!=(const ExpressionVariant& lhs,
                    const ExpressionVariant& rhs);

    // PRIVATE CREATORS
    constexpr ExpressionVariant(Value value);
};

class Expression {
    // This value-semantic class..

  public:
    // TYPES
    typedef Expression        Type;
    typedef ExpressionVariant Variant;

  private:
    // DATA
    Variant d_variant;

  public:
    // CREATORS
    Expression() = delete;

    inline explicit
    Expression(Variant variant);
        // ...

    Expression(const Type&  source) = default;
    Expression(      Type&& source) = default;
        // ...

    virtual
   ~Expression() = 0;
        // ...

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    // ACCESSORS
    Variant variant() const;
        // ...
};

class ApplicationExpression final : public Expression {
    // This value-semantic class..

  public:
    // TYPES
    typedef ApplicationExpression Type;

  private:
    // DATA
    std::unique_ptr<Expression> d_function;
    std::unique_ptr<Expression> d_argument;

  public:
    // CREATORS
    ApplicationExpression() = delete;

    inline
    ApplicationExpression(const Expression& function,
                          const Expression& argument);

    inline
    ApplicationExpression(Expression&& function,
                          Expression&& argument);

    ApplicationExpression(const Type& source);

    ApplicationExpression(Type&& source) = default;

    virtual override
   ~ApplicationExpression();

    // MANIPULATORS
    Type& operator=(const Type&  source);
    Type& operator=(      Type&& source) = default;

    void setFunction(const Expression&  function);
    void setFunction(      Expression&& function);

    void setArgument(const Expression&  argument);
    void setArgument(      Expression&& argument);

    // ACCESSORS
    const Expression& function() const;

    const Expression& argument() const;
};

class FunctionExpression final : public Expression {
    // This value-semantic class..

  public:
    // TYPES
    typedef FunctionExpression Type;

  private:
    // DATA
    Identifier                  d_parameter;
    std::unique_ptr<Expression> d_body;

  public:
    // CREATORS
    FunctionExpression() = delete;

    inline
    FunctionExpression(const Identifier& parameter,
                       const Expression& body);

    inline
    FunctionExpression(Identifier&& parameter,
                       Expression&& body);

    FunctionExpression(const Type&  source);
    FunctionExpression(      Type&& source) = default;

    virtual override
   ~FunctionExpression() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source);
    Type& operator=(      Type&& source) = default;

    void setParameter(const Identifier&  parameter);
    void setParameter(      Identifier&& parameter);

    void setBody(const Expression&  body);
    void setBody(      Expression&& body);

    // ACCESSORS
    const Identifier& parameter() const;

    const Expression& body() const;
};

class IdentifierExpression final : public Expression {
    // This value-semantic class..
  public:
    typedef IdentifierExpression Type;

  private:
    // DATA
    Identifier d_identifier;

  public:
    // CREATORS
    IdentifierExpression() = delete;

    IdentifierExpression(const Identifier&  identifier);
    IdentifierExpression(      Identifier&& identifier);

    IdentifierExpression(const Type&  source) = default;
    IdentifierExpressoin(      Type&& source) = default;

    virtual override
   ~IdentifierExpression() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    void setIdentifier(const Identifier&  identifier);
    void setIdentifier(      Identifier&& identifier);

    // ACCESSORS
    const Identifier& identifier() const;
};

class IntegerExpression final : public Expression {
    // This value-semantic class..

  public:
    // TYPES
    typedef IntegerExpression Type;

  private:
    // DATA
    int64_t d_value;

  public:
    // CREATORS
    IntegerExpression() = delete;

    IntegerExpression(int64_t value);

    IntegerExpression(const Type&  source) = default;
    IntegerExpression(      Type&& source) = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    void setValue(int64_t value);

    // ACCESSORS
    int64_t value() const;
};

class LetExpression final : public Expression {
    // this value-semantic class..

  public:
    // TYPES
    typedef LetExpression Type;

  private:
    // DATA
    Identifier                  d_identifier;
    std::unique_ptr<Expression> d_value;
    std::unique_ptr<Expression> d_continuation;

  public:
    // CREATORS
    LetExpression() = default;

    LetExpression(const Identifier& identifier,
                  const Expression& value,
                  const Expression& continuation);

    LetExpression(Identifier&& identifier,
                  Expression&& value,
                  Expression&& continuation);

    LetExpression(const Type&  source);
    LetExpression(      Type&  source) = default;

    virtual override
   ~LetExpression() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source);
    Type& operator=(      Type&& source) = default;

    void setIdentifier(const Identifier&  identifier);
    void setIdentifier(      Identifier&& identifier);

    void setValue(const Expression&  value);
    void setValue(      Expression&& value);

    void setContinuation(const Expression&  continuation);
    void setContinuation(      Expression&& continuation);

    // ACCESSORS
    const Identifier& identifier() const;

    const Expression& value() const;

    const Expression& continuation() const;
};

class PrimitiveExpression final : public Expression {
    // This value-semantic type..

  public:
    // TYPES
    typedef PrimitiveExpression Type;

  private:
    // DATA
    Primitive d_primitive;

  public:
    // CREATORS
    PrimitiveExpression() = delete;

    PrimitiveExpression(const Primitive&  primitive);
    PrimitiveExpression(      Primitive&& primitive);

    PrimitiveExpression(const Type&  source) = default;
    PrimitiveExpression(      Type&& source) = default;

    virtual override
   ~PrimitiveExpression() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    void setPrimitive(const Primitive&  primitive);
    void setPrimitive(      Primitive&& primitive);

    // ACCESSORS
    const Primitive& primitive() const;
};


template <typename RESULT_TYPE>
class ExpressionVisitor {
    // This protocol class..

  public:
    // TYPES
    typedef RESULT_TYPE Result;

  public:
    // CREATORS
    virtual ~ExpressionVisitor() = 0;

    // ACCESSORS
    void operator()(Result      *result,
                    Expression&  expression) const;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result                 *result,
                    ApplicationExpression&  expression) const = 0;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result              *result,
                    FunctionExpression&  expression) const = 0;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result             *result,
                    IntegerExpression&  expression) const = 0;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result         *result,
                    LetExpression  *expression) const = 0;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result              *result,
                    PrimitiveExpression *expression) const = 0;
        // Visit the specified 'expression'..
};

template <typename RESULT_TYPE>
class ExpressionConstVisitor: public ExpressionVisitor<RESULT_TYPE> {
    // This protocol class..

  public:
    // TYPES
    typedef ExpressionConstVisitor Type;
    typedef RESULT_TYPE            Result;

  public:
    // CREATORS
    ExpressionConstVisitor() = delete;

    ExpressionConstVisitor(const Type&  source) = default;
    ExpressionConstvisitor(      Type&& source) = default;

    virtual override
   ~ExpressionConstVisitor() = default;

    // MANIPULATORS
    Type& operator=(const Type&  source) = default;
    Type& operator=(      Type&& source) = default;

    // ACCESSORS
    virtual override
    void operator()(Result                *result,
                    ApplicationExpression *expression) const;
        // Visit the specified 'expression'..

    virtual override
    void operator()(Result             *result,
                    FunctionExpression *expression) const;
        // Visit the specified 'expression'..

    virtual override
    void operator()(Result            *result
                    IntegerExpression *expression) const;
        // Visit the specified 'expression'..

    virtual override
    void operator()(Result        *result
                    LetExpression *expression) const;
        // Visit the specified 'expression'..

    virtual override
    void operator()(Result              *result,
                    PrimitiveExpression *expression) const;
        // Visit the specified 'expression'..

    void operator()(Result            *result,
                    const Expression&  expression) const;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result                       *result,
                    const ApplicationExpression&  expression) const = 0;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result                    *result
                    const FunctionExpression&  expression) const = 0;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result                   *result,
                    const IntegerExpression&  expression) const = 0;
        // Visit the specified 'expression'..

    virtual
    void operator()(Result               *result,
                    const LetExpression&  expression) const = 0;
        // Visit the specified 'expression'..
};

template <typename APPLICATION_EXPRESSION_VISITOR_TYPE,
          typename FUNCTION_EXPRESSION_VISITOR_TYPE,
          typename INTEGER_EXPRESSION_VISITOR_TYPE,
          typename LET_EXPRESSION_VISITOR_TYPE,
          typename RESULT_TYPE>
class ExpressionConstFunctorVisitor final :
                                   public ExpressionConstVisitor<RESULT_TYPE> {
    // This adapter class..

  public:
    // TYPES
    typedef ExpressionConstFunctorVisitor       Type;
    typedef APPLICATION_EXPRESSION_VISITOR_TYPE ApplicationVisitor;
    typedef FUNCTION_EXPRESSION_VISITOR_TYPE    FunctionVisitor;
    typedef INTEGER_EXPRESSION_VISITOR_TYPE     IntegerVisitor;
    typedef LET_EXPRESSION_VISITOR_TYPE         LetVisitor;

  private:
    // DATA
    ApplicationVisitor d_applicationVisitor;
    FunctionVisitor    d_functionVisitor;
    IntegerVisitor     d_integerVisitor;
    LetVisitor         d_letVisitor;

  public:
    // CREATORS
    ExpressionConstFunctorVisitor() = delete;

    ExpressionConstFunctorVisitor(const ApplicationVisitor& applicationVisitor,
                                  const FunctionVisitor&    functionVisitor,
                                  const IntegerVisitor&     integerVisitor,
                                  const LetVisitor&         letVisitor);

    ExpressionConstFunctorVisitor(ApplicationVisitor&& applicationVisitor,
                                  FunctionVisitor&&    functionVisitor,
                                  IntegerVisitor&&     integerVisitor,
                                  LetVisitor&&         letVisitor);

    ExpressionConstFunctorVisitor(const Type&  source) = default;
    ExpressionConstFunctorVisitor(      Type&& source) = default;

    virtual override
   ~ExpressionConstFunctorVisitor() = default;

    // MANIPULATORS
    Type& operator=(const Type& source) = default;

    Type& operator=(Type&& source) = default;

    // ACCESSORS
    virtual override
    void operator()(Result                       *result,
                    const ApplicationExpression&  expression) const;

    virtual override
    void operator()(Result                    *result,
                    const FunctionExpression&  expression) const;

    virtual override
    void operator()(Result                   *result,
                    const IntegerExpression&  expression) const;

    virtual override
    void operator()(Result               *result,
                    const LetExpression&  expression) const;
};


} // close package namespace
} // close enterprise namespace

// ============================================================================
//                            INLINE DEFINITIONS
// ============================================================================

                        // -------------------
                        // class UniquePtrUtil
                        // -------------------

// CLASS METHODS
template <typename    RESULT,
          typename    ALLOCATOR,
          typename... CONSTRUCTOR_ARGUMENTS>
std::unique_ptr<RESULT> UniquePtrUtil::allocate(
                               const ALLOCATOR&           allocator,
                               CONSTRUCTOR_ARGUMENTS&&... constructorArguments)
{
    typedef RESULT Result;
    Result *const result_p = new (allocator) Result(
                 std::forward<CONSTRUCTOR_ARGUMENTS>(constructorArguments)...);
    return std::unique_ptr<Result>(result_p);
}

template <typename RESULT>
std::unique_ptr<RESULT> UniquePtrUtil::copy(const RESULT& source)
{
    return make<RESULT>(source);
}

template <typename RESULT>
std::unique_ptr<RESULT> UniquePtrUtil::copy(
                                         const std::unique_ptr<RESULT>& source)
{
    return make<RESULT>(*source);
}

template <typename    RESULT,
          typename... CONSTRUCTOR_ARGUMENTS>
std::unique_ptr<RESULT> UniquePtrUtil::make(
                               CONSTRUCTOR_ARGUMENTS&&... constructorArguments)
{
    typedef RESULT Result;
    Result *const result_p = new Result(
                 std::forward<CONSTRUCTOR_ARGUMENTS>(constructorArguments)...);
    return std::unique_ptr<Result>(result_p);
}

template <typename RESULT>
std::unique_ptr<RESULT> UniquePtrUtil::move(RESULT&& source)
{
    return UniquePtrUtil::make<RESULT>(std::forward<RESULT>(source));
}

                        // -----------------------
                        // class ExpressionVariant
                        // -----------------------

// CLASS METHODS
ExpressionVariant ExpressionVariant::application()
{
    return ExpressionVariant::e_APPLICATION;
}

ExpressionVariant ExpressionVariant::function()
{
    return ExpressionVariant::e_FUNCTION;
}

ExpressionVariant ExpressionVariant::integer()
{
    return ExpressionVariant::e_INTEGER;
}

ExpressionVariant ExpressionVariant::let()
{
    return ExpressionVariant::e_LET;
}

std::size_t ExpressionVariant::numberOfVariants()
{
    return ExpressionVariant::e_NUMBER_OF_VARIANTS;
}

// CREATORS
ExpressionVariant::ExpressionVariant(ExpressionVariant::Value)
    : d_value(value)
{
}

// FREE OPERATORS
bool operator==(const ExpressionVariant& lhs,
                const ExpressionVariant& rhs)
{
    return lhs.d_value == rhs.d_value;
}

bool operator!=(const ExpressionVariant& lhs,
                const ExpressionVariant& rhs)
{
    return lhs.d_value != rhs.d_value;
}

                        // --------------------------------
                        // class ExpressionConstVisitorUtil
                        // --------------------------------
// CLASS METHODS
template <typename RESULT_TYPE>
static void ExpressionConstVisitorUtil::visit(
                                          RESULT_TYPE              *result,
                                          const Expression&         expression,
                                          const ExpressionVisitor&  visitor)
{
    switch (expression.variant()) {
        case ExpressionVariant::application(): {
            visitor(result,
                    static_cast<const ApplicationExpression&>(expression));
        } break;
        case ExpressionVariant::function(): {
            visitor(result,
                    static_cast<const FunctionExpression&>(expression));
        } break;
        case ExpressionVariant::integer(): {
            visitor(result,
                    static_cast<const IntegerExpression&>(expression));
        } break;
        case ExpressionVariant::let(): {
            visitor(result,
                    static_cast<const LetExpression&>(expression));
        } break;
    }
}


#endif // INCLUDED_LRKP_PLAYGROUND
