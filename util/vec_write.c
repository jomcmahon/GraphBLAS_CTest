/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: vec_write from vector of certain type
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

// write GraphBLAS vector to matrix market file
void vec_write(GrB_Vector A, FILE *f)
{
  GrB_Info info;
  MM_typecode matcode;
  GrB_Type thetype;
  GrB_Index M = 1, N, nz, nvals;

  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  mm_set_matrix(&matcode);
  mm_set_coordinate(&matcode);
  mm_set_real(&matcode);
  mm_set_general(&matcode);

  if (mm_write_banner(f, matcode) != 0)
    { printf("couldn't write mtx banner\n"); exit(1); }

  OK (GxB_Vector_type (&thetype, A));
  OK (GrB_Vector_size(&N, A));
  OK (GrB_Vector_nvals(&nz, A));
  nvals = nz;

  if (mm_write_mtx_crd_size(f, M, N, nz) !=0)
    { printf("couldn't write sizes\n"); exit(1); }

  GrB_Index *J = malloc(nz * sizeof(GrB_Index));
  if (J == NULL) { printf("problem with malloc J\n"); exit(1); }
  double *Z = malloc (nz * sizeof(double)); // allocate maximum size
  if (Z == NULL) { printf("problem with malloc Z\n"); exit(1); }

#define SET_ELT							  \
  OK (GrB_Vector_extractTuples (J, X, &nvals, A));		  \
  if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }	  \
  for (int k = 0 ; k < nvals ; k++)				  \
    fprintf(f, "%lu %lu %d\n", 1LU, J[k]+1, X[k]);

  if (thetype == GrB_BOOL) { bool *X = (bool *)Z; SET_ELT; }
  else if (thetype == GrB_INT8) { int8_t *X = (int8_t *)Z; SET_ELT; }
  else if (thetype == GrB_INT16) { int16_t *X = (int16_t *)Z; SET_ELT; }
  else if (thetype == GrB_INT32) { int32_t *X = (int32_t *)Z; SET_ELT; }
  else if (thetype == GrB_INT64) {
    int64_t *X = (int64_t *)Z;
    OK (GrB_Vector_extractTuples (J, X, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%lu %lu %ld\n", 1LU, J[k]+1, X[k]);
  } else if (thetype == GrB_UINT8) { uint8_t *X = (uint8_t *)Z; SET_ELT; }
  else if (thetype == GrB_UINT16) { uint16_t *X = (uint16_t *)Z; SET_ELT; }
  else if (thetype == GrB_UINT32) { uint32_t *X = (uint32_t *)Z; SET_ELT; }
  else if (thetype == GrB_UINT64) {
    uint64_t *X = (uint64_t *)Z;
    OK (GrB_Vector_extractTuples (J, X, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%lu %lu %lu\n", 1LU, J[k]+1, X[k]);
  } else if (thetype == GrB_FP32) {
    float *X = (float *)Z;
    OK (GrB_Vector_extractTuples (J, X, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%lu %lu %.16f\n", 1LU, J[k]+1, X[k]);
  } else if (thetype == GrB_FP64) {
    OK (GrB_Vector_extractTuples (J, Z, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%lu %lu %.16f\n", 1LU, J[k]+1, Z[k]);
  } else { printf("vec_write: bad type\n"); exit(1); }

  free(Z); free(J);
}
