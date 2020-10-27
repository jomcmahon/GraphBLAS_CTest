/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: mm_read into matrix of certain type
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

// read a GraphBLAS matrix that has been written by the C Test Suite
GrB_Info mm_read(GrB_Matrix *A, FILE *f, GrB_Type thetype)
{
  GrB_Info info;
  MM_typecode matcode;
  int M, N, nz, valctr = 0;
  char line[MM_MAX_LINE_LENGTH];

  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  if (mm_read_banner(f, &matcode) != 0)
    { printf("couldn't read mtx banner\n"); exit(1); }

  if (mm_read_mtx_crd_size(f, &M, &N, &nz) != 0)
    { printf("couldn't read sizes\n"); exit(1); }

  // allocate matrix
  OK (GrB_Matrix_new(A, thetype, M, N));

  // read the data
  while (fgets(line, MM_MAX_LINE_LENGTH, f) && (valctr < nz)) {
    GrB_Index ival, jval;
    int64_t r0;
    uint64_t r1;
    double r2;
    if (thetype == GrB_BOOL) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (bool)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_INT8) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (int8_t)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_INT16) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (int16_t)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_INT32) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (int32_t)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_INT64) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (int64_t)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_UINT8) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (uint8_t)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_UINT16) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (uint16_t)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_UINT32) {
      if (sscanf(line, "%lu %lu %ld", &ival, &jval, &r0) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (uint32_t)r0, ival - 1, jval - 1));
    } else if (thetype == GrB_UINT64) { // UINT64 uses different scanf
      if (sscanf(line, "%lu %lu %lu", &ival, &jval, &r1) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (uint64_t)r1, ival - 1, jval - 1));
    } else if (thetype == GrB_FP32) { // FP32 uses different scanf
      if (sscanf(line, "%lu %lu %lg", &ival, &jval, &r2) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, (float)r2, ival - 1, jval - 1));
    } else if (thetype == GrB_FP64) { // FP64 uses different scanf
      if (sscanf(line, "%lu %lu %lg", &ival, &jval, &r2) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
      OK (GrB_Matrix_setElement(*A, r2, ival - 1, jval - 1));
    } else { printf("mm_read: bad type\n"); exit(1); }

    valctr++; // increment the number of values read
  }
  // test that the right number of values was read
  if (valctr != nz) { printf("wrong number of vals\n"); exit(1); }

  return GrB_SUCCESS;
}
