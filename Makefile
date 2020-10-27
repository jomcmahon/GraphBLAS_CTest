
#   Copyright 2020 by Lucata Corporation.
#   Lucata grants a free license for noncommercial use and requires that this
#   notice not be removed from the source files.

#   GraphBLAS C Test Suite
#   DESCRIPTION: Makefile for generation and execution of tests

# . env.sh

-include make.inc

# GraphBLAS location
HOMEDIR ?= /home1/mcmahon
GBDIR ?= $(HOMEDIR)/SuiteSparse/GraphBLAS
# cd $(GBDIR) ; make static

# each test needs a wholly contained test<N>.c file created using the template
# each test needs also a data/test<N>.m file to generate inputs and outputs
# matrices will be in data/test<N>; use "test<N>" as input to read function

UTILSRC = $(wildcard util/*.c)
UTILOBJ = $(UTILSRC:.c=.o)
UTILLIB = util/libtest_utils.a

ifdef F
NOT_YET = -DNOT_YET_SUPPORTED
endif

CFLAGS ?= -Wall -Werror -I$(GBDIR)/Include $(NOT_YET)
CXX ?= g++-7
CXXFLAGS += -fopenmp
LOADLIBS ?= -lm $(GBDIR)/build/libgraphblas.a

N ?= read
SRCS = $(wildcard test*.c)
P1SRCS = $(wildcard test*Extr.c)
GENSRCS = $(wildcard testmxm.c testmxv.c testvxm.c teste*.c test*Assn.c test*SubA.c test*Sel.c test*Appl.c test*Red.c testtran.c testkron.c)

# assign and subassign use extract outputs, need a second pass for gen
EXES = $(SRCS:%.c=%)
P1EXES = $(P1SRCS:%.c=%)
GENEXES = $(GENSRCS:%.c=%)
UNITS = testBinary testDesc testMatrix testMonoid testScalar testSelect testSemi testTypes testUnary testVector

default: test$(N)

all: $(EXES)

info:
	grep DESCRIPTION util/*.c

setup:
	ln -s $(GBDIR)/Demo

lib: $(UTILLIB)

run: test$(N)
	./test$(N) $(INPUTS)

gen: test$(N)
	./test$(N) -g $(INPUTS)

runall: $(EXES)
	for x in $(EXES); do ./$$x; done

genall: $(P1EXES) $(GENEXES)
	for x in $(P1EXES); do mkdir -p ./data/$$x ; done
	for x in $(P1EXES); do ./$$x -g > ./data/$$x/$$x.out ; done
	cd data/testread && for x in $(P1EXES); do ln -s ../$$x ; done
	for x in $(GENEXES); do mkdir -p ./data/$$x ; done
	for x in $(GENEXES); do ./$$x -g > ./data/$$x/$$x.out ; done

unit: $(UNITS)
	for x in $(UNITS); do ./$$x; done

test%: test%.o $(UTILLIB)
	$(CXX) $(CXXFLAGS) $^ $(LOADLIBS) -o $@

$(UTILLIB): $(UTILOBJ)
	ar r $@ $^
	ranlib $@

$(UTILOBJ): util/test_utils.h

clean:
	rm -f *~ *.o $(EXES)

cleanlib:
	rm -f $(UTILLIB) util/*.o
