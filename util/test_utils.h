/*
   GraphBLAS C Test Suite
   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
   SPDX-License-Identifier: Apache-2.0

   DESCRIPTION: test utilities include file
*/

#include <assert.h>
#include <getopt.h>

// test if MM file is valid
#define MM_INVALID(_m) (!mm_is_matrix(_m) || mm_is_complex(_m) || \
			mm_is_symmetric(_m) || mm_is_skew(_m) || \
			mm_is_hermitian(_m) || mm_is_pattern(_m))

// macros for use in tests
#ifdef VERSION4
#define OK(method) do { info = method;					\
    if (info != GrB_SUCCESS) {						\
      printf("%s:%d:GB: %d\n", __FILE__, __LINE__, info);		\
      exit(info); } } while (0)
#else
#define OK(method) do { info = method;					\
    if (info != GrB_SUCCESS) {						\
      printf("%s:%d: GB: %d: %s\n", __FILE__, __LINE__, info, GrB_error()); \
      exit(info); } } while (0)
#endif

// test argument parsing
typedef enum { TYPE, SEMI, MON, BINOP, UNOP, SELOP, DESC, ACCUM, TOTAL } spec;

// structure for passing arguments to a test wrapper
#define MATNAME_SIZE 64
typedef struct testargs {
  bool generate;
  int specobj[TOTAL];
  char mask[MATNAME_SIZE];
  char input0[MATNAME_SIZE];
  char input1[MATNAME_SIZE];
  char input2[MATNAME_SIZE];
  char output[MATNAME_SIZE];
  char initvals[MATNAME_SIZE];
  char testbase[MATNAME_SIZE];
  char inbase[MATNAME_SIZE];
  char spectest[256];
} testargs;

// methods for built-ins
int num_Types();
int find_Type(GrB_Type);
void get_Type(int, GrB_Type *);
int num_BinaryOps();
int find_BinaryOp(GrB_BinaryOp);
void get_BinaryOp(int, GrB_BinaryOp *);
int num_UnaryOps();
int find_UnaryOp(GrB_UnaryOp);
void get_UnaryOp(int, GrB_UnaryOp *);
int num_Monoids();
int find_Monoid(GrB_Monoid);
void get_Monoid(int, GrB_Monoid *);
int num_Semirings();
int find_Semiring(GrB_Semiring);
void get_Semiring(int, GrB_Semiring *);
int num_Descriptors();
int find_Descriptor(GrB_Descriptor);
void get_Descriptor(int, GrB_Descriptor *);
int num_SelectOps();
int find_SelectOp(GxB_SelectOp);
void get_SelectOp(int, GxB_SelectOp *);

// methods for argument and spec manipulation
void print_args(testargs *, GrB_Descriptor, GrB_BinaryOp);
testargs *get_test_args(int argc, char **argv);
bool run_test(int, char **, bool (*g)(testargs *));

// test_matrix matrix routines
void read_matlab_matrix(const char *, const char *, GrB_Type, GrB_Matrix *);
void write_typed_matrix(const char *, const char *, GrB_Matrix);
bool check_typed_matrix(const char *, const char *, GrB_Matrix);

// test_matrix vector routines
void read_matlab_vector(const char *, const char *, GrB_Type, GrB_Vector *);
void write_typed_vector(const char *, const char *, GrB_Vector);
bool check_typed_vector(const char *, const char *, GrB_Vector);

// test_matrix index routines
void read_test_index(const char *, const char *, GrB_Index **, GrB_Index *);
GrB_Index get_index_size(GrB_Index *, GrB_Index, GrB_Index);
GrB_Index get_index_dim(GrB_Index *, GrB_Index, GrB_Index);

// test_matrix routines to query objects
void get_types_unop(GrB_UnaryOp, GrB_Type *, GrB_Type *);
void get_types_binop(GrB_BinaryOp, GrB_Type *, GrB_Type *, GrB_Type *);
void get_types_monoid(GrB_Monoid, GrB_Type *, GrB_Type *, GrB_Type *);
void get_types_semiring(GrB_Semiring, GrB_Type *, GrB_Type *, GrB_Type *);
void get_inp_size(GrB_Descriptor, GrB_Matrix, GrB_Index *, GrB_Index *,
		  GrB_Desc_Field);

// user-defined objects for tests
void get_User_Type(GrB_Type *type);
void get_User_Semiring(GrB_Semiring *semi);
void get_User_Monoid(GrB_Monoid *mon);
void get_User_BinaryOp(GrB_BinaryOp *binop);
void get_User_UnaryOp(GrB_UnaryOp *unop);
void get_User_SelectOp(GxB_SelectOp *selop, GrB_Type type);
void get_User_Scalar(GxB_Scalar *scal);
