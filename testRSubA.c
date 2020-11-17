/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Row subassign for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_RSubA(testargs *myargs)
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
  GrB_Index *J = NULL, nj = 0; // index vector
  TEST_OK(read_test_index(myargs->inbase, myargs->input1, &J, &nj));

  GrB_Matrix C = NULL; // inputs and outputs
  GrB_Vector A = NULL, M = NULL;
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, thetype, &A));
  TEST_OK(read_matlab_matrix(myargs->inbase, myargs->initvals, thetype, &C));
  if (strlen(myargs->mask) > 0) // read mask if file name given
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->mask, GrB_BOOL, &M));

  TEST_OK(GxB_subassign(C, M, accum, A, 0, J, nj, desc)); // do operation, row 0

  if (myargs->generate) { // if generating, write to file
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, thetype, C));
  } else TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, thetype,
				      C), myargs->output); // test and print

  // free the inputs and outputs
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C)); if (M) TEST_OK(GrB_free(&M));
  if (J != GrB_ALL) free(J);
  return testerror;
}

void default_spec(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "CE");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "A_col");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "A");
}

void default_specA(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "CEA");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "ALL");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CA");
  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "A");
}

void default_specR(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "CER");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_RANGE");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CR");
  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "A");
}

void default_specS(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "CES");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_STRIDE");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CS");
  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "A");
}

void default_specB(testargs *myargs, int **specptr)
{
  if (!specptr[TYPE]) set_test_spec(TYPE, num_Types(), specptr); // all types

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "CEB");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "I_BACK");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "CB");
  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, "A");
}

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  bool testerror = false;

  testargs myargsA, myargsR, myargsS, myargsB; // additions to default
  testargs *myargs = get_test_args(argc, argv);
  memcpy(&myargsA, myargs, sizeof(testargs));
  memcpy(&myargsR, myargs, sizeof(testargs));
  memcpy(&myargsS, myargs, sizeof(testargs));
  memcpy(&myargsB, myargs, sizeof(testargs));
  sprintf(myargs->spectest, "data/specfiles/%s.def", myargs->testbase);
  int **specptr = get_test_spec(myargs, default_spec);
  sprintf(myargsA.spectest, "data/specfiles/%s.A", myargs->testbase);
  int **specptrA = get_test_spec(&myargsA, default_specA);
  sprintf(myargsR.spectest, "data/specfiles/%s.R", myargs->testbase);
  int **specptrR = get_test_spec(&myargsR, default_specR);
  sprintf(myargsS.spectest, "data/specfiles/%s.S", myargs->testbase);
  int **specptrS = get_test_spec(&myargsS, default_specS);
  sprintf(myargsB.spectest, "data/specfiles/%s.B", myargs->testbase);
  int **specptrB = get_test_spec(&myargsB, default_specB);

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  testerror = test_L_DA_loop(myargs, TYPE, specptr, run_RSubA);
  testerror |= test_L_DA_loop(&myargsA, TYPE, specptrA, run_RSubA);
  testerror |= test_L_DA_loop(&myargsR, TYPE, specptrR, run_RSubA);
  testerror |= test_L_DA_loop(&myargsS, TYPE, specptrS, run_RSubA);
  testerror |= test_L_DA_loop(&myargsB, TYPE, specptrB, run_RSubA);

  OK(GrB_finalize());
  return testerror;
}
