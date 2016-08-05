#!/usr/bin/env bash
# generate.sh                                                        -*-Bash-*-

#@PURPOSE:
#
#@SEE_ALSO:
#
#@DESCRIPTION:
#

                                # Include Guard

if test "defined" = "${INCLUDED_LRKB_CODEGENERATOR+defined}"; 
then
    return 0;
else 
    INCLUDED_LRKB_CODEGENERATOR=1;
fi 

                                 # Main Program

# -----------------------------------------------------------------------------
# m_lshgen_heredoc(heredoc)
#
# -----------------------------------------------------------------------------
function m_lshgen_heredoc
{
    while read -r;
    do
        printf "%s\n" "$REPLY";
    done;
}

# -----------------------------------------------------------------------------
# m_lshgen_splitString(string, separator)
#
# -----------------------------------------------------------------------------
function m_lshgen_splitString
{
    local string="$1";
    local separator="$2";

    local saveIFS="$IFS";
    IFS=$separator;
    read -ra result <<< "$string";
    IFS=$safeIfs;
    echo "${result[@]}";
}

# -----------------------------------------------------------------------------
# m_lshgen_uppercase(string)
#
# -----------------------------------------------------------------------------
function m_lshgen_uppercase
{
    echo "${1^^}";
}

# -----------------------------------------------------------------------------
# m_lshgen_lowercase(string)
#
# ----------------------------------------------------------------------------- 
function m_lshgen_lowercase
{
    echo "${1,,}";
}

# -----------------------------------------------------------------------------
# m_lshgen_generateCopyright(author, year)
#
# -----------------------------------------------------------------------------
function m_lshgen_generateCopyright
{
    local author="$1";
    local year="$2";
    m_lshgen_heredoc <<EOF
// ----------------------------------------------------------------------------
// Copyright (c) ${year} ${author}                                              
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
EOF
}

# -----------------------------------------------------------------------------
# m_lshgen_generateHeader(componentId, author)
#
# -----------------------------------------------------------------------------
function m_lshgen_generateHeader
{
    local componentId="$1";
    local author="$2";
    read -ra componentParts <<< `m_lshgen_splitString "$componentId" "::"`;
    local package="${componentParts[0]}";
    local component="${componentParts[1]}";
    local uppercasePackage=`m_lshgen_uppercase "$package"`;
    local uppercaseComponent=`m_lshgen_uppercase "$component"`;
    local lowercasePackage=`m_lshgen_lowercase "$package"`;
    local lowercaseComponent=`m_lshgen_lowercase "$component"`;

    local fileNameBanner="// ${lowercasePackage}_${lowercaseComponent}.h";
    local fileTypeBanner="-*-C++-*-";
    local bannerSepLength=$[79 - ${#fileNameBanner} - ${#fileTypeBanner}];
    local bannerSep=`printf "%${bannerSepLength}s"`;

    local componentBannerText="class ${uppercaseComponent}";
    local componentBannerFlag=`printf "=%.0s" $(seq 1 ${#componentBannerText})`;

    local impBannerFlag=`printf "%.0s-" $(seq 1 ${#componentBannerText})`;

    local componentBannerSepLength=$[(79 - 3 - ${#componentBannerText}) / 2];
    local componentBannerSep=`printf "%${componentBannerSepLength}s"`;

    local year=`printf "%(%Y)T"`;
    local copyright=`m_lshgen_generateCopyright "$author" "$year"`;

    m_lshgen_heredoc <<EOF
${fileNameBanner}${bannerSep}${fileTypeBanner}
#ifndef INCLUDED_${uppercasePackage}_${uppercaseComponent}
#define INCLUDED_${uppercasePackage}_${uppercaseComponent}

//@PURPOSE: Provide ...
//
//@TYPES:
//  ${lowercasePackage}::${component}: 
//
//@SEE_ALSO:
//
//@DESCRIPTION: ...
//

#ifndef INCLUDED_LRKP_BOOLEAN
#include <lrkp_boolean.h>
#endif

namespace LarkCompiler {
namespace ${lowercasePackage} {

${componentBannerSep}// ${componentBannerFlag}
${componentBannerSep}// ${componentBannerText}
${componentBannerSep}// ${componentBannerFlag}

class $component
    // This value-semantic class is primarily provided to ... 
{
  public:
    // TYPES

  private:
    // DATA

  public:
    // CREATORS
    explicit ${component} () = default;

    explicit ${component} (const ${component}&  original) = default;
    explicit ${component} (      ${component}&& original) = default;

    ~${component} () = default;

    // MANIPULATORS
    ${component}& operator= (const ${component}&  original);
    ${component}& operator= (      ${component}&& original);

    // ACCESSORS

};

// FREE OPERATORS
lrkp::Boolean operator== (const ${package}::${component}& lhs,
                          const ${package}::${component}& rhs);

lrkp::Boolean operator!= (const ${package}::${component}& lhs,
                          const ${package}::${component}& rhs);

// ============================================================================
//                             INLINE DEFINITIONS
// ============================================================================

${componentBannerSep}// ${impBannerFlag}
${componentBannerSep}// ${componentBannerText}
${componentBannerSep}// ${impBannerFlag}
 
// CREATORS

// MANIPULATORS

// ACCESSORS

// FREE OPERATORS

} // close namespace ${lowercasePackage}
} // close namespace LarkCompiler

#endif // INCLUDED_${uppercasePackage}_${uppercaseComponent}

${copyright}
EOF
}

# -----------------------------------------------------------------------------
# m_lshgen_generateSource(componentId, author)
#
# -----------------------------------------------------------------------------
function m_lshgen_generateSource
{
    local componentId="$1";
    local author="$2";
    read -ra componentParts <<< `m_lshgen_splitString "$componentId" "::"`;
    local package="${componentParts[0]}";
    local component="${componentParts[1]}";
    local uppercasePackage=`m_lshgen_uppercase "$package"`;
    local uppercaseComponent=`m_lshgen_uppercase "$component"`;
    local lowercasePackage=`m_lshgen_lowercase "$package"`;
    local lowercaseComponent=`m_lshgen_lowercase "$component"`;

    local fileNameBanner="// ${lowercasePackage}_${lowercaseComponent}.cpp";
    local fileTypeBanner="-*-C++-*-";
    local bannerSepLength=$[79 - ${#fileNameBanner} - ${#fileTypeBanner}];
    local bannerSep=`printf "%${bannerSepLength}s"`;

    local componentBannerText="class ${uppercaseComponent}";
    local componentBannerFlag=`printf "%.0s-" $(seq 1 ${#componentBannerText})`;

    local componentBannerSepLength=$[(79 - 3 - ${#componentBannerText}) / 2];
    local componentBannerSep=`printf "%${componentBannerSepLength}s"`;

    local year=`printf "%(%Y)T"`;
    local copyright=`m_lshgen_generateCopyright "$author" "$year"`; 

    m_lshgen_heredoc <<EOF
${fileNameBanner}${bannerSep}${fileTypeBanner}
#include <${lowercasePackage}_${lowercaseComponent}.h>

namespace LarkCompiler {
namespace ${lowercasePackage} {
namespace {

} // close unnamed namespace

${componentBannerSep}// ${componentBannerFlag}
${componentBannerSep}// ${componentBannerText}
${componentBannerSep}// ${componentBannerFlag}

// CREATORS

// MANIPULATORS

// ACCESSORS

} // close namespace ${lowercasePackage}
} // close namespace LarkCompiler

${copyright}
EOF
}
 
# -----------------------------------------------------------------------------
# m_lshgen_generateTestDriver(componentId, author)
#
# -----------------------------------------------------------------------------
function m_lshgen_generateTestDriver
{
    local componentId="$1";
    local author="$2";
    read -ra componentParts <<< `m_lshgen_splitString "$componentId" "::"`;
    local package="${componentParts[0]}";
    local component="${componentParts[1]}";
    local uppercasePackage=`m_lshgen_uppercase "$package"`;
    local uppercaseComponent=`m_lshgen_uppercase "$component"`;
    local lowercasePackage=`m_lshgen_lowercase "$package"`;
    local lowercaseComponent=`m_lshgen_lowercase "$component"`;

    local fileNameBanner="// ${lowercasePackage}_${lowercaseComponent}.t.cpp";
    local fileTypeBanner="-*-C++-*-";
    local bannerSepLength=$[79 - ${#fileNameBanner} - ${#fileTypeBanner}];
    local bannerSep=`printf "%${bannerSepLength}s"`;

    local componentBannerText="class ${uppercaseComponent}";
    local componentBannerFlag=`printf "=%.0s" $(seq 1 ${#componentBannerText})`;

    local impBannerFlag=`printf "%.0s-" $(seq 1 ${#componentBannerText})`;

    local componentBannerSepLength=$[(79 - 3 - ${#componentBannerText}) / 2];
    local componentBannerSep=`printf "%${componentBannerSepLength}s"`;

    local year=`printf "%(%Y)T"`;
    local copyright=`m_lshgen_generateCopyright "$author" "$year"`;
 
    m_lshgen_heredoc <<EOF
${fileNameBanner}${bannerSep}${fileTypeBanner}
#include <${lowercasePackage}_${lowercaseComponent}.h>

using namespace LarkCompiler;
using namespace ${lowercasePackage};

//=============================================================================
//                                 TEST PLAN
//-----------------------------------------------------------------------------
//                                  Overview
//                                  --------
// '${lowercasePackage}::${component}' provides ... 
// This test driver tests ...
//-----------------------------------------------------------------------------
// CREATORS
// [  ] ${component}()
// MANIPULATORS
// ACCESSORS


//=============================================================================
//                           BOOTSTRAP TEST HARNESS
//-----------------------------------------------------------------------------
// @PURPOSE: This section provides a bootstrapped test harness utility.
// 
// @MACROS:
//   ASSERT: Set the test failure line number unless a condition is true
//
// @TYPES:
//   TestHarnessUtil: Platform independent test harness utility
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

#define ASSERT(CONDITION) TestHarnessUtil::assert((CONDITION), __LINE__)
    // This macro asserts that the specified 'CONDITION' is 'true' using 
    // the 'TestHarnessUtil', providing the line number at the point of 
    // macro expansion.

                           // ======================
                           // struct TestHarnessUtil
                           // ======================

struct TestHarnessUtil
{
  private:
    // CLASS DATA
    static int d_firstFailureLineNumber = 0;
        // The specified 'lineNumber' of the first call to 'assert' where the
        // specified 'condition' is 'false', or '0' otherwise. 

  public:
    // CLASS MANIPULATORS
    static bool parseCase(int        *testCaseNumber,
                          const char  testCaseString[]);
        // Load into the specified 'testCaseNumber' the non-negative integer
        // value of the number represented by the specified 'testCaseString'
        // and return 'true' if the 'testCaseString' is an ASCII-encoded
        // non-negative integer, otherwise do not modify 'testCaseNumber' and
        // return 'false'.

    static void assert(bool condition,
                       int  lineNumber);
        // Load into the specified 'testStatus' the value of the specified
        // 'lineNumber' unless the specified 'condition' is 'true', otherwise
        // do nothing.

    // CLASS ACCESSORS
    static int firstFailureLineNumber() const;
        // Return the specified 'lineNumber' of the first call to 'assert'
        // where the specified 'condition' is 'false', or '0' otherwise.
};

                           // ----------------------
                           // struct TestHarnessUtil
                           // ----------------------

// CLASS MANIPULATORS
void TestHarnessUtil::assert(const bool condition,
                             const int  lineNumber)
{
    if (0 != d_firstFailureLineNumber || true == condition) {
        return;                                                       // RETURN
    }
    d_firstFailureLineNumber = lineNumber;
}

bool TestHarnessUtil::parseCase(int        *testCaseNumber,
                                const char  testCaseString[])
{
    int         test      = 0;
    const char *character = &testCaseString[0];
    for (const char *character  = &testCaseString[0];
                    *character != 0;
                   ++character) {
        if ('0' < *character || *character > '9') {
            return false;                                             // RETURN
        }
        int digit = character - '0';
        test      = test * 10 + digit;
    }
    *testCaseNumber = test;
    return true;
}

// CLASS ACCESSORS
int TestHarnessUtil::firstFailureLineNumber() const
{
    return d_firstFailureLineNumber;
}

//=============================================================================
//                   GLOBAL TYPES AND CONSTANTS FOR TESTING
//-----------------------------------------------------------------------------
// @PURPOSE: Provide types and constants used throughout multiple test cases.
//
// @MACROS:
//
// @TYPES:
//
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

${copyright}
EOF
}

# =============================================================================
#                                 MAIN PROGRAM
# =============================================================================

# -----------------------------------------------------------------------------
# m_lshgen_main(componentId, author)
#
# -----------------------------------------------------------------------------
function m_lshgen_main
{
    m_lshgen_generateHeader "lrku::ComponentName" "Nathan Burgers";
    m_lshgen_generateSource "lrku::ComponentName" "Nathan Burgers";
    m_lshgen_generateTestDriver "lrku::ComponentName" "Nathan Burgers";
}

m_lshgen_main "$1" "$2"

# -----------------------------------------------------------------------------
# Copyright (c) 2016 Nathan Burgers
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
# ------------------------------ END-OF-FILE ----------------------------------
