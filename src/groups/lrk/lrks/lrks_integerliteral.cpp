// lrks_integerliteral.cpp                                            -*-C++-*-
#include <lrks_integerliteral.h>

namespace BloombergLP {
namespace lrks {

                            // --------------------
                            // class IntegerLiteral
                            // --------------------

// ACCESSORS
bsl::ostream& IntegerLiteral::print(bsl::ostream& stream,
                                    int           level,
                                    int           spacesPerLevel) const
{
    if (stream.good()) {
        stream << d_value;
    }
    return stream;
}

}  // close package namespace
}  // close enterprise namespace

// ----------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2015
//      All Rights Reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ----------------------------------
