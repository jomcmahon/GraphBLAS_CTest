/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: mm_write from matrix of certain type
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

// write a GraphBLAS matrix to matrix market file
GrB_Info mm_write(GrB_Matrix A, FILE *f)
{
  GrB_Info info;
  MM_typecode matcode;
  GrB_Type thetype;
  GrB_Index M, N, nz, nvals;

  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  mm_set_matrix(&matcode);
  mm_set_coordinate(&matcode);
  mm_set_real(&matcode);
  mm_set_general(&matcode);

  if (mm_write_banner(f, matcode) != 0)
    { printf("couldn't write mtx banner\n"); exit(1); }

  OK (GxB_Matrix_type (&thetype, A));
  OK (GrB_Matrix_nrows(&M, A));
  OK (GrB_Matrix_ncols(&N, A));
  OK (GrB_Matrix_nvals(&nz, A));
  nvals = nz;

  if (mm_write_mtx_crd_size(f, M, N, nz) !=0)
    { printf("couldn't write sizes\n"); exit(1); }

  GrB_Index *I = malloc(nz * sizeof(GrB_Index));
  if (I == NULL) { printf("problem with malloc I\n"); exit(1); }
  GrB_Index *J = malloc(nz * sizeof(GrB_Index));
  if (J == NULL) { printf("problem with malloc J\n"); exit(1); }
  double *Z = malloc (nz * sizeof(double)); // allocate maximum size
  if (Z == NULL) { printf("problem with malloc Z\n"); exit(1); }

#define SET_ELT							  \
  OK (GrB_Matrix_extractTuples (I, J, X, &nvals, A));		  \
  if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }	  \
  for (int k = 0 ; k < nvals ; k++)				  \
    fprintf(f, "%ld %ld %d\n", I[k]+1, J[k]+1, X[k]);

  if (thetype == GrB_BOOL) { bool *X = (bool *)Z; SET_ELT; }
  else if (thetype == GrB_INT8) { int8_t *X = (int8_t *)Z; SET_ELT; }
  else if (thetype == GrB_INT16) { int16_t *X = (int16_t *)Z; SET_ELT; }
  else if (thetype == GrB_INT32) { int32_t *X = (int32_t *)Z; SET_ELT; }
  else if (thetype == GrB_INT64) {
    int64_t *X = (int64_t *)Z;
    OK (GrB_Matrix_extractTuples (I, J, X, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%ld %ld %ld\n", I[k]+1, J[k]+1, X[k]);
  } else if (thetype == GrB_UINT8) { uint8_t *X = (uint8_t *)Z; SET_ELT; }
  else if (thetype == GrB_UINT16) { uint16_t *X = (uint16_t *)Z; SET_ELT; }
  else if (thetype == GrB_UINT32) { uint32_t *X = (uint32_t *)Z; SET_ELT; }
  else if (thetype == GrB_UINT64) {
    uint64_t *X = (uint64_t *)Z;
    OK (GrB_Matrix_extractTuples (I, J, X, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%ld %ld %lu\n", I[k]+1, J[k]+1, X[k]);
  } else if (thetype == GrB_FP32) {
    float *X = (float *)Z;
    OK (GrB_Matrix_extractTuples (I, J, X, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%ld %ld %.16f\n", I[k]+1, J[k]+1, X[k]);
  } else if (thetype == GrB_FP64) {
    OK (GrB_Matrix_extractTuples (I, J, Z, &nvals, A));
    if (nz != nvals) { printf("Bad number of vals\n"); exit(1); }
    for (int k = 0 ; k < nvals ; k++)
      fprintf(f, "%ld %ld %.16f\n", I[k]+1, J[k]+1, Z[k]);
  } else { printf("mm_write: bad type\n"); exit(1); }

  free(Z);
  free(J);
  free(I);

  return (GrB_SUCCESS) ;
}
