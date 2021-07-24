#include <iostream>
#include <string>
#include "matrix.hpp"

int main() {
  Matrix sudoku("./tests/sudoku_0.txt");
  std::cout << "Loaded sudoku:" << std::endl;
  std::cout << sudoku << std::endl;
  sudoku = Transpose(sudoku);
  sudoku.SolveSudoku();
  std::cout << "Solved sudoku:" << std::endl;
  std::cout << sudoku << std::endl;
  return 0;
}
