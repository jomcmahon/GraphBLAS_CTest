
Copyright 2020 by Lucata Corporation.
Lucata grants a free license for noncommercial use and requires that this
notice not be removed from the source files.

GraphBLAS C Test Suite
DESCRIPTION: README file

INTRODUCTION:

GB_CTest is a test infrastructure for testing GraphBLAS
operations on built-in objects. Each operation has a wrapper function
that supplies arguments to the operation according to the options
supplied. There is a mechanism for iterating over a space defined by
lists of objects and a default iteration space for each test. There
are 43 tests, including 10 unit tests for API functions and 2
miscellaneous tests (file read and basic init/finalize). The tests
work by generating common inputs via Octave in Matrix Market format
(if Octave is not available, any program that generates an MM file can
be used). Tests are first executed in "generate" mode, linked to a
stable proven version of SuiteSparse to generate the correct
answers. Thereafter, the same codes can be linked with another
GraphBLAS library under development and run in "comparison" mode,
where the data generated is compared to the answer files. If no
arguments are supplied, the default iteration is executed. Options and
arguments can change the iteration space as desired.

INSTRUCTIONS:

1) tar -xvf GB_CTest.tar && cd CTest
2) edit Makefile so that GBDIR points to stable, verified GraphBLAS
3) "make setup" to  link Demo directory
4) "cd util && python codegen.py" to create database of GraphBLAS objects
5) "octave testread.m" to create input data
6) "make genall" to generate answers for default iteration in data dir
7) edit Makefile so that GBDIR points to GraphBLAS version under test
8) "make runall" to run all tests in default iteration on that version

INDIVIDUAL TESTS:

running test<N> where test<N>.c exists: "make N=<N> run"
generating for test<N> where test<N>.c exists: "make N=<N> gen"
to view options, run with -h or "make N=<N> -INPUTS=-h run"

options: hgt:u:b:s:n:l:d:a:m:0:1:2:o:i:p:

help, generate

type, unaryop, binaryop, semiring, monoid, selectop, descriptor, accum:
option value is a number that indexes into the database; if the number is not
known, there are finding functions to get the indexes, see any of the tests
for an example. The index can also be found using the python
codegenerator in the util directory.

mask, i0, i1, i2, out, init, spec:
option value is a string that is used as a file base name for data read and/or
write for each of the inputs and outputs to a graphBLAS operation. spec is
a spec file that defines an iteration space for tests (see sample in
file TESTSPEC). There is a default iteration in each test; see any of
the C files for an example.

The option values for filenames are basenames. For inputs (mask, i0,
i1, i2, init) these are the actual basenames for .mm files. The
default directory for inputs is data/testread (if a non-option
argument is supplied to a test, that argument will be used instead of
"testread"). For the output, the option argument is a basename to
which characters and index values will be added to denote the objects used in
generating the output. To create a new known output, run the test with
-g to create the output file, then run without -g to test against that
file. In the generation phase, the filename base and the filename
option values will be printed to stdout, so that the indices and the
corresponding objects will be known. After the "make genall"
operation, there will be .out files in all of the data directories for
each test that describe the default iteration.

For tests that take indices, those arrays will be given in the -1 and
-2 file name options. If any of those file names contain the strings
"ALL", "RANGE", "STRIDE" or "BACK", the file will be interpreted as
GrB_ALL, GrB_RANGE, GrB_STRIDE, or GrB_BACK, respectively. See any of
the assign tests as an example.