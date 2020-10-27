/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Column extract for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_CExtr(testargs *myargs)
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

  GrB_Matrix A = NULL; // inputs and outputs
  GrB_Vector C = NULL, M = NULL;
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input0, thetype, &A));

  GrB_Index nrA = 0, ncA = 0; // rows and columns of inputs
  GrB_Index *I = NULL, ni = 0; // default for GrB_ALL
  TEST_OK(get_inp_size(desc, A, &nrA, &ncA, GrB_INP0)); // input0
  TEST_OK(read_test_index(myargs->inbase, myargs->input1, &I, &ni));

  GrB_Index outsize = get_index_size(I, ni, nrA); // size of column

  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, thetype, outsize)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, thetype, &C));

  // do the operation
  TEST_OK(GrB_extract(C, M, accum, A, I, ni, 0, desc)); // column 0

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, thetype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, thetype,
				    C), myargs->output); // test and print

  // free all data products
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  if (I != GrB_ALL) free(I);
  return testerror;
}

void default_spec(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "A_row");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
}

void default_specA(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "ALL");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CA");
}

void default_specR(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_RANGE");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CR");
}

void default_specS(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_STRIDE");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CS");
}

void default_specB(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
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

  testerror = test_L_DA_loop(myargs, TYPE, specptr, run_CExtr);
  testerror |= test_L_DA_loop(&myargsA, TYPE, specptrA, run_CExtr);
  testerror |= test_L_DA_loop(&myargsR, TYPE, specptrR, run_CExtr);
  testerror |= test_L_DA_loop(&myargsS, TYPE, specptrS, run_CExtr);
  testerror |= test_L_DA_loop(&myargsB, TYPE, specptrB, run_CExtr);

  OK(GrB_finalize());
  return testerror;
}
