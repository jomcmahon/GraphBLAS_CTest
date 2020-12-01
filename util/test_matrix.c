/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: routines for reading and checking test files
*/

#include "GraphBLAS.h"
#include "test_utils.h"

#define FNAME_SIZE 4096
#define INSTR_SIZE 256

// get file name base from desired type, append string to name
void get_typed_name(char *in, const char *name, GrB_Type type)
{
  strcpy(in, name);
  if (type == GrB_BOOL) strcat(in, "_bool");
  else if (type == GrB_INT8) strcat(in, "_i8");
  else if (type == GrB_INT16) strcat(in, "_i16");
  else if (type == GrB_INT32) strcat(in, "_i32");
  else if (type == GrB_INT64) strcat(in, "_i64");
  else if (type == GrB_UINT8) strcat(in, "_u8");
  else if (type == GrB_UINT16) strcat(in, "_u16");
  else if (type == GrB_UINT32) strcat(in, "_u32");
  else if (type == GrB_UINT64) strcat(in, "_u64");
  else if (type == GrB_FP32) strcat(in, "_f32");
  else if (type == GrB_FP64) strcat(in, "_f64");
  else { printf("bad type\n"); exit(1); }
}

// construct path and file name and read matrix written by matlab
GrB_Info read_matlab_matrix(const char *base, const char *name, GrB_Type type,
			    GrB_Matrix *A)
{
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE *fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  GrB_Info info = mm_matlab(A, fp, type);
  fclose(fp);
  return info;
}

// construct path and file name from type and read matrix from C Test Suite
GrB_Info read_typed_matrix(const char *base, const char *name, GrB_Type type,
			   GrB_Matrix *A)
{
  char in[INSTR_SIZE], filename[FNAME_SIZE];
  get_typed_name(in, name, type);
  sprintf(filename, "data/%s/%s.mm", base, in);
  FILE *fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  GrB_Info info = mm_read(A, fp, type);
  fclose(fp);
  return info;
}

// construct path and file name from type and write matrix from C Test Suite
GrB_Info write_typed_matrix(const char *base, const char *name, GrB_Type type,
			    GrB_Matrix A)
{
  char in[INSTR_SIZE], filename[FNAME_SIZE];
  get_typed_name(in, name, type);
  sprintf(filename, "data/%s/%s.mm", base, in);
  FILE *fp = fopen(filename, "w");
  if (!fp) { printf("Failed to open test output %s\n", filename); exit(1); }
  GrB_Info info = mm_write(A, fp);
  fclose(fp);
  return info;
}

// construct path and file name from type and compare C Test Suite matrices
bool check_typed_matrix(const char *base, const char *name, GrB_Type type,
			GrB_Matrix A)
{
  GrB_Info info;
  GrB_Matrix T;
  char in[INSTR_SIZE]; get_typed_name(in, "", type); printf("%s", in);
  OK (read_typed_matrix(base, name, type, &T));
  bool eqtest = is_approx_equal_mat(T, A);
  GrB_free(&T);
  return eqtest;
}

// construct path and file name and read vector written by matlab
GrB_Info read_matlab_vector(const char *base, const char *name, GrB_Type type,
			    GrB_Vector *A)
{
  char filename[FNAME_SIZE];
  sprintf(filename, "data/%s/%s.mm", base, name);
  FILE * fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  GrB_Info info = vec_matlab(A, fp, type);
  fclose(fp);
  return info;
}

// construct path and file name from type and read vector from C Test Suite
GrB_Info read_typed_vector(const char *base, const char *name, GrB_Type type,
			   GrB_Vector *A)
{
  char in[INSTR_SIZE], filename[FNAME_SIZE];
  get_typed_name(in, name, type);
  sprintf(filename, "data/%s/%s.mm", base, in);
  FILE * fp = fopen(filename, "r");
  if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
  GrB_Info info = vec_read(A, fp, type);
  fclose(fp);
  return info;
}

// construct path and file name from type and write vector from C Test Suite
GrB_Info write_typed_vector(const char *base, const char *name, GrB_Type type,
			    GrB_Vector A)
{
  char in[INSTR_SIZE], filename[FNAME_SIZE];
  get_typed_name(in, name, type);
  sprintf(filename, "data/%s/%s.mm", base, in);
  FILE * fp = fopen(filename, "w");
  if (!fp) { printf("Failed to open test output %s\n", filename); exit(1); }
  GrB_Info info = vec_write(A, fp);
  fclose(fp);
  return info;
}

// construct path and file name from type and compare C Test Suite vectors
bool check_typed_vector(const char *base, const char *name, GrB_Type type,
			GrB_Vector A)
{
  GrB_Info info;
  GrB_Vector T;
  char in[INSTR_SIZE]; get_typed_name(in, "", type); printf("%s", in);
  OK (read_typed_vector(base, name, type, &T));
  bool eqtest = is_approx_equal_vec(T, A);
  GrB_free(&T);
  return eqtest;
}

// read an index file written from matlab as dense vector
GrB_Info read_test_index(const char *tname, const char *mat, GrB_Index **Ind,
			 GrB_Index *nInd)
{
  GrB_Info info = GrB_SUCCESS;
  if (!strcmp(mat, "ALL")) *Ind = (GrB_Index *)GrB_ALL;
  else {
    char filename[FNAME_SIZE];
    sprintf(filename, "data/%s/%s.mm", tname, mat);
    FILE * fp = fopen(filename, "r");
    if (!fp) { printf("Failed to open test input %s\n", filename); exit(1); }
    info = ind_read(Ind, nInd, fp); fclose(fp);
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
  return info;
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
GrB_Info get_inp_size(GrB_Descriptor desc, GrB_Matrix A, GrB_Index *nrows,
		      GrB_Index *ncols, GrB_Desc_Field dfield)
{
  GrB_Info info;
  GrB_Desc_Value descval = GxB_DEFAULT;
  if (desc) { OK (GxB_Desc_get(desc, dfield, &descval)); }
  if (descval == GrB_TRAN)
    { OK (GrB_Matrix_ncols(nrows, A)); OK (GrB_Matrix_nrows(ncols, A)); }
  else { OK (GrB_Matrix_nrows(nrows, A)); OK (GrB_Matrix_ncols(ncols, A)); }
  return GrB_SUCCESS;
}  

// get input and output types of unary operator
GrB_Info get_types_unop(GrB_UnaryOp unop, GrB_Type *xtype, GrB_Type *ztype)
{
  GrB_Info info;
  OK (GxB_UnaryOp_xtype(xtype, unop)); // input0 type
  OK (GxB_UnaryOp_ztype(ztype, unop)); // output type
  return GrB_SUCCESS;
}

// get input and output types of binary operator
GrB_Info get_types_binop(GrB_BinaryOp binop, GrB_Type *xtype, GrB_Type *ytype,
			 GrB_Type *ztype)
{
  GrB_Info info;
  OK (GxB_BinaryOp_xtype(xtype, binop)); // input0 type
  OK (GxB_BinaryOp_ytype(ytype, binop)); // input1 type
  OK (GxB_BinaryOp_ztype(ztype, binop)); // output type
  return GrB_SUCCESS;
}

// get input and output types of monoid
GrB_Info get_types_monoid(GrB_Monoid mon, GrB_Type *xtype, GrB_Type *ytype,
			  GrB_Type *ztype)
{
  GrB_Info info;
  GrB_BinaryOp binop;
  OK (GxB_Monoid_operator(&binop, mon)); // get binary op from monoid
  return get_types_binop(binop, xtype, ytype, ztype);
}

// get input and output types of semiring
GrB_Info get_types_semiring(GrB_Semiring semi, GrB_Type *xtype, GrB_Type *ytype,
			    GrB_Type *ztype)
{
  GrB_Info info;
  GrB_Monoid addmon;
  GrB_BinaryOp mulop;
  GrB_Type unused0, unused1;
  OK (GxB_Semiring_multiply(&mulop, semi));
  OK (get_types_binop(mulop, xtype, ytype, &unused0));
  OK (GxB_Semiring_add(&addmon, semi));
  return get_types_monoid(addmon, &unused0, &unused1, ztype);
}
