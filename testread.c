/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test reading and checking for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);
  bool testerror = false;

  printf("Running %s:\n", myargs->testbase); fflush(stdout);

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "A");
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, "V1");
  if (strlen(myargs->input2) == 0) strcpy(myargs->input2, "V2");
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");

  char ostr[256]; strcpy(ostr, myargs->output);
  for (int i = 0; i < num_Types(); i++) {
    info = GrB_SUCCESS;
    GrB_Type thetype; get_Type(i, &thetype);
    GrB_Matrix A = NULL;
    GrB_Vector V1 = NULL, V2 = NULL;

    TEST_OK(read_matlab_matrix(myargs->testbase, myargs->input0, thetype, &A));
    TEST_OK(read_matlab_vector(myargs->testbase, myargs->input1, thetype, &V1));
    TEST_OK(read_matlab_vector(myargs->testbase, myargs->input2, thetype, &V2));

    sprintf(myargs->output, "%s", ostr);
    TEST_OK(write_typed_matrix(myargs->testbase, myargs->output, thetype, A));
    TEST_COND(check_typed_matrix(myargs->testbase, myargs->output, thetype, A),
	      myargs->output);

    sprintf(myargs->output, "%s%d", ostr, 1);
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, thetype, V1));
    TEST_COND(check_typed_vector(myargs->testbase, myargs->output, thetype, V1),
	      myargs->output);

    sprintf(myargs->output, "%s%d", ostr, 2);
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, thetype, V2));
    TEST_COND(check_typed_vector(myargs->testbase, myargs->output, thetype, V2),
	      myargs->output);

    GrB_free (&A); GrB_free (&V1); GrB_free (&V2);
  }

  OK(GrB_finalize());
  return testerror;
}
