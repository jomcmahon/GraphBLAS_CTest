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
% A_row = find(any(A, 1)) ;
% A_col = find(any(A, 2)) ;
A_row = [2 4 5 7 9];
A_col = [1 3 6 8 10];
V1_ind = find(A(1, :)) ;
V2_ind = find(A(:, 1)) ;
I_RANGE = [1 10];
I_STRIDE = [1 10 2];
I_BACK = [10 1 2];
A_row1 = A_row(1) ;
A_col1 = A_col(1) ;
