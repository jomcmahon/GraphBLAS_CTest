/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: test utilities include file
*/

#include <assert.h>
#include <getopt.h>

// macros for use in tests
#define OK(method) do { info = method;					\
    if (info != GrB_SUCCESS) {						\
      printf("%s:%d:GB: %d: %s\n", __FILE__, __LINE__, info, GrB_error()); \
      exit(info); } } while (0)

#define TEST_OK(method) do { if (info == GrB_SUCCESS) { info = method;	\
      if (info != GrB_SUCCESS) {					\
	printf("%s:%d:GB: %d: %s\n", __FILE__, __LINE__, info, GrB_error()); \
	fflush(stdout); testerror = true; } } } while (0)

#define TEST_COND(_c, _s) do { printf("%s", _s);			\
    if ((info == GrB_SUCCESS) && (_c)) printf(": PASSED\n");		\
    else { printf(": FAILED at %s:%d\n", __FILE__, __LINE__);		\
      testerror = true; } fflush(stdout); } while (0)

#define SUBTEST_COND(_c, _s) do {					\
    if ((info == GrB_SUCCESS) && testok && !(_c)) { printf("%s\n", _s); \
      testerror = true; testok = false; fflush(stdout); } } while (0)

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
void write_test_spec(testargs *, void (*f)(testargs *, int**));
void set_test_spec(spec, int, int **);
testargs *get_test_args(int argc, char **argv);
bool get_spec_list(testargs *, spec, bool (*g)(testargs *));

// routines in separate files
GrB_Info mm_matlab(GrB_Matrix *, FILE *, GrB_Type);
GrB_Info vec_matlab(GrB_Vector *, FILE *, GrB_Type);
GrB_Info mm_read(GrB_Matrix *, FILE *, GrB_Type);
GrB_Info vec_read(GrB_Vector *, FILE *, GrB_Type);
GrB_Info ind_read(GrB_Index **, GrB_Index *, FILE *);
GrB_Info mm_write(GrB_Matrix, FILE *);
GrB_Info vec_write(GrB_Vector, FILE *);
bool is_approx_equal_mat(GrB_Matrix, GrB_Matrix) ;
bool is_approx_equal_vec(GrB_Vector, GrB_Vector) ;
bool is_equal_ind(GrB_Index *I, GrB_Index ni, GrB_Index *J, GrB_Index nj);

// test_matrix matrix routines
GrB_Info read_matlab_matrix(const char *, const char *, GrB_Type, GrB_Matrix *);
GrB_Info read_typed_matrix(const char *, const char *, GrB_Type, GrB_Matrix *);
GrB_Info write_typed_matrix(const char *, const char *, GrB_Type, GrB_Matrix);
bool check_typed_matrix(const char *, const char *, GrB_Type, GrB_Matrix);

// test_matrix vector routines
GrB_Info read_matlab_vector(const char *, const char *, GrB_Type, GrB_Vector *);
GrB_Info read_typed_vector(const char *, const char *, GrB_Type, GrB_Vector *);
GrB_Info write_typed_vector(const char *, const char *, GrB_Type, GrB_Vector);
bool check_typed_vector(const char *, const char *, GrB_Type, GrB_Vector);

// test_matrix index routines
GrB_Info read_test_index(const char *, const char *, GrB_Index **, GrB_Index *);
GrB_Index get_index_size(GrB_Index *, GrB_Index, GrB_Index);

// test_matrix routines to query objects
GrB_Info get_types_unop(GrB_UnaryOp, GrB_Type *, GrB_Type *);
GrB_Info get_types_binop(GrB_BinaryOp, GrB_Type *, GrB_Type *, GrB_Type *);
GrB_Info get_types_monoid(GrB_Monoid, GrB_Type *, GrB_Type *, GrB_Type *);
GrB_Info get_types_semiring(GrB_Semiring, GrB_Type *, GrB_Type *, GrB_Type *);
GrB_Info get_inp_size(GrB_Descriptor, GrB_Matrix, GrB_Index *, GrB_Index *,
		      GrB_Desc_Field);
