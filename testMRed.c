/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test Matrix reduce op for all types, MIN binary op
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_MRed(testargs *myargs)
{
  GrB_Info info;
  GrB_BinaryOp binop; get_BinaryOp(myargs->specobj[BINOP], &binop);
  GrB_Monoid mon; get_Monoid(myargs->specobj[MON], &mon);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    if (mon) OK (GxB_print(mon, GxB_SUMMARY));
    else OK (GxB_print(binop, GxB_SUMMARY));
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // types defined by ops
  if (mon) get_types_monoid(mon, &xtype, &ytype, &ztype);
  else get_types_binop(binop, &xtype, &ytype, &ztype);

  GrB_Matrix A = NULL;
  GrB_Vector C = NULL, M = NULL;
  read_matlab_matrix(myargs->inbase, myargs->input0, ztype, &A);
  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  GrB_Index nrA = 0, ncA = 0;
  get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0

  // if initvals file supplied, initialize, otherwise empty matrix
  if (strlen(myargs->initvals) == 0) OK (GrB_Vector_new(&C, ztype, nrA));
  else read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C);

  if (mon) OK (GrB_reduce(C, M, accum, mon, A, desc)); // do the operation
  else OK (GrB_reduce(C, M, accum, binop, A, desc));

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_vector(myargs->testbase, myargs->output, C);
  else testerror = check_typed_vector(myargs->testbase, myargs->output, C);

  // free all data products
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_MRed);
}
