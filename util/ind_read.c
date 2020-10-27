/*
   Copyright 2020 by Lucata Corporation.
   Lucata grants a free license for noncommercial use and requires that this
   notice not be removed from the source files.

   GraphBLAS C Test Suite
   DESCRIPTION: ind_read read indices written from matlab
*/

#include "GraphBLAS.h"
#include "test_utils.h"
#include "mmio.h"

// only dense, non-complex, non pattern matrices allowed
bool gbi_is_valid(MM_typecode matcode)
{
  if (!mm_is_matrix(matcode) || mm_is_sparse(matcode) ||
      mm_is_complex(matcode) || mm_is_hermitian(matcode) ||
      mm_is_pattern(matcode) || mm_is_skew(matcode)) return false;
  else return true;
}

// read an index array written from matlab as a vector
GrB_Info ind_read(GrB_Index **Ind, GrB_Index *nInd, FILE *f)
{
  MM_typecode matcode;
  int M, N, valctr = 0;
  char line[MM_MAX_LINE_LENGTH];

  if (f == NULL)
    { printf("file or object pointer is null\n"); exit(1); }

  if (mm_read_banner(f, &matcode) != 0)
    { printf("couldn't read mtx banner\n"); exit(1); }

  if (!gbi_is_valid(matcode))
    { printf("invalid index matrix %s\n", matcode); exit(1); }

  if (mm_read_mtx_array_size(f, &M, &N) !=0)
    { printf("couldn't read sizes\n"); exit(1); }

  // index arrays are dense and always uint64
  assert ((M == 1) || (N == 1));
  GrB_Index nz = (M == 1) ? N : M;
  GrB_Index *I = malloc(nz * sizeof(GrB_Index));

  // read the data
  while (fgets(line, MM_MAX_LINE_LENGTH, f) && (valctr < nz)) {
    GrB_Index ival;
    if (sscanf(line, "%lu", &ival) != 1)
      { printf("couldn't scan index %d\n", valctr); exit(1); }
    I[valctr++] = ival - 1;
  }
  // test that the right number of values was read
  if (valctr != nz) { printf("wrong number of inds\n"); exit(1); }

  *Ind = I;  // return values
  *nInd = nz;

  return GrB_SUCCESS;
}
