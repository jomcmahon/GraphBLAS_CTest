/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: unit tests for basic methods of semirings
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

#define SUBTEST_COND(_c, _s) do \
    { if (!(_c)) { printf("%s\n", _s); testok = false; } } while (0)

#define TEST_COND(_c, _s) do { printf("%s: ", _s); if (_c) printf("PASSED\n"); \
    else { printf("FAILED\n"); testerror = true; } } while (0)

void get_Semiring_BinaryOp(int, GrB_BinaryOp *);
void get_Semiring_Monoid(int, GrB_Monoid *);

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

#define TEST_OP								\
  OK (GxB_Semiring_add(&mon, thesemi));				\
  SUBTEST_COND(mon == themon, "Semiring monoids don't match");		\
  OK (GxB_Semiring_multiply(&op, thesemi));				\
  SUBTEST_COND(op == thebinop, "Semiring ops don't match");

  // test a reasonable subset of 1355 built-in semirings
  for (int i = 0; i < num_Semirings(); i++) { // semiring loop
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Semiring thesemi; get_Semiring(i, &thesemi);
    GrB_Monoid mon, themon; get_Semiring_Monoid(i, &themon);
    GrB_BinaryOp op, thebinop; get_Semiring_BinaryOp(i, &thebinop);

    TEST_OP;
    char tout[64];
    sprintf(tout, "unit test built-in semiring %d", i);
    TEST_COND(testok, tout);
  }

#ifdef NOT_YET_SUPPORTED
  // test user-defined semirings
  info = GrB_SUCCESS; // reset for next sub-test
  bool testok = true;
  GrB_Semiring thesemi;
  GrB_Monoid mon, themon = GxB_PLUS_INT8_MONOID;
  GrB_BinaryOp op, thebinop = GrB_TIMES_INT8;
  OK (GrB_Semiring_new(&thesemi, themon, thebinop));
  TEST_OP;
  OK (GrB_Semiring_free(&thesemi));
  SUBTEST_COND(!thesemi, "User-defined semiring not freed");
  TEST_COND(testok, "unit test user-defined semiring");
#endif

  OK(GrB_finalize());
  return testerror;
}
