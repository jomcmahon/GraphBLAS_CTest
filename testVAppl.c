/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Vector apply for all types, IDENTITY unary op
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_VAppl(testargs *myargs)
{
  GrB_UnaryOp unop; get_UnaryOp(myargs->specobj[UNOP], &unop);
  if (!unop) return false; // required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(unop, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Type xtype = NULL, ztype = NULL; // types defined by unary op
  TEST_OK(get_types_unop(unop, &xtype, &ztype));

  GrB_Vector A = NULL, C = NULL, M = NULL;
  GrB_Index vsize = 0;
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, ztype, &A));
  TEST_OK(GrB_Vector_size(&vsize, A));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, ztype, vsize)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C));

  TEST_OK(GrB_apply(C, M, accum, unop, A, desc)); // do the operation

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, ztype, C),
		 myargs->output); // test and print

  // free all data products
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  bool testerror = get_spec_list(myargs, UNOP, run_VAppl);

  OK(GrB_finalize());
  return testerror;
}
