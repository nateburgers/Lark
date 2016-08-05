// lrks_integerliteral.h                                              -*-C++-*-
#ifndef INCLUDED_LRKS_INTEGERLITERAL
#define INCLUDED_LRKS_INTEGERLITERAL

//@PURPOSE: Provide a representation of integer literal values.
//
//@CLASSES:
//  lrks::IntegerLiteral: Lark language source integer literal
//
//@DESCRIPTION: This component defines 'lrks::IntegerLiteral', a value-semantic
//  representation of integer literals in the syntax of the Lark programming
//  language.

#ifndef INCLUDED_BSL_IOSFWD
#include <bsl_iosfwd.h>
#endif

namespace BloombergLP {
namespace lrks {

                            // ====================
                            // class IntegerLiteral
                            // ====================

class IntegerLiteral {
    // This class implements a fully value-semantic representation of integer
    // literals in the source syntax of the Lark programming language.
    //
    // More generally, this class supports a complete set of *value* *semantic*
    // operations, including copy construction, assignment, equality
    // comparison, and 'ostream' printing.  A precise operational definition of
    // when two objects have the same value can be found in the description of
    // 'operator==' for the class.

    // DATA
    bsls::Types::Int64 d_value;
                         // The numeric value of the literal

  public:
    // CREATORS
    IntegerLiteral();
        // Create an 'IntegerLiteral' object having the 0 value.

    IntegerLiteral(bsls::Types:::Int64 value);
        // Create an 'IntegerLiteral' object having the specified 'value'.

    //! IntegerLiteral(const IntegerLiteral& original) = default;
        // Create a 'IntegerLiteral' object having the same value as the
        // specified 'original' object.

    //! ~IntegerLiteral() = default;
        // Destroy this object.

    // MANIPULATORS
    //! IntegerLiteral& operator=(const IntegerLiteral& rhs) = default;
        // Assign to this object the value of the specified 'rhs', and return a
        // reference to this modifiable object.

    void setValue(bsls::Types::Int64 value);
        // Assign the specified 'value' to the value of this object.

    // ACCESSORS
    bsls::Types::Int64 value() const;
        // Return the value of this object.

    bsl::ostream& print(bsl::ostream& stream,
                        int           level          = 0,
                        int           spacesPerLevel = 4) const;
        // Write the value of this object to the specified output 'stream' in
        // a human-readable format, and return a reference to 'stream'.
        // Optionally specify an initial indentation 'level', whose absolute
        // value is incremented recursively for nested objects.  If 'level' is
        // specified, optionally specify 'spacesPerLevel', whose absolute
        // value indicates the number of spaces per indentation level for this
        // and all of its nested objects.  If 'level' is negative, suppress
        // indentation of the first line.  If 'spacesPerLevel' is negative,
        // format the entire output on one line, suppressing all but the
        // initial indentation (as governed by 'level').  If 'stream' is not
        // valid on entry, this operation has no effect.  Note that this
        // human-readable format is not fully specified, and can change
        // without notice.
};

// FREE OPERATORS
bool operator==(const IntegerLiteral& lhs,
                const IntegerLiteral& rhs);
    // Return 'true' if the specified 'lhs' and 'rhs' objects have the same
    // value, and 'false' otherwise.  Two objects have the same value if TBD

bool operator!=(const IntegerLiteral& lhs,
                const IntegerLiteral& rhs);
    // Return 'true' if the specified 'lhs' and 'rhs' objects do not have the
    // same value, and 'false' otherwise.  Two objects do not have the same
    // value if TBD

bsl::ostream& operator<<(bsl::ostream&         stream,
                         const IntegerLiteral& object);
    // Write the value of the specified 'object' to the specified output
    // 'stream' in a single-line format, and return a reference to 'stream'.
    // If 'stream' is not valid on entry, this operation has no effect.  Note
    // that this human-readable format is not fully specified, can change
    // without notice, and is logically equivalent to:
    //..
    //  print(stream, 0, -1);
    //..

// ============================================================================
//                            INLINE DEFINITIONS
// ============================================================================

                            // --------------------
                            // class IntegerLiteral
                            // --------------------

// CREATORS
inline
IntegerLiteral::IntegerLiteral()
: d_value(0)
{
}

inline
IntegerLiteral::IntegerLiteral(bsls::Types::Int64 value)
: d_value(value)
{
}

// MANIPULATORS
inline
void IntegerLiteral::setValue(bsls::Types::Int64 value)
{
    d_value = value;
}

// ACCESSORS
inline
bsls::Types::Int64 IntegerLiteral::value() const
{
    return d_value;
}

} // close package namespace

// FREE OPERATORS
inline
bool lrks::operator==(const lrks::IntegerLiteral& lhs,
                      const lrks::IntegerLiteral& rhs)
{
    return lhs.value() == rhs.value();
}

inline
bool lrks::operator!=(const lrks::IntegerLiteral& lhs,
                      const lrks::IntegerLiteral& rhs)
{
    return lhs.value() != rhs.value();
}

inline
bsl::ostream& lrks::operator<<(bsl::ostream&               stream,
                               const lrks::IntegerLiteral& object)
{
    return object.print(stream, 0, -1);
}

} // close enterprise namespace

#endif

// ----------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2016
//      All rights reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ----------------------------------
