/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: unit tests for basic methods of descriptors
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

#define INP1_TRAN(i) (i & 1)
#define INP0_TRAN(i) (i & 2)
#define MASK_COMP(i) (i & 4)
#define MASK_STRUCT(i) (i & 8)
#define OUTP_REPL(i) (i & 16)

#define SUBTEST_COND(_c, _s) do \
    { if (!(_c)) { printf("%s\n", _s); testok = false; } } while (0)

#define TEST_COND(_c, _s) do { printf("%s: ", _s); if (_c) printf("PASSED\n"); \
    else { printf("FAILED\n"); testerror = true; } } while (0)

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  for (int i = 1; i < num_Descriptors(); i++) { // built-in descriptors
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Descriptor desc; get_Descriptor(i, &desc);
    GrB_Desc_Value val;

    OK (GxB_Desc_get(desc, GrB_OUTP, &val));
    bool dt0 = ((OUTP_REPL(i) && (val == GrB_REPLACE)) ||
	       (!OUTP_REPL(i) && (val != GrB_REPLACE)));
    SUBTEST_COND(dt0, "output replace");
    OK (GxB_Desc_get(desc, GrB_INP0, &val));
    bool dt1 = ((INP0_TRAN(i) && (val == GrB_TRAN)) ||
	  (!INP0_TRAN(i) && (val != GrB_TRAN)));
    SUBTEST_COND(dt1, "input 0 transpose");
    OK (GxB_Desc_get(desc, GrB_INP1, &val));
    bool dt2 = ((INP1_TRAN(i) && (val == GrB_TRAN)) ||
	  (!INP1_TRAN(i) && (val != GrB_TRAN)));
    SUBTEST_COND(dt2, "input 1 transpose");
    OK (GxB_Desc_get(desc, GrB_MASK, &val));
    bool dt3 = ((MASK_COMP(i) && (val & GrB_COMP)) ||
	  (!MASK_COMP(i) && !(val & GrB_COMP)));
    SUBTEST_COND(dt3, "mask complement");
    bool dt4 = ((MASK_STRUCT(i) && (val & GrB_STRUCTURE)) ||
	  (!MASK_STRUCT(i) && !(val & GrB_STRUCTURE)));
    SUBTEST_COND(dt4, "mask structure");

    char tout[64];
    sprintf(tout, "unit test built-in descriptor %d", i);
    TEST_COND(testok, tout);
  }

  // user-defined descriptors
  info = GrB_SUCCESS; // reset for next sub-test
  bool testok = true;
  GrB_Descriptor desc;
  GrB_Desc_Value val;
  OK (GrB_Descriptor_new(&desc));
  OK (GrB_Descriptor_set(desc, GrB_OUTP, GrB_REPLACE));
  OK (GxB_Desc_set(desc, GrB_MASK, GrB_COMP));
  OK (GxB_Desc_get(desc, GrB_OUTP, &val));
  SUBTEST_COND(val == GrB_REPLACE , "replace not correct");
  OK (GxB_Desc_get(desc, GrB_MASK, &val));
  SUBTEST_COND(val == GrB_COMP, "mask complement not correct");
  OK (GrB_Descriptor_free(&desc));
  TEST_COND(testok, "unit test user-def descriptor");

  OK(GrB_finalize());
  return testerror;
}
