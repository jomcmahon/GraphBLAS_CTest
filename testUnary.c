/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: unit tests for basic methods of unary operations
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

#define SUBTEST_COND(_c, _s) do \
    { if (!(_c)) { printf("%s\n", _s); testok = false; } } while (0)

#define TEST_COND(_c, _s) do { printf("%s: ", _s); if (_c) printf("PASSED\n"); \
    else { printf("FAILED\n"); testerror = true; } } while (0)

void f_un_b (void *z, const void *x) { *(bool *)z = *(bool *)x; }
void f_un_i8 (void *z, const void *x) { *(int8_t *)z = *(int8_t *)x; }
void f_un_u8 (void *z, const void *x) { *(uint8_t *)z = *(uint8_t *)x; }
void f_un_i16 (void *z, const void *x) { *(int16_t *)z = *(int16_t *)x; }
void f_un_u16 (void *z, const void *x) { *(uint16_t *)z = *(uint16_t *)x; }
void f_un_i32 (void *z, const void *x) { *(int32_t *)z = *(int32_t *)x; }
void f_un_u32 (void *z, const void *x) { *(uint32_t *)z = *(uint32_t *)x; }
void f_un_i64 (void *z, const void *x) { *(int64_t *)z = *(int64_t *)x; }
void f_un_u64 (void *z, const void *x) { *(uint64_t *)z = *(uint64_t *)x; }
void f_un_flt (void *z, const void *x) { *(float *)z = *(float *)x; }
void f_un_dbl (void *z, const void *x) { *(double *)z = *(double *)x; }

void get_UnaryOp_Type(int, GrB_Type *);

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

#define TEST_OP								\
    OK (GxB_UnaryOp_ztype(&ztype, unop));				\
    SUBTEST_COND(ztype == thetype, "Unary op ztypes don't match");	\
    OK (GxB_UnaryOp_xtype(&xtype, unop));				\
    SUBTEST_COND(xtype == thetype, "Unary op xtypes don't match");

  // test type methods of 67 built-in UnaryOps
  for (int i = 0; i < num_UnaryOps(); i++) { // unary op loop
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type xtype, ztype, thetype; get_UnaryOp_Type(i, &thetype);
    GrB_UnaryOp unop; get_UnaryOp(i, &unop);

    TEST_OP;
    char tout[64];
    sprintf(tout, "unit test built-in unary operator %d", i);
    TEST_COND(testok, tout);
  }

#ifdef NOT_YET_SUPPORTED
  // user-defined UnaryOp, all types
  for (int i = 0; i < num_Types(); i++) { // all types
    info = GrB_SUCCESS; // reset for next sub-test
    bool testok = true;
    GrB_Type xtype, ztype, thetype; get_UnaryOp_Type(i, &thetype); // pick type
    GrB_UnaryOp unop;
    void (*f) (void *, const void *);

#define SET_AND_TEST						\
    OK (GrB_UnaryOp_new (&unop, f, thetype, thetype));	\
    TEST_OP;							\
    OK (GrB_UnaryOp_free(&unop));				\
    SUBTEST_COND(!unop, "User-defined unary op not freed");
    
    if (thetype == GrB_BOOL) { f = f_un_b; SET_AND_TEST; }
    else if (thetype == GrB_INT8) { f = f_un_i8; SET_AND_TEST; }
    else if (thetype == GrB_UINT8) { f = f_un_u8; SET_AND_TEST; }
    else if (thetype == GrB_INT16) { f = f_un_i16; SET_AND_TEST; }
    else if (thetype == GrB_UINT16) { f = f_un_u16; SET_AND_TEST; }
    else if (thetype == GrB_INT32) { f = f_un_i32; SET_AND_TEST; }
    else if (thetype == GrB_UINT32) { f = f_un_u32; SET_AND_TEST; }
    else if (thetype == GrB_INT64) { f = f_un_i64; SET_AND_TEST; }
    else if (thetype == GrB_UINT64) { f = f_un_u64; SET_AND_TEST; }
    else if (thetype == GrB_FP32) { f = f_un_flt; SET_AND_TEST; }
    else if (thetype == GrB_FP64) { f = f_un_dbl; SET_AND_TEST; }
    else { printf("bad type,\n"); exit(1); }

    char tout[64];
    sprintf(tout, "unit test user-defined unary operator type %d", i);
    TEST_COND(testok, tout);
  }
#endif

  OK(GrB_finalize());
  return testerror;
}
