// lrkbt_testharness.cpp                                              -*-C++-*-
#include <lrkbt_testharness.h>

namespace LarkCompiler {
namespace lrkbt {

                              // -----------------
                              // class TestHarness
                              // -----------------

// CREATORS
TestHarness::TestHarness()
    : d_firstFailureLineNumber(0)
{
}

// MANIPULATORS
void TestHarness::assert(const bool condition,
                         const int  lineNumber)
{
    if (0 != d_firstFailureLineNumber || true == condition) {
        return;                                                       // RETURN
    }
    d_firstFailureLineNumber = lineNumber;
}
 
void TestHarness::reset()
{
    d_firstFailureLineNumber = 0;
}

// ACCESSORS
int TestHarness::firstFailureLineNumber() const
{
    return d_firstFailureLineNumber;
}

                           // ----------------------
                           // struct TestHarnessUtil
                           // ----------------------

// CLASS DATA
extern TestHarness TestHarnessUtil::d_testHarness;

// PRIVATE CLASS METHODS
TestHarness& TestHarnessUtil::instance()
{
    return d_testHarness;
}

// CLASS METHODS
bool TestHarnessUtil::parseCase(int        *testCaseNumber,
                                const char  testCaseString[])
{
    if (0 == testCaseString[0]) {
        return false;                                                 // RETURN
    }

    int test = 0;
    for (const char *character  = &testCaseString[0];
                    *character != 0;
                   ++character) {
        if ('0' > *character || *character > '9') {
            return false;                                             // RETURN
        }
        int digit = *character - '0';
        test      = test * 10 + digit;
    }
    *testCaseNumber = test;
    return true;
}
 
void TestHarnessUtil::assert(const bool condition,
                             const int  lineNumber)
{
    instance().assert(condition, lineNumber);
}

void TestHarnessUtil::reset()
{
    instance().reset();
}

int TestHarnessUtil::firstFailureLineNumber()
{
    return instance().firstFailureLineNumber();
}

} // close namespace lrkbt
} // close namespace LarkCompiler

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
