/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: mm_matlab read double to typed matrix
*/

#include "GraphBLAS.h"
#include "test_utils.h"

void mm_setup(FILE *, GrB_Index *, GrB_Index *, GrB_Index *, GrB_Index **,
	      GrB_Index **, double **);
void mm_double(FILE *, GrB_Type, GrB_Index, GrB_Index *, GrB_Index *, double *);
void mm_type(FILE *, GrB_Type, GrB_Index, GrB_Index *, GrB_Index *, double *);
void mm_vecbuild(GrB_Vector, GrB_Type, GrB_Index, GrB_Index *, double *);
void mm_matbuild(GrB_Matrix, GrB_Type, GrB_Index, GrB_Index *, GrB_Index *,
		 double *);

void mm_output(FILE *, GrB_Index, GrB_Index, GrB_Index, GrB_Index **,
	       GrB_Index **, double **);
void mm_print(FILE *, GrB_Type, GrB_Index, GrB_Index *, GrB_Index *, double *);
void mm_vecextract(GrB_Vector, GrB_Type, GrB_Index, GrB_Index *, double *);
void mm_matextract(GrB_Matrix, GrB_Type, GrB_Index, GrB_Index *, GrB_Index *,
		   double *);

// read a matrix written by matlab into a GraphBLAS matrix of a certain type
void mm_matlab(GrB_Matrix *A, FILE *f, GrB_Type thetype)
{
  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  GrB_Info info;
  GrB_Index M, N, nz, *I, *J;
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
  GrB_Index M, N, nz, *I, *J;
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
  GrB_Index M, N, nz, *I, *J;
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
  GrB_Index M, N, nz, *I, *J;
  double *X_f64;

  mm_setup(f, &M, &N, &nz, &I, &J, &X_f64);
  assert ((M == 1) || (N == 1));
  GrB_Index vsize = (M == 1) ? N : M;
  OK (GrB_Vector_new(A, thetype, vsize)); // allocate vector
  mm_type(f, thetype, nz, I, J, X_f64);
  if (M == 1) mm_vecbuild(*A, thetype, nz, J, X_f64); // row vector
  else mm_vecbuild(*A, thetype, nz, I, X_f64); // column vector
}

// write a GraphBLAS matrix to matrix market file
void mm_write(GrB_Matrix A, FILE *f)
{
  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  GrB_Info info;
  GrB_Type thetype;
  GrB_Index M, N, nz, *I, *J;
  double *X_f64;

  OK (GxB_Matrix_type (&thetype, A));
  OK (GrB_Matrix_nrows(&M, A));
  OK (GrB_Matrix_ncols(&N, A));
  OK (GrB_Matrix_nvals(&nz, A));

  mm_output(f, M, N, nz, &I, &J, &X_f64);
  mm_matextract(A, thetype, nz, I, J, X_f64);
  mm_print(f, thetype, nz, I, J, X_f64);
}

// write GraphBLAS vector to matrix market file
void vec_write(GrB_Vector A, FILE *f)
{
  if ((f == NULL) || (A == NULL))
    { printf("file or object pointer is null\n"); exit(1); }

  GrB_Info info;
  GrB_Type thetype;
  GrB_Index M = 1, N, nz, *I, *J;
  double *X_f64;

  OK (GxB_Vector_type (&thetype, A));
  OK (GrB_Vector_size(&N, A));
  OK (GrB_Vector_nvals(&nz, A));

  mm_output(f, M, N, nz, &I, &J, &X_f64);
  mm_vecextract(A, thetype, nz, J, X_f64);
  for (int i = 0; i < nz; i++) I[i] = 0LU; // row vector
  mm_print(f, thetype, nz, I, J, X_f64);
}
