/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test eWiseAdd matrix: ANY_PAIR_BOOL semi or PLUS binop, 4 desc
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_eAddM(testargs *myargs)
{
  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_BinaryOp binop; get_BinaryOp(myargs->specobj[BINOP], &binop);
  GrB_Monoid mon; get_Monoid(myargs->specobj[MON], &mon);
  GrB_Semiring semi; get_Semiring(myargs->specobj[SEMI], &semi);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if ((!binop) && (!mon) && (!semi)) return false; // must have one of these
  if (semi) TEST_OK(GxB_Semiring_add(&mon, semi));
  if (mon) TEST_OK(GxB_Monoid_operator(&binop, mon));

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    if (semi) GxB_print(semi, GxB_SUMMARY);
    else if (mon) GxB_print(mon, GxB_SUMMARY);
    else GxB_print(binop, GxB_SUMMARY);
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // binary op defines type
  TEST_OK(get_types_binop(binop, &xtype, &ytype, &ztype));

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
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, ztype,
			       &C));

  if (semi) TEST_OK(GrB_eWiseAdd(C, M, accum, semi, A, B, desc));
  else if (mon) TEST_OK(GrB_eWiseAdd(C, M, accum, mon, A, B, desc));
  else TEST_OK(GrB_eWiseAdd(C, M, accum, binop, A, B, desc));

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, ztype, C),
		 myargs->output); // otherwise, test and print result

  // free the inputs and outputs
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&B)); TEST_OK(GrB_free (&C));
  if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_eAddM);
}
