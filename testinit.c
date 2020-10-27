/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: simple test of init and finalize
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  printf("init: PASSED\n");
  OK(GrB_finalize());
  printf("finalize: PASSED\n");
  return 0;
}
