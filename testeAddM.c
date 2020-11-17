/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test eWiseAdd matrix: ANY_PAIR_BOOL semi or PLUS binop, 4 desc
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_eAddM(testargs *myargs)
{
  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Type xtype, ytype, ztype; // types defined by semiring or binary op
  GrB_BinaryOp binop = NULL;
  GrB_Semiring semi; get_Semiring(myargs->specobj[SEMI], &semi);
  if (!semi) { // if no semiring, try binop
    get_BinaryOp(myargs->specobj[BINOP], &binop);
    if (!binop) return false; // semi or binaryop is required
    TEST_OK(get_types_binop(binop, &xtype, &ytype, &ztype));
  } else TEST_OK(get_types_semiring(semi, &xtype, &ytype, &ztype));
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    if (semi) GxB_print(semi, GxB_SUMMARY);
    else GxB_print(binop, GxB_SUMMARY);
  }

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
    TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, ztype,
			       &C));

  if (semi) TEST_OK(GrB_eWiseAdd(C, M, accum, semi, A, B, desc));
  else TEST_OK(GrB_eWiseAdd(C, M, accum, binop, A, B, desc));

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, ztype, C),
		 myargs->output); // otherwise, test and print result

  // free the inputs and outputs
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&B)); TEST_OK(GrB_free (&C));
  if (M) TEST_OK(GrB_free(&M));
  return testerror;
}

void default_spec(testargs *myargs, int **sptr)
{
  if (!sptr[DESC]) set_test_spec(DESC, 4, sptr); // first four
  if (!sptr[SEMI]) { // if no semiring supplied
    set_test_spec(SEMI, 1, sptr); // allocate array
    sptr[SEMI][1] = find_Semiring(GxB_ANY_PAIR_BOOL);
  }
  if (!sptr[BINOP]) {
    set_test_spec(BINOP, num_Types() - 1, sptr); // allocate array
    int g = 1;
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT8);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT8);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT16);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT16);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT32);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT32);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT64);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT64);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_FP32);
    sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_FP64);
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

  testargs myargsC;
  memcpy(&myargsC, myargs, sizeof(testargs));
  bool testerror = get_spec_list(myargs, SEMI, run_eAddM);
  testerror |= get_spec_list(&myargsC, BINOP, run_eAddM);

  OK(GrB_finalize());
  return testerror;
}
