/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Vector assign type for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_VTAssn(testargs *myargs)
{
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  if (!thetype) return false; // required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(thetype, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Index *I = NULL, ni = 0; // index vector
  TEST_OK(read_test_index(myargs->inbase, myargs->input1, &I, &ni));

  GrB_Vector C = NULL, M = NULL; // inputs and outputs
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, thetype, &C));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));

#define SET_AND_TEST \
  TEST_OK(GrB_assign(C, M, accum, c, I, ni, desc)); // do the operation

  // call based on type
  if (thetype == GrB_BOOL) { bool c = false; SET_AND_TEST; }
  else if (thetype == GrB_INT8) { int8_t c = INT8_MAX; SET_AND_TEST; }
  else if (thetype == GrB_INT16) { int16_t c = INT16_MAX; SET_AND_TEST; }
  else if (thetype == GrB_INT32) { int32_t c = INT32_MAX; SET_AND_TEST; }
  else if (thetype == GrB_INT64) { int64_t c = INT64_MAX; SET_AND_TEST; }
  else if (thetype == GrB_UINT8) { uint8_t c = UINT8_MAX; SET_AND_TEST; }
  else if (thetype == GrB_UINT16) { uint16_t c = UINT16_MAX; SET_AND_TEST; }
  else if (thetype == GrB_UINT32) { uint32_t c = UINT32_MAX; SET_AND_TEST; }
  else if (thetype == GrB_UINT64) { uint64_t c = UINT64_MAX; SET_AND_TEST; }
  else if (thetype == GrB_FP32) { float c = 1e6; SET_AND_TEST; }
  else if (thetype == GrB_FP64) { double c = 1e6; SET_AND_TEST; }
  else { printf("bad type\n"); exit(1); }

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, thetype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, thetype,
					C), myargs->output); // test and print

  // free the inputs and outputs
  TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  if (I != GrB_ALL) free(I);
  return testerror;
}

void default_spec(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "V1");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "V1_ind");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
}

void default_specA(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "V1");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "ALL");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CA");
}

void default_specR(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "V1");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_RANGE");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CR");
}

void default_specS(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "V1");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_STRIDE");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CS");
}

void default_specB(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "V1");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_BACK");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CB");
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  bool testerror = false;

  testargs myargsA, myargsR, myargsS, myargsB; // additions to default
  testargs *myargs = get_test_args(argc, argv);
  memcpy(&myargsA, myargs, sizeof(testargs));
  memcpy(&myargsR, myargs, sizeof(testargs));
  memcpy(&myargsS, myargs, sizeof(testargs));
  memcpy(&myargsB, myargs, sizeof(testargs));
  int **specptr = get_test_spec(myargs, default_spec);
  int **specptrA = get_test_spec(&myargsA, default_specA);
  int **specptrR = get_test_spec(&myargsR, default_specR);
  int **specptrS = get_test_spec(&myargsS, default_specS);
  int **specptrB = get_test_spec(&myargsB, default_specB);

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  testerror = test_L_DA_loop(myargs, TYPE, specptr, run_VTAssn);
  testerror |= test_L_DA_loop(&myargsA, TYPE, specptrA, run_VTAssn);
  testerror |= test_L_DA_loop(&myargsR, TYPE, specptrR, run_VTAssn);
  testerror |= test_L_DA_loop(&myargsS, TYPE, specptrS, run_VTAssn);
  testerror |= test_L_DA_loop(&myargsB, TYPE, specptrB, run_VTAssn);

  OK(GrB_finalize());
  return testerror;
}
