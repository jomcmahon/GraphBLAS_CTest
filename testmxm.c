/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test mxm: default ANY_PAIR_BOOL or PLUS_TIMES, four descriptors
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_mxm(testargs *myargs)
{
  GrB_Info info;
  GrB_Semiring semi; get_Semiring(myargs->specobj[SEMI], &semi);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (!semi) get_User_Semiring(&semi);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(semi, GxB_SUMMARY));
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // semiring defines type
  get_types_semiring(semi, &xtype, &ytype, &ztype);

  GrB_Matrix A = NULL, B = NULL, C = NULL, M = NULL; // inputs and outputs
  read_matlab_matrix(myargs->inbase, myargs->input0, xtype, &A);
  read_matlab_matrix(myargs->inbase, myargs->input1, ytype, &B);
  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  GrB_Index nrA = 0, ncA = 0, nrB = 0, ncB = 0; // rows and columns of inputs
  get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0
  get_inp_size(desc, B, &nrB, &ncB, GrB_INP1); // input 1

  // if initvals file supplied, initialize, otherwise empty matrix
  if (strlen(myargs->initvals) == 0) OK (GrB_Matrix_new(&C, ztype, nrA, ncB));
  else read_matlab_matrix(myargs->inbase, myargs->initvals, ztype, &C);

  OK (GrB_mxm(C, M, accum, semi, A, B, desc)); // do the operation

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_matrix(myargs->testbase, myargs->output, C);
  else testerror = check_typed_matrix(myargs->testbase, myargs->output, C);

  OK (GrB_free (&C)); OK (GrB_free(&A)); OK (GrB_free(&B));
  if (M) OK (GrB_free(&M)); // free all matrices

  return testerror; // false means no error
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_mxm);
}
