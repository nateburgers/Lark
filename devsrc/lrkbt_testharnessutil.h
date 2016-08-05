// lrkbt_testharness.h                                                -*-C++-*-
#ifndef INCLUDED_LRKBT_TESTHARNESS
#define INCLUDED_LRKBT_TESTHARNESS

// ----------------------------------------------------------------------------
// @PURPOSE: This section provides a platform-independent test harness.
// 
// @MACROS:
//   LRKBT_ASSERT: Set the test failure line number unless a condition is true
//
// @TYPES:
//   TestHarness:     Platform-independent test harness object
//   TestHarnessUtil: Platform-independent test harness utility
//
// @DESCRIPTION: This section provides 'TestHarnessUtil', a utility 'struct'
//   that does not depend on any library level code, such that it can be used
//   to test software at any level of the dependency hierarchy of a library.
//   In particular, this utility 'struct' can be used to test software before
//   the platform layer of a library is available.
//-----------------------------------------------------------------------------

#ifndef __LINE__
# error The test harness requires the compiler provide a '__LINE__' macro.
#endif

#define LRKBT_ASSERT(CONDITION) \
            LarkCompiler::lrkbt::TestHarnessUtil::assert((CONDITION), __LINE__)
    // This macro asserts that the specified 'CONDITION' is 'true' using 
    // the 'TestHarnessUtil', providing the line number at the point of 
    // macro expansion.

namespace LarkCompiler {
namespace lrkbt {

                              // =================
                              // class TestHarness
                              // =================

class TestHarness
{
    // DATA
    int d_firstFailureLineNumber;
        // The specified 'lineNumber' of the first call to 'assert' where the
        // specified 'condition' is 'false', or '0' otherwise.  
       
  public:
    // CREATORS
    explicit TestHarness ();

    explicit TestHarness (const TestHarness&  original) = delete;
    explicit TestHarness (      TestHarness&& original) = delete;

    ~TestHarness ();

    // MANIPULATORS
    TestHarness& operator= (const TestHarness&  original) = delete;
    TestHarness& operator= (      TestHarness&& original) = delete;
    
    void assert(bool condition,
                int  lineNumber);
        // Load into the specified 'testStatus' the value of the specified
        // 'lineNumber' unless the specified 'condition' is 'true', otherwise
        // do nothing.

    void reset();
        // Reset the state of this object such that calling 
        // 'firstFailureLineNumber', immediately after calling this method,
        // returns '0'.
    
    // ACCESSORS
    int firstFailureLineNumber() const;
        // Return the specified 'lineNumber' of the first call to 'assert'
        // where the specified 'condition' is 'false', or '0' otherwise. 
};

                           // ======================
                           // struct TestHarnessUtil
                           // ======================

struct TestHarnessUtil
{
  private:
    // CLASS DATA
    static TestHarness d_testHarness;
        // The global 'TestHarness' object.

  public:
    // CLASS METHODS
    static bool parseCase (int        *testCaseNumber,
                           const char  testCaseString[]);

    static TestHarness& instance();
        // Return a reference providing modifiable access to the global
        // 'TestHarness' object.
};

                           // ----------------------
                           // struct TestHarnessUtil
                           // ----------------------

// CLASS MANIPULATORS
void TestHarnessUtil::assert(const bool condition,
                             const int  lineNumber)
{
    static bool firstAssertion = true;
    if (firstAssertion) {
        d_firstFailureLineNumber = 0;
        firstAssertion = false;
    }

    if (0 != d_firstFailureLineNumber || true == condition) {
        return;                                                       // RETURN
    }
    d_firstFailureLineNumber = lineNumber;
}

bool TestHarnessUtil::parseCase(int        *testCaseNumber,
                                const char  testCaseString[])
{
    int test = 0;
    for (const char *character  = &testCaseString[0];
                    *character != 0;
                   ++character) {
        if ('0' < *character || *character > '9') {
            return false;                                             // RETURN
        }
        int digit = *character - '0';
        test      = test * 10 + digit;
    }
    *testCaseNumber = test;
    return true;
}

// CLASS ACCESSORS
int TestHarnessUtil::firstFailureLineNumber()
{
    return d_firstFailureLineNumber;
}
 

} // close namespace lrkbt
} // close namespace LarkCompiler
 
#endif // INCLUDED_LRKBT_TESTHARNESS

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
