// lrkbt_testharness.h                                                -*-C++-*-
#ifndef INCLUDED_LRKBT_TESTHARNESS
#define INCLUDED_LRKBT_TESTHARNESS

//@PURPOSE: Provide a minimal, platform-independent test harness.
//
//@MACROS:
//  LRKBT_ASSERT: Set the test failure line number unless a condition is true
//
//@TYPES:
//  Test:     Platform-independent test harness object
//  TestOptions:
//  TestUtil: Platform-independent test harness utility
//
//@DESCRIPTION: This section provides 'TestHarnessUtil', a utility 'struct'
//  that does not depend on any library level code, such that it can be used
//  to test software at any level of the dependency hierarchy of a library.
//  In particular, this utility 'struct' can be used to test software before
//  the platform layer of a library is available.
//
///Thread Safety
///- - - - - - -
// Unless otherwise specified no operations on a 'lrkbt::TestHarness' object
// nor the 'lrkbt::TestHarnessUtil' are safe to call across threads.

#ifndef INCLUDED_IOSTREAM
#include <iostream>
#endif

#ifndef INCLUDED_CSTDLIB
#include <cstdlib>
#endif
 
// MACROS
#define LRKBT_ASSERT(CONDITION, ...) \
    LarkCompiler::lrkbt::TestUtil::assert(&std::cerr, \
                                          exit, \
                                          CONDITION, \
                                          __FILE__, \
                                          __LINE__, \
                                          #CONDITION, \
                                          __VA_ARGS__)

#define LRKBT_ASSERT1(CONDITION, A)                                           \
    LRKBT_ASSERT(CONDITION, #A##": ", A)

#define LRKBT_ASSERT2(CONDITION, A, B)                                        \
    LRKBT_ASSERT(CONDITION, #A ": ", A, #B ": ", B)

#define LRKBT_ASSERT3(CONDITOIN, A, B, C)                                     \
    LRKBT_ASSERT(CONDITION, #A ": ", A, #B ": ", B, #C ": ", C)

#define LRKBT_ASSERT4(CONDITION, A, B, C, D)                                  \
    LRKBT_ASSERT(CONDITION, #A ": ", A, #B ": ", B, #C ": ", C, #D ": ", D)

#define LRKBT_ASSERT_EQ(A, B) \
    LRKBT_ASSERT2(A == B, A, B)

#define LRKBT_ASSERT_NE(A, B) \
    LRKBT_ASSERT2(A != B, A, B)

#define LRKBT_ASSERT_LT(A, B) \
    LRKBT_ASSERT2(A  < B, A, B)

#define LRKBT_ASSERT_LE(A, B) \
    LRKBT_ASSERT2(A <= B, A, B)

#define LRKBT_ASSERT_GT(A, B) \
    LRKBT_ASSERT2(A  > B, A, B)

#define LRKBT_ASSERT_GE(A, B) \
    LRKBT_ASSERT2(A >= B, A, B)

// TYPES
namespace LarkCompiler {
namespace lrkbt {

class TestHarness;
using TestFunction = void (*)(TestHarness *harness);

                                 // ==========
                                 // class Test
                                 // ==========

template <unsigned TEST_CASE_INDEX>
class Test {

    // DATA
    TestFunction d_impl;

  public:
    // CREATORS
    Test() = delete;

    Test(const Test&  test) = delete;
    Test(      Test&& test) = default;

    template <typename TEST_FUNCTION_OBJECT>
    Test(TEST_FUNCTION_OBJECT&& implementation);

    ~Test() = default;

    // MANIPULATORS
    Test& operator=(const Test&  test) = delete;
    Test& operator=(      Test&& test) = default;
};

Test<1> BreathingTest = [] (TestHarness *h)
{
    //h->verbose() << "Breathing Test" << std::endl
    //             << "==============" << std::endl;
    static_cast<void>(h);
};

                               // ===============
                               // class TestIndex
                               // ===============

class TestIndex {
  public:
    // CONSTANTS 
    enum {
        k_MAX_TEST_CASES = 4096,
    };

  private:
    // CLASS DATA
    static TestFunction d_tests[k_MAX_TEST_CASES];
    static unsigned     d_lastTestCaseIndex;
    static bool         d_testsAreSequential;

  public:
    // CLASS MANIPULATORS
    static void setCase(int          testCaseIndex,
                        TestFunction implementation);

    static bool hasCase(int testCaseIndex);

    static TestFunction getCase(int testCaseIndex);  
    
    // CREATORS
    TestIndex() = delete;

    TestIndex(const TestIndex&  original) = delete;
    TestIndex(      TestIndex&& original) = delete;

    ~TestIndex() = delete;

    // MANIPULATORS
    TestIndex& operator=(const TestIndex&  original) = delete;
    TestIndex& operator=(      TestIndex&& original) = delete;
};

                              // =================
                              // class ExitHandler
                              // =================

class ExitHandler {
  public:
    // CREATORS
    virtual ~ExitHandler() = 0;
        // Destroy this object.

    // MANIPULATORS
    virtual void exit(int status) = 0;
        // Quit the program with the specified 'status'.
};

                            // ====================
                            // class CrtExitHandler
                            // ====================

class CrtExitHandler : public ExitHandler {
  public:
    // CREATORS
    CrtExitHandler() = default;

    CrtExitHandler(const CrtExitHandler&  original) = delete;
    CrtExitHandler(      CrtExitHandler&& original) = default;

    ~CrtExitHandler() override = default;

    // MANIPULATORS
    CrtExitHandler& operator=(const CrtExitHandler&  original) = delete;
    CrtExitHandler& operator=(      CrtExitHandler&& original) = default;

    void exit(int status) override;
};

                            // =====================
                            // class MockExitHandler
                            // =====================

class MockExitHandler : public ExitHandler {

    // DATA 
    int d_status;

  public:
    // CREATORS
    MockExitHandler() = default;

    MockExitHandler(const MockExitHandler&  original) = delete;
    MockExitHandler(      MockExitHandler&& original);

    ~MockExitHandler() override = default;

    // MANIPULATORS
    MockExitHandler& operator=(const MockExitHandler&  original) = delete;
    MockExitHandler& operator=(      MockExitHandler&& original);

    int& status();

    void exit(int status) override;

    // ACCESSORS
    int status() const;
};

                             // ==================
                             // class FilePosition
                             // ==================

#define LRKBT_FILE_POSITION \
    LarkCompiler::lrkbt::FilePosition(__FILE__, __LINE__)

class FilePosition {

    // DATA
    int         d_lineNumber;
    const char *d_fileName_p;

  public:
    // CREATORS
    FilePosition() = default;

    FilePosition(const char fileName[],
                 int        lineNumber);

    FilePosition(const FilePosition&  original) = default;
    FilePosition(      FilePosition&& original) = default;

    ~FilePosition() = default;

    // MANIPULATORS
    FilePosition& operator=(const FilePosition&  original) = default;
    FilePosition& operator=(      FilePosition&& original) = default;

    int& lineNumber();

    const char *&fileName();

    // ACCESSORS
    int lineNumber() const;

    const char *fileName() const;
};

                              // =================
                              // class TestHarness
                              // =================

class TestHarness {
    // This concrete mechanism class provides the capability 

  public:
    // CLASS DATA
    enum {
        k_MAX_ASSERTION_FAILURES = 100,
            // The maximum number of assertion failures to allow to occur
            // before quitting the program.  This number must be less than
            // the maximum return code of the platform.
    };

  private:
    // DATA
    int           d_exitStatus;
        // The status code to use when quitting the program.

    ExitHandler  *d_exitHandler_p;
        // The exit handler to use in order to quit the program when an 
        // assertion fails.

    std::ostream *d_ostream_p;
        // The stream to write assertion failure messages.

  public:
    // CREATORS
    TestHarness() = delete;

    TestHarness(ExitHandler *exitHandler);
        // Construct a 'TestHarness' object having the specified 'exitHandler'.

    TestHarness(ExitHandler  *exitHandler,
                std::ostream *errorStream);

    TestHarness(const TestHarness&  original) = delete;
    TestHarness(      TestHarness&& original) = default;

    ~TestHarness() = default;
        // Destroy this object.

    // MANIPULATORS
    TestHarness& operator=(const TestHarness&  original) = delete;
    TestHarness& operator=(      TestHarness&& original) = default;

    int& exitStatus();
        // Return a reference providing modifiable access to the "exit status"
        // attribute of this object.

    ExitHandler *&exitHandler();
        // Return a reference providing modifiable access to the address of 
        // the "exit handler" attribute of this object.

    template <typename... TRACE_PARAMETERS>
    void assert(const FilePosition&   filePosition,
                bool                  condition,
                TRACE_PARAMETERS&&... trace);
    
    // ACCESSORS
    int exitStatus() const;
        // Return the "exit status" attribute of this object.

    const ExitHandler *exitHandler() const;
        // Return a pointer providing non-modifiable access to the 
        // "exit handler" attribute of this object.
};

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                              // =================
                              // class Test<INDEX>
                              // =================

// CREATORS
template <unsigned TEST_CASE_INDEX>
template <typename TEST_FUNCTION_OBJECT>
Test<TEST_CASE_INDEX>::Test(TEST_FUNCTION_OBJECT&& implementation)
    : d_impl(implementation)
{
    TestIndex::setCase(TEST_CASE_INDEX, implementation);
}

                              // -----------------
                              // class ExitHandler
                              // -----------------

// CREATORS
ExitHandler::~ExitHandler()
{
}

                            // --------------------
                            // class CrtExitHandler
                            // --------------------

// MANIPULATORS
void CrtExitHandler::exit(int status)
{
    std::exit(status);
}

                            // ---------------------
                            // class MockExitHandler
                            // ---------------------

// CREATORS
MockExitHandler::MockExitHandler(MockExitHandler&& original)
    : d_status(original.d_status)
{
}

// MANIPULATORS
MockExitHandler& MockExitHandler::operator=(MockExitHandler&& original)
{
    d_status = original.d_status;
    return *this;
}

int& MockExitHandler::status()
{
    return d_status;
}

void MockExitHandler::exit(int status)
{
    d_status = status;
}

// ACCESSORS
int MockExitHandler::status() const
{
    return d_status;
}


namespace {

// LOCAL FUNCTIONS
template <typename OBJECT_TYPE>
inline
void trace(std::ostream& stream, OBJECT_TYPE&& object)
{
    stream << object;
}

template <typename    FIRST_OBJECT_TYPE,
          typename... REMAINING_OBJECT_TYPES>
inline 
void trace(std::ostream&               stream,
           FIRST_OBJECT_TYPE&&         firstObject,
           REMAINING_OBJECT_TYPES&&... remainingObjects)
{
    trace(stream, firstObject);
    trace(stream, remainingObjects...);
}

} // close unnamed namespace

                              // -----------------
                              // class TestHarness
                              // -----------------

// CREATORS
TestHarness::TestHarness(ExitHandler *exitHandler)
    : d_exitStatus(0)
    , d_exitHandler_p(exitHandler)
    , d_ostream_p(&std::cerr)
{
}

TestHarness::TestHarness(ExitHandler *exitHandler, std::ostream *errorStream)
    : d_exitStatus(0)
    , d_exitHandler_p(exitHandler)
    , d_ostream_p(errorStream)
{
}

// MANIPULATORS
ExitHandler *&TestHarness::exitHandler()
{
    return d_exitHandler_p;
}

template <typename... TRACE_PARAMETERS>
void TestHarness::assert(const FilePosition&   filePosition,
                         bool                  condition,
                         TRACE_PARAMETERS&&... parameters)
{
    if (!condition) {
        *d_ostream_p << "ASSERTION FAILED ["
                     << filePosition.fileName()
                     << " " 
                     << filePosition.lineNumber()
                     << "] ";
        trace(*d_ostream_p, parameters...);
        *d_ostream_p << '\n';

        ++d_exitStatus;
    }

    if (k_MAX_ASSERTION_FAILURES <= d_exitStatus) {
        d_exitHandler_p->exit(d_exitStatus);
    }
}

// ACCESSORS
const ExitHandler *TestHarness::exitHandler() const
{
    return d_exitHandler_p;
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
