/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test Vector reduce type for all types, ANY monoid
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

bool run_VTRed(testargs *myargs)
{
  GrB_Monoid mon; get_Monoid(myargs->specobj[MON], &mon);
  if (!mon) return false; // required
  GrB_BinaryOp accum; get_BinaryOp(myargs->specobj[ACCUM], &accum);
  GrB_Descriptor desc; get_Descriptor(myargs->specobj[DESC], &desc);

  if (myargs->generate)  { // if generating, show accum, desc and semi
    print_args(myargs, desc, accum);
    GxB_print(mon, GxB_SUMMARY);
  }

  bool testerror = false;
  GrB_Info info = GrB_SUCCESS; // reset for next sub-test
  GrB_Type xtype = NULL, ytype = NULL, ztype = NULL; // types defined by monoid
  TEST_OK(get_types_monoid(mon, &xtype, &ytype, &ztype));

  GrB_Vector A = NULL, C = NULL; // inputs and outputs
  TEST_OK(read_matlab_vector(myargs->inbase, myargs->input0, ztype, &A));
  if (strlen(myargs->initvals) == 0) // initvals file name
    TEST_OK(GrB_Vector_new(&C, ztype, 1)); // create empty vector length 1
  else // read initvals if file name specified
    TEST_OK(read_matlab_vector(myargs->inbase, myargs->initvals, ztype, &C));

#define SET_AND_TEST					\
  TEST_OK(GrB_reduce(&c, accum, mon, A, desc));		\
  TEST_OK(GrB_Vector_setElement(C, c, 0));

  // call reduce based on type
  if (ztype == GrB_BOOL) { bool c = false; SET_AND_TEST; }
  else if (ztype == GrB_INT8) { int8_t c = INT8_MAX; SET_AND_TEST; }
  else if (ztype == GrB_INT16) { int16_t c = INT16_MAX; SET_AND_TEST; }
  else if (ztype == GrB_INT32) { int32_t c = INT32_MAX; SET_AND_TEST; }
  else if (ztype == GrB_INT64) { int64_t c = INT64_MAX; SET_AND_TEST; }
  else if (ztype == GrB_UINT8) { uint8_t c = UINT8_MAX; SET_AND_TEST; }
  else if (ztype == GrB_UINT16) { uint16_t c = UINT16_MAX; SET_AND_TEST; }
  else if (ztype == GrB_UINT32) { uint32_t c = UINT32_MAX; SET_AND_TEST; }
  else if (ztype == GrB_UINT64) { uint64_t c = UINT64_MAX; SET_AND_TEST; }
  else if (ztype == GrB_FP32) { float c = 1e6; SET_AND_TEST; }
  else if (ztype == GrB_FP64) { double c = 1e6; SET_AND_TEST; }
  else { printf("bad type\n"); exit(1); }

  if (myargs->generate) // if generating, write to file
    TEST_OK(write_typed_vector(myargs->testbase, myargs->output, ztype, C));
  else TEST_COND(check_typed_vector(myargs->testbase, myargs->output, ztype, C),
		 myargs->output); // test and print

  // free all data products
  TEST_OK(GrB_free(&A)); TEST_OK(GrB_free(&C));
  return testerror;
}

void default_spec(testargs *myargs, int **sptr)
{
    
  if (!sptr[MON]) set_test_spec(MON, num_Monoids(), sptr); // allocate array

  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, "V1");
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

  bool testerror = get_spec_list(myargs, MON, run_VTRed);

  OK(GrB_finalize());
  return testerror;
}
