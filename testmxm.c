/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test mxm: default ANY_PAIR_BOOL or PLUS_TIMES, four descriptors
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"
#include "gen_default.h"

bool run_mxm(testargs *myargs)
{
  GrB_Semiring semi; get_Semiring(myargs->specobj[SEMI], &semi);
  if (!semi) return false; // required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(semi, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // semiring defines type
  TEST_OK(get_types_semiring(semi, &xtype, &ytype, &ztype));

  GrB_Matrix A = NULL, B = NULL, C = NULL, M = NULL; // inputs and outputs
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input0, xtype, &A));
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input1, ytype, &B));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  GrB_Index nrA = 0, ncA = 0, nrB = 0, ncB = 0; // rows and columns of inputs
  TEST_OK(get_inp_size(desc, A, &nrA, &ncA, GrB_INP0)); // input 0
  TEST_OK(get_inp_size(desc, B, &nrB, &ncB, GrB_INP1)); // input 1

  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Matrix_new(&C, ztype, nrA, ncB)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, ztype, &C));

  TEST_OK(GrB_mxm(C, M, accum, semi, A, B, desc)); // do the operation

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, ztype,
				    C), myargs->output); // test and print

  TEST_OK(GrB_free (&C)); // free all matrices
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&B)); if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  matmul_defs(myargs, "A", "B", "M", "A");

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  bool testerror = get_spec_list(myargs, SEMI, run_mxm);

  OK(GrB_finalize());
  return testerror;
}
