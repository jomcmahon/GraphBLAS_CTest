/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test matrix equality with tolerance
*/

#include "GraphBLAS.h"
#include "test_utils.h"

#define EPS 1e-12

// approximate equality for double
void approx_equal_d(void *zin, const void *xin, const void *yin)
{
  bool *z = (bool *)zin;
  if (zin == NULL) return;
  if (xin == yin) *z = true;
  if ((xin == NULL) || (yin == NULL)) *z = false;

  double xval = *(double *)xin;
  double yval = *(double *)yin;

  int xclass = fpclassify (xval);
  int yclass = fpclassify (yval);
  if (xclass != yclass) *z = false;
  else {
    if ((xclass != FP_ZERO) && (xclass != FP_NAN) && (xclass != FP_INFINITE)) {
      double err = fabs(xval - yval) / fabs(xval);
      if (err <= EPS) *z = true; else *z = false;
    } else *z = true;
  }
}

// approximate equality for float
void approx_equal_f(void *zin, const void *xin, const void *yin)
{
  bool *z = (bool *)zin;
  if (zin == NULL) return;
  if (xin == yin) *z = true;
  if ((xin == NULL) || (yin == NULL)) *z = false;

  float xval = *(float *)xin;
  float yval = *(float *)yin;

  int xclass = fpclassify (xval);
  int yclass = fpclassify (yval);
  if (xclass != yclass) *z = false;
  else {
    if ((xclass != FP_ZERO) && (xclass != FP_NAN) && (xclass != FP_INFINITE)) {
      double err = fabsf(xval - yval) / fabsf(xval);
      if (err <= EPS) *z = true; else *z = false;
    } else *z = true;
  }
}

// return values:
//   GrB_SUCCESS if successful
//   GrB_NULL_POINTER if result is NULL
//   GrB_NO_VALUE if A and B are not conformant and FP64
bool is_approx_equal_mat(GrB_Matrix A, GrB_Matrix B)
{
    GrB_Info info ;
    GrB_Type atype, btype;
    GrB_Matrix C = NULL ;
    GrB_Index nrows1, ncols1, nrows2, ncols2, nvals, nvals1, nvals2 ;
    GrB_BinaryOp approx;
    bool result;

    // check the type of A and B
    OK (GxB_Matrix_type (&atype, A)) ;
    OK (GxB_Matrix_type (&btype, B)) ;
    if (atype != btype) {
		printf("Error: atype != btype\n");
		return false;
	}

    // check the size of A and B
    OK (GrB_Matrix_nrows (&nrows1, A)) ;
    OK (GrB_Matrix_nrows (&nrows2, B)) ;
    if (nrows1 != nrows2) {
		printf("Error: anrows != bnrows\n");
		return false;
	}

    OK (GrB_Matrix_ncols (&ncols1, A)) ;
    OK (GrB_Matrix_ncols (&ncols2, B)) ;
    if (ncols1 != ncols2) {
		printf("Error: ancols != bncols\n");
		return false;
	}

    // check the # entries in A and B
    OK (GrB_Matrix_nvals (&nvals1, A)) ;
    OK (GrB_Matrix_nvals (&nvals2, B)) ;
    if (nvals1 != nvals2) {
		printf("Error: anvals != bnvals: %ld %ld\n", nvals1, nvals2);
		fflush(stdout);
		return false;
	}

    // C = A .* B, where the pattern of C is the intersection of A and B
    OK (GrB_Matrix_new (&C, GrB_BOOL, nrows1, ncols1)) ;
    if      (atype == GrB_BOOL  ) approx = GrB_EQ_BOOL   ;
    else if (atype == GrB_INT8  ) approx = GrB_EQ_INT8   ;
    else if (atype == GrB_INT16 ) approx = GrB_EQ_INT16  ;
    else if (atype == GrB_INT32 ) approx = GrB_EQ_INT32  ;
    else if (atype == GrB_INT64 ) approx = GrB_EQ_INT64  ;
    else if (atype == GrB_UINT8 ) approx = GrB_EQ_UINT8  ;
    else if (atype == GrB_UINT16) approx = GrB_EQ_UINT16 ;
    else if (atype == GrB_UINT32) approx = GrB_EQ_UINT32 ;
    else if (atype == GrB_UINT64) approx = GrB_EQ_UINT64 ;
    else if (atype == GrB_FP32) {
      OK (GrB_BinaryOp_new (&approx, approx_equal_f, GrB_BOOL, atype, atype));
    } else if (atype == GrB_FP64) {
      OK (GrB_BinaryOp_new (&approx, approx_equal_d, GrB_BOOL, atype, atype));
    } else { printf("Bad type\n"); exit(1); }

    OK (GrB_eWiseMult (C, NULL, NULL, approx, A, B, NULL)) ;

    // ensure C has the same number of entries as A and B
    OK (GrB_Matrix_nvals (&nvals, C)) ;
    if (nvals != nvals1) { // pattern of A and B are different
	  printf("A and B have different patterns\n");
      GrB_free (&C) ;
      return false;
    }

    // result = and (C)
    OK (GrB_reduce (&result, NULL, GxB_LAND_BOOL_MONOID, C, NULL)) ;

    // free workspace and return result
    GrB_free (&C) ;
    return result;
}

// return values:
//   GrB_SUCCESS if successful
//   GrB_NULL_POINTER if result is NULL
//   GrB_NO_VALUE if A and B are not conformant and FP64
bool is_approx_equal_vec(GrB_Vector A, GrB_Vector B)
{
    GrB_Info info ;
    GrB_Type atype, btype;
    GrB_Vector C = NULL ;
    GrB_Index ncols1, ncols2, nvals, nvals1, nvals2 ;
    GrB_BinaryOp approx;
    bool result;

    // check the type of A and B
    OK (GxB_Vector_type (&atype, A)) ;
    OK (GxB_Vector_type (&btype, B)) ;
    if (atype != btype) return false;

    // check the size of A and B
    OK (GrB_Vector_size (&ncols1, A)) ;
    OK (GrB_Vector_size (&ncols2, B)) ;
    if (ncols1 != ncols2) return false;

    // check the # entries in A and B
    OK (GrB_Vector_nvals (&nvals1, A)) ;
    OK (GrB_Vector_nvals (&nvals2, B)) ;
    if (nvals1 != nvals2) return false;

    // C = A .* B, where the pattern of C is the intersection of A and B
    OK (GrB_Vector_new (&C, GrB_BOOL, ncols1)) ;
    if      (atype == GrB_BOOL  ) approx = GrB_EQ_BOOL   ;
    else if (atype == GrB_INT8  ) approx = GrB_EQ_INT8   ;
    else if (atype == GrB_INT16 ) approx = GrB_EQ_INT16  ;
    else if (atype == GrB_INT32 ) approx = GrB_EQ_INT32  ;
    else if (atype == GrB_INT64 ) approx = GrB_EQ_INT64  ;
    else if (atype == GrB_UINT8 ) approx = GrB_EQ_UINT8  ;
    else if (atype == GrB_UINT16) approx = GrB_EQ_UINT16 ;
    else if (atype == GrB_UINT32) approx = GrB_EQ_UINT32 ;
    else if (atype == GrB_UINT64) approx = GrB_EQ_UINT64 ;
    else if (atype == GrB_FP32) {
      OK (GrB_BinaryOp_new (&approx, approx_equal_f, GrB_BOOL, atype, atype));
    } else if (atype == GrB_FP64) {
      OK (GrB_BinaryOp_new (&approx, approx_equal_d, GrB_BOOL, atype, atype));
    } else { printf("Bad type\n"); exit(1); }

    OK (GrB_eWiseMult (C, NULL, NULL, approx, A, B, NULL)) ;

    // ensure C has the same number of entries as A and B
    OK (GrB_Vector_nvals (&nvals, C)) ;
    if (nvals != nvals1) { // pattern of A and B are different
      GrB_free (&C) ;
      return false;
    }

    // result = and (C)
    OK (GrB_reduce (&result, NULL, GxB_LAND_BOOL_MONOID, C, NULL)) ;

    // free workspace and return result
    GrB_free (&C) ;
    return result;
}
