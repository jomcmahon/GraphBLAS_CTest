/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Matrix transpose for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_tran(testargs *myargs)
{
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  if (!thetype) return false; // required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(thetype, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Matrix A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Index nrA = 0, ncA = 0;
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input0, thetype, &A));
  get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0, no desc
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M));
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Matrix_new(&C, thetype, nrA, ncA)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C));

  TEST_OK(GrB_transpose(C, M, accum, A, desc)); // do the operation

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, thetype, C));
  else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, thetype,
				    C), myargs->output); // test and print

  // free all data products
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

void default_spec(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  if (myargs->generate) { // create spec files
    sprintf(myargs->spectest, "data/specfiles/%s.def", myargs->testbase);
    write_test_spec(myargs, default_spec);
    char lfname[256];
    sprintf(lfname, "data/specfiles/%s.spec", myargs->testbase);
    FILE *outfp = fopen(lfname, "w"); // file with list of spec files
    if (outfp) {
      fprintf(outfp, "data/specfiles/%s.def\n", myargs->testbase);
      fclose(outfp);
    }
  }

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  bool testerror = get_spec_list(myargs, TYPE, run_tran);

  OK(GrB_finalize());
  return testerror;
}
