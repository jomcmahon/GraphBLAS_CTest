/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Matrix apply for all types, IDENTITY unary op
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_MAppl(testargs *myargs)
{
  GrB_Info info;
  GrB_UnaryOp unop; get_UnaryOp(myargs->specobj[UNOP], &unop);
  GrB_BinaryOp binop; get_BinaryOp(myargs->specobj[BINOP], &binop);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    if (unop) OK (GxB_print(unop, GxB_SUMMARY));
    else OK (GxB_print(binop, GxB_SUMMARY));
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // types defined by ops
  if (unop) get_types_unop(unop, &xtype, &ztype);
  else get_types_binop(binop, &xtype, &ytype, &ztype);

  GrB_Matrix A = NULL, C = NULL, M = NULL;
  GrB_Index nrA = 0, ncA = 0;
  read_matlab_matrix(myargs->inbase, myargs->input0, xtype, &A);
  get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0, no desc
  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  // if initvals file supplied, initialize, otherwise empty matrix
  if (strlen(myargs->initvals) == 0) OK (GrB_Matrix_new(&C, ztype, nrA, ncA));
  else read_matlab_matrix(myargs->inbase, myargs->initvals, ztype, &C);

  if (unop) OK (GrB_apply(C, M, accum, unop, A, desc)); // do the operation
  else { // create scalar of type and do 1st and 2nd
#ifdef NOT_YET_SUPPORTED
    GxB_Scalar scal;
    OK (GxB_Scalar_new(&scal, xtype));
    OK (GxB_Scalar_setElement(scal, 0));
    OK (GrB_apply(C, M, accum, binop, scal, A, desc));
    OK (GxB_Scalar_new(&scal, ytype));
    OK (GxB_Scalar_setElement(scal, 0));
    OK (GrB_apply(C, M, accum, binop, A, scal, desc));
#else
    return false;
#endif
  }

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_matrix(myargs->testbase, myargs->output, C);
  else testerror = check_typed_matrix(myargs->testbase, myargs->output, C);

  // free all data products
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_MAppl);
}
