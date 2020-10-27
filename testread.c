/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test reading and checking for all types
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

char *testbase = "testread";

int main(int argc, char * argv[])
{
  GrB_Info info = GrB_SUCCESS;
  OK(GrB_init(GrB_BLOCKING));
  bool testerror = false;

  printf("Running %s:\n", testbase);

  for (int i = 0; i < num_Types(); i++) {
    info = GrB_SUCCESS;
    GrB_Type thetype; get_Type(i, &thetype);
    GrB_Matrix A = NULL;
    GrB_Vector V1 = NULL, V2 = NULL;

    TEST_OK(read_matlab_matrix(testbase, "A", thetype, &A));
    TEST_OK(read_matlab_vector(testbase, "V1", thetype, &V1));
    TEST_OK(read_matlab_vector(testbase, "V2", thetype, &V2));

    TEST_OK(write_typed_matrix(testbase, "C", thetype, A));
    TEST_OK(write_typed_vector(testbase, "C1", thetype, V1));
    TEST_OK(write_typed_vector(testbase, "C2", thetype, V2));

    TEST_COND(check_typed_matrix(testbase, "C", thetype, A), "testread");
    TEST_COND(check_typed_vector(testbase, "C1", thetype, V1), "testread");
    TEST_COND(check_typed_vector(testbase, "C2", thetype, V2), "testread");

    GrB_free (&A); GrB_free (&V1); GrB_free (&V2);
  }

  OK(GrB_finalize());
  return testerror;
}
