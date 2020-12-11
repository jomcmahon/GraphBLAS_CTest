/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: simple test of init and finalize
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

void gen_all_defaults();

int main(int argc, char * argv[])
{
  GrB_Info info;
  OK(GrB_init(GrB_BLOCKING));

  printf("init: PASSED\n");

  OK(GrB_finalize());
  printf("finalize: PASSED\n");
  return 0;
}
