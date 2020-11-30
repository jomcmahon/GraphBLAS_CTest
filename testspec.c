/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: simple test of init and finalize
*/

#include <libgen.h>
#include "GraphBLAS.h"
#include "util/test_utils.h"

void gen_default(testargs *);

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));
  testargs *myargs = get_test_args(argc, argv);

  if (myargs->generate) gen_default(myargs);

  OK(GrB_finalize());
  return 0;
}
