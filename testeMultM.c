/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test eWiseMult matrix for all types, ANY binop
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_eMultM(testargs *myargs)
{
  GrB_Info info;
  GrB_BinaryOp binop; get_BinaryOp(myargs->specobj[BINOP], &binop);
  GrB_Monoid mon; get_Monoid(myargs->specobj[MON], &mon);
  GrB_Semiring semi; get_Semiring(myargs->specobj[SEMI], &semi);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (semi) OK (GxB_Semiring_multiply(&binop, semi));
  else if (mon) OK (GxB_Monoid_operator(&binop, mon));
  if (!binop) get_User_BinaryOp(&binop);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    if (semi) OK (GxB_print(semi, GxB_SUMMARY));
    else if (mon) OK (GxB_print(mon, GxB_SUMMARY));
    else OK (GxB_print(binop, GxB_SUMMARY));
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // binary op defines type
  get_types_binop(binop, &xtype, &ytype, &ztype);

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

  if (semi) OK (GrB_eWiseMult(C, M, accum, semi, A, B, desc));
  else if (mon) OK (GrB_eWiseMult(C, M, accum, mon, A, B, desc));
  else OK (GrB_eWiseMult(C, M, accum, binop, A, B, desc));

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_matrix(myargs->testbase, myargs->output, C);
  else testerror = check_typed_matrix(myargs->testbase, myargs->output, C);

  OK (GrB_free(&C)); OK (GrB_free(&A)); OK (GrB_free(&B));
  if (M) OK (GrB_free(&M)); // free all matrices

  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_eMultM);
}
