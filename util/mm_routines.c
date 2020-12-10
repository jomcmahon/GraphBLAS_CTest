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

void mm_setup(FILE *, int *, int *, int *, GrB_Index **, GrB_Index **,
	      double **);
void mm_double(FILE *, GrB_Type, int, GrB_Index *, GrB_Index *, double *);
void mm_type(FILE *, GrB_Type, int, GrB_Index *, GrB_Index *, double *);
void mm_matbuild(GrB_Matrix, GrB_Type, int, GrB_Index *, GrB_Index *, double *);
void mm_vecbuild(GrB_Vector, GrB_Type, int, GrB_Index *, double *);

// read a matrix written by matlab into a GraphBLAS matrix of a certain type
void mm_matlab(GrB_Matrix *A, FILE *f, GrB_Type thetype)
{
  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  GrB_Info info;
  int M, N, nz;
  GrB_Index *I, *J;
  double *X_f64;

  mm_setup(f, &M, &N, &nz, &I, &J, &X_f64);
  OK (GrB_Matrix_new(A, thetype, M, N)); // allocate matrix
  mm_double(f, thetype, nz, I, J, X_f64);
  mm_matbuild(*A, thetype, nz, I, J, X_f64);
}

// read a vector written by matlab into a GraphBLAS matrix of a certain type
void vec_matlab(GrB_Vector *A, FILE *f, GrB_Type thetype)
{
  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  GrB_Info info;
  int M, N, nz;
  GrB_Index *I, *J;
  double *X_f64;

  mm_setup(f, &M, &N, &nz, &I, &J, &X_f64);
  assert ((M == 1) || (N == 1));
  GrB_Index vsize = (M == 1) ? N : M;
  OK (GrB_Vector_new(A, thetype, vsize)); // allocate vector
  mm_double(f, thetype, nz, I, J, X_f64);
  if (M == 1) mm_vecbuild(*A, thetype, nz, J, X_f64); // row vector
  else mm_vecbuild(*A, thetype, nz, I, X_f64); // column vector
}

// read a GraphBLAS matrix that has been written by the C Test Suite
void mm_read(GrB_Matrix *A, FILE *f, GrB_Type thetype)
{
  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  GrB_Info info;
  int M, N, nz;
  GrB_Index *I, *J;
  double *X_f64;

  mm_setup(f, &M, &N, &nz, &I, &J, &X_f64);
  OK (GrB_Matrix_new(A, thetype, M, N)); // allocate matrix
  mm_type(f, thetype, nz, I, J, X_f64);
  mm_matbuild(*A, thetype, nz, I, J, X_f64);
}

// read a GraphBLAS vector that has been written by the C Test Suite
void vec_read(GrB_Vector *A, FILE *f, GrB_Type thetype)
{
  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  GrB_Info info;
  int M, N, nz;
  GrB_Index *I, *J;
  double *X_f64;

  mm_setup(f, &M, &N, &nz, &I, &J, &X_f64);
  assert ((M == 1) || (N == 1));
  GrB_Index vsize = (M == 1) ? N : M;
  OK (GrB_Vector_new(A, thetype, vsize)); // allocate vector
  mm_type(f, thetype, nz, I, J, X_f64);
  if (M == 1) mm_vecbuild(*A, thetype, nz, J, X_f64); // row vector
  else mm_vecbuild(*A, thetype, nz, I, X_f64); // column vector
}
