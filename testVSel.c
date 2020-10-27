/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Vector select for all types, GT_ZERO select op
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_VSel(testargs *myargs)
{
  GxB_SelectOp selop; get_SelectOp(myargs->specobj[SELOP], &selop);
  GrB_Type thetype; get_Type(myargs->specobj[TYPE], &thetype);
  if (!thetype || !selop) return false; // type and select op are required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(thetype, GxB_SUMMARY);
    GxB_print(selop, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Vector A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Index vsize = 0;
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, thetype, &A));
  TEST_OK(GrB_Vector_size(&vsize, A));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, thetype, vsize)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, thetype, &C));

  // do the operation
  TEST_OK(GxB_select(C, M, accum, selop, A, NULL, desc)); // no thunk

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, thetype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, thetype,
				    C), myargs->output); // test and print

  // free all data products
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

void default_spec(testargs *myargs, int **sptr)
{
  if (!sptr[SELOP]) set_test_spec(SELOP, num_SelectOps(), sptr); // all
  if (!sptr[TYPE]) { // if no semiring supplied
    set_test_spec(TYPE, 4, sptr); // allocate array
    int g = 1;
    sptr[TYPE][g++] = find_Type(GrB_BOOL);
    sptr[TYPE][g++] = find_Type(GrB_INT64);
    sptr[TYPE][g++] = find_Type(GrB_FP32);
    sptr[TYPE][g++] = find_Type(GrB_FP64);
  }

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "V1");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  int **specptr = get_test_spec(myargs, default_spec);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  testerror = test_L_TDA_loop(myargs, SELOP, specptr, run_VSel);

  OK(GrB_finalize());
  return testerror;
}
