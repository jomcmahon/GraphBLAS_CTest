/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Vector extract for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_VExtr(testargs *myargs)
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

  GrB_Vector A = NULL, C = NULL, M = NULL; // inputs and outputs
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, thetype, &A));

  GrB_Index vsize = 0, *I = NULL, ni = 0; // default for GrB_ALL
  TEST_OK(GrB_Vector_size(&vsize, A)); // default for GrB_ALL
  TEST_OK(read_test_index(myargs->inbase, myargs->input1, &I, &ni));

  GrB_Index outsize = get_index_size(I, ni, vsize);

  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, thetype, outsize)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, thetype, &C));

  TEST_OK(GrB_extract(C, M, accum, A, I, ni, desc)); // do the operation

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, thetype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, thetype,
				    C), myargs->output); // test and print

  // free all data products
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  if (I != GrB_ALL) free(I);
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_VExtr);
}
