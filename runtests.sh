#!/bin/bash

# $1 is test executable name; all other args passed
function singlerun {
    mkdir -p data/specfiles
    eval "../../CTest/testspec $@ -g" >> out.log
    mkdir -p data/$1
    eval "../../CTest/$@ -g" >> out.log
    if [ $? -eq 0 ]; then
	echo $1 : GENERATED
    else
	echo $1 : PROBLEM GENERATING DATA
    fi

    eval "./$@" >> out.log
    if [ $? -eq 0 ]; then
	echo $1 : PASSED
    else
	echo $1 : FAILED ====================================
    fi
#    rm -rf data/$1
}

rm -f out.log
shopt -s nullglob

if [ $1 == "ALL" ]; then
    for t in test*; do
	singlerun $t ${@:2}
    done
else
    singlerun $1 ${@:2}
fi
