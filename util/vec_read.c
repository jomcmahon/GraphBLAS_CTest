/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: vec_read into vector of certain type
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

// read a GraphBLAS vector that has been written by the C Test Suite
GrB_Info vec_read(GrB_Vector *A, FILE *f, GrB_Type thetype)
{
  GrB_Info info;
  MM_typecode matcode;
  int M, N, nz, valctr = 0;
  char line[MM_MAX_LINE_LENGTH];

  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  if (mm_read_banner(f, &matcode) != 0)
    { printf("couldn't read mtx banner\n"); exit(1); }

  if (mm_read_mtx_crd_size(f, &M, &N, &nz) !=0)
    { printf("couldn't read sizes\n"); exit(1); }

  // get the type
  assert ((M == 1) || (N == 1));
  GrB_Index vsize = (M == 1) ? N : M;
  OK (GrB_Vector_new(A, thetype, vsize));

  // read the data
  while (fgets(line, MM_MAX_LINE_LENGTH, f) && (valctr < nz)) {
    GrB_Index ival, jval;
    int64_t r0;
    uint64_t r1;
    double r2;
    if (thetype == GrB_BOOL) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (bool)r0, vind));
    } else if (thetype == GrB_INT8) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (int8_t)r0, vind));
    } else if (thetype == GrB_INT16) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (int16_t)r0, vind));
    } else if (thetype == GrB_INT32) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (int32_t)r0, vind));
    } else if (thetype == GrB_INT64) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (int64_t)r0, vind));
    } else if (thetype == GrB_UINT8) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (uint8_t)r0, vind));
    } else if (thetype == GrB_UINT16) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (uint16_t)r0, vind));
    } else if (thetype == GrB_UINT32) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (uint32_t)r0, vind));
    } else if (thetype == GrB_UINT64) { // UINT64 uses different scanf
      if (sscanf(line, "%lu %lu %lu", &ival, &jval, &r1) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (uint64_t)r1, vind));
    } else if (thetype == GrB_FP32) { // FP32 uses different scanf
      if (sscanf(line, "%lu %lu %lg", &ival, &jval, &r2) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, (float)r2, vind));
    } else if (thetype == GrB_FP64) { // FP64 uses different scanf
      if (sscanf(line, "%lu %lu %lg", &ival, &jval, &r2) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
      OK (GrB_Vector_setElement(*A, r2, vind));
    } else { printf("vec_read: bad type\n"); exit(1); }

    valctr++; // increment the number of values read
  }
  // test that the right number of values was read
  if (valctr != nz) { printf("wrong number of vals\n"); exit(1); }

  return GrB_SUCCESS;
}
