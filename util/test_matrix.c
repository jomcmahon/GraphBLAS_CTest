/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: routines for reading and checking test files
*/

#include "GraphBLAS.h"
#include "test_utils.h"

#define FNAME_SIZE 4096
#define INSTR_SIZE 256

void mm_matlab(GrB_Matrix *, FILE *, GrB_Type);
void vec_matlab(GrB_Vector *, FILE *, GrB_Type);
void mm_read(GrB_Matrix *, FILE *, GrB_Type);
void vec_read(GrB_Vector *, FILE *, GrB_Type);
void mm_write(GrB_Matrix, FILE *);
void vec_write(GrB_Vector, FILE *);
void ind_read(GrB_Index **, GrB_Index *, FILE *);
bool is_approx_equal_mat(GrB_Matrix, GrB_Matrix) ;
bool is_approx_equal_vec(GrB_Vector, GrB_Vector) ;
bool is_equal_ind(GrB_Index *I, GrB_Index ni, GrB_Index *J, GrB_Index nj);

// construct path and file name and read matrix written by matlab
void read_matlab_matrix(const char *base, const char *name, GrB_Type type,
			GrB_Matrix *A)
{
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE *fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  mm_matlab(A, fp, type);
  fclose(fp);
}

// construct path and file name from type and write matrix from C Test Suite
void write_typed_matrix(const char *base, const char *name, GrB_Matrix A)
{
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE *fp = fopen(filename, "w");
  if (!fp) { printf("Failed to open test output %s\n", filename); exit(1); }
  mm_write(A, fp);
  fclose(fp);
}

// construct path and file name from type and compare C Test Suite matrices
bool check_typed_matrix(const char *base, const char *name, GrB_Matrix A)
{
  GrB_Info info;
  GrB_Matrix T;
  GrB_Type type; OK (GxB_Matrix_type(&type, A));
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE *fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  mm_read(&T, fp, type);
  fclose(fp);
  bool eqtest = is_approx_equal_mat(T, A);
  OK (GrB_free(&T));
  if (eqtest) printf("%s: PASSED\n", name); else printf("%s: FAILED\n", name);
  return !eqtest; // return true if error, false if ok
}

// construct path and file name and read vector written by matlab
void read_matlab_vector(const char *base, const char *name, GrB_Type type,
			    GrB_Vector *A)
{
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE * fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  vec_matlab(A, fp, type);
  fclose(fp);
}

// construct path and file name from type and write vector from C Test Suite
void write_typed_vector(const char *base, const char *name, GrB_Vector A)
{
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE * fp = fopen(filename, "w");
  if (!fp) { printf("Failed to open test output %s\n", filename); exit(1); }
  vec_write(A, fp);
  fclose(fp);
}

// construct path and file name from type and compare C Test Suite vectors
bool check_typed_vector(const char *base, const char *name, GrB_Vector A)
{
  GrB_Info info;
  GrB_Vector T;
  GrB_Type type; OK (GxB_Vector_type(&type, A));
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE * fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  vec_read(&T, fp, type);
  fclose(fp);
  bool eqtest = is_approx_equal_vec(T, A);
  OK (GrB_free(&T));
  if (eqtest) printf("%s: PASSED\n", name); else printf("%s: FAILED\n", name);
  return !eqtest; // return true if error, false if ok
}

// read an index file written from matlab as dense vector
void read_test_index(const char *tname, const char *mat, GrB_Index **Ind,
		     GrB_Index *nInd)
{
  if (!strcmp(mat, "ALL")) *Ind = (GrB_Index *)GrB_ALL;
  else {
    char filename[FNAME_SIZE];
    sprintf(filename, "data/%s/%s.mm", tname, mat);
    FILE * fp = fopen(filename, "r");
    if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
    ind_read(Ind, nInd, fp); fclose(fp);
    if (strstr(mat, "RANGE")) {
      assert (*nInd >= 2); *nInd = (GrB_Index)GxB_RANGE;
    } else if (strstr(mat, "STRIDE")) {
      assert (*nInd >= 3); *nInd = (GrB_Index)GxB_STRIDE;
      GrB_Index *ip = *Ind;
      ip[2]++;
    } else if (strstr(mat, "BACK")) {
      assert (*nInd >= 3); *nInd = (GrB_Index)GxB_BACKWARDS;
      GrB_Index *ip = *Ind;
      ip[2]++;
    }
  }
}

// get array size based on index vector
GrB_Index get_index_dim(GrB_Index *I, GrB_Index ni, GrB_Index asize)
{
  if (I == GrB_ALL) return asize;
  else if ((ni == GxB_RANGE) || (ni == GxB_STRIDE)) return I[1] + 1; // max
  else if (ni == GxB_BACKWARDS) return I[0] + 1; // max index
  else return I[ni - 1] + 1; // assume sorted and max is at end
}

// get array size based on index vector
GrB_Index get_index_size(GrB_Index *I, GrB_Index ni, GrB_Index asize)
{
  if (I == GrB_ALL) return asize;
  else if (ni == GxB_RANGE) return I[1] - I[0] + 1;
  else if (ni == GxB_STRIDE) return ((I[1] - I[0]) / I[2]) + 1;
  else if (ni == GxB_BACKWARDS) return ((I[0] - I[1]) / I[2]) + 1;
  else return ni;
}

// get matrix input size based on descriptor
void get_inp_size(GrB_Descriptor desc, GrB_Matrix A, GrB_Index *nrows,
		  GrB_Index *ncols, GrB_Desc_Field dfield)
{
  GrB_Info info;
  GrB_Desc_Value descval = GxB_DEFAULT;
  if (desc) { OK (GxB_Desc_get(desc, dfield, &descval)); }
  if (descval == GrB_TRAN)
    { OK (GrB_Matrix_ncols(nrows, A)); OK (GrB_Matrix_nrows(ncols, A)); }
  else { OK (GrB_Matrix_nrows(nrows, A)); OK (GrB_Matrix_ncols(ncols, A)); }
}  

// get input and output types of unary operator
void get_types_unop(GrB_UnaryOp unop, GrB_Type *xtype, GrB_Type *ztype)
{
  GrB_Info info;
  OK (GxB_UnaryOp_xtype(xtype, unop)); // input0 type
  OK (GxB_UnaryOp_ztype(ztype, unop)); // output type
}

// get input and output types of binary operator
void get_types_binop(GrB_BinaryOp binop, GrB_Type *xtype, GrB_Type *ytype,
		     GrB_Type *ztype)
{
  GrB_Info info;
  OK (GxB_BinaryOp_xtype(xtype, binop)); // input0 type
  OK (GxB_BinaryOp_ytype(ytype, binop)); // input1 type
  OK (GxB_BinaryOp_ztype(ztype, binop)); // output type
}

// get input and output types of monoid
void get_types_monoid(GrB_Monoid mon, GrB_Type *xtype, GrB_Type *ytype,
		      GrB_Type *ztype)
{
  GrB_Info info;
  GrB_BinaryOp binop;
  OK (GxB_Monoid_operator(&binop, mon)); // get binary op from monoid
  get_types_binop(binop, xtype, ytype, ztype);
}

// get input and output types of semiring
void get_types_semiring(GrB_Semiring semi, GrB_Type *xtype, GrB_Type *ytype,
			GrB_Type *ztype)
{
  GrB_Info info;
  GrB_Monoid addmon;
  GrB_BinaryOp mulop;
  GrB_Type unused0, unused1;
  OK (GxB_Semiring_multiply(&mulop, semi));
  get_types_binop(mulop, xtype, ytype, &unused0);
  OK (GxB_Semiring_add(&addmon, semi));
  get_types_monoid(addmon, &unused0, &unused1, ztype);
}
