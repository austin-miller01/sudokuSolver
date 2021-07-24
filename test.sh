#!/bin/bash

# File: test.sh
# Description: test sudoku functionality of Matrix class

SRC="./src"     # Source code dir.
TEST="./tests"   # Unit tests dir.

g++ --std=c++11 $SRC/matrix.cpp $TEST/tests.cpp -o $TEST/sudoku_test 2>/dev/null
${TEST}/sudoku_test
for f in $TEST/*.sol; do
   f=${f%*.sol}
   DIFF=$(diff ${f}.ans ${f}.sol)
   if [ "$DIFF" != "" ]; then
      echo "${f} failed <---"
   else
      echo "${f} passed"
   fi
   rm ${f}.sol
done
rm $TEST/sudoku_test
