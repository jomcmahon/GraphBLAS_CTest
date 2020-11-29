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
mmwrite("data/testread/S.mm", S) ;
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
mmwrite("data/testread/ME.mm", ME) ;
mmwrite("data/testread/MEA.mm", MEA) ;
mmwrite("data/testread/MER.mm", MER) ;
mmwrite("data/testread/MES.mm", MES) ;
mmwrite("data/testread/MEB.mm", MEB) ;
mmwrite("data/testread/CE.mm", CE) ;
mmwrite("data/testread/CEA.mm", CEA) ;
mmwrite("data/testread/CER.mm", CER) ;
mmwrite("data/testread/CES.mm", CES) ;
mmwrite("data/testread/CEB.mm", CEB) ;
mmwrite("data/testread/VE.mm", VE) ;
mmwrite("data/testread/VEA.mm", VEA) ;
mmwrite("data/testread/VER.mm", VER) ;
mmwrite("data/testread/VES.mm", VES) ;
mmwrite("data/testread/VEB.mm", VEB) ;
