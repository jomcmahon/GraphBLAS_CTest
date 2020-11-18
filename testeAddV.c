/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test eWiseAdd vector for all types, PAIR binop
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

void fdiff(void *z, const void *x, const void *y) {
  float delta = (* ((float *) x)) - (* ((float *) y)) ;
  (*((float *) z)) = delta * delta ;
}

bool run_eAddV(testargs *myargs)
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
  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // binary op defines type
  TEST_OK(get_types_binop(binop, &xtype, &ytype, &ztype));

  if (ztype == GrB_FP32) // use user-defined for F32 type
    TEST_OK(GrB_BinaryOp_new(&binop, fdiff, GrB_FP32, GrB_FP32, GrB_FP32));
    
  GrB_Vector A = NULL, B = NULL, C = NULL, M = NULL; // inputs and outputs
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, xtype, &A));
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input1, ytype, &B));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  GrB_Index vsize = 0;
  TEST_OK(GrB_Vector_size(&vsize, A)); // size of input
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, ztype, vsize)); // create empty matrix
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C));

  TEST_OK(GrB_eWiseAdd(C, M, accum, binop, A, B, desc)); // do the operation

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, ztype,
				    C), myargs->output); // test and print

  // free the inputs and outputs
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free (&B)); TEST_OK(GrB_free(&C));
  if (M) TEST_OK(GrB_free(&M)); // free mask if there
  return testerror;
}

void spec_iteration(int **sptr)
{
  set_test_spec(BINOP, num_Types(), sptr); // allocate array
  int g = 1;
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_BOOL);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT8);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT8);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT16);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT16);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT64);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT64);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_FP32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_FP64);
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "V1");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "V2");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
  if (myargs->generate) { // create spec files
    int **myspec = spec_from_args(myargs); // args
    spec_iteration(myspec); // whole iteration for gen
    testargs *myargsC = malloc(sizeof(testargs)); // copy rgs
    memcpy(myargsC, myargs, sizeof(testargs));
    print_test_spec(myargsC, myspec, "D"); // default
    free(myargsC); free_test_spec(myspec);
  }

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  bool testerror = get_spec_list(myargs, BINOP, run_eAddV);

  OK(GrB_finalize());
  return testerror;
}
