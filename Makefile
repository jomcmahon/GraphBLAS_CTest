
#   GraphBLAS C Test Suite
#   Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
#   SPDX-License-Identifier: Apache-2.0

#   DESCRIPTION: Makefile for generation and execution of tests

# . env.sh

-include make.inc

# GraphBLAS location
GBDIR ?= $(HOME)/SuiteSparse/GraphBLAS
ifdef TEST
LOADLIBS ?= $(HOME)/LucataGraphBLAS/build_x86/src/lib/libLucataGraphBLAS.a
INCDIR ?= $(HOME)/LucataGraphBLAS/src/include
else
LOADLIBS ?= -lm $(GBDIR)/build/libgraphblas.a
INCDIR ?= $(GBDIR)/Include
endif

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

CC ?= g++-7
CFLAGS ?= -Wall -Werror -I$(INCDIR) $(NOT_YET)
CXX ?= g++-7
CXXFLAGS += -fopenmp

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
	for x in $(EXES); do mkdir -p ./data/$$x ; done
	for x in $(EXES); do ./$$x -g > ./data/$$x/$$x.out ; done

specall:
	mkdir -p ./data/working
	python util/specgen.py WORKING
	mkdir -p ./data/regression
	python util/specgen.py REGRESSION
	cd data && ln -s regression specfiles

unit: $(UNITS)
	for x in $(UNITS); do ./$$x; done

%spec: util/specgen.py
	mkdir -p ./data/$*
	rm -f data/specfiles
	cd data && ln -s $* specfiles

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
