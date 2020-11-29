% Copyright 2020 by Lucata Corporation.
% Lucata grants a free license for noncommercial use and requires that this
% notice not be removed from the source files

% GraphBLAS C Test Suite
% DESCRIPTION: generate input matrices based on SuiteSparse demo data

% write files for matrix in all types, assumes mat is generated with sprand
w = load ('Demo/Matrix/ibm32a') ;
nz = size (w,1) ;
n = max (max (w (:,1:2))) + 1 ;
A = sparse (w (:,1)+1, w (:,2)+1, 20 * rand (nz,1) - 10, n, n) ;
B = A (16:25, 16:25) .* rand (10) ;
A = A (1:10,1:10) ;

assert (issparse (A)) ;

[m n] = size (A) ;
assert (m == n) ;

[i, j, ~] = find (A) ;
nz = nnz (A) ;
p = randperm (nz, floor (nz/2)) ;

Mask = sparse (i (p), j (p), ones (length (p),1), m, n) + ...
       spones (sprandn (m, n, 1/n)) ;

V1 = A(1,:) ;
V2 = A(:,1) ;
S = [ A(1:1) ] ;
A_row = [2 4 5 7 9];
A_col = [1 3 6 8 10];
V1_ind = find(A(1, :)) ;
V2_ind = find(A(:, 1)) ;
low = 1 ;
high = 10 ;
stride = 2 ;
I_RANGE = [low high] ;
I_STRIDE = [low high stride] ;
I_BACK = [high low stride] ;
r = low:high ;
s = low:stride:high ;
b = high:-stride:low ;
ME = A(A_row, A_col) ;
MEA = A(:, :) ;
MER = A(r, r) ;
MES = A(s, s) ;
MEB = A(b, b) ;
CE = A(A_row, 1) ;
CEA = A(:, 1) ;
CER = A(r, 1) ;
CES = A(s, 1) ;
CEB = A(b, 1) ;
VE = V1(V1_ind) ;
VEA = V1(:) ;
VER = V1(r) ;
VES = V1(s) ;
VEB = V1(b) ;
