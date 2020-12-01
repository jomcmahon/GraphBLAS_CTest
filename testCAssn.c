/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Column assign for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_CAssn(testargs *myargs)
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

  GrB_Matrix C = NULL; // inputs and outputs
  GrB_Vector A = NULL, M = NULL;
  GrB_Index *I = NULL, *J = NULL, ni = 0, nj = 0; // index vectors
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, thetype, &A));
  TEST_OK(read_test_index(myargs->inbase, myargs->input1, &I, &ni));
  TEST_OK(read_test_index(myargs->inbase, myargs->input2, &J, &nj));
  GrB_Index cval = J[0]; // column to assign

  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  if (strlen(myargs->initvals) == 0) { // initvals file name
    GrB_Index outR = 0;
    if (M) TEST_OK(GrB_Vector_size(&outR, M));
    else {
      GrB_Index nr = 0;
      GrB_Vector_size(&nr, A);
      outR = get_index_dim(I, ni, nr);
    }
    GrB_Index outC = cval + 1; // minimum size possible
    TEST_OK(GrB_Matrix_new(&C, thetype, outR, outC)); // assume sorted
  } else // read initvals if file name specified
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C));

  TEST_OK(GrB_assign(C, M, accum, A, I, ni, cval, desc)); // do operation

  if (myargs->generate) { // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, thetype, C));
  } else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, thetype,
				      C), myargs->output); // test and print

  // free the inputs and outputs
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  if (I != GrB_ALL) free(I);
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_CAssn);
}
