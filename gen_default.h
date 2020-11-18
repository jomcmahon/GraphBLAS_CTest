/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: routines to generate iteration and argument specifications
*/

// test argument parsing
typedef enum { TYPE_I, MON_I, ANY_I, PAIR_I, PLUS_I, MIN_I, MINV_I, EADDM_I,
	       SELOP_I, TOTAL_I } iter_spec;

void semi_iteration_plus_times(int **sptr);
void accum_iteration_plus(int **sptr);
void unop_iteration_minv(int **specptr);
void binop_iteration_any(int **sptr);
void binop_iteration_pair(int **sptr);
void binop_iteration_plus(int **sptr);
void binop_iteration_min(int **sptr);
void eAddM_iteration(int **sptr);
void iterate_defs(testargs *, char *, char *, iter_spec);
void matmul_defs(testargs *, char *, char *, char *, char *);
void index_defs(testargs *, char *, char *, char *, char *, bool);
