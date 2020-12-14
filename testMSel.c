/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test Matrix select for all types, GT_ZERO select op
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_MSel(testargs *myargs)
{
  GrB_Info info;
  GxB_SelectOp selop; get_SelectOp(myargs->specobj[SELOP], &selop);
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);
  GxB_Scalar scal = NULL; // thunk

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(thetype, GxB_SUMMARY));
    OK (GxB_print(selop, GxB_SUMMARY));
  }

  GrB_Matrix A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Vector T = NULL;
  GrB_Index nrA = 0, ncA = 0;
  read_matlab_matrix(myargs->inbase, myargs->input0, thetype, &A);
  if (strlen(myargs->input1) > 0) {
    read_matlab_vector(myargs->inbase, myargs->input1, thetype, &T); // thunk
    OK (GxB_Scalar_new(&scal, thetype));
  }
  get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0, no desc
  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  // if initvals file supplied, initialize, otherwise empty matrix
  if (strlen(myargs->initvals) == 0) OK (GrB_Matrix_new(&C, thetype, nrA, ncA));
  else read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C);

#define SET_AND_TEST				\
  OK (GrB_Vector_extractElement(&c, T, 0));	\
  OK (GxB_Scalar_setElement(scal, c));

  if (T) { // set thunk based on type
    if (thetype == GrB_BOOL) { bool c; SET_AND_TEST; }
    else if (thetype == GrB_INT8) { int8_t c; SET_AND_TEST; }
    else if (thetype == GrB_INT16) { int16_t c; SET_AND_TEST; }
    else if (thetype == GrB_INT32) { int32_t c; SET_AND_TEST; }
    else if (thetype == GrB_INT64) { int64_t c; SET_AND_TEST; }
    else if (thetype == GrB_UINT8) { uint8_t c; SET_AND_TEST; }
    else if (thetype == GrB_UINT16) { uint16_t c; SET_AND_TEST; }
    else if (thetype == GrB_UINT32) { uint32_t c; SET_AND_TEST; }
    else if (thetype == GrB_UINT64) { uint64_t c; SET_AND_TEST; }
    else if (thetype == GrB_FP32) { float c; SET_AND_TEST; }
    else if (thetype == GrB_FP64) { double c; SET_AND_TEST; }
    else { printf("bad type\n"); exit(1); }
  }

  OK (GxB_select(C, M, accum, selop, A, scal, desc)); // do the operation

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_matrix(myargs->testbase, myargs->output, C);
  else testerror = check_typed_matrix(myargs->testbase, myargs->output, C);

  // free all data products
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  return testerror;
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_MSel);
}
