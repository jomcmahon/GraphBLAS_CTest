/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Row subassign for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_RSubA(testargs *myargs)
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
  GrB_Index *J = NULL, nj = 0; // index vector
  TEST_OK(read_test_index(myargs->inbase, myargs->input1, &J, &nj));

  GrB_Matrix C = NULL; // inputs and outputs
  GrB_Vector A = NULL, M = NULL;
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, thetype, &A));
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  TEST_OK(GxB_subassign(C, M, accum, A, 0, J, nj, desc)); // do operation, row 0

  if (myargs->generate) { // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, thetype, C));
  } else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, thetype,
				      C), myargs->output); // test and print

  // free the inputs and outputs
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  if (J != GrB_ALL) free(J);
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_RSubA);
}
