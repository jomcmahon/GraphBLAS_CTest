/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Matrix reduce op for all types, MIN binary op
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_MRed(testargs *myargs)
{
  GrB_BinaryOp binop; get_BinaryOp(myargs->specobj[BINOP], &binop);
  if (!binop) return false; // required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(binop, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // types defined by monoid
  TEST_OK(get_types_binop(binop, &xtype, &ytype, &ztype));

  GrB_Matrix A = NULL;
  GrB_Vector C = NULL, M = NULL;
  GrB_Index nrA = 0, ncA = 0;
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input0, ztype, &A));
  get_inp_size(desc, A, &nrA, &ncA, GrB_INP0); // input 0
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, ztype, nrA)); // create empty vector length 1
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  TEST_OK(GrB_reduce(C, M, accum, binop, A, desc)); // do the operation

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, ztype, C),
		 myargs->output); // test and print

  // free all data products
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

void default_spec(testargs *myargs, int **sptr)
{
  if (!sptr[BINOP]) {
    set_test_spec(BINOP, num_Types(), sptr); // allocate array
    int g = 1;
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_BOOL);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT8);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT8);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT16);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT16);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT32);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT32);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT64);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT64);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_FP32);
    sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_FP64);
  }

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  sprintf(myargs->spectest, "data/specfiles/%s.def", myargs->testbase);
  int **specptr = get_test_spec(myargs, default_spec);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  testerror = test_L_DA_loop(myargs, BINOP, specptr, run_MRed);

  OK(GrB_finalize());
  return testerror;
}
