/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test eWiseMult matrix for all types, ANY binop
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_eMultM(testargs *myargs)
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
  GrB_Type xtype = NULL, ytype = NULL, ztype; // types defined by binary op
  TEST_OK(get_types_binop(binop, &xtype, &ytype, &ztype));

  GrB_Matrix A = NULL, B = NULL, C = NULL, M = NULL; // inputs and outputs
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input0, xtype, &A));
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->input1, ytype, &B));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  GrB_Index nrA = 0, ncA = 0, nrB = 0, ncB = 0; // rows and columns of inputs
  TEST_OK(get_inp_size(desc, A, &nrA, &ncA, GrB_INP0)); // input 0
  TEST_OK(get_inp_size(desc, B, &nrB, &ncB, GrB_INP1)); // input 1

  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Matrix_new(&C, ztype, nrA, ncB)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, ztype, &C));

  TEST_OK(GrB_eWiseMult(C, M, accum, binop, A, B, desc)); // do the operation

  if (myargs->generate) { // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, ztype, C));
  } else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, ztype,
				      C), myargs->output); // test and print

  // free the inputs and outputs
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&B)); TEST_OK(GrB_free(&C));
  if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

void default_spec(testargs *myargs, int **sptr)
{
  if (!sptr[DESC]) set_test_spec(DESC, 4, sptr); // first four
  if (!sptr[BINOP]) {
    set_test_spec(BINOP, num_Types(), sptr); // allocate array
    int g = 1;
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_BOOL);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT8);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT8);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT16);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT16);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT32);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT32);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT64);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT64);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_FP32);
    sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_FP64);
  }

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "B");
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

  bool testerror = get_spec_list(myargs, BINOP, run_eMultM);

  OK(GrB_finalize());
  return testerror;
}
