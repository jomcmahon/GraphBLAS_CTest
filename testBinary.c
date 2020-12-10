/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: unit tests for basic methods of binary operations
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

#define SUBTEST_COND(_c, _s) do \
    { if (!(_c)) { printf("%s\n", _s); testok = false; } } while (0)

#define TEST_COND(_c, _s) do { printf("%s: ", _s); if (_c) printf("PASSED\n"); \
    else { printf("FAILED\n"); testerror = true; } } while (0)

void f_bin_b (void *z, const void *x, const void *y)
{ *(bool *)z = *(bool *)x + *(bool *)y; }
void f_bin_i8 (void *z, const void *x, const void *y)
{ *(int8_t *)z = *(int8_t *)x + *(int8_t *)y; }
void f_bin_u8 (void *z, const void *x, const void *y)
{ *(uint8_t *)z = *(uint8_t *)x + *(uint8_t *)y; }
void f_bin_i16 (void *z, const void *x, const void *y)
{ *(int16_t *)z = *(int16_t *)x + *(int16_t *)y; }
void f_bin_u16 (void *z, const void *x, const void *y)
{ *(uint16_t *)z = *(uint16_t *)x + *(uint16_t *)y; }
void f_bin_i32 (void *z, const void *x, const void *y)
{ *(int32_t *)z = *(int32_t *)x + *(int32_t *)y; }
void f_bin_u32 (void *z, const void *x, const void *y)
{ *(uint32_t *)z = *(uint32_t *)x + *(uint32_t *)y; }
void f_bin_i64 (void *z, const void *x, const void *y)
{ *(int64_t *)z = *(int64_t *)x + *(int64_t *)y; }
void f_bin_u64 (void *z, const void *x, const void *y)
{ *(uint64_t *)z = *(uint64_t *)x + *(uint64_t *)y; }
void f_bin_flt (void *z, const void *x, const void *y)
{ *(float *)z = *(float *)x + *(float *)y; }
void f_bin_dbl (void *z, const void *x, const void *y)
{ *(double *)z = *(double *)x + *(double *)y; }

void get_BinaryOp_inType(int, GrB_Type *);
void get_BinaryOp_outType(int, GrB_Type *);

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

#define TEST_OP								\
  OK (GxB_BinaryOp_ztype(&ztype, binop));				\
  SUBTEST_COND(ztype == outtype, "binary op ztypes don't match");	\
  OK (GxB_BinaryOp_xtype(&xtype, binop));				\
  SUBTEST_COND(xtype == intype, "binary op xtypes don't match");	\
  OK (GxB_BinaryOp_ytype(&ytype, binop));				\
  SUBTEST_COND(ytype == intype, "binary op ytypes don't match");

  // test type methods of 21 x 11 built-in UnaryOps
  for (int i = 0; i < num_BinaryOps(); i++) { // binary op loop
    info = GrB_SUCCESS; // reset for next subtest
    bool testok = true;
    GrB_Type ztype, xtype, ytype;
    GrB_Type intype; get_BinaryOp_inType(i, &intype);
    GrB_Type outtype; get_BinaryOp_outType(i, &outtype);
    GrB_BinaryOp binop; get_BinaryOp(i, &binop);

    TEST_OP;
    char tout[64];
    sprintf(tout, "unit test built-in binary operator %d", i);
    TEST_COND(testok, tout);
  }

#ifdef NOT_YET_SUPPORTED
  // user-defined BinaryOp, all types
  for (int i = 0; i < num_Types(); i++) { // all types
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type ztype, xtype, ytype;
    GrB_Type intype; get_Type(i, &intype); // pick type
    GrB_Type outtype; get_Type(i, &outtype); // pick type
    GrB_BinaryOp binop;
    void (*f) (void *, const void *, const void *);

#define SET_AND_TEST						     \
    OK (GrB_BinaryOp_new (&binop, f, outtype, intype, intype));  \
    TEST_OP;							     \
    OK (GrB_BinaryOp_free(&binop));				     \
    SUBTEST_COND(!binop, "User-defined binary op not freed");

    if (intype == GrB_BOOL) { f = f_bin_b; SET_AND_TEST; }
    else if (intype == GrB_INT8) { f = f_bin_i8; SET_AND_TEST; }
    else if (intype == GrB_UINT8) { f = f_bin_u8; SET_AND_TEST; }
    else if (intype == GrB_INT16) { f = f_bin_i16; SET_AND_TEST; }
    else if (intype == GrB_UINT16) { f = f_bin_u16; SET_AND_TEST; }
    else if (intype == GrB_INT32) { f = f_bin_i32; SET_AND_TEST; }
    else if (intype == GrB_UINT32) { f = f_bin_u32; SET_AND_TEST; }
    else if (intype == GrB_INT64) { f = f_bin_i64; SET_AND_TEST; }
    else if (intype == GrB_UINT64) { f = f_bin_u64; SET_AND_TEST; }
    else if (intype == GrB_FP32) { f = f_bin_flt; SET_AND_TEST; }
    else if (intype == GrB_FP64) { f = f_bin_dbl; SET_AND_TEST; }
    else { printf("bad type,\n"); exit(1); }

    char tout[64];
    sprintf(tout, "unit test user-defined binary operator type %d", i);
    TEST_COND(testok, tout);
  }
#endif

  OK(GrB_finalize());
  return testerror;
}
