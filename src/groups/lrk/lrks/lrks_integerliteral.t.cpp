// lrks_integerliteral.t.cpp                                          -*-C++-*-
#include <lrks_integerliteral.h>

#include <bsl_iostream.h>
#include <bslim_testutil.h>
#include <bslma_default.h>
#include <bslma_testallocator.h>            // to verify that we do not
#include <bslma_testallocatormonitor.h>     // allocate any memory
#include <bsls_asserttest.h>

using namespace BloombergLP;
using namespace bsl;

// ============================================================================
//                                  TEST PLAN
// ----------------------------------------------------------------------------
//                                   Overview
//                                   --------
// TBD
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// [ 1] BREATHING TEST
// [  ] USAGE EXAMPLE
// [ *] CONCERN: TBD
// [  ] TEST APPARATUS: TBD
// [ 5] PRINTING: TBD

// ============================================================================
//                        STANDARD BDE ASSERT TEST MACRO
// ----------------------------------------------------------------------------

namespace {

int testStatus = 0;

void aSsErT(int c, const char *s, int i)
{
    if (c) {
        cout << "Error " << __FILE__ << "(" << i << "): " << s
             << "    (failed)" << endl;
        if (0 <= testStatus && 100 >= testStatus) {
            ++testStatus;
        }
    }
}

}  // close unnamed namespace

// ============================================================================
//                      STANDARD BDE TEST DRIVER MACROS
// ----------------------------------------------------------------------------

#define ASSERT       BSLIM_TESTUTIL_ASSERT
#define LOOP_ASSERT  BSLIM_TESTUTIL_LOOP_ASSERT
#define LOOP0_ASSERT BSLIM_TESTUTIL_LOOP0_ASSERT
#define LOOP1_ASSERT BSLIM_TESTUTIL_LOOP1_ASSERT
#define LOOP2_ASSERT BSLIM_TESTUTIL_LOOP2_ASSERT
#define LOOP3_ASSERT BSLIM_TESTUTIL_LOOP3_ASSERT
#define LOOP4_ASSERT BSLIM_TESTUTIL_LOOP4_ASSERT
#define LOOP5_ASSERT BSLIM_TESTUTIL_LOOP5_ASSERT
#define LOOP6_ASSERT BSLIM_TESTUTIL_LOOP6_ASSERT
#define ASSERTV      BSLIM_TESTUTIL_ASSERTV

#define Q   BSLIM_TESTUTIL_Q   // Quote identifier literally.
#define P   BSLIM_TESTUTIL_P   // Print identifier and value.
#define P_  BSLIM_TESTUTIL_P_  // P(X) without newline.
#define T_  BSLIM_TESTUTIL_T_  // Print a tab (w/o newline).
#define L_  BSLIM_TESTUTIL_L_  // current Line number

// ============================================================================
//                      NEGATIVE-TEST MACRO ABBREVIATIONS
// ----------------------------------------------------------------------------

#define ASSERT_SAFE_PASS(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_PASS(EXPR)
#define ASSERT_SAFE_FAIL(EXPR) BSLS_ASSERTTEST_ASSERT_SAFE_FAIL(EXPR)
#define ASSERT_PASS(EXPR)      BSLS_ASSERTTEST_ASSERT_PASS(EXPR)
#define ASSERT_FAIL(EXPR)      BSLS_ASSERTTEST_ASSERT_FAIL(EXPR)
#define ASSERT_OPT_PASS(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_PASS(EXPR)
#define ASSERT_OPT_FAIL(EXPR)  BSLS_ASSERTTEST_ASSERT_OPT_FAIL(EXPR)

// ============================================================================
//                             USEFUL MACROS
// ----------------------------------------------------------------------------

// The following macros may be used to print an expression 'X' at different
// levels of verbosity.  Note that 'X' is not surrounded with parentheses so
// that expressions containing output stream operations can be supported.

#define PV(X)   if         (verbose) cout << endl << X << endl;
#define PVV(X)  if     (veryVerbose) cout << endl << X << endl;
#define PVVV(X) if (veryVeryVerbose) cout << endl << X << endl;

// ============================================================================
//                              GLOBAL TYPEDEFS
// ----------------------------------------------------------------------------

typedef lrks::IntegerLiteral Obj;

// ============================================================================
//                 HELPER CLASSES AND FUNCTIONS FOR TESTING
// ----------------------------------------------------------------------------

// ============================================================================
//                                 MAIN PROGRAM
// ----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    int                 test = argc > 1 ? atoi(argv[1]) : 0;
    bool             verbose = argc > 2; (void)            verbose;
    bool         veryVerbose = argc > 3; (void)        veryVerbose;
    bool     veryVeryVerbose = argc > 4; (void)    veryVeryVerbose;
    bool veryVeryVeryVerbose = argc > 5; (void)veryVeryVeryVerbose;

    cout << "TEST " << __FILE__ << " CASE " << test << endl;

    // CONCERN: DOES NOT ALLOCATE MEMORY

    bslma::TestAllocator ga("global", veryVeryVeryVerbose);
    bslma::Default::setGlobalAllocator(&ga);

    bslma::TestAllocator da("default", veryVeryVeryVerbose);
    bslma::Default::setDefaultAllocator(&da);

    bslma::TestAllocator ta("test", veryVeryVeryVerbose); (void)ta;

    bslma::TestAllocatorMonitor gam(&ga), dam(&da);

    switch (test) { case 0:
      case 1: {
        // --------------------------------------------------------------------
        // BREATHING TEST:
        //   This case exercises (but does not fully test) basic functionality.
        //
        // Concerns:
        //:
        //: 1 The class is sufficiently functional to enable comprehensive
        //:   testing in subsequent test cases
        //
        // Plan:
        //:
        //: 1 TBD
        //
        // Testing:
        //   BREATHING TEST
        // --------------------------------------------------------------------

        if (verbose) cout << endl << "BREATHING TEST" << endl
                                  << "==============" << endl;

        // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

      } break;
      default: {
        cerr << "WARNING: CASE '" << test << "' NOT FOUND." << endl;
        testStatus = -1;
      }
    }

    // CONCERN: DOES NOT ALLOCATE MEMORY

    ASSERTV(gam.isTotalSame());
    ASSERTV(dam.isTotalSame());

    if (testStatus > 0) {
        cerr << "Error, non-zero test status = " << testStatus << "." << endl;
    }
    return testStatus;
}

// ----------------------------------------------------------------------------
// NOTICE:
//      Copyright (C) Bloomberg L.P., 2016
//      All rights reserved.
//      Property of Bloomberg L.P. (BLP)
//      This software is made available solely pursuant to the
//      terms of a BLP license agreement which governs its use.
// ----------------------------- END-OF-FILE ----------------------------------
