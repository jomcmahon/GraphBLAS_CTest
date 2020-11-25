/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: unit tests for basic methods of vectors
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

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

  GrB_Index *I = malloc(2 * sizeof(*I));
  double *Xspace = malloc(2 * sizeof(*Xspace));
  for (int i = 0; i < num_Types(); i++) { // type loop
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type vtype, thetype; get_Type(i, &thetype); // pick type
    GrB_Vector vec;
    GrB_Index vsize, nvals, sz = 8, vind = 3, nv = 0;
    int8_t sval = 10;

#define TEST_VEC(_v)							\
    TEST_OK(GrB_Vector_size(&vsize, vec));				\
    SUBTEST_COND(sz == vsize, "vector size not equal");			\
    TEST_OK(GrB_Vector_nvals(&nvals, vec));				\
    SUBTEST_COND(nv == nvals, "vector values not equal");		\
    TEST_OK(GxB_Vector_type(&vtype, vec));				\
    SUBTEST_COND(thetype == vtype, "vector types not equal");

#define TEST_ELTS(_v)							\
    TEST_VEC(_v);							\
    TEST_OK(GrB_Vector_extractElement(&r, _v, vind));			\
    SUBTEST_COND(r == s, "extracted not equal first set");		\
    TEST_OK(GrB_Vector_extractElement(&r, _v, vind + 1));		\
    SUBTEST_COND(r == s, "extracted not equal second set");

#ifdef NOT_YET_SUPPORTED
#define SET_AND_TEST_TBD						\
    GrB_Vector dupvec;							\
    TEST_OK(GrB_Vector_dup(&dupvec, vec));				\
    TEST_ELTS(dupvec);							\
    TEST_ELTS(vec);							\
    TEST_OK(GrB_Vector_free(&dupvec));					\
    SUBTEST_COND(!dupvec, "duplicated not freed");			\
    GrB_Vector buildvec;						\
    int opind = (i == 0) ? 271 : i - 1;					\
    GrB_BinaryOp binop; get_BinaryOp(opind, &binop);			\
    TEST_OK(GrB_Vector_new(&buildvec, thetype, sz));			\
    TEST_OK(GrB_Vector_build(buildvec, I, X, nv, binop));		\
    TEST_ELTS(buildvec);						\
    TEST_ELTS(vec);							\
    TEST_OK(GrB_Vector_free(&buildvec));				\
    SUBTEST_COND(!buildvec, "built not freed");
#else
#define SET_AND_TEST_TBD
#endif    

#define SET_AND_TEST							\
    TEST_OK(GrB_Vector_new(&vec, thetype, sz));				\
    TEST_VEC(vec);							\
    TEST_OK(GrB_Vector_setElement(vec, s, vind));			\
    TEST_OK(GrB_Vector_setElement(vec, s, vind + 1));			\
    nv += 2; TEST_ELTS(vec);						\
    sz++; TEST_OK(GxB_Vector_resize(vec, sz));				\
    TEST_ELTS(vec);							\
    TEST_OK(GrB_Vector_extractTuples(NULL, X, &nv, vec));		\
    bool vtest = ((X[0] == r) && (X[1] == r));				\
    SUBTEST_COND(vtest, "extracted tuples not correct");		\
    TEST_OK(GrB_Vector_extractTuples(I, X, &nv, vec));			\
    vtest = ((X[0] == r) && (X[1] == r) &&				\
    	     (I[0] == vind) && (I[1] == vind + 1));			\
    SUBTEST_COND(vtest, "extracted tuples not correct");		\
    X = NULL;								\
    TEST_OK(GrB_Vector_extractTuples(I, X, &nv, vec));			\
    vtest = ((I[0] == vind) && (I[1] == vind + 1));			\
    SUBTEST_COND(vtest, "extracted tuples not correct");		\
    SET_AND_TEST_TBD;							\
    TEST_OK(GrB_Vector_clear(vec));					\
    nv = 0; TEST_VEC(vec);						\
    TEST_OK(GrB_Vector_free(&vec));					\
    SUBTEST_COND(!vec, "vector not freed");

    if (thetype == GrB_BOOL) {
      bool r = 0, s = true, *X = (bool *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_INT8) {
      int8_t r = 0, s = (int8_t)sval, *X = (int8_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_UINT8) {
      uint8_t r = 0, s = (uint8_t)sval, *X = (uint8_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_INT16) {
      int16_t r = 0, s = (int16_t)sval, *X = (int16_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_UINT16) {
      uint16_t r = 0, s = (uint16_t)sval, *X = (uint16_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_INT32) {
      int32_t r = 0, s = (int32_t)sval, *X = (int32_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_UINT32) {
      uint32_t r = 0, s = (uint32_t)sval, *X = (uint32_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_INT64) {
      int64_t r = 0, s = (int64_t)sval, *X = (int64_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_UINT64) {
      uint64_t r = 0, s = (uint64_t)sval, *X = (uint64_t *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_FP32) {
      float r = 0, s = (float)sval, *X = (float *)Xspace; SET_AND_TEST;
    } else if (thetype == GrB_FP64) {
      double r = 0, s = (double)sval, *X = (double *)Xspace; SET_AND_TEST;
    } else { printf("bad type,\n"); exit(1); }
    char tout[64];
    sprintf(tout, "unit test vector built-in type %d", i);
    TEST_COND(testok, tout);
  }

#ifdef NOT_YET_SUPPORTED
  // test with user-defined type
  info = GrB_SUCCESS; // reset for next sub-test
  bool testok = true;
  GrB_Vector vec;
  GrB_Type vtype, thetype;
  GrB_Index vsize, nvals, sz = 8, nv = 0;
  TEST_OK(GrB_Type_new (&thetype, sizeof(wildtype)));
  TEST_OK(GrB_Vector_new(&vec, thetype, sz));
  TEST_VEC(vec);
  TEST_OK(GrB_Vector_free(&vec));
  SUBTEST_COND(!vec, "User-defined not freed");
  TEST_COND(testok, "unit test vector user-defined type");
#endif

  free(I); free(Xspace);
  OK(GrB_finalize());
  return testerror;
}
