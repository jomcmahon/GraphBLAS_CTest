/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: unit tests for basic methods of matrices
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
  GrB_Index *J = malloc(2 * sizeof(*J));
  double *Xspace = malloc(2 * sizeof(*Xspace));
  for (int i = 0; i < num_Types(); i++) { // type loop
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type mtype, thetype; get_Type(i, &thetype); // pick type
    GrB_Matrix mat;
    GrB_Index nrows, ncols, nvals, nr = 3, nc = 4, rind = 1, cind = 2, nv = 0;
    int8_t sval = 10;

#define TEST_MAT(_m)							\
    TEST_OK(GrB_Matrix_nrows(&nrows, mat));				\
    SUBTEST_COND(nr == nrows, "matrix rows not equal");			\
    TEST_OK(GrB_Matrix_ncols(&ncols, mat));				\
    SUBTEST_COND(nc == ncols, "matrix columns not equal");		\
    TEST_OK(GrB_Matrix_nvals(&nvals, mat));				\
    SUBTEST_COND(nv == nvals, "matrix values not equal");		\
    TEST_OK(GxB_Matrix_type(&mtype, mat));				\
    SUBTEST_COND(thetype == mtype, "matrix types not equal");

#define TEST_ELTS(_m)							\
    TEST_MAT(_m);							\
    TEST_OK(GrB_Matrix_extractElement(&r, _m, rind, cind));		\
    SUBTEST_COND(r == s, "extracted not equal set: first");		\
    TEST_OK(GrB_Matrix_extractElement(&r, _m, rind + 1, cind + 1));	\
    SUBTEST_COND(r == s, "extracted not equal set: second");

#ifdef NOT_YET_SUPPORTED
#define SET_AND_TEST_TBD						\
    GrB_Matrix dupmat;							\
    TEST_OK(GrB_Matrix_dup(&dupmat, mat));				\
    TEST_ELTS(dupmat);							\
    TEST_ELTS(mat);							\
    TEST_OK(GrB_Matrix_free(&dupmat));					\
    SUBTEST_COND(!dupmat, "duplicated not freed");			\
    GrB_Matrix buildmat;						\
    int opind = (i == 0) ? 271 : i - 1;					\
    GrB_BinaryOp binop; get_BinaryOp(opind, &binop);			\
    TEST_OK(GrB_Matrix_new(&buildmat, thetype, nr, nc));		\
    TEST_OK(GrB_Matrix_build(buildmat, I, J, X, nv, binop));		\
    TEST_ELTS(buildmat);						\
    TEST_ELTS(mat);							\
    TEST_OK(GrB_Matrix_free(&buildmat));				\
    SUBTEST_COND(!buildmat, "built not freed");
#else
#define SET_AND_TEST_TBD
#endif

#define SET_AND_TEST							\
    TEST_OK(GrB_Matrix_new(&mat, thetype, nr, nc));			\
    TEST_MAT(mat);							\
    TEST_OK(GrB_Matrix_setElement(mat, s, rind, cind));			\
    TEST_OK(GrB_Matrix_setElement(mat, s, rind + 1, cind + 1));		\
    nv += 2; TEST_ELTS(mat);						\
    nr++; nc++;	TEST_OK(GxB_Matrix_resize(mat, nr, nc));		\
    TEST_ELTS(mat);							\
    TEST_OK(GrB_Matrix_extractTuples(NULL, NULL, X, &nv, mat));		\
    bool vtest = ((X[0] == r) && (X[1] == r));				\
    SUBTEST_COND(vtest, "extracted tuples not correct");		\
    TEST_OK(GrB_Matrix_extractTuples(NULL, J, X, &nv, mat));		\
    vtest = ((X[0] == r) && (X[1] == r) && (J[0] == cind) &&		\
	     (J[1] == cind + 1));					\
    SUBTEST_COND(vtest, "extracted tuples not correct");		\
    TEST_OK(GrB_Matrix_extractTuples(I, J, X, &nv, mat));		\
    vtest = ((X[0] == r) && (I[0] == rind) && (I[1] == rind + 1) &&	\
	     (X[1] == r) && (J[0] == cind) && (J[1] == cind + 1));	\
    SUBTEST_COND(vtest, "extracted tuples not correct");		\
    X = NULL;								\
    TEST_OK(GrB_Matrix_extractTuples(I, J, X, &nv, mat));		\
    vtest = ((I[0] == rind) && (I[1] == rind + 1) && (J[0] == cind) &&	\
	     (J[1] == cind + 1));					\
    SUBTEST_COND(vtest, "extracted tuples not correct");		\
    SET_AND_TEST_TBD;							\
    TEST_OK(GrB_Matrix_clear(mat));					\
    nv = 0; TEST_MAT(mat);						\
    TEST_OK(GrB_Matrix_free(&mat));					\
    SUBTEST_COND(!mat, "matrix not freed");

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
    sprintf(tout, "unit test matrix built-in type %d", i);
    TEST_COND(testok, tout);
  }

#ifdef NOT_YET_SUPPORTED
  // test with user-defined type
  info = GrB_SUCCESS; // reset for next sub-test
  bool testok = true;
  GrB_Matrix mat;
  GrB_Type mtype, thetype;
  GrB_Index nrows, ncols, nvals, nr = 3, nc = 4, nv = 0;
  TEST_OK(GrB_Type_new (&thetype, sizeof(wildtype)));
  TEST_OK(GrB_Matrix_new(&mat, thetype, nr, nc));
  TEST_MAT(mat);
  TEST_OK(GrB_Matrix_free(&mat));
  SUBTEST_COND(!mat, "User-defined not freed");
  TEST_COND(testok, "unit test matrix user-defined type");
#endif

  OK(GrB_finalize());
  free(I); free(J); free(Xspace);
  return testerror;
}
