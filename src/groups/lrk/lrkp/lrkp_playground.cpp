// lrkp_playground.cpp
#include <lrkp_playground.h>

namespace BloombergLP {
namespace lrkp {

                        // ----------------
                        // class Identifier
                        // ----------------

// CREATORS
Identifier::Identifier(uint64_t value)
    : d_value(value)
{
}

// FREE OPERATORS
bool operator==(const Identifier& lhs,
                const Identifier& rhs)
{
    return lhs.d_value == rhs.d_value;
}

bool operator!=(const Identifier& lhs,
                const Identifier& rhs)
{
    return lhs.d_value != rhs.d_value;
}

bool operator<(const Identifier& lhs,
               const Identifier& rhs)
{
    return lhs.d_value < rhs.d_value;
}

bool operator<=(const Identifier& lhs,
                const Identifier& rhs)
{
    return lhs.d_value <= rhs.d_value;
}

bool operator>(const Identifier& lhs,
               const Identifier& rhs)
{
    return lhs.d_value > rhs.d_value;
}

bool operator>=(const Identifier& lhs,
                const Identifier& rhs)
{
    return lhs.d_value >= rhs.d_value;
}

                        // ----------------------------
                        // class MonomorphicTypeVariant
                        // ----------------------------

// CLASS METHODS
MonomorphicTypeVariant MonomorphicTypeVariant::function()
{
    return e_FUNCTION;
}

MonomorphicTypeVariant MonomorphicTypeVariant::integer()
{
    return e_INTEGER;
}

MonomorphicTypeVariant MonomorphicTypeVariant::variable()
{
    return e_VARIABLE;
}

std::size_t MonomorphicTypeVariant::numberOfVariants()
{
    return e_NUMBER_OF_VARIANTS;
}

// CREATORS
MonomorphicTypeVariant::MonomorphicTypeVariant(
                                           MonomorphicTypeVariant::Value value)
    : d_value(value)
{
}

// FREE OPERATORS
bool operator==(const MonomorphicTypeVariant& lhs,
                const MonomorphicTypeVariant& rhs)
{
    return lhs.d_value == rhs.d_value;
}

bool operator!=(const MonomorphicTypeVariant& lhs,
                const MonomorphicTypeVariant& rhs)
{
    return lhs.d_value != rhs.d_value;
}

                        // ---------------------
                        // class MonomorphicType
                        // ---------------------

// CREATORS
MonomorphicType::MonomorphicType(MonomorphicType::Variant variant)
    : d_variant(variant)
{
}

MonomorphicType::~MonomorphicType()
{
}

// ACCESSORS
MonomorphicType::Variant MonomorphicType::variant() const
{
    return d_variant;
}

                        // ------------------
                        // class FunctionType
                        // ------------------

// CREATORS
FunctionType::FunctionType(const MonomorphicType& domain,
                           const MonomorphicType& codomain)
    : MonomorphicType(MonomorphicType::Variant::function())
    , d_domain(UniquePtrUtil::copy(domain))
    , d_codomain(UniquePtrUtil::copy(codomain))
{
}

FunctionType::FunctionType(MonomorphicType&& domain,
                           MonomorphicType&& codomain)
    : MonomorphicType(MonomorphicType::Variant::function())
    , d_domain(UniquePtrUtil::move(std::forward<MonomorphicType>(domain)))
    , d_codomain(UniquePtrUtil::move(std::forward<MonomorphicType>(codomain)))
{
}

FunctionType::FunctionType(const FunctionType& source)
    : MonomorphicType(MonomorphicType::Variant::function())
    , d_domain(UniquePtrUtil::copy(source.d_domain))
    , d_codomain(UniquePtrUtil::copy(source.d_codomain))
{
}

// MANIPULATORS
FunctionType& FunctionType::operator=(const FunctionType& source)
{
    d_domain   = UniquePtrUtil::copy(source.d_domain);
    d_codomain = UniquePtrUtil::copy(source.d_codomain);
    return *this;
}

void FunctionType::setDomain(const Monomorphictype& domain)
{
    d_domain = UniquePtrUtil::copy(domain);
}

void FunctionType::setDomain(MonomorphicType&& domain)
{
    d_domain = UniquePtrUtil::move(std::forward<MonomorphicType>(domain));
}

void FunctionType::setCodomain(const MonomorphicType& codomain)
{
    d_codomain = UniquePtrUtil::copy(codomain);
}

void FunctionType::setCodomain(MonomorphicType&& codomain)
{
    d_codomain = UniquePtrUtil::move(std::forward<MonomorphicType>(codomain));
}

// ACCESSORS
const MonomorphicType& FunctionType::domain() const
{
    return *d_domain;
}

const Monomorphictype& FunctionType::codomain() const
{
    return *d_codomain;
}


} // close package namespace
} // close enterprise namespace
