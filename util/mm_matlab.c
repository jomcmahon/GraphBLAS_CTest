/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: mm_matlab read double to typed matrix
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

// no dense or complex matrices
bool gb_is_valid(MM_typecode matcode)
{
  if (mm_is_matrix(matcode) && !mm_is_complex(matcode) &&
      !mm_is_symmetric(matcode) && !mm_is_skew(matcode) &&
      !mm_is_hermitian(matcode)) return true;
  else return false;
}

// read a matrix written by matlab into a GraphBLAS matrix of a certain type
GrB_Info mm_matlab(GrB_Matrix *A, FILE *f, GrB_Type thetype)
{
  GrB_Info info;
  MM_typecode matcode;
  int M, N, nz, valctr = 0;
  char line[MM_MAX_LINE_LENGTH];

  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  if (mm_read_banner(f, &matcode) != 0)
    { printf("couldn't read mtx banner\n"); exit(1); }

  if (!gb_is_valid(matcode))
    { printf("invalid matrix %s\n", matcode); exit(1); }

  if (mm_read_mtx_crd_size(f, &M, &N, &nz) !=0)
    { printf("couldn't read sizes\n"); exit(1); }

  // allocate matrix
  OK (GrB_Matrix_new(A, thetype, M, N));

  GrB_Index *I = malloc(nz * sizeof(GrB_Index));
  GrB_Index *J = malloc(nz * sizeof(GrB_Index));
  int8_t *X_i8; uint8_t *X_u8; int16_t *X_i16; uint16_t *X_u16;
  int32_t *X_i32; uint32_t *X_u32; int64_t *X_i64; uint64_t *X_u64;
  bool *X_b; float *X_f32; double *X_f64;

  if (thetype == GrB_BOOL) X_b = malloc(nz * sizeof(bool));
  else if (thetype == GrB_INT8) X_i8 = malloc(nz * sizeof(int8_t));
  else if (thetype == GrB_INT16) X_i16 = malloc(nz * sizeof(int16_t));
  else if (thetype == GrB_INT32) X_i32 = malloc(nz * sizeof(int32_t));
  else if (thetype == GrB_INT64) X_i64 = malloc(nz * sizeof(int64_t));
  else if (thetype == GrB_UINT8) X_u8 = malloc(nz * sizeof(uint8_t));
  else if (thetype == GrB_UINT16) X_u16 = malloc(nz * sizeof(uint16_t));
  else if (thetype == GrB_UINT32) X_u32 = malloc(nz * sizeof(uint32_t));
  else if (thetype == GrB_UINT64) X_u64 = malloc(nz * sizeof(uint64_t));
  else if (thetype == GrB_FP32) X_f32 = malloc(nz * sizeof(float));
  else if (thetype == GrB_FP64) X_f64 = malloc(nz * sizeof(double));
  else { printf("mm_matlab: bad type\n"); exit(1); }

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
    I[valctr] = ival - 1; J[valctr] = jval - 1; // adjust matlab index

    if (thetype == GrB_BOOL) X_b[valctr] = (bool)zd;
    else if (thetype == GrB_INT8) X_i8[valctr] = (int8_t)zd;
    else if (thetype == GrB_INT16) X_i16[valctr] = (int16_t)zd;
    else if (thetype == GrB_INT32) X_i32[valctr] = (int32_t)zd;
    else if (thetype == GrB_INT64) X_i64[valctr] = (int64_t)zd;
    else if (thetype == GrB_UINT8) X_u8[valctr] = (uint8_t)(fabs(zd));
    else if (thetype == GrB_UINT16) X_u16[valctr] = (uint16_t)(fabs(zd));
    else if (thetype == GrB_UINT32) X_u32[valctr] = (uint32_t)(fabs(zd));
    else if (thetype == GrB_UINT64) X_u64[valctr] = (uint64_t)(fabs(zd));
    else if (thetype == GrB_FP32) X_f32[valctr] = (float)zd;
    else if (thetype == GrB_FP64) X_f64[valctr] = (double)zd;
    else { printf("mm_matlab: bad type\n"); exit(1); }

    valctr++; // increment the number of values read
  }
  // test that the right number of values was read
  if (valctr != nz) { printf("wrong number of vals\n"); exit(1); }

  if (thetype == GrB_BOOL) GrB_Matrix_build(*A, I, J, X_b, nz, GxB_ANY_BOOL);
  else if (thetype == GrB_INT8)
    GrB_Matrix_build(*A, I, J, X_i8, nz, GxB_ANY_INT8);
  else if (thetype == GrB_INT16)
    GrB_Matrix_build(*A, I, J, X_i16, nz, GxB_ANY_INT16);
  else if (thetype == GrB_INT32)
    GrB_Matrix_build(*A, I, J, X_i32, nz, GxB_ANY_INT32);
  else if (thetype == GrB_INT64)
    GrB_Matrix_build(*A, I, J, X_i64, nz, GxB_ANY_INT64);
  else if (thetype == GrB_UINT8)
    GrB_Matrix_build(*A, I, J, X_u8, nz, GxB_ANY_UINT8);
  else if (thetype == GrB_UINT16)
    GrB_Matrix_build(*A, I, J, X_u16, nz, GxB_ANY_UINT16);
  else if (thetype == GrB_UINT32)
    GrB_Matrix_build(*A, I, J, X_u32, nz, GxB_ANY_UINT32);
  else if (thetype == GrB_UINT64)
    GrB_Matrix_build(*A, I, J, X_u64, nz, GxB_ANY_UINT64);
  else if (thetype == GrB_FP32)
    GrB_Matrix_build(*A, I, J, X_f32, nz, GxB_ANY_FP32);
  else if (thetype == GrB_FP64)
    GrB_Matrix_build(*A, I, J, X_f64, nz, GxB_ANY_FP64);
  else { printf("mm_matlab: bad type\n"); exit(1); }

  return GrB_SUCCESS;
}
