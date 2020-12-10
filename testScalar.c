/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: unit tests for basic methods of scalars
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
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

#define TEST_SCAL(_s)						\
  OK (GxB_Scalar_nvals(&nvals, _s));			\
  SUBTEST_COND(nv == nvals, "scalar nvals not correct");	\
  OK (GxB_Scalar_type(&stype, _s));				\
  SUBTEST_COND(thetype == stype, "scalar type not correct");

  for (int i = 0; i < num_Types(); i++) { // type loop
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type stype, thetype; get_Type(i, &thetype); // pick type
    GxB_Scalar scal, dupscal;
    int8_t sval = 10;
    GrB_Index nvals, nv = 0;

#define SET_AND_TEST							\
    OK (GxB_Scalar_new(&scal, thetype));				\
    TEST_SCAL(scal);							\
    OK (GxB_Scalar_setElement(scal, s));				\
    nv++; TEST_SCAL(scal);						\
    OK (GxB_Scalar_extractElement(&r, scal));			\
    TEST_SCAL(scal); SUBTEST_COND(r == s, "scalar values not equal") ;	\
    OK (GxB_Scalar_dup(&dupscal, scal));				\
    TEST_SCAL(dupscal);							\
    OK (GxB_Scalar_extractElement(&r, dupscal));			\
    TEST_SCAL(dupscal); SUBTEST_COND(r == s, "scalar values not equal"); \
    OK (GxB_Scalar_clear(scal));					\
    nv = 0; TEST_SCAL(scal);						\
    nv = 1; TEST_SCAL(dupscal);						\
    OK (GxB_Scalar_free(&scal));					\
    SUBTEST_COND(!scal, "scalar not freed");				\
    OK (GxB_Scalar_free(&dupscal));					\
    SUBTEST_COND(!dupscal, "scalar not freed");

    if (thetype == GrB_BOOL) {
      bool     r = 0, s = true; SET_AND_TEST;
    } else if (thetype == GrB_INT8) {
      int8_t   r = 0, s = (int8_t)sval;   SET_AND_TEST;
    } else if (thetype == GrB_UINT8) {
      uint8_t  r = 0, s = (uint8_t)sval;  SET_AND_TEST;
    } else if (thetype == GrB_INT16) {
      int16_t  r = 0, s = (int16_t)sval;  SET_AND_TEST;
    } else if (thetype == GrB_UINT16) {
      uint16_t r = 0, s = (uint16_t)sval; SET_AND_TEST;
    } else if (thetype == GrB_INT32) {
      int32_t  r = 0, s = (int32_t)sval;  SET_AND_TEST;
    } else if (thetype == GrB_UINT32) {
      uint32_t r = 0, s = (uint32_t)sval; SET_AND_TEST;
    } else if (thetype == GrB_INT64) {
      int64_t  r = 0, s = (int64_t)sval;  SET_AND_TEST;
    } else if (thetype == GrB_UINT64) {
      uint64_t r = 0, s = (uint64_t)sval; SET_AND_TEST;
    } else if (thetype == GrB_FP32) {
      float    r = 0, s = (float)sval;    SET_AND_TEST;
    } else if (thetype == GrB_FP64) {
      double   r = 0, s = (double)sval;   SET_AND_TEST;
    } else { printf("bad type,\n"); exit(1); }

    char tout[64];
    sprintf(tout, "unit test built-in scalar %d", i);
    TEST_COND(testok, tout);
  }
  
#ifdef NOT_YET_SUPPORTED
  // test with user-defined type
  info = GrB_SUCCESS; // reset for next sub-test
  bool testok = true;
  GxB_Scalar scal;
  GrB_Type stype, thetype;
  GrB_Index nvals, nv = 0;
  OK (GrB_Type_new (&thetype, sizeof(wildtype)));
  OK (GxB_Scalar_new(&scal, thetype));
  TEST_SCAL(scal);
  OK (GxB_Scalar_free(&scal));
  SUBTEST_COND(!scal, "User-defined scalar not freed");
  TEST_COND(testok, "unit test user-defined scalar");
#endif

  OK(GrB_finalize());
  return testerror;
}
