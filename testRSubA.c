/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test Row subassign for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_RSubA(testargs *myargs)
{
  GrB_Info info;
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(thetype, GxB_SUMMARY));
  }

  GrB_Matrix C = NULL; // inputs and outputs
  GrB_Vector A = NULL, M = NULL;
  GrB_Index *I = NULL, ni = 0, *J = NULL, nj = 0; // index vectors
  read_matlab_vector(myargs->inbase, myargs->input0, thetype, &A);
  read_test_index(myargs->inbase, myargs->input1, &I, &ni);
  read_test_index(myargs->inbase, myargs->input2, &J, &nj);
  GrB_Index rval = I[0]; // row to assign

  if (strlen(myargs->initvals) == 0) { // initvals file name
    GrB_Index nc = 0;
    OK (GrB_Vector_size(&nc, A));
    GrB_Index outR = rval + 1; // minimum size possible
    GrB_Index outC = get_index_dim(J, nj, nc);
    OK (GrB_Matrix_new(&C, thetype, outR, outC)); // assume sorted
  } else // read initvals if file name specified
    read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C);

  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  OK (GxB_subassign(C, M, accum, A, rval, J, nj, desc)); // do operation

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_matrix(myargs->testbase, myargs->output, C);
  else testerror = check_typed_matrix(myargs->testbase, myargs->output, C);

  // free the inputs and outputs
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  if (J != GrB_ALL) free(J);
  return testerror; // false means no error
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_RSubA);
}
