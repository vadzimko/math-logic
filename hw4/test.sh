#!/usr/bin/env bash

make run
make clean > log.txt
cp ans.txt ././../hw1-2/input.txt

cd ././../hw1-2
bash run.sh

#rm ././../hw1-2/answer
#cat answer