// lrkbt_testharness.t.cpp                                            -*-C++-*-
#include <lrkbt_testharness.h>

//=============================================================================
//                                 TEST PLAN
//-----------------------------------------------------------------------------
//                                  Overview
//                                  --------
// 'lrku::ComponentName' provides ... 
// This test driver tests ...
//-----------------------------------------------------------------------------
// CREATORS
// [  ] ComponentName()
// MANIPULATORS
// ACCESSORS

extern Test<1> BreathingTest;
    // This case exercises (but does not fully test) basic functionality.

//=============================================================================
//                          BOOTSTRAP TESTING MACROS
//----------------------------------------------------------------------------- 

#define ASSERT LRKBT_ASSERT

template <unsigned int CASE_NUMBER> 
using Test = LarkCompiler::lrkbt::Test<CASE_NUMBER>;

//=============================================================================
//                   GLOBAL TYPES AND CONSTANTS FOR TESTING
//----------------------------------------------------------------------------- 

//=============================================================================
//                                 TEST CASES
//-----------------------------------------------------------------------------

Test<1> BreathingTest = [] 
{
    ASSERT(false);
};

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
