// lrkbt_testharness.h                                                -*-C++-*-
#ifndef INCLUDED_LRKBT_TESTHARNESS
#define INCLUDED_LRKBT_TESTHARNESS

//=============================================================================
// @PURPOSE: Provide a minimal, platform-independent test harness.
// 
// @MACROS:
//   LRKBT_ASSERT: Set the test failure line number unless a condition is true
//
// @TYPES:
//   Test:     Platform-independent test harness object
//   TestUtil: Platform-independent test harness utility
//
// @DESCRIPTION: This section provides 'TestHarnessUtil', a utility 'struct'
//   that does not depend on any library level code, such that it can be used
//   to test software at any level of the dependency hierarchy of a library.
//   In particular, this utility 'struct' can be used to test software before
//   the platform layer of a library is available.
//
///Thread Safety
///- - - - - - -
// Unless otherwise specified no operations on a 'lrkbt::TestHarness' object
// nor the 'lrkbt::TestHarnessUtil' are safe to call across threads.
//-----------------------------------------------------------------------------

// ============================================================================
//                                   Macros
// ---------------------------------------------------------------------------- 
// This section defines the set of macros exported by the test harness 
// component.
// ---------------------------------------------------------------------------- 

#define LRKBT_ASSERT(CONDITION) \
        LarkCompiler::lrkbt::TestUtil::assert(CONDITION)
    // This macro asserts that the specified 'CONDITION' is 'true' using 
    // the 'TestUtil'.

// ============================================================================
//                            C++ Runtime Support
// ----------------------------------------------------------------------------
// This section declares the data and functions required by the C++ runtime
// such that this component can be compiled without the C/C++ runtime library.
//
// The following declarations do not necessarily represent the complete set of
// data or functions required by the C++ runtime, but merely the minimal set
// of data and functions required to compile this component.  It is possible 
// that different compilers or platforms may require definitions not yet 
// included here, in which case the following section shall be amended for 
// the compiler or platform.
// ----------------------------------------------------------------------------

// C++ RUNTIME DATA
void *__dso_handle = nullptr;

// C++ RUNTIME FUNCTIONS
void *operator new(unsigned int numBytes) noexcept;
    // Return 'nullptr'.

void *operator new[](unsigned int numBytes) noexcept;
    // Return 'nullptr'.

void operator delete(void *object) noexcept;
    // Do nothing.

void operator delete(void         *object, 
                     unsigned int  numBytes) noexcept;
    // Do nothing.

void operator delete[](void *object) noexcept;
    // Do nothing.

void operator delete[](void         *object,
                       unsigned int  numBytes) noexcept;
    // Do nothing.

extern "C"
void __cxa_atexit();
    // Do nothing.

extern "C"
void __cxa_pure_virtual();
    // Do nothing.

// ============================================================================
//                                 Component
// ---------------------------------------------------------------------------- 
// This section declares the publicly exported classes used in the test
// harness.
// ---------------------------------------------------------------------------- 

namespace LarkCompiler {
namespace lrkbt {

                                 // ==========
                                 // class Test
                                 // ==========

template <unsigned TEST_CASE_INDEX>
class Test 
{
  public:
    // CREATORS
    Test() = delete;

    template <typename PROCEDURE_TYPE>
    Test(PROCEDURE_TYPE&& procedure);

    Test(const Test&  original) = default;
    Test(      Test&& original) = default;

    ~Test() = default;
    
    // MANIPULATORS
    Test& operator=(const Test&  original) = default;
    Test& operator=(      Test&& original) = default;
};

                               // ==============
                               // class TestUtil
                               // ==============

struct TestUtil
{
  public:
    // TYPES
    using Procedure = int (*)(void);

  private:
    // CLASS DATA
    static Procedure d_cases[4096];

    // PRIVATE CLASS METHODS
    static void failAssertion();

  public:
    // CLASS METHODS
    static void assert(bool condition);

    static void setCase(unsigned int index,
                        Procedure    testCase);

    static bool hasCase(unsigned int index);

    static int runCase(unsigned int index);
};

} // close namespace lrkbt
} // close namespace LarkCompiler

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

                             // -------------------
                             // C++ Runtime Support
                             // -------------------
                             
// C++ RUNTIME FUNCTIONS
void *operator new(unsigned) noexcept
{
    return nullptr;
}

void *operator new[](unsigned) noexcept
{
    return nullptr;
}

void operator delete(void *) noexcept
{
}

void operator delete(void *, unsigned) noexcept
{
}

void operator delete[](void *) noexcept
{
}

void operator delete[](void *, unsigned) noexcept
{
}

extern "C" 
void __cxa_atexit()
{
}

extern "C"
void __cxa_pure_virtual()
{
}
 
namespace LarkCompiler {
namespace lrkbt {

                                 // ----------
                                 // class Test
                                 // ----------

template <unsigned int TEST_CASE_INDEX>
template <typename     PROCEDURE_TYPE>
Test<TEST_CASE_INDEX>::Test(PROCEDURE_TYPE&& procedure)
{
    TestUtil::setCase(TEST_CASE_INDEX, procedure);
}
 
                               // --------------
                               // class TestUtil
                               // --------------

// CLASS DATA
TestUtil::Procedure TestUtil::d_cases[4096] = { };

// PRIVATE CLASS METHODS
void TestUtil::failAssertion()
{
}

// CLASS METHODS
void TestUtil::assert(bool condition)
{
    if (!condition) {
        failAssertion();
    }
}

void TestUtil::setCase(unsigned int index,
                       Procedure    testCase)
{
    d_cases[index] = testCase;
}

bool TestUtil::hasCase(unsigned int index)
{
    return nullptr != d_cases[index];
}

int TestUtil::runCase(unsigned int index)
{
    return d_cases[index]();
}

} // close namespace lrkbt
} // close namespace LarkCompiler

// ============================================================================
//                                MAIN PROGRAM
// ----------------------------------------------------------------------------

using StaticConstructor = void (*)();
extern "C" StaticConstructor LRKBT_STATIC_CONSTRUCTORS[];
extern "C" unsigned          LRKBT_NUM_STATIC_CONSTRUCTORS;

using StaticDestructor  = void (*)();
extern "C" StaticDestructor  LRKBT_STATIC_DESTRUCTORS[];
extern "C" unsigned          LRKBT_NUM_STATIC_DESTRUCTORS;

extern "C"
void __stdcall ExitProcess(unsigned int exitCode);

extern "C" 
void start()
{
    using namespace LarkCompiler;

    // Evaluate the constructor of each statically allocated object.
    for (unsigned int constructorIdx  = 0;
                      constructorIdx != LRKBT_NUM_STATIC_CONSTRUCTORS;
                    ++constructorIdx) {
        LRKBT_STATIC_CONSTRUCTORS[constructorIdx]();
    }

    // Execute all of the registered unit tests.
    for (unsigned int testIndex = 0; 
                      lrkbt::TestUtil::hasCase(testIndex);
                    ++testIndex) {
        if (0 != lrkbt::TestUtil::runCase(testIndex)) {
            break;                                                     // BREAK
        }
    }                                                                 
    
    // Evaluate the destructor of each statically allocated object.
    for (unsigned int destructorIdx  = 0;
                      destructorIdx != LRKBT_NUM_STATIC_DESTRUCTORS;
                    ++destructorIdx) {
        LRKBT_STATIC_DESTRUCTORS[destructorIdx]();
    }

    ExitProcess(10);
}

extern "C" __stdcall
void mainCRTStartup()
{
    start();
}

extern "C" __stdcall
void WinMainCRTStartup()
{
    start();
}

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
