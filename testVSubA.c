/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test Vector subassign for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_VSubA(testargs *myargs)
{
  GrB_Info info;
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(thetype, GxB_SUMMARY));
  }

  GrB_Vector A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Index *I = NULL, ni = 0; // index vector
  read_matlab_vector(myargs->inbase, myargs->input0, thetype, &A);
  read_test_index(myargs->inbase, myargs->input1, &I, &ni);

  if (strlen(myargs->initvals) == 0) { // initvals file name
    GrB_Index vsize = 0;
    OK (GrB_Vector_size(&vsize, A));
    GrB_Index outS = get_index_dim(I, ni, vsize);
    OK (GrB_Vector_new(&C, thetype, outS)); // assume sorted
  } else // read initvals if file name specified
    read_matlab_vector(myargs->inbase, myargs->initvals, thetype, &C);

  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  OK (GxB_subassign(C, M, accum, A, I, ni, desc)); // do the operation

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_vector(myargs->testbase, myargs->output, C);
  else testerror = check_typed_vector(myargs->testbase, myargs->output, C);

  // free the inputs and outputs
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  if (I != GrB_ALL) free(I);
  return testerror; // false means no error
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_VSubA);
}
