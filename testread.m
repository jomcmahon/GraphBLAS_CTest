% Copyright 2020 by Lucata Corporation.
% Lucata grants a free license for noncommercial use and requires that this
% notice not be removed from the source files

% GraphBLAS C Test Suite
% DESCRIPTION: write matrices to input data directory

inputs

mkdir("data") ;
mkdir("data/testread") ;
mmwrite("data/testread/A.mm", A) ;
mmwrite("data/testread/B.mm", B) ;
mmwrite("data/testread/M.mm", Mask) ;
mmwrite("data/testread/V1.mm", V1) ;
mmwrite("data/testread/V2.mm", V2) ;
mmwrite("data/testread/A_row.mm", A_row) ;
mmwrite("data/testread/A_col.mm", A_col) ;
mmwrite("data/testread/V1_ind.mm", V1_ind) ;
mmwrite("data/testread/V2_ind.mm", V2_ind) ;
mmwrite("data/testread/I_RANGE.mm", I_RANGE) ;
mmwrite("data/testread/I_STRIDE.mm", I_STRIDE) ;
mmwrite("data/testread/I_BACK.mm", I_BACK) ;
