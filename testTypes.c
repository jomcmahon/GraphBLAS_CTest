/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: unit tests for basic methods of types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

#define SUBTEST_COND(_c, _s) do \
    { if (!(_c)) { printf("%s\n", _s); testok = false; } } while (0)

#define TEST_COND(_c, _s) do { printf("%s: ", _s); if (_c) printf("PASSED\n"); \
    else { printf("FAILED\n"); testerror = true; } } while (0)

typedef struct {
  float stuff [4][4];
  char whatstuff [64];
} wildtype;

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false, testok = true;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  // test sizes of 11 built-in types
  size_t tsize;
  OK (GxB_Type_size(&tsize, GrB_BOOL));
  SUBTEST_COND(tsize == sizeof(bool), "size not same bool");
  TEST_COND(testok, "unit test built-in type 0"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_INT8));
  SUBTEST_COND(tsize == sizeof(int8_t), "size not same int8");
  TEST_COND(testok, "unit test built-in type 1"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_UINT8));
  SUBTEST_COND(tsize == sizeof(uint8_t), "size not same uint8");
  TEST_COND(testok, "unit test built-in type 2"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_INT16));
  SUBTEST_COND(tsize == sizeof(int16_t), "size not same int16");
  TEST_COND(testok, "unit test built-in type 3"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_UINT16));
  SUBTEST_COND(tsize == sizeof(uint16_t), "size not same uint16");
  TEST_COND(testok, "unit test built-in type 4"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_INT32));
  SUBTEST_COND(tsize == sizeof(int32_t), "size not same int32");
  TEST_COND(testok, "unit test built-in type 5"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_UINT32));
  SUBTEST_COND(tsize == sizeof(uint32_t), "size not same uint32");
  TEST_COND(testok, "unit test built-in type 6"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_INT64));
  SUBTEST_COND(tsize == sizeof(int64_t), "size not same int64");
  TEST_COND(testok, "unit test built-in type 7"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_UINT64));
  SUBTEST_COND(tsize == sizeof(uint64_t), "size not same uint64");
  TEST_COND(testok, "unit test built-in type 8"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_FP32));
  SUBTEST_COND(tsize == sizeof(float), "size not same fp32");
  TEST_COND(testok, "unit test built-in type 9"); testok = true;
  OK (GxB_Type_size(&tsize, GrB_FP64));
  SUBTEST_COND(tsize == sizeof(double), "size not same fp64");
  TEST_COND(testok, "unit test built-in type 10"); testok = true;

#ifdef NOT_YET_SUPPORTED
  // user-defined type
  GrB_Type thetype;
  OK (GrB_Type_new (&thetype, sizeof(wildtype)));
  OK (GxB_Type_size(&tsize, thetype)) ;
  SUBTEST_COND(tsize == sizeof(wildtype), "size not same user-defined");
  OK (GrB_Type_free(&thetype));
  SUBTEST_COND((!thetype), "User-def not freed");
  TEST_COND(testok, "unit test user-defined type");
#endif

  OK(GrB_finalize());
  return testerror;
}
