/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: vec_matlab read double to typed vector
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

// no dense or complex matrices
bool gbv_is_valid(MM_typecode matcode)
{
  if (!mm_is_matrix(matcode) || mm_is_dense(matcode) ||
      mm_is_complex(matcode) || mm_is_hermitian(matcode) ||
      mm_is_skew(matcode)) return false;
  else return true;
}

// read a vector written by matlab into a GraphBLAS vector of a certain type
GrB_Info vec_matlab(GrB_Vector *A, FILE *f, GrB_Type thetype)
{
  GrB_Info info;
  MM_typecode matcode;
  int M, N, nz, valctr = 0;
  char line[MM_MAX_LINE_LENGTH];

  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  if (mm_read_banner(f, &matcode) != 0)
    { printf("couldn't read mtx banner\n"); exit(1); }

  if (!gbv_is_valid(matcode))
    { printf("invalid vector matrix %s\n", matcode); exit(1); }

  if (mm_read_mtx_crd_size(f, &M, &N, &nz) !=0)
    { printf("couldn't read sizes\n"); exit(1); }

  assert ((M == 1) || (N == 1));
  GrB_Index vsize = (M == 1) ? N : M;

  OK (GrB_Vector_new(A, thetype, vsize));

  // read the data
  while (fgets(line, MM_MAX_LINE_LENGTH, f) && (valctr < nz)) {
    GrB_Index ival, jval;
    double zd = 1.0; // default value if pattern
    if (mm_is_pattern(matcode)) {
      if (sscanf(line, "%lu %lu", &ival, &jval) != 2)
	{ printf("couldn't scan pattern %d\n", valctr); exit(1); }
    } else {
      if (sscanf(line, "%lu %lu %lf", &ival, &jval, &zd) != 3)
	{ printf("couldn't scan data %d\n", valctr); exit(1); }
    }
    double zu = fabs(zd); // get a positive number for the uint's
    GrB_Index vind = (M == 1) ? jval - 1 : ival - 1;
    
#define SET_ELT OK (GrB_Vector_setElement(*A, sval, vind));

    if (thetype == GrB_BOOL)        { bool sval = (bool)zd; SET_ELT; }
    else if (thetype == GrB_INT8)   { int8_t sval = (int8_t)zd; SET_ELT; }
    else if (thetype == GrB_INT16)  { int16_t sval = (int16_t)zd; SET_ELT; }
    else if (thetype == GrB_INT32)  { int32_t sval = (int32_t)zd; SET_ELT; }
    else if (thetype == GrB_INT64)  { int64_t sval = (int64_t)zd; SET_ELT; }
    else if (thetype == GrB_UINT8)  { uint8_t sval = (uint8_t)zu; SET_ELT; }
    else if (thetype == GrB_UINT16) { uint16_t sval = (uint16_t)zu; SET_ELT; }
    else if (thetype == GrB_UINT32) { uint32_t sval = (uint32_t)zu; SET_ELT; }
    else if (thetype == GrB_UINT64) { uint64_t sval = (uint64_t)zu; SET_ELT; }
    else if (thetype == GrB_FP32)   { float sval = (float)zd; SET_ELT; }
    else if (thetype == GrB_FP64)   { double sval = (double)zd; SET_ELT; }
    else { printf("vec_matlab: bad type\n"); exit(1); }

    valctr++; // increment the number of values read
  }
  // test that the right number of values was read
  if (valctr != nz) { printf("wrong number of vals\n"); exit(1); }

  return GrB_SUCCESS;
}
