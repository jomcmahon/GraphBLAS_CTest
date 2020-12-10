/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Matrix transpose for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_tran(testargs *myargs)
{
  GrB_Info info;
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(thetype, GxB_SUMMARY));
  }

  GrB_Matrix A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Index nrA = 0, ncA = 0;
  read_matlab_matrix(myargs->inbase, myargs->input0, thetype, &A);
  get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0, no desc
  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  // if initvals file supplied, initialize, otherwise empty matrix
  if (strlen(myargs->initvals) == 0) OK (GrB_Matrix_new(&C, thetype, nrA, ncA));
  else read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C);

  OK (GrB_transpose(C, M, accum, A, desc)); // do the operation

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_matrix(myargs->testbase, myargs->output, C);
  else testerror = check_typed_matrix(myargs->testbase, myargs->output, C);

  // free all data products
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_tran);
}
