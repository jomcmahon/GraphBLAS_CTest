function [ err ] = mmwrite(filename,A)
% Writes sparse or dense matrix A to a Matrix Market (MM) formatted file.
% Required arguments: 
%   filename - destination file
%   A        - sparse or full matrix

  precision = 16;
  symm = 'general';

  mmfile = fopen([filename],'w');
  if ( mmfile == -1 )
    error('Cannot open file for output');
  end;

  [M,N] = size(A);

% sparse matrices
  if ( issparse(A) )
    rep = 'coordinate';
    [I,J,V] = find(A);
    NZ = length(V);
    if ( sum(abs(imag(nonzeros(V)))) > 0 )
      mattype = 'complex';
    else
      mattype = 'real';
    end;

    fprintf(mmfile,'%%%%MatrixMarket matrix %s %s %s\n',rep,mattype,symm);
    fprintf(mmfile,'%% Generated %s\n',[date]);
    fprintf(mmfile,'%d %d %d\n',M,N,NZ);
    cplxformat = sprintf('%%d %%d %% .%dg %% .%dg\n',precision,precision);
    realformat = sprintf('%%d %%d %% .%dg\n',precision);
    if ( strcmp(mattype,'real') )
      for i=1:NZ
	fprintf(mmfile,realformat,I(i),J(i),V(i));
      end;
    else ( strcmp(mattype,'complex') )
      for i=1:NZ
	fprintf(mmfile,cplxformat,I(i),J(i),real(V(i)),imag(V(i)));
      end;
    end;

% dense matrices
  else
    rep = 'array';
    if ( sum(abs(imag(nonzeros(A)))) > 0 )
      mattype = 'complex';
    else
      mattype = 'real';
    end;

    fprintf(mmfile,'%%%%MatrixMarket matrix %s %s %s\n',rep,mattype,symm);
    fprintf(mmfile,'%d %d\n',M,N);
    cplxformat = sprintf('%% .%dg %% .%dg\n', precision,precision);
    realformat = sprintf('%% .%dg\n', precision);
    if ( strcmp(mattype,'real') )
      for j=1:N
	for i=1:M
          fprintf(mmfile,realformat,A(i,j));
	end;
      end;
    else ( strcmp(mattype,'complex') )
      for j=1:N
	for i=1:M
          fprintf(mmfile,cplxformat,real(A(i,j)),imag(A(i,j)));
	end;
      end;
    end;
  end;
  fclose(mmfile);
