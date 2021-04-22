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
  float val;
} wildtype;

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

bool user_selop(const GrB_Index i, const GrB_Index j, const GrB_Index nrows,
		const GrB_Index ncols, const void *z, const void *thunk)
{
  return (i == j);
}

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
