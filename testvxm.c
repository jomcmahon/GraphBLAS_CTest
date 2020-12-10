/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test vxm: default ANY_PAIR_BOOL or PLUS_TIMES, four descriptors
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_vxm(testargs *myargs)
{
  GrB_Info info;
  GrB_Semiring semi; get_Semiring(myargs->specobj[SEMI], &semi);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(semi, GxB_SUMMARY));
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // semiring defines type
  get_types_semiring(semi, &xtype, &ytype, &ztype);

  GrB_Vector A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Matrix B = NULL;
  read_matlab_vector(myargs->inbase, myargs->input0, xtype, &A);
  read_matlab_matrix(myargs->inbase, myargs->input1, ytype, &B);
  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  GrB_Index nrB, ncB; // rows and columns of input
  get_inp_size(desc, B, &nrB, &ncB, GrB_INP1); // input 1

  // if initvals file supplied, initialize, otherwise empty matrix
  if (strlen(myargs->initvals) == 0) OK (GrB_Vector_new(&C, ztype, ncB));
  else read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C);

  OK (GrB_vxm(C, M, accum, semi, A, B, desc)); // do the operation

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_vector(myargs->testbase, myargs->output, C);
  else testerror = check_typed_vector(myargs->testbase, myargs->output, C);

  OK (GrB_free (&C)); OK (GrB_free(&A)); OK (GrB_free(&B));
  if (M) OK (GrB_free(&M)); // free all matrices

  return testerror; // false means no error
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_vxm);
}
