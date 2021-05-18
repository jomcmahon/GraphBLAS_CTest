/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: routines for reading and checking test files
*/

#include "GraphBLAS.h"
#include "test_utils.h"

typedef struct {
  bool uflag;
  double val;
} wildtype;

void approx_equal_d(void *zin, const void *xin, const void *yin);

void wild_binop(void *z, const void *x, const void *y)
{
  wildtype *zp = (wildtype *)z; wildtype *xp = (wildtype *)x;
  zp->uflag = xp->uflag; zp->val = xp->val;
}

void wild_approx(void *z, const void *x, const void *y)
{
  wildtype *xp = (wildtype *)x; wildtype *yp = (wildtype *)y;
  approx_equal_d(z, &xp->val, &yp->val);
}

void user_binop_f32(void *z, const void *x, const void *y)
{
  float delta = (*((float *)x)) - (*((float *)y));
  (*((float *)z)) = delta * delta;
}

void user_unop_f32(void *z, const void *x)
{
  float delta = *((float *)x);
  *((float *)z) = 2 * delta;
}

#if GxB_IMPLEMENTATION >= GxB_VERSION (4,0,0)
bool user_selop(const GrB_Index i, const GrB_Index j, const void *z,
		const void *thunk)
{
  return (i == j);
}
#else
bool user_selop(const GrB_Index i, const GrB_Index j, const GrB_Index nrows,
		const GrB_Index ncols, const void *z, const void *thunk)
{
  return (i == j);
}
#endif

void get_User_Type(GrB_Type *type) {
  GrB_Info info;
  OK(GrB_Type_new(type, sizeof(wildtype)));
}

void get_User_Semiring(GrB_Semiring *semi)
{
  GrB_Info info;
  GrB_Monoid mon;
  GrB_BinaryOp binop;
  get_User_Monoid(&mon);
  get_User_BinaryOp(&binop);
  OK(GrB_Semiring_new(semi, mon, binop));
}

void get_User_Monoid(GrB_Monoid *mon)
{
  GrB_BinaryOp binop;
  get_User_BinaryOp(&binop);
  float id = 0; float term = 1;
  GxB_Monoid_terminal_new(mon, binop, id, term);
}
  
void get_User_BinaryOp(GrB_BinaryOp *binop)
{
  GrB_Info info;
  OK(GrB_BinaryOp_new(binop, user_binop_f32, GrB_FP32, GrB_FP32, GrB_FP32));
}

void get_User_UnaryOp(GrB_UnaryOp *unop)
{
  GrB_Info info;
  OK(GrB_UnaryOp_new(unop, user_unop_f32, GrB_FP32, GrB_FP32));
}

void get_User_SelectOp(GxB_SelectOp *selop, GrB_Type type)
{
  GrB_Info info;
  OK(GxB_SelectOp_new(selop, user_selop, type, type));
}

void get_User_Scalar(GxB_Scalar *scal)
{
  GrB_Info info;
  GrB_Type type;
  get_User_Type(&type);
  OK(GxB_Scalar_new(scal, type));
}

void get_UDT_Scalar(void **p)
{
  wildtype *XW = malloc(sizeof(wildtype));
  *p = XW;
}

void build_Matrix_UDT(GrB_Matrix A, GrB_Type thetype, GrB_Index *I,
		      GrB_Index *J, double *X, GrB_Index nz)
{
  GrB_Info info;
  wildtype *XW = malloc(nz * sizeof(wildtype));
  for (int i = 0; i < nz; i++) {
    XW[i].uflag = (X[i] > 0) ? true : false;
    XW[i].val = X[i];
  }
  GrB_BinaryOp binop;
  OK(GrB_BinaryOp_new(&binop, wild_binop, thetype, thetype, thetype));
  OK(GrB_Matrix_build(A, I, J, (void *)XW, nz, binop));
}

void build_Vector_UDT(GrB_Vector A, GrB_Type thetype, GrB_Index *I,
		      double *X, GrB_Index nz)
{
  GrB_Info info;
  wildtype *XW = malloc(nz * sizeof(wildtype));
  for (int i = 0; i < nz; i++) {
    XW[i].uflag = (X[i] > 0) ? true : false;
    XW[i].val = X[i];
  }
  GrB_BinaryOp binop;
  OK(GrB_BinaryOp_new(&binop, wild_binop, thetype, thetype, thetype));
  OK(GrB_Vector_build(A, I, (void *)XW, nz, binop));
}

void extract_Matrix_UDT(GrB_Index *I, GrB_Index *J, double *X, GrB_Index nv,
			GrB_Index *nz, GrB_Matrix A)
{
  GrB_Info info;
  wildtype *XW = malloc(nv * sizeof(wildtype));
  OK(GrB_Matrix_extractTuples(I, J, (void *)XW, nz, A));
  for (int i = 0; i < nv; i++) X[i] = XW[i].val;
}

void extract_Vector_UDT(GrB_Index *I, double *X, GrB_Index nv, GrB_Index *nz,
			GrB_Vector A)
{
  GrB_Info info;
  wildtype *XW = malloc(nv * sizeof(wildtype));
  OK(GrB_Vector_extractTuples(I, (void *)XW, nz, A));
  for (int i = 0; i < nv; i++) X[i] = XW[i].val;
}

void get_UDT_BinaryOp(GrB_BinaryOp *approx, GrB_Type thetype)
{
  GrB_Info info;
  OK(GrB_BinaryOp_new(approx, wild_approx, GrB_BOOL, thetype, thetype));
}
