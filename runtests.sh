#!/bin/bash

# GraphBLAS C Test Suite
# Lucata Corporation/Emu Technology, (c) 2020, All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

# DESCRIPTION: script to generate data from reference and then run test

# $1 is test executable name; all other args passed
function singlerun {
    mkdir -p data/specfiles
    eval "../../CTest/testspec $@ -g"
    mkdir -p data/$1
    eval "../../CTest/$@ -g" > data/$1/$1.out
    if [ $? -eq 0 ]; then
	echo $1 : GENERATED
    else
	echo $1 : PROBLEM GENERATING DATA
    fi

    eval "./$@" > data/$1/$1.log
    if [ $? -eq 0 ]; then
	echo $1 : PASSED
    else
	echo $1 : FAILED ====================================
    fi
#    rm -rf data/$1
}

shopt -s nullglob

if [ $1 == "ALL" ]; then
    for t in test*; do
	singlerun $t ${@:2}
    done
else
    singlerun $1 ${@:2}
fi
