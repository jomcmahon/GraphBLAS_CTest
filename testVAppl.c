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
  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_UnaryOp unop; get_UnaryOp(myargs->specobj[UNOP], &unop);
  GrB_BinaryOp binop; get_BinaryOp(myargs->specobj[BINOP], &binop);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if ((!binop) && (!unop)) return false; // must have one of these

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    if (unop) GxB_print(unop, GxB_SUMMARY);
    else GxB_print(binop, GxB_SUMMARY);
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // types defined by ops
  if (unop) TEST_OK(get_types_unop(unop, &xtype, &ztype));
  else TEST_OK(get_types_binop(binop, &xtype, &ytype, &ztype));

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

  if (unop) TEST_OK(GrB_apply(C, M, accum, unop, A, desc)); // do the operation
  else { // create scalar of type and do 1st and 2nd
#ifdef NOT_YET_SUPPORTED
    GxB_Scalar scal;
    TEST_OK(GxB_Scalar_new(&scal, xtype));
    TEST_OK(GxB_Scalar_setElement(scal, 0));
    TEST_OK(GrB_apply(C, M, accum, binop, scal, A, desc));
    TEST_OK(GxB_Scalar_new(&scal, ytype));
    TEST_OK(GxB_Scalar_setElement(scal, 0));
    TEST_OK(GrB_apply(C, M, accum, binop, A, scal, desc));
#else
    return false;
#endif
  }

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
  return run_test(argc, argv, run_VAppl);
}
