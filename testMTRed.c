/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test Matrix reduce type for all types, ANY monoid
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_MTRed(testargs *myargs)
{
  GrB_Info info;
  GrB_Monoid mon; get_Monoid(myargs->specobj[MON], &mon);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(mon, GxB_SUMMARY));
  }

  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // types defined by monoid
  get_types_monoid(mon, &xtype, &ytype, &ztype);

  GrB_Matrix A = NULL; // inputs and outputs
  GrB_Vector C = NULL;
  read_matlab_matrix(myargs->inbase, myargs->input0, ztype, &A);

  // if initvals file supplied, initialize, otherwise empty matrix
  if (strlen(myargs->initvals) == 0) OK (GrB_Vector_new(&C, ztype, 1));
  else read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C);

#define SET_AND_TEST					\
  GrB_Vector_extractElement(&c, C, 0);			\
  OK (GrB_reduce(&c, accum, mon, A, desc));		\
  OK (GrB_Vector_setElement(C, c, 0));

  // call reduce based on type
  if (ztype == GrB_BOOL) { bool c; SET_AND_TEST; }
  else if (ztype == GrB_INT8) { int8_t c; SET_AND_TEST; }
  else if (ztype == GrB_INT16) { int16_t c; SET_AND_TEST; }
  else if (ztype == GrB_INT32) { int32_t c; SET_AND_TEST; }
  else if (ztype == GrB_INT64) { int64_t c; SET_AND_TEST; }
  else if (ztype == GrB_UINT8) { uint8_t c; SET_AND_TEST; }
  else if (ztype == GrB_UINT16) { uint16_t c; SET_AND_TEST; }
  else if (ztype == GrB_UINT32) { uint32_t c; SET_AND_TEST; }
  else if (ztype == GrB_UINT64) { uint64_t c; SET_AND_TEST; }
  else if (ztype == GrB_FP32) { float c; SET_AND_TEST; }
  else if (ztype == GrB_FP64) { double c; SET_AND_TEST; }
  else { printf("bad type\n"); exit(1); }

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_vector(myargs->testbase, myargs->output, C);
  else testerror = check_typed_vector(myargs->testbase, myargs->output, C);

  // free all data products
  OK (GrB_free(&A)); OK (GrB_free(&C));
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_MTRed);
}
