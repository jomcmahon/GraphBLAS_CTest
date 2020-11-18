#!/bin/bash

# $1 is test executable name; $2 is location of reference executable
function singlerun {
    mkdir -p data/$1
    eval "$2/$1 -g" >> out.log
    if [ $? -eq 0 ]; then
	echo $1 : GENERATED
    else
	echo $1 : PROBLEM GENERATING DATA
    fi

    eval "./$1" >> out.log
    if [ $? -eq 0 ]; then
	echo $1 : PASSED
    else
	echo $1 : FAILED ====================================
    fi
#    rm -rf data/$1
}

rm -f out.log
shopt -s nullglob
if [ $# -eq 0 ]; then
    d=.
else
    d=$1
fi

if [ $# -gt 1 ]; then
    singlerun $2 $d
else
    for t in test*; do
	singlerun $t $d
    done
fi
