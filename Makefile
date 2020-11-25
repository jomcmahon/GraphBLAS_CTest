
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
EXES = $(SRCS:%.c=%)
UNITS = testBinary testDesc testMatrix testMonoid testScalar testSelect testSemi testTypes testUnary testVector

empty :=
space := $(empty) $(empty)
fstr = $(subst $(space),$(empty),$(INPUTS))

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
	mkdir -p ./data/test$(N)
	./test$(N) -g $(INPUTS) > data/test$(N)/test$(N)$(fstr).out

runall: $(EXES)
	for x in $(EXES); do ./$$x; done

genall: $(EXES)
	mkdir -p ./data/specfiles
	./testinit -g
	for x in $(EXES); do mkdir -p ./data/$$x ; done
	for x in $(EXES); do ./$$x -g > ./data/$$x/$$x.out ; done

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
