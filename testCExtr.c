/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test Column extract for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_CExtr(testargs *myargs)
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

  GrB_Matrix A = NULL; // inputs and outputs
  GrB_Vector C = NULL, M = NULL;
  GrB_Index *I = NULL, ni = 0, *J = NULL, nj = 0;
  read_matlab_matrix(myargs->inbase, myargs->input0, thetype, &A);
  read_test_index(myargs->inbase, myargs->input1, &I, &ni);
  read_test_index(myargs->inbase, myargs->input2, &J, &nj);
  GrB_Index cval = J[0]; // column to extract

  if (strlen(myargs->initvals) == 0) { // initvals file name
    GrB_Index nrA = 0, ncA = 0; // rows and columns of inputs
    get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input0
    GrB_Index outsize = get_index_size(I, ni, nrA); // size of column
    OK (GrB_Vector_new(&C, thetype, outsize)); // create empty matrix
  } else // read initvals if file name specified
    read_matlab_vector(myargs->inbase, myargs->initvals, thetype, &C);

  if (strlen(myargs->mask) > 0) // read mask if file name given
    read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M);

  // do the operation
  OK (GrB_extract(C, M, accum, A, I, ni, cval, desc)); // column 0

  bool testerror = false; // if generating, write to file, otherwise compare
  if (myargs->generate) write_typed_vector(myargs->testbase, myargs->output, C);
  else testerror = check_typed_vector(myargs->testbase, myargs->output, C);

  // free all data products
  OK (GrB_free(&A)); OK (GrB_free(&C)); if (M) OK (GrB_free(&M));
  if (I != GrB_ALL) free(I);
  return testerror; // false means no error
}

int main(int argc, char * argv[])
{
  return run_test(argc, argv, run_CExtr);
}
