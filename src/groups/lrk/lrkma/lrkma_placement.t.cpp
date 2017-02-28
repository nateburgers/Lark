// lrkma_placement.t.cpp                                              -*-C++-*-
#include <lrkma_placement.h>

using namespace LarkCompiler;
using namespace lrkma;

//=============================================================================
//                                 TEST PLAN
//-----------------------------------------------------------------------------
//                                  Overview
//                                  --------
// 'lrkma::Placement' provides ...
// This test driver tests ...
//-----------------------------------------------------------------------------
// CREATORS
// [  ] Placement()
// MANIPULATORS
// ACCESSORS


#ifndef __LINE__
# error The test harness requires the compiler provide a '__LINE__' macro.
#endif

#define ASSERT(CONDITION) TestHarnessUtil::assert((CONDITION), __LINE__)
    // This macro asserts that the specified 'CONDITION' is 'true' using
    // the 'TestHarnessUtil', providing the line number at the point of
    // macro expansion.


//=============================================================================
//                       STANDARD ASSERT TEST FUNCTION
//-----------------------------------------------------------------------------

namespace {

int testStatus = 0;

void aSsErT(bool condition, const char *message, int line)

} // close unnamed namespace

//=============================================================================
//                   GLOBAL TYPES AND CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------

//=============================================================================
//                                MAIN PROGRAM
//-----------------------------------------------------------------------------

int main (int argc, char *argv[])
{
    int test = 0;
    ASSERT(1 < argc);
    ASSERT(TestHarnessUtil::parseTestCase(&test, argv[1]));

    switch (test) {
        case 0: {
            return __LINE__;                                          // RETURN
        } break;
        case 1: {
            // ----------------------------------------------------------------
            // BREATHING TEST
            //   This case exercises (but does not fully test) basic
            //   functionality.
            //
            // Concerns:
            //: 1 The class is sufficiently functional to enable comprehensive
            //    testing in subsequent test cases.
            //
            // Plan:
            //: 1 Developer test sandbox.
            //
            // Testing:
            //   BREATHING TEST
            // ----------------------------------------------------------------

            ASSERT(true);

            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        } break;
    }
    return TestHarnessUtil::firstFailureLineNumber();
}

#undef ASSERT

// ----------------------------------------------------------------------------
// Copyright (c) 2017 
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
