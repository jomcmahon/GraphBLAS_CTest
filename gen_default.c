/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: routines to generate iteration and argument specifications
*/

#include "GraphBLAS.h"
#include "util/test_utils.h"

typedef enum { TYPE_I, MON_I, ANY_I, PAIR_I, PLUS_I, MIN_I, MINV_I, EADDM_I,
	       SELOP_I, SEMI_I, TOTAL_I } iter_spec;

bool find_in_list(int *list, int f, int size)
{
  for (int i = 0; i < size; i++) if (f == list[i]) return true;
  return false;
}

void semi_iteration_plus_times(int **sptr)
{
  set_test_spec(DESC, 4, sptr); // first four
  set_test_spec(SEMI, num_Types(), sptr); // allocate array
  int g = 1;
  sptr[SEMI][g++] = find_Semiring(GxB_ANY_PAIR_BOOL);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT8);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT8);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT16);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT16);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT32);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT32);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_INT64);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_UINT64);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_FP32);
  sptr[SEMI][g++] = find_Semiring(GxB_PLUS_TIMES_FP64);
}

void accum_iteration_plus(int **sptr)
{
  set_test_spec(ACCUM, num_Types(), sptr); // allocate array
  int g = 1;
  sptr[ACCUM][g++] = find_BinaryOp(GxB_ANY_BOOL);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_INT8);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_UINT8);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_INT16);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_UINT16);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_INT32);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_UINT32);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_INT64);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_UINT64);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_FP32);
  sptr[ACCUM][g++] = find_BinaryOp(GrB_PLUS_FP64);
}

void unop_iteration_minv(int **specptr)
{
  int b = 0, *blocked = malloc(9 * sizeof(int)); // don't test MINV ops
  blocked[b++] = find_UnaryOp(GrB_MINV_BOOL);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT8);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT8);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT16);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT16);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT32);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT32);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT64);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT64);

  set_test_spec(UNOP, num_UnaryOps() - 9, specptr);
  for (int i = 0, actual = 1; i < num_UnaryOps(); i++)
    if (!find_in_list(blocked, i, 9)) specptr[UNOP][actual++] = i;
}

void binop_iteration_any(int **sptr)
{
  set_test_spec(DESC, 4, sptr); // first four
  set_test_spec(BINOP, num_Types(), sptr); // allocate array
  int g = 1;
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_BOOL);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT8);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT8);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT16);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT16);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_INT64);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_UINT64);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_FP32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_ANY_FP64);
}

void binop_iteration_pair(int **sptr)
{
  set_test_spec(BINOP, num_Types(), sptr); // allocate array
  int g = 1;
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_BOOL);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT8);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT8);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT16);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT16);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_INT64);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_UINT64);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_FP32);
  sptr[BINOP][g++] = find_BinaryOp(GxB_PAIR_FP64);
}

void binop_iteration_plus(int **sptr)
{
  set_test_spec(BINOP, num_Types(), sptr); // allocate array
  int g = 1;
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_BOOL);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT8);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT8);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT16);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT16);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT64);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT64);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_FP32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_FP64);
}

void binop_iteration_min(int **sptr)
{
  set_test_spec(BINOP, num_Types(), sptr); // allocate array
  int g = 1;
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_BOOL);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT8);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT8);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT16);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT16);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_INT64);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_UINT64);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_FP32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_MIN_FP64);
}

void eAddM_iteration(int **sptr)
{
  set_test_spec(DESC, 4, sptr); // first four
  set_test_spec(SEMI, 1, sptr); // allocate array
  sptr[SEMI][1] = find_Semiring(GxB_ANY_PAIR_BOOL);
  set_test_spec(BINOP, num_Types() - 1, sptr); // allocate array
  int g = 1;
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT8);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT8);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT16);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT16);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_INT64);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_UINT64);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_FP32);
  sptr[BINOP][g++] = find_BinaryOp(GrB_PLUS_FP64);
}

void iterate_defs(testargs *myargs, char *i0, char *i1, char *m, char *iv,
		  iter_spec iter_sel)
{
  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, i0);
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, i1);
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
  if (myargs->generate) { // create spec files
    int **myspec = spec_from_args(myargs); // args

    switch (iter_sel) {
    case TYPE_I: set_test_spec(TYPE, num_Types(), myspec); break; // all types
    case MON_I: set_test_spec(MON, num_Monoids(), myspec); break; // all monoids
    case ANY_I: binop_iteration_any(myspec); break; // ANY binops
    case PAIR_I: binop_iteration_pair(myspec); break; // PAIR binops
    case PLUS_I: binop_iteration_plus(myspec); break; // PLUS binops
    case MIN_I: binop_iteration_min(myspec); break; // PLUS binops
    case MINV_I: unop_iteration_minv(myspec); break; // MINV unops
    case EADDM_I: eAddM_iteration(myspec); break; // eAddM
    case SELOP_I: set_test_spec(TYPE, num_Types(), myspec); // all types
      set_test_spec(SELOP, num_SelectOps(), myspec); break; // all selops
    case SEMI_I: semi_iteration_plus_times(myspec); break; // semirings
    default: break;
    }

    testargs *myargsC = malloc(sizeof(testargs)); // copy args
    memcpy(myargsC, myargs, sizeof(testargs));
    print_test_spec(myargsC, myspec, "D"); // default
    if (strlen(m) > 0) {
      memcpy(myargsC, myargs, sizeof(testargs));
      strcpy(myargsC->mask, m);
      print_test_spec(myargsC, myspec, "M"); // with mask
    }
    if (strlen(iv) > 0) {
      accum_iteration_plus(myspec); // add accumulators to spec
      memcpy(myargsC, myargs, sizeof(testargs));
      strcpy(myargsC->initvals, iv);
      print_test_spec(myargsC, myspec, "A"); // with accums
      if (strlen(m) > 0) {
	memcpy(myargsC, myargs, sizeof(testargs));
	strcpy(myargsC->mask, m);
	strcpy(myargsC->initvals, iv);
	print_test_spec(myargsC, myspec, "B"); // with mask and accum
      }
    }
    free(myargsC); free_test_spec(myspec);
  }
}

void index_defs(testargs *myargs, char *i0, char *i1, char *i2, char *iv,
		bool A_flag)
{
  if (strlen(myargs->initvals) == 0) strcpy(myargs->initvals, iv);
  if (strlen(myargs->input0) == 0) strcpy(myargs->input0, i0);
  if (strlen(myargs->input1) == 0) strcpy(myargs->input1, i1);
  if (strlen(myargs->input2) == 0) strcpy(myargs->input2, i2);
  if (strlen(myargs->output) == 0) strcpy(myargs->output, "C");
  if (myargs->generate) { // create spec files
    testargs *myargsC = malloc(sizeof(testargs)); // copy args
    memcpy(myargsC, myargs, sizeof(testargs));

    char i0str[64], ostr[64];
    strcpy(i0str, myargsC->input0); strcpy(ostr, myargsC->output);
    sprintf(myargsC->output, "%sD", ostr);
    iterate_defs(myargsC, i0, i1, "", "", TYPE_I);

    sprintf(myargsC->output, "%sA", ostr);
    if (A_flag) sprintf(myargsC->input0, "%sA", i0str);
    strcpy(myargsC->input1, "ALL");
    if (strlen(myargsC->input2) > 0) strcpy(myargsC->input2, "ALL");
    iterate_defs(myargsC, i0, i1, "", "", TYPE_I);

    sprintf(myargsC->output, "%sR", ostr);
    if (A_flag) sprintf(myargsC->input0, "%sR", i0str);
    strcpy(myargsC->input1, "I_RANGE");
    if (strlen(myargsC->input2) > 0) strcpy(myargsC->input2, "I_RANGE");
    iterate_defs(myargsC, i0, i1, "", "", TYPE_I);

    sprintf(myargsC->output, "%sS", ostr);
    if (A_flag) sprintf(myargsC->input0, "%sS", i0str);
    strcpy(myargsC->input1, "I_STRIDE");
    if (strlen(myargsC->input2) > 0) strcpy(myargsC->input2, "I_STRIDE");
    iterate_defs(myargsC, i0, i1, "", "", TYPE_I);

    sprintf(myargsC->output, "%sB", ostr);
    if (A_flag) sprintf(myargsC->input0, "%sB", i0str);
    strcpy(myargsC->input1, "I_BACK");
    if (strlen(myargsC->input2) > 0) strcpy(myargsC->input2, "I_BACK");
    iterate_defs(myargsC, i0, i1, "", "", TYPE_I);
  }
}

void clear_args(testargs *myargs, char *testbasestr)
{
  for (int i = 0; i < TOTAL; i++) myargs->specobj[i] = -1;
  myargs->mask[0] = '\0'; // empty strings for filenames
  myargs->input0[0] = '\0';
  myargs->input1[0] = '\0';
  myargs->input2[0] = '\0';
  myargs->initvals[0] = '\0';
  myargs->output[0] = '\0';
  myargs->spectest[0] = '\0';
  strcpy(myargs->inbase, "testread"); // default input directory
  strcpy(myargs->testbase, testbasestr);
}

void gen_all_defaults()
{
  testargs *myargs = malloc(sizeof(testargs));
  myargs->generate = true;
  clear_args(myargs, "testeAddM");
  iterate_defs(myargs, "A", "B", "", "", EADDM_I);
  clear_args(myargs, "testeAddV");
  iterate_defs(myargs, "V1", "V2", "", "", PAIR_I);
  clear_args(myargs, "testeMultM");
  iterate_defs(myargs, "A", "B", "", "", ANY_I);
  clear_args(myargs, "testeMultV");
  iterate_defs(myargs, "V1", "V2", "", "", ANY_I);
  clear_args(myargs, "testkron");
  iterate_defs(myargs, "A", "B", "", "", PLUS_I);
  clear_args(myargs, "testMAppl");
  iterate_defs(myargs, "A", "", "", "", MINV_I);
  clear_args(myargs, "testMRed");
  iterate_defs(myargs, "A", "", "", "", MIN_I);
  clear_args(myargs, "testMSel");
  iterate_defs(myargs, "A", "", "", "", SELOP_I);
  clear_args(myargs, "testMTRed");
  iterate_defs(myargs, "A", "", "", "", MON_I);
  clear_args(myargs, "testmxm");
  iterate_defs(myargs, "A", "B", "M", "A", SEMI_I);
  clear_args(myargs, "testmxv");
  iterate_defs(myargs, "A", "V2", "V1", "V2", SEMI_I);
  clear_args(myargs, "testtran");
  iterate_defs(myargs, "A", "", "", "", TYPE_I);
  clear_args(myargs, "testVAppl");
  iterate_defs(myargs, "V1", "", "", "", MINV_I);
  clear_args(myargs, "testVSel");
  iterate_defs(myargs, "V1", "", "", "", SELOP_I);
  clear_args(myargs, "testVTRed");
  iterate_defs(myargs, "V1", "", "", "", MON_I);
  clear_args(myargs, "testvxm");
  iterate_defs(myargs, "V1", "A", "V1", "V2", SEMI_I);
  clear_args(myargs, "testCAssn");
  index_defs(myargs, "CE", "A_row", "", "A", true);
  clear_args(myargs, "testCExtr");
  index_defs(myargs, "A", "A_row", "", "", false);
  clear_args(myargs, "testCSubA");
  index_defs(myargs, "CE", "A_row", "", "A", true);
  clear_args(myargs, "testMAssn");
  index_defs(myargs, "ME", "A_row", "A_col", "A", true);
  clear_args(myargs, "testMExtr");
  index_defs(myargs, "A", "A_row", "A_col", "", false);
  clear_args(myargs, "testMSubA");
  index_defs(myargs, "ME", "A_row", "A_col", "A", true);
  clear_args(myargs, "testMTAssn");
  index_defs(myargs, "", "A_row", "A_col", "A", false);
  clear_args(myargs, "testMTSubA");
  index_defs(myargs, "", "A_row", "A_col", "A", false);
  clear_args(myargs, "testRAssn");
  index_defs(myargs, "CE", "A_col", "", "A", true);
  clear_args(myargs, "testRSubA");
  index_defs(myargs, "CE", "A_col", "", "A", true);
  clear_args(myargs, "testVAssn");
  index_defs(myargs, "VE", "V1_ind", "", "V1", true);
  clear_args(myargs, "testVExtr");
  index_defs(myargs, "V1", "V1_ind", "", "", false);
  clear_args(myargs, "testVSubA");
  index_defs(myargs, "VE", "V1_ind", "", "V1", true);
  clear_args(myargs, "testVTAssn");
  index_defs(myargs, "", "V1_ind", "", "V1", false);
  clear_args(myargs, "testVTSubA");
  index_defs(myargs, "", "V1_ind", "", "V1", false);
}
