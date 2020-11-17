/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test vxm: default ANY_PAIR_BOOL or PLUS_TIMES, four descriptors
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_vxm(testargs *myargs)
{
  GrB_Semiring semi; get_Semiring(myargs->specobj[SEMI], &semi);
  if (!semi) return false; // required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(semi, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // semiring defines type
  TEST_OK(get_types_semiring(semi, &xtype, &ytype, &ztype));

  GrB_Vector A = NULL, C = NULL, M = NULL; // inputs and outputs
  GrB_Matrix B = NULL;
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, xtype, &A));
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input1, ytype, &B));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  GrB_Index nrB, ncB; // rows and columns of input
  get_inp_size(desc, B, &nrB, &ncB, GrB_INP1); // input 1

  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, ztype, ncB)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C));

  TEST_OK(GrB_vxm(C, M, accum, semi, A, B, desc)); // do the operation

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, ztype,
				    C), myargs->output); // test and print

  TEST_OK(GrB_free (&C)); // free all matrices
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&B)); if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

void default_spec(testargs *myargs, int **sptr)
{
  if (!sptr[DESC]) set_test_spec(DESC, 4, sptr); // first four
  if (!sptr[SEMI]) { // if no semiring supplied
    set_test_spec(SEMI, num_Types(), sptr); // allocate array
    int g = 1;
    sptr[SEMI][g++] = find_Semiring(GxB_ANY_PAIR_BOOL);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT8);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT8);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT16);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT16);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT32);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT32);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT64);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT64);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_FP32);
    sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_FP64);
  }

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "V1");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "A");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  bool testerror = get_spec_list(myargs, SEMI, default_spec, run_vxm);

  OK(GrB_finalize());
  return testerror;
}
