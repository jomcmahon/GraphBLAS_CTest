/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: unit tests for basic methods of select operations
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

#define SUBTEST_COND(_c, _s) do \
    { if (!(_c)) { printf("%s\n", _s); testok = false; } } while (0)

#define TEST_COND(_c, _s) do { printf("%s: ", _s); if (_c) printf("PASSED\n"); \
    else { printf("FAILED\n"); testerror = true; } } while (0)

bool f_sel (const GrB_Index i, const GrB_Index j, const GrB_Index nrows,
	const GrB_Index ncols, const void *z, const void *thunk)
{ return (i == j); }

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

#define TEST_OP \
  OK (GxB_SelectOp_xtype(&xtype, inop));		       \
  SUBTEST_COND(xtype == thetype, "select xtypes don't match"); \
  OK (GxB_SelectOp_ttype(&ttype, inop));		       \
  SUBTEST_COND(ttype == thetype, "select ttypes don't match");

  // test type methods of built-in SelectOps (type-generic)
  for (int i = 0; i < num_SelectOps(); i++) { // selectop loop
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GxB_SelectOp inop; get_SelectOp(i, &inop);
    GrB_Type xtype, ttype, thetype = NULL;

    TEST_OP;
    char tout[64];
    sprintf(tout, "unit test built-in select operator %d", i);
    TEST_COND(testok, tout);
  }


#ifdef NOT_YET_SUPPORTED
  // user-defined SelectOp, all types
  for (int i = 0; i < num_Types(); i++) { // all types
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type xtype, ttype, thetype; get_Type(i, &thetype); // pick type
    GxB_SelectOp inop;

    OK (GxB_SelectOp_new (&inop, f_sel, thetype, thetype));
    TEST_OP;
    OK (GxB_SelectOp_free(&inop));
    SUBTEST_COND(!inop, "User-defined not freed");
    char tout[64];
    sprintf(tout, "unit test user-defined select operator type %d", i);
    TEST_COND(testok, tout);
  }
#endif

  OK(GrB_finalize());
  return testerror;
}
