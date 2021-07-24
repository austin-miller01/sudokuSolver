#include <iostream>
#include <cstdio>
#include <string>
#include <cassert>
#include "../src/matrix.hpp"

int main(){
    Matrix sudoku0("./tests/sudoku_0.txt");
    Matrix sudoku1("./tests/sudoku_1.txt");
    Matrix sudoku2("./tests/sudoku_2.txt");
    Matrix sudoku3("./tests/sudoku_3.txt");
    Matrix pgm1("./tests/m1.pgm");
    
   //assert(sudoku0.IsValidSudoku());
   //assert(sudoku1.IsValidSudoku());
   //assert(sudoku2.IsValidSudoku());    
   //assert(!sudoku3.IsValidSudoku());
   //assert(!pgm1.IsValidSudoku());

    sudoku0.SolveSudoku();
    sudoku1.SolveSudoku();
    sudoku2.SolveSudoku();

    sudoku0.SaveSudoku("./tests/sudoku_0.sol");
    sudoku1.SaveSudoku("./tests/sudoku_1.sol");
    sudoku2.SaveSudoku("./tests/sudoku_2.sol");

    return 0;
}
