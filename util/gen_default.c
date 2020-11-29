/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: routines to generate iteration and argument specifications
*/

#include "GraphBLAS.h"
#include "test_utils.h"

void free_test_spec(int **);
int spec_limits(spec);
void print_spec(testargs *, int **);
testargs *new_args(char *);
int **new_spec();

bool find_in_list(int *list, int f, int size)
{
  for (int i = 0; i < size; i++) if (f == list[i]) return true;
  return false;
}

void print_test_spec(testargs *myargs, int **myspec, char *str)
{
  strcat(myargs->output, str); // output name with string to identify sub-test

  char sfile[256];
  sprintf(sfile, "data/specfiles/%s%s.spec", myargs->testbase,
	  myargs->output); // spec output file
  FILE *infp = fopen(sfile, "r");
  if (!infp) {
    char lfname[256];
    sprintf(lfname, "data/specfiles/%s.list", myargs->testbase);
    FILE *listfp = fopen(lfname, "a"); // file with list of spec files
    if (listfp) // write spec name to list file if exists
      { fprintf(listfp, "%s\n", sfile); fclose(listfp); }
  } else fclose(infp);

  print_spec(myargs, myspec);
}

// set a test spec for whole range in selected category
void set_test_spec(spec inspec, int lim, int **myspec)
{
  if (lim >= spec_limits(inspec)) { // whole range
    myspec[inspec] = malloc(sizeof(int)); // just put limit into first position
    myspec[inspec][0] = spec_limits(inspec);
  } else if (lim > 0) {
    int *read_vals = malloc((lim + 1) * sizeof(int));
    for (int i = 0; i < lim; i++) read_vals[i + 1] = i; // set values
    read_vals[0] = lim; // first elt is number elts
    myspec[inspec] = read_vals;
  }
}

// set spec to include all types
void set_all_monoids(int **myspec)
{
  set_test_spec(MON, num_Monoids(), myspec);
}

// set spec to include all types
void set_all_types(int **myspec)
{
  set_test_spec(TYPE, num_Types(), myspec);
}

// set spec to include all select ops
void set_all_selops(int **myspec)
{
  set_test_spec(SELOP, num_SelectOps(), myspec);
}

// set spec to include first 4 descriptors
void set_first_4_desc(int **myspec)
{
  set_test_spec(DESC, 4, myspec);
}

void semi_loop_plus_times(int **sptr)
{
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

void unop_loop_no_minv(int **specptr)
{
  int num_b = 9;
  int b = 0, *blocked = malloc(num_b * sizeof(int)); // don't test MINV ops
  blocked[b++] = find_UnaryOp(GrB_MINV_BOOL);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT8);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT8);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT16);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT16);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT32);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT32);
  blocked[b++] = find_UnaryOp(GrB_MINV_INT64);
  blocked[b++] = find_UnaryOp(GrB_MINV_UINT64);

  assert (b <= num_b);
  set_test_spec(UNOP, num_UnaryOps() - b, specptr);
  for (int i = 0, actual = 1; i < num_UnaryOps(); i++)
    if (!find_in_list(blocked, i, b)) specptr[UNOP][actual++] = i;
}

void binop_loop_any(int **sptr)
{
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

void binop_loop_pair(int **sptr)
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

void binop_loop_plus(int **sptr)
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

void binop_loop_min(int **sptr)
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

void select_defs(int **sptr)
{
  set_all_selops(sptr);
  set_all_types(sptr);
}

void loop_defs(testargs *myargs, char *i0, char *i1, char *i2, char *m,
	       char *iv, char *out, void (*f)(int **))
{
  strcpy(myargs->input0, i0);
  strcpy(myargs->input1, i1);
  strcpy(myargs->input2, i2);
  strcpy(myargs->output, out);

  int **myspec = new_spec(); // create new spec
  set_first_4_desc(myspec); // first four descriptors
  f(myspec);

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

void index_defs(testargs *myargs, char *i0, char *i1, char *i2, char *m,
		char *iv, bool A_flag)
{
  char i0str[64], i2str[64]; strcpy(i0str, i0);
  testargs *myargsC = malloc(sizeof(testargs)); // copy args
  strcpy(myargs->initvals, iv);

  memcpy(myargsC, myargs, sizeof(testargs));
  loop_defs(myargsC, i0, i1, i2, m, iv, "CD", set_all_types);

  memcpy(myargsC, myargs, sizeof(testargs));
  if (A_flag) sprintf(i0str, "%sA", i0);
  if (strlen(i2) > 0) strcpy(i2str, "ALL");
  loop_defs(myargsC, i0str, "ALL", i2str, m, iv, "CA", set_all_types);

  memcpy(myargsC, myargs, sizeof(testargs));
  if (A_flag) sprintf(i0str, "%sR", i0);
  if (strlen(i2) > 0) strcpy(i2str, "I_RANGE");
  loop_defs(myargsC, i0str, "I_RANGE", i2str, m, iv, "CR", set_all_types);

  memcpy(myargsC, myargs, sizeof(testargs));
  if (A_flag) sprintf(i0str, "%sS", i0);
  if (strlen(i2) > 0) strcpy(i2str, "I_STRIDE");
  loop_defs(myargsC, i0str, "I_STRIDE", i2str, m, iv, "CS", set_all_types);

  memcpy(myargsC, myargs, sizeof(testargs));
  if (A_flag) sprintf(i0str, "%sB", i0);
  if (strlen(i2) > 0) strcpy(i2str, "I_BACK");
  loop_defs(myargsC, i0str, "I_BACK", i2str, m, iv, "CB", set_all_types);
}

void unop_binop_defs(testargs *myargs, char *i0, char *m, char *iv)
{
  loop_defs(myargs, i0, "", "", m, iv, "CU", unop_loop_no_minv);
#ifdef NOT_YET_SUPPORTED
  loop_defs(myargs, i0, "", "", m, iv, "CB", binop_loop_min);
#endif
}

void two_op_defs(testargs *myargs, char *i0, char *i1, char *m, char *iv,
		 int op)
{
  if (op == 0) loop_defs(myargs, i0, i1, "", m, iv, "CB", binop_loop_plus);
  else if (op == 1) loop_defs(myargs, i0, i1, "", m, iv, "CB", binop_loop_pair);
  else if (op == 2) loop_defs(myargs, i0, i1, "", m, iv, "CB", binop_loop_any);
  else loop_defs(myargs, i0, i1, "", m, iv, "CB", binop_loop_min);

  loop_defs(myargs, i0, i1, "", m, iv, "CM", set_all_monoids);
}

void three_op_defs(testargs *myargs, char *i0, char *i1, char *m, char *iv,
		   int op)
{
  loop_defs(myargs, i0, i1, "", m, iv, "CS", semi_loop_plus_times);
  two_op_defs(myargs, i0, i1, m, iv, op);
}

void gen_default(char *testbase)
{
  testargs *myargs = new_args(testbase);

  // operations that take three different op types
  if (strcmp(testbase, "testeAddM") == 0)
    three_op_defs(myargs, "A", "B", "M", "A", 0); // use PLUS binops
  else if (strcmp(testbase, "testeAddV") == 0)
    three_op_defs(myargs, "V1", "V2", "V1", "V2", 1); // use PAIR binops
  else if (strcmp(testbase, "testeAddVU") == 0)
    three_op_defs(myargs, "V1", "V2", "V1", "V2", 1); // use PAIR binops
  else if (strcmp(testbase, "testeMultM") == 0)
    three_op_defs(myargs, "A", "B", "M", "A", 2); // use ANY binops
  else if (strcmp(testbase, "testeMultV") == 0)
    three_op_defs(myargs, "V1", "V2", "V1", "V2", 2); // use ANY binops
  else if (strcmp(testbase, "testkron") == 0)
    three_op_defs(myargs, "A", "B", "M", "A", 0); // use PLUS binops

  // operations that take two different op types
  else if (strcmp(testbase, "testMRed") == 0)
    two_op_defs(myargs, "A", "", "V1", "V2", 3); // use MIN binops

  // operations that take unops or binops
  else if (strcmp(testbase, "testMAppl") == 0)
    unop_binop_defs(myargs, "A", "M", "A");
  else if (strcmp(testbase, "testVAppl") == 0)
    unop_binop_defs(myargs, "V1", "V2", "V1");

  // operations with a single object type
  else if (strcmp(testbase, "testMSel") == 0)
    loop_defs(myargs, "A", "", "", "M", "A", "C", select_defs);
  else if (strcmp(testbase, "testVSel") == 0)
    loop_defs(myargs, "V1", "", "", "V2", "V1", "C", select_defs);
  else if (strcmp(testbase, "testMTRed") == 0) // no mask
    loop_defs(myargs, "A", "", "", "", "S", "C", set_all_monoids);
  else if (strcmp(testbase, "testVTRed") == 0) // no mask
    loop_defs(myargs, "V1", "", "", "", "S", "C", set_all_monoids);
  else if (strcmp(testbase, "testmxm") == 0)
    loop_defs(myargs, "A", "B", "", "M", "A", "C", semi_loop_plus_times);
  else if (strcmp(testbase, "testmxv") == 0)
    loop_defs(myargs, "A", "V2", "", "V1", "V2", "C", semi_loop_plus_times);
  else if (strcmp(testbase, "testvxm") == 0)
    loop_defs(myargs, "V1", "A", "", "V1", "V2", "C", semi_loop_plus_times);
  else if (strcmp(testbase, "testtran") == 0)
    loop_defs(myargs, "A", "", "", "", "", "C", set_all_types);

  // operations that use different index patterns, any input is scalar
  else if (strcmp(testbase, "testCExtr") == 0)
    index_defs(myargs, "A", "A_row", "", "V1", "V2", false);
  else if (strcmp(testbase, "testVExtr") == 0)
    index_defs(myargs, "V1", "V1_ind", "", "V2", "V1", false);
  else if (strcmp(testbase, "testMExtr") == 0)
    index_defs(myargs, "A", "A_row", "A_col", "M", "A", false);
  else if (strcmp(testbase, "testMTAssn") == 0)
    index_defs(myargs, "", "A_row", "A_col", "M", "A", false);
  else if (strcmp(testbase, "testMTSubA") == 0)
    index_defs(myargs, "", "A_row", "A_col", "M", "A", false);
  else if (strcmp(testbase, "testVTAssn") == 0)
    index_defs(myargs, "", "V1_ind", "", "V2", "V1", false);
  else if (strcmp(testbase, "testVTSubA") == 0)
    index_defs(myargs, "", "V1_ind", "", "V2", "V1", false);

  // operations that use different index patterns, input is vector or matrix
  else if (strcmp(testbase, "testCAssn") == 0)
    index_defs(myargs, "CE", "A_row", "", "V1", "V2", true);
  else if (strcmp(testbase, "testCSubA") == 0)
    index_defs(myargs, "CE", "A_row", "", "V1", "V2", true);
  else if (strcmp(testbase, "testMAssn") == 0)
    index_defs(myargs, "ME", "A_row", "A_col", "M", "A", true);
  else if (strcmp(testbase, "testMSubA") == 0)
    index_defs(myargs, "ME", "A_row", "A_col", "M", "A", true);
  else if (strcmp(testbase, "testRAssn") == 0)
    index_defs(myargs, "CE", "A_col", "", "V2", "V1", true);
  else if (strcmp(testbase, "testRSubA") == 0)
    index_defs(myargs, "CE", "A_col", "", "V2", "V1", true);
  else if (strcmp(testbase, "testVAssn") == 0)
    index_defs(myargs, "VE", "V1_ind", "", "V2", "V1", true);
  else if (strcmp(testbase, "testVSubA") == 0)
    index_defs(myargs, "VE", "V1_ind", "", "V2", "V1", true);
}
