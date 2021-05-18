/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: support routines to read and write data to/from MM files
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

void build_Matrix_UDT(GrB_Matrix, GrB_Type, GrB_Index *, GrB_Index *, double *,
		      GrB_Index);
void build_Vector_UDT(GrB_Vector, GrB_Type, GrB_Index *, double *, GrB_Index);
void extract_Matrix_UDT(GrB_Index *, GrB_Index *, double *, GrB_Index,
			GrB_Index *, GrB_Matrix);
void extract_Vector_UDT(GrB_Index *, double *, GrB_Index, GrB_Index *,
			GrB_Vector);

// read banner and allocate arrays
void mm_setup(FILE *f, GrB_Index *M, GrB_Index *N, GrB_Index *nz, GrB_Index **I,
	      GrB_Index **J, double **X_f64)
{
  int m, n, nv;
  MM_typecode matcode;

  if (mm_read_banner(f, &matcode) != 0)
    { printf("couldn't read mtx banner\n"); exit(1); }

  if (MM_INVALID(matcode) || mm_is_dense(matcode))
    { printf("invalid matrix %s\n", matcode); exit(1); }

  if (mm_read_mtx_crd_size(f, &m, &n, &nv) !=0)
    { printf("couldn't read sizes\n"); exit(1); }

  *nz = nv; *M = m; *N = n;
  *I = malloc(nv * sizeof(GrB_Index));
  *J = malloc(nv * sizeof(GrB_Index));
  *X_f64 = malloc(nv * sizeof(double));
}

// read values as double and cast to type
void mm_double(FILE *f, GrB_Type thetype, GrB_Index nz, GrB_Index *I,
	       GrB_Index *J, double *X_f64)
{
  int valctr = 0;
  char line[MM_MAX_LINE_LENGTH];
  while (fgets(line, MM_MAX_LINE_LENGTH, f) && (valctr < nz)) {
    GrB_Index ival, jval;
    double zd;
    if (sscanf(line, "%lu %lu %lf", &ival, &jval, &zd) != 3)
      { printf("couldn't scan data %d\n", valctr); exit(1); }
    I[valctr] = ival - 1; J[valctr] = jval - 1; // adjust matlab index

    if (thetype == GrB_BOOL)
      { bool *X = (bool *)X_f64; X[valctr] = (bool)zd; }
    else if (thetype == GrB_INT8)
      { int8_t *X = (int8_t *)X_f64; X[valctr] = (int8_t)zd; }
    else if (thetype == GrB_INT16)
      { int16_t *X = (int16_t *)X_f64; X[valctr] = (int16_t)zd; }
    else if (thetype == GrB_INT32)
      { int32_t *X = (int32_t *)X_f64; X[valctr] = (int32_t)zd; }
    else if (thetype == GrB_INT64)
      { int64_t *X = (int64_t *)X_f64; X[valctr] = (int64_t)zd; }
    else if (thetype == GrB_UINT8)
      { uint8_t *X = (uint8_t *)X_f64; X[valctr] = (uint8_t)(fabs(zd)); }
    else if (thetype == GrB_UINT16)
      { uint16_t *X = (uint16_t *)X_f64; X[valctr] = (uint16_t)(fabs(zd)); }
    else if (thetype == GrB_UINT32)
      { uint32_t *X = (uint32_t *)X_f64; X[valctr] = (uint32_t)(fabs(zd)); }
    else if (thetype == GrB_UINT64)
      { uint64_t *X = (uint64_t *)X_f64; X[valctr] = (uint64_t)(fabs(zd)); }
    else if (thetype == GrB_FP32)
      { float *X = (float *)X_f64; X[valctr] = (float)zd; }
    else { double *X = (double *)X_f64; X[valctr] = (double)zd; }

    valctr++; // increment the number of values read
  }
  // test that the right number of values was read
  if (valctr != nz) { printf("wrong number of vals\n"); exit(1); }
}

// read values as given type
void mm_type(FILE *f, GrB_Type thetype, GrB_Index nz, GrB_Index *I,
	     GrB_Index *J, double *X_f64)
{
  int valctr = 0;
  char line[MM_MAX_LINE_LENGTH];
  while (fgets(line, MM_MAX_LINE_LENGTH, f) && (valctr < nz)) {
    int n;
    GrB_Index ival, jval;
    if (thetype == GrB_BOOL) { int r; bool *X = (bool *)X_f64;
      n = sscanf(line, "%lu %lu %d", &ival, &jval, &r); X[valctr] = r;
    } else if (thetype == GrB_INT8) { int8_t *X = (int8_t *)X_f64;
      n = sscanf(line, "%lu %lu %hhd", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_INT16) { int16_t *X = (int16_t *)X_f64;
      n = sscanf(line, "%lu %lu %hd", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_INT32) { int32_t *X = (int32_t *)X_f64;
      n = sscanf(line, "%lu %lu %d", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_INT64) { int64_t *X = (int64_t *)X_f64;
      n = sscanf(line, "%lu %lu %ld", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_UINT8) { uint8_t *X = (uint8_t *)X_f64;
      n = sscanf(line, "%lu %lu %hhu", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_UINT16) { uint16_t *X = (uint16_t *)X_f64;
      n = sscanf(line, "%lu %lu %hu", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_UINT32) { uint32_t *X = (uint32_t *)X_f64;
      n = sscanf(line, "%lu %lu %u", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_UINT64) { uint64_t *X = (uint64_t *)X_f64;
      n = sscanf(line, "%lu %lu %lu", &ival, &jval, &X[valctr]);
    } else if (thetype == GrB_FP32) { float *X = (float *)X_f64;
      n = sscanf(line, "%lu %lu %g", &ival, &jval, &X[valctr]);
    } else { double *X = (double *)X_f64;
      n = sscanf(line, "%lu %lu %lg", &ival, &jval, &X[valctr]);
    }

    if (n != 3) { printf("couldn't scan data %d\n", valctr); exit(1); }
    I[valctr] = ival - 1; J[valctr] = jval - 1; // adjust indices
    valctr++; // increment the number of values read
  }
  // test that the right number of values was read
  if (valctr != nz) { printf("wrong number of vals\n"); exit(1); }
}

// build matrix from arrays according to type
void mm_matbuild(GrB_Matrix A, GrB_Type thetype, GrB_Index nz, GrB_Index *I,
		 GrB_Index *J, double *X_f64)
{
  if (nz == 0) return;
  GrB_Info info;
  if (thetype == GrB_BOOL)
    OK (GrB_Matrix_build(A, I, J, (bool *)X_f64, nz, GxB_ANY_BOOL));
  else if (thetype == GrB_INT8)
    OK (GrB_Matrix_build(A, I, J, (int8_t *)X_f64, nz, GxB_ANY_INT8));
  else if (thetype == GrB_INT16)
    OK (GrB_Matrix_build(A, I, J, (int16_t *)X_f64, nz, GxB_ANY_INT16));
  else if (thetype == GrB_INT32)
    OK (GrB_Matrix_build(A, I, J, (int32_t *)X_f64, nz, GxB_ANY_INT32));
  else if (thetype == GrB_INT64)
    OK (GrB_Matrix_build(A, I, J, (int64_t *)X_f64, nz, GxB_ANY_INT64));
  else if (thetype == GrB_UINT8)
    OK (GrB_Matrix_build(A, I, J, (uint8_t *)X_f64, nz, GxB_ANY_UINT8));
  else if (thetype == GrB_UINT16)
    OK (GrB_Matrix_build(A, I, J, (uint16_t *)X_f64, nz, GxB_ANY_UINT16));
  else if (thetype == GrB_UINT32)
    OK (GrB_Matrix_build(A, I, J, (uint32_t *)X_f64, nz, GxB_ANY_UINT32));
  else if (thetype == GrB_UINT64)
    OK (GrB_Matrix_build(A, I, J, (uint64_t *)X_f64, nz, GxB_ANY_UINT64));
  else if (thetype == GrB_FP32)
    OK (GrB_Matrix_build(A, I, J, (float *)X_f64, nz, GxB_ANY_FP32));
  else if (thetype == GrB_FP64)
    OK (GrB_Matrix_build(A, I, J, (double *)X_f64, nz, GxB_ANY_FP64));
  else build_Matrix_UDT(A, thetype, I, J, X_f64, nz);
}

// build vector from arrays according to type
void mm_vecbuild(GrB_Vector A, GrB_Type thetype, GrB_Index nz, GrB_Index *I,
		 double *X_f64)
{
  if (nz == 0) return;
  GrB_Info info;
  if (thetype == GrB_BOOL)
    OK (GrB_Vector_build(A, I, (bool *)X_f64, nz, GxB_ANY_BOOL));
  else if (thetype == GrB_INT8)
    OK (GrB_Vector_build(A, I, (int8_t *)X_f64, nz, GxB_ANY_INT8));
  else if (thetype == GrB_INT16)
    OK (GrB_Vector_build(A, I, (int16_t *)X_f64, nz, GxB_ANY_INT16));
  else if (thetype == GrB_INT32)
    OK (GrB_Vector_build(A, I, (int32_t *)X_f64, nz, GxB_ANY_INT32));
  else if (thetype == GrB_INT64)
    OK (GrB_Vector_build(A, I, (int64_t *)X_f64, nz, GxB_ANY_INT64));
  else if (thetype == GrB_UINT8)
    OK (GrB_Vector_build(A, I, (uint8_t *)X_f64, nz, GxB_ANY_UINT8));
  else if (thetype == GrB_UINT16)
    OK (GrB_Vector_build(A, I, (uint16_t *)X_f64, nz, GxB_ANY_UINT16));
  else if (thetype == GrB_UINT32)
    OK (GrB_Vector_build(A, I, (uint32_t *)X_f64, nz, GxB_ANY_UINT32));
  else if (thetype == GrB_UINT64)
    OK (GrB_Vector_build(A, I, (uint64_t *)X_f64, nz, GxB_ANY_UINT64));
  else if (thetype == GrB_FP32)
    OK (GrB_Vector_build(A, I, (float *)X_f64, nz, GxB_ANY_FP32));
  else if (thetype == GrB_FP64)
    OK (GrB_Vector_build(A, I, (double *)X_f64, nz, GxB_ANY_FP64));
  else build_Vector_UDT(A, thetype, I, X_f64, nz);
}

// read banner and allocate arrays
void mm_output(FILE *f, GrB_Index M, GrB_Index N, GrB_Index nz, GrB_Index **I,
	       GrB_Index **J, double **X_f64)
{
  MM_typecode matcode;

  mm_set_matrix(&matcode);
  mm_set_coordinate(&matcode);
  mm_set_real(&matcode);
  mm_set_general(&matcode);

  if (mm_write_banner(f, matcode) != 0)
    { printf("couldn't write mtx banner\n"); exit(1); }

  if (mm_write_mtx_crd_size(f, M, N, nz) !=0)
    { printf("couldn't write sizes\n"); exit(1); }

  *I = malloc(nz * sizeof(GrB_Index));
  *J = malloc(nz * sizeof(GrB_Index));
  *X_f64 = malloc(nz * sizeof(double));
}

// read values as given type
void mm_print(FILE *f, GrB_Type thetype, GrB_Index nz, GrB_Index *I,
	      GrB_Index *J, double *X_f64)
{
  for (int k = 0; k < nz; k++) {
    if (thetype == GrB_BOOL) { bool *X = (bool *)X_f64;
      fprintf(f, "%lu %lu %d\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_INT8) { int8_t *X = (int8_t *)X_f64;
      fprintf(f, "%lu %lu %hhd\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_INT16) { int16_t *X = (int16_t *)X_f64;
      fprintf(f, "%lu %lu %hd\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_INT32) { int32_t *X = (int32_t *)X_f64;
      fprintf(f, "%lu %lu %d\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_INT64) { int64_t *X = (int64_t *)X_f64;
      fprintf(f, "%lu %lu %ld\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_UINT8) { uint8_t *X = (uint8_t *)X_f64;
      fprintf(f, "%lu %lu %hhu\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_UINT16) { uint16_t *X = (uint16_t *)X_f64;
      fprintf(f, "%lu %lu %hu\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_UINT32) { uint32_t *X = (uint32_t *)X_f64;
      fprintf(f, "%lu %lu %u\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_UINT64) { uint64_t *X = (uint64_t *)X_f64;
      fprintf(f, "%lu %lu %lu\n", I[k]+1, J[k]+1, X[k]);
    } else if (thetype == GrB_FP32) { float *X = (float *)X_f64;
      fprintf(f, "%lu %lu %.16f\n", I[k]+1, J[k]+1, X[k]);
    } else { double *X = (double *)X_f64;
      fprintf(f, "%lu %lu %.16f\n", I[k]+1, J[k]+1, X[k]);
    }
  }
}

// build matrix from arrays according to type
void mm_matextract(GrB_Matrix A, GrB_Type thetype, GrB_Index nv, GrB_Index *I,
		   GrB_Index *J, double *X_f64)
{
  GrB_Info info;
  GrB_Index nz = nv;
  if (nz == 0) return;
  if (thetype == GrB_BOOL)
    OK (GrB_Matrix_extractTuples(I, J, (bool *)X_f64, &nz, A));
  else if (thetype == GrB_INT8)
    OK (GrB_Matrix_extractTuples(I, J, (int8_t *)X_f64, &nz, A));
  else if (thetype == GrB_INT16)
    OK (GrB_Matrix_extractTuples(I, J, (int16_t *)X_f64, &nz, A));
  else if (thetype == GrB_INT32)
    OK (GrB_Matrix_extractTuples(I, J, (int32_t *)X_f64, &nz, A));
  else if (thetype == GrB_INT64)
    OK (GrB_Matrix_extractTuples(I, J, (int64_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT8)
    OK (GrB_Matrix_extractTuples(I, J, (uint8_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT16)
    OK (GrB_Matrix_extractTuples(I, J, (uint16_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT32)
    OK (GrB_Matrix_extractTuples(I, J, (uint32_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT64)
    OK (GrB_Matrix_extractTuples(I, J, (uint64_t *)X_f64, &nz, A));
  else if (thetype == GrB_FP32)
    OK (GrB_Matrix_extractTuples(I, J, (float *)X_f64, &nz, A));
  else if (thetype == GrB_FP64)
    OK (GrB_Matrix_extractTuples(I, J, (double *)X_f64, &nz, A));
  else extract_Matrix_UDT(I, J, X_f64, nv, &nz, A);
  if (nz != nv) { printf("Bad number of vals %lu %lu\n", nz, nv); exit(1); }
}

// build matrix from arrays according to type
void mm_vecextract(GrB_Vector A, GrB_Type thetype, GrB_Index nv, GrB_Index *I,
		   double *X_f64)
{
  GrB_Info info;
  GrB_Index nz = nv;
  if (nz == 0) return;
  if (thetype == GrB_BOOL)
    OK (GrB_Vector_extractTuples(I, (bool *)X_f64, &nz, A));
  else if (thetype == GrB_INT8)
    OK (GrB_Vector_extractTuples(I, (int8_t *)X_f64, &nz, A));
  else if (thetype == GrB_INT16)
    OK (GrB_Vector_extractTuples(I, (int16_t *)X_f64, &nz, A));
  else if (thetype == GrB_INT32)
    OK (GrB_Vector_extractTuples(I, (int32_t *)X_f64, &nz, A));
  else if (thetype == GrB_INT64)
    OK (GrB_Vector_extractTuples(I, (int64_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT8)
    OK (GrB_Vector_extractTuples(I, (uint8_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT16)
    OK (GrB_Vector_extractTuples(I, (uint16_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT32)
    OK (GrB_Vector_extractTuples(I, (uint32_t *)X_f64, &nz, A));
  else if (thetype == GrB_UINT64)
    OK (GrB_Vector_extractTuples(I, (uint64_t *)X_f64, &nz, A));
  else if (thetype == GrB_FP32)
    OK (GrB_Vector_extractTuples(I, (float *)X_f64, &nz, A));
  else if (thetype == GrB_FP64)
    OK (GrB_Vector_extractTuples(I, (double *)X_f64, &nz, A));
  else extract_Vector_UDT(I, X_f64, nv, &nz, A);
  if (nz != nv) { printf("Bad number of vals %lu %lu\n", nz, nv); exit(1); }
}
