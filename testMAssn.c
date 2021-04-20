/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test Matrix assign for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_MAssn(testargs *myargs)
{
  GrB_Info info;
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (!thetype) get_User_Type(&thetype);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    OK (GxB_print(thetype, GxB_SUMMARY));
  }

  GrB_Matrix A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Index *I = NULL, ni = 0, *J = NULL, nj = 0; // index vectors
  read_matlab_matrix(myargs->inbase, myargs->input0, thetype, &A);
  read_test_index(myargs->inbase, myargs->input1, &I, &ni);
  read_test_index(myargs->inbase, myargs->input2, &J, &nj);

  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  if (strlen(myargs->initvals) == 0) { // initvals file name
    GrB_Index outR = 0, outC = 0;
    if (M) { OK (GrB_Matrix_nrows(&outR, M)); OK (GrB_Matrix_ncols(&outC, M)); }
    else {
      GrB_Index nrA = 0, ncA = 0;
      get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0, no desc
      outR = get_index_dim(I, ni, nrA);
      outC = get_index_dim(J, nj, ncA);
    }
    OK (GrB_Matrix_new(&C, thetype, outR, outC)); // assume sorted
  } else // read initvals if file name specified
    read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C);

  OK (GrB_assign(C, M, accum, A, I, ni, J, nj, desc)); // do operation

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_matrix(myargs->testbase, myargs->output, C);
  else testerror = check_typed_matrix(myargs->testbase, myargs->output, C);

  // free the inputs and outputs
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  if (I != GrB_ALL) free(I);
  if (J != GrB_ALL) free(J);
  return testerror; // false means no error
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_MAssn);
}
