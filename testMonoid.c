/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: unit tests for basic methods of monoids
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

#define SUBTEST_COND(_c, _s) do \
    { if (!(_c)) { printf("%s\n", _s); testok = false; } } while (0)

#define TEST_COND(_c, _s) do { printf("%s: ", _s); if (_c) printf("PASSED\n"); \
    else { printf("FAILED\n"); testerror = true; } } while (0)

int get_Monoid_BinaryOp(int, GrB_BinaryOp *);
void get_Monoid_Type(int, GrB_Type *);

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  GrB_Monoid themon;
  GrB_BinaryOp getbinop, thebinop;
  bool getflag, theflag;
  void *ispace = malloc(8);
  void *tspace = malloc(8);
  bool mt;

#define SET_AND_TEST							\
  OK (GxB_Monoid_operator(&getbinop, themon));			\
  SUBTEST_COND(getbinop == thebinop, "monoid ops not equal");		\
  OK (GxB_Monoid_identity(I, themon));				\
  OK (GxB_Monoid_terminal(&getflag, T, themon));			\
  SUBTEST_COND(theflag == getflag, "monoid flags not equal");		\
  SUBTEST_COND(*I == id, "monoid ids not equal");			\
  mt = !getflag || (getflag && (*T == term));				\
  SUBTEST_COND(mt, "monoid terms not equal");

  // test 55 built-in monoids
  for (int i = 0; i < num_Monoids(); i++) { // monoid loop
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type thetype; get_Monoid_Type(i, &thetype);
    int opPick = i % 5;
    theflag = true;
    get_Monoid(i, &themon);
    get_Monoid_BinaryOp(i, &thebinop);

    if (thetype == GrB_BOOL) {
      bool id, term, *I = (bool *)ispace, *T = (bool *)tspace;;
      switch (opPick) {
      case 0: id = false; term = true; break; // LOR
      case 1: id = true; term = false; break; // LAND
      case 2: id = false; theflag = false; break; // LXOR
      case 3: id = true; theflag = false; break; // EQ
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_INT8) {
      int8_t id, term, *I = (int8_t *)ispace, *T = (int8_t *)tspace;
      switch (opPick) {
      case 0: id = SCHAR_MAX; term = SCHAR_MIN; break; // MIN
      case 1: id = SCHAR_MIN; term = SCHAR_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_UINT8) {
      uint8_t id, term, *I = (uint8_t *)ispace, *T = (uint8_t *)tspace;
      switch (opPick) {
      case 0: id = UCHAR_MAX; term = 0; break; // MIN
      case 1: id = 0; term = UCHAR_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_INT16) {
      int16_t id, term, *I = (int16_t *)ispace, *T = (int16_t *)tspace;
      switch (opPick) {
      case 0: id = SHRT_MAX; term = SHRT_MIN; break; // MIN
      case 1: id = SHRT_MIN; term = SHRT_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_UINT16) {
      uint16_t id, term, *I = (uint16_t *)ispace, *T = (uint16_t *)tspace;
      switch (opPick) {
      case 0: id = USHRT_MAX; term = 0; break; // MIN
      case 1: id = 0; term = USHRT_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_INT32) {
      int32_t id, term, *I = (int32_t *)ispace, *T = (int32_t *)tspace;
      switch (opPick) {
      case 0: id = INT_MAX; term = INT_MIN; break; // MIN
      case 1: id = INT_MIN; term = INT_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_UINT32) {
      uint32_t id, term, *I = (uint32_t *)ispace, *T = (uint32_t *)tspace;
      switch (opPick) {
      case 0: id = UINT_MAX; term = 0; break; // MIN
      case 1: id = 0; term = UINT_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_INT64) {
      int64_t id, term, *I = (int64_t *)ispace, *T = (int64_t *)tspace;
      switch (opPick) {
      case 0: id = LONG_MAX; term = LONG_MIN; break; // MIN
      case 1: id = LONG_MIN; term = LONG_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_UINT64) {
      uint64_t id, term, *I = (uint64_t *)ispace, *T = (uint64_t *)tspace;
      switch (opPick) {
      case 0: id = ULONG_MAX; term = 0; break; // MIN
      case 1: id = 0; term = ULONG_MAX; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; term = 0; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_FP32) {
      float id, term, *I = (float *)ispace, *T = (float *)tspace;
      switch (opPick) {
      case 0: id = INFINITY; term = -INFINITY; break; // MIN
      case 1: id = -INFINITY; term = INFINITY; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; theflag = false; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else if (thetype == GrB_FP64) {
      double id, term, *I = (double *)ispace, *T = (double *)tspace;
      switch (opPick) {
      case 0: id = INFINITY; term = -INFINITY; break; // MIN
      case 1: id = -INFINITY; term = INFINITY; break; // MAX
      case 2: id = 0; theflag = false; break; // PLUS
      case 3: id = 1; theflag = false; break; // TIMES
      case 4: id = 0; term = 0; break; // ANY
      }
      SET_AND_TEST;
    } else { printf("bad type,\n"); exit(1); }

    char tout[64];
    sprintf(tout, "unit test built-in monoid %d", i);
    TEST_COND(testok, tout);
  }

#ifdef NOT_YET_SUPPORTED
  // user-defined monoids
  info = GrB_SUCCESS;
  bool testok = true;
  int8_t id = 0, term = 0, *I = (int8_t *)ispace, *T = (int8_t *)tspace;
  theflag = false;
  thebinop = GrB_PLUS_INT8;
  info = GrB_Monoid_new(&themon, thebinop, id);
  SUBTEST_COND(info == GrB_SUCCESS, "user-defined monoid new");
  SET_AND_TEST;
  OK (GrB_Monoid_free(&themon));
  SUBTEST_COND(!themon, "monoid not freed");
  id = SCHAR_MAX; term = SCHAR_MIN; theflag = true;
  thebinop = GrB_MIN_INT8;
  info = GxB_Monoid_terminal_new(&themon, thebinop, id, term);
  SUBTEST_COND(info == GrB_SUCCESS, "user-defined monoid term new");
  SET_AND_TEST;
  OK (GrB_Monoid_free(&themon));
  SUBTEST_COND(!themon, "monoid not freed");
  TEST_COND(testok, "unit test user-defined monoid");
#endif

  OK(GrB_finalize());
  return testerror;
}
