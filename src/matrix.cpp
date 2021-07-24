/**
 * @brief Implementation of class Matrix.
 */

#include "matrix.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>


Matrix::Matrix()
/**
   
   This is the default concstructor for the osm class
   initializes numRows and numColumns to zero, sets m to null

    @return void
*/
{
    //initialize the array to zero array and then set numrows
    //and num columns to zero.
    this->m = new int *[0];
    this->m[0] = new int[0];
    this->numRows = 0;
    this->numColumns = 0;
}

Matrix::Matrix(const unsigned r, const unsigned c)
/**
   
   This is a parametized concstructor for the osm class
   initializes  matrix to size (r,c) and sets all the values to zero

    @return void
*/
{
    //set numrows to r and numcolumns to c
    //then initialize matrix with values of zero.

    this->numRows = r;
    this->numColumns = c;
    if (r == 0 && c == 0)
    {
        this->m = new int *[0];
        this->m[0] = new int[0];
    }
    else
    {
        this->m = new int *[r];
        for (unsigned int i = 0; i < r; ++i)
            this->m[i] = new int[c];

        for (unsigned int i = 0; i < r; i++)
        {
            for (unsigned int j = 0; j < c; j++)
            {
                this->m[i][j] = 0;
            }
        }
    }
}

Matrix::Matrix(const unsigned r, const unsigned c, const std::string &e)
/**
   
   This is a parametized concstructor for the osm class
   initializes  matrix to size (r,c)
   sets the values of Matrix to values stored in string e
    @return void
*/
{

    //set numrows to r and numcolumns to c
    //then initialize matrix with values stored inside string e.
    numRows = r;
    numColumns = c;

    if (numRows == 0 && numColumns == 0)
    {
        m = nullptr;
    }
    else
    {
        std::stringstream stream(e);
        m = new int *[r];

        for (unsigned int i = 0; i < numRows; i++)
        {
            m[i] = new int[c];
            for (unsigned int j = 0; j < numColumns; j++)
            {
                stream >> m[i][j];
            }
        }
        stream.clear();
    }
}
Matrix::Matrix(const std::string &pgmPath)
/**
   
   This is a parametized concstructor for the osm class, takes in a PGM file name
   initializes  matrix to size (r,c) found inside PGM file
   sets the values of Matrix to values stored in PGM file

    @return void
*/
{

    //use a PGM file to initialize matrix
    //take in values for numRows and numColumns
    //then take in values for positions in matrix
    std::ifstream testStream(pgmPath);

    std::string test = "";

    getline(testStream, test);
    testStream.close();

    if (test == "P2")
    {
        std::ifstream inStream(pgmPath);

        std::string inLine = "";

        //skips lines that are not useful
        getline(inStream, inLine);

        getline(inStream, inLine);

        int row = 0, col = 0;

        inStream >> row >> col;
        this->numRows = row;
        this->numColumns = col;

        //skips line that is not useful
        getline(inStream, inLine);
        this->m = new int *[row];
        for (int i = 0; i < row; i++)
        {
            this->m[i] = new int[col];
        }

        //skips line that is not useful
        getline(inStream, inLine);

        int num = 0;
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                inStream >> num;
                this->m[i][j] = num;
            }
        }

        inStream.close();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (this->m[i][j] < 0)
                    this->m[i][j] = 0;
                if (this->m[i][j] > 65535)
                    this->m[i][j] = 65535;
            }
        }
    }
    else
    {
        std::ifstream input(pgmPath);

        const unsigned int N = 9;
        this->numRows = N;
        this->numColumns = N;
        m = new int *[N];

        char t;
        for (unsigned int i = 0; i < N; i++)
        {
            m[i] = new int[N];
            for (unsigned int j = 0; j < N; j++)
            {
                input >> t;

                if (t == '*')
                    m[i][j] = 0;
                else
                    m[i][j] = t - '0';
            }
        }

        input.close();
    }
}
Matrix::Matrix(const Matrix &A)
/**
   
  This is the copy constructor for the Matrix class
  Takes a matrix A and copies all values and data from A into
  the new matrix

    @return void
*/
{
    //copy constructor,take values for numRows and numCols
    //of A and set new matrix row and colummn values
    //then take values from A matrix and set object matrix
    //to those values
    numRows = A.NumRows();
    numColumns = A.NumColumns();

    if (numRows == 0 && numColumns == 0)
    {
        m = nullptr;
    }
    else
    {

        m = new int *[numRows];

        for (unsigned int i = 0; i < numRows; i++)
        {
            m[i] = new int[numColumns];
            for (unsigned int j = 0; j < numColumns; j++)
            {
                m[i][j] = A.m[i][j];
            }
        }
    }
}
Matrix::~Matrix()
/**
   
    The destructor for the Matrix Class, frees all allocated memory for
    matrices.

    @return void
*/
{
    //matrix destructor, free up all allocated memory
    //for object matrix
    //executes at end of execution
    int row = this->numRows;

    for (int i = 0; i < row; i++)
    {
        delete[] this->m[i];
    }
    delete[] this->m;
}

Matrix &Matrix::operator=(const Matrix &A)
/**
   
    Assignment operator, example A = B
    Sets A equal to B while also freeing previously stored memory for A

    @return void
*/
{
    //assignment operator
    //if the matrix is not equal to A and is not null,
    //delete allocated memory
    //then copy all A matrix values into object matrix
    //including numRows and numColumns.
    if (&A != this)
    {
        if (this->m != nullptr)
        {
            for (unsigned int i = 0; i < this->numRows; i++)
            {
                delete[] m[i];
            }
            delete[] m;
        }
        this->numRows = A.NumRows();
        this->numColumns = A.NumColumns();
        if (numRows == 0 && numColumns == 0)
            m = nullptr;

        m = new int *[numRows];
        for (unsigned int i = 0; i < this->numRows; i++)
        {
            m[i] = new int[numColumns];
            for (unsigned int j = 0; j < this->numColumns; j++)
            {
                m[i][j] = A.m[i][j];
            }
        }
    }
    return *this;
}

bool operator==(const Matrix &A, const Matrix &B)
/**
   
    Equality operator, returns true if A and B are equal
    example A == B

    @return void
*/
{
    //returns true if all values of A and B are equal
    //all values plus amount of rows and columns must be
    //equal in order the return true
    //otherwise it returns false.
    bool ret = false;

    if (A.numRows == B.numRows)
    {
        if (A.numColumns == B.numColumns)
            ret = true;
    }

    if (ret == true)
    {
        for (unsigned int i = 0; i < A.NumRows(); i++)
        {
            for (unsigned int j = 0; j < A.NumColumns(); j++)
            {
                if (A.m[i][j] != B.m[i][j])
                    ret = false;
            }
        }
    }

    return ret;
}
bool operator!=(const Matrix &A, const Matrix &B)
/**
   
    Opposite of the equality operator
    returns the opposite of A == B, 
    if A does not equal B returns true

    @return void
*/
{
    //returns the opposite of the == operator
    return !(A == B);
}
Matrix operator+(const Matrix &A, const Matrix &B)
/**
   
    Adds two Matrices and returns the resultant
    Overloading the operator +

    Example A + B

    @return void
*/
{

    //computes matrix addition
    //adds values at each position, then returns the resulting matrix
    Matrix C(A.NumRows(), A.NumColumns());
    if (A.NumRows() != B.NumRows())
    {
        if (A.NumColumns() != B.NumColumns())
        {
            std::cout << "Cannot Add" << std::endl;
            return C;
        }
    }
    for (unsigned int i = 0; i < A.NumRows(); i++)
    {
        for (unsigned int j = 0; j < A.NumColumns(); j++)
        {
            C.m[i][j] = (A.m[i][j] + B.m[i][j]);
        }
    }
    return C;
}
Matrix operator-(const Matrix &A, const Matrix &B)
/**
   
    subtracts two Matrices and returns the resultant
    Overloading the operator -

    Example A - B

    @return void
*/
{
    //computes matrix subtraction
    //subtracts values at each position, then returns the resulting matrix
    Matrix C(A.NumRows(), A.NumColumns());
    if (A.NumRows() != B.NumRows())
    {
        if (A.NumColumns() != B.NumColumns())
        {
            std::cout << "Cannot Add" << std::endl;
            return C;
        }
    }
    for (unsigned int i = 0; i < A.NumRows(); i++)
    {
        for (unsigned int j = 0; j < A.NumColumns(); j++)
        {
            C.m[i][j] = (A.m[i][j] - B.m[i][j]);
        }
    }
    return C;
}
Matrix operator*(const int c, const Matrix &A)
/**
   
    Overloads Operator *
    Multiplies a Matrix by a constant C, then returns a constant

    Example 2*A

    @return void
*/
{
    //computes matrix multiplication with a constant
    //multiplies values at each position by the constant, then returns the resulting matrix
    Matrix C(A.NumRows(), A.NumColumns());
    for (unsigned int i = 0; i < A.NumRows(); i++)
    {
        for (unsigned int j = 0; j < A.NumColumns(); j++)
        {
            C.m[i][j] = (A.m[i][j] * c);
        }
    }
    return C;
}
Matrix operator*(const Matrix &A, const Matrix &B)
/**
   
    Overloads operator *
    Computes cross product of Matrices, A X B
    Then returns the resultant

    @return void
*/
{
    //computes matrix multiplication with another matrix
    //uses the cross product formula to result in a new matrix, it then returns said matrix
    Matrix C(A.NumRows(), B.NumColumns());
    int num = 0;
    for (unsigned int i = 0; i < A.NumRows(); i++)
    {
        for (unsigned int j = 0; j < B.NumColumns(); j++)
        {
            for (unsigned int k = 0; k < B.NumRows(); k++)
            {
                num += (A.m[i][k] * B.m[k][j]);
            }
            C.m[i][j] = num;
            num = 0;
        }
    }
    return C;
}
Matrix Transpose(const Matrix &A)
/**
   
    Computes the transpose of Matrix A, and then returns the resultant matrix
    flips the values across the diagonal

    @return void
*/
{
    //computes matrix transpose
    //flips values across the diagonal, when i is not equal to j
    Matrix C(A.NumColumns(), A.NumRows());

    for (unsigned int i = 0; i < A.NumRows(); i++)
    {
        for (unsigned int j = 0; j < A.NumColumns(); j++)
        {
            C.m[j][i] = A.m[i][j];
        }
    }
    return C;
}
std::ostream &operator<<(std::ostream &os, const Matrix &A)
/**
   
    Overloads the << operator
    Outputs the matrix values to the ostream and then returns the ostream

    @return void
*/
{
    //overloads the << operator, and outputs matrix values in a readable format
    //then returns the ostream
    for (unsigned int i = 0; i < A.NumRows(); i++)
    {
        for (unsigned int j = 0; j < A.NumColumns(); j++)
        {
            if (j + 1 == A.NumColumns())
                os << A.m[i][j] << "\n";
            else
                os << A.m[i][j] << " ";
        }
    }
    return os;
}

/* Sudoku Solver */
void Matrix::SaveSudoku(std::string outPutFile)
{
    const int N = 9;
    std::ofstream output(outPutFile);

    for (unsigned int i = 0; i < N; i++)
    {
        for (unsigned int j = 0; j < N; j++)
        {
            output << this->m[i][j];
        }
        output << std::endl;
    }
    output.close();
}
bool Matrix::IsValidSudoku()
{
    if(numRows != 9 && numColumns != 9)return false;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(m[i][j] < 0 || m[i][j] > 9)return false;
        }
    }
    for(int i = 0; i < 9; i+=3){
        for(int j = 0; j < 9; j+=3){
                if(!isValidBox(i,j,*this))return false;
        }
    }

    for(int i = 0; i < 9; i++){
        if(!isValidCol(i,*this))return false;
        if(!isValidRow(i,*this))return false;
    }

    return true;
}
bool isValidBox(int row, int col, const Matrix &A){
    int freq[9] = {0};

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
                freq[A.m[i+row][j+col]-1]++;
                //std::cout << A.m[i+row][j+row] << " ";

        }
        //std::cout << std::endl;
    }
    for(int i = 0; i < 9; i++){
       
        if(freq[i] > 1)return false;
    }
    //std::cout << std::endl;

    return true;
}
bool isValidRow(int row,const Matrix &A){
    int freq[9] = {0};
    
    for(int ii = 0; ii < 9; ii++){
        freq[A.m[row][ii]-1]++;
    }
    for(int i = 0; i < 9; i++){
       
        if(freq[i] > 1)return false;
    }
    return true;
}
bool isValidCol(int col,const Matrix &A){
    int freq[9] = {0};
    
    for(int ii = 0; ii < 9; ii++){
        freq[A.m[ii][col]-1]++;
    }
    for(int i = 0; i < 9; i++){
       
        if(freq[i] > 1)return false;
    }
    return true;
}

void Matrix::SolveSudoku()
{
    //if (this->IsValidSudoku())
    //{
        BacktrackSolve(*this);
    //}
}

bool BacktrackSolve(const Matrix &A)
{
    //sets vlaus of row and col to zero
    int row = 0, col = 0;

    //if there is no open spaces, the sodoku is finished and returns true
    if (!findOpenSpace(A, row, col))
        return true;

    //loops through #'s 1-9 checking if they can fit into empty spaces
    for (int i = 1; i <= 9; i++)
    {

        //if the number can fit into empty space
        if (isSafeMove(A, i, row, col))
        {

            //set that position to the value
            A.m[row][col] = i;

            //Recursively goes through all the spaces
            //if we reach the end and return true then we
            //have achieved a finished sodoku.
            if (BacktrackSolve(A))
                return true;

            //if we reach this point, one of our previous
            //enrtries is invalid, so it will backtrack until
            //it fixes the issue that has occured
            A.m[row][col] = 0;
        }
    }

    //if in the end we have gone through everything and nothing has returned true
    //the sodoku is unsolvable and we therefore must return false
    //meaning the sodoku is unsolvable
    return false;
}

//finds and open space within the matrix
bool findOpenSpace(const Matrix &A, int &row, int &col)
{

    //loops through all the matrix positions to find an open space
    //then alters the row and col numbers to that (i,j) position
    for (unsigned int i = 0; i < 9; i++)
    {
        for (unsigned int j = 0; j < 9; j++)
        {

            //an open space will be marked by a zero
            if (A.m[i][j] == 0)
            {
                row = i;
                col = j;
                //returns true if we find and open space
                return true;
            }
        }
    }

    //if we never find an open space it will return false
    //meaning the matrix is full
    return false;
}
bool isSafeMove(const Matrix &A, int num, int row, int col)
{

    //if the number appears in the column return false
    for (unsigned int i = 0; i < 9; i++)
    {
        if (A.m[row][i] == num)
            return false;
    }

    //if the number appears in the row, return false;
    for (unsigned int i = 0; i < 9; i++)
    {
        if (A.m[i][col] == num)
            return false;
    }

    //makes sure we start at the beggining of the box
    //Say row = 3, this will allow us to start at the 0 index for checking
    //that first box.
    int rowPos = row - row % 3;
    int colPos = col - col % 3;

    //if the number appears in the box return false
    for (unsigned int i = 0; i < 3; i++)
    {
        for (unsigned int j = 0; j < 3; j++)
        {
            if (A.m[i + rowPos][j + colPos] == num)
                return false;
        }
    }

    return true;
}
/* GENERAL MATRIX INFORMATION */

bool Matrix::IsEmpty() const
/**
   
   This checks to see if the matrix is empty

    @return bool
*/
{
    if (this->numRows == 0 && this->numColumns == 0)
        return true;
    return false;
}

bool Matrix::IsSquare() const
/**
   
   This checks if the matrix is a square

    @return IsSquare
*/
{
    bool IsSquare = false;
    if (this->numRows == this->numColumns)
        IsSquare = true;
    // if rows equals colums the matrix is square and is square is true

    return IsSquare;
}

bool Matrix::IsZero() const
/**
   
   This checks of the matrix is a zero matrix.

    @return bool
*/
{
    // initialize
    // if the constrthiucted matrix is the same as the zero matrix isZero is true.
    for (unsigned int i = 0; i < this->numRows; i++)
    {
        for (unsigned int j = 0; j < this->numColumns; j++)
        {
            if (this->m[i][j] != 0)
                return false;
        }
    }
    return true;
}

unsigned Matrix::NumRows() const
/**
   
   returns the number of rows in the matrix

    @return numRows
*/
{
    return this->numRows;
}

unsigned Matrix::NumColumns() const
/**
   
   returns the number of columns in the matrix


    @return numColumns
*/
{
    return this->numColumns;
}

std::string Matrix::Size() const
/**
   
   This returns the size of the matrix
    @return ret
*/
{
    std::string ret = "";
    ret += std::to_string(this->numRows) + "x" + std::to_string(this->numColumns);
    return ret;
}
/* GENERAL SQUARE MATRIX INFORMATION */

bool Matrix::IsDiagonal() const
/**
   
   This checks to see of the matrix is a diagonal matrix.

    @return isDiagnoal
*/
{
    bool isDiagonal = true;

    for (unsigned int i = 0; i < this->numRows; i++)
    {
        for (unsigned int j = 0; j < this->numColumns; j++)
            if ((i != j) && this->m[i][j] != 0)
                isDiagonal = false;
    }
    return isDiagonal;
}

bool Matrix::IsLowerTriangular() const
/**
   
   This checks if the matrix is a lower triangle or not.

    @return bool
*/
{
    for (unsigned int i = 0; i < this->numRows; i++)
    {
        for (unsigned int j = 0; j < this->numColumns; j++)
        {
            if (i < j)
            {
                if (this->m[i][j] != 0)
                    return false;
            }
        }
    }
    return true;
}

bool Matrix::IsSkewSymmetric() const
/**
   
   This checks if the matrix is a skew symetric matrix or not.

    @return bool
*/
{
    if (this->numRows != this->numColumns)
        return false;
    Matrix C;
    C = Transpose(*this);

    for (unsigned int i = 0; i < this->numRows; i++)
    {
        for (unsigned int j = 0; j < this->numColumns; j++)
        {
            C.m[i][j] = -C.m[i][j];
        }
    }

    if (C == *this)
        return true;
    return false;
}

bool Matrix::IsSymmetric() const
/**
   
   This checks if the matrix is symetric or not.

    @return bool
*/
{
    if (this->numRows != this->numColumns)
        return false;

    if (*this == Transpose(*this))
        return true;
    return false;
}
bool Matrix::IsUpperTriangular() const
/**
   
   This determines if the matrix is an upper
   triangle matrix or not

    @return bool
*/
{
    for (unsigned int i = 0; i < this->numRows; i++)
    {
        for (unsigned int j = 0; j < this->numColumns; j++)
        {
            if (i > j)
            {
                if (this->m[i][j] != 0)
                    return false;
            }
        }
    }
    return true;
}

//ELEMENT ACCESS
int &Matrix::operator()(const unsigned i, const unsigned j) const
/**
   
   This gives element access

    @return int
*/
{
    return this->m[i - 1][j - 1];
}

void Matrix::Save(const std::string &pgmPath) const
/**
   
   This saves the matrix and chages numbers that are grater than 
   or less than the min and max to the min or max number.

    @return void
*/
{
    std::ofstream os(pgmPath);

    os << "P2\n";
    os << "# comments line\n";
    os << this->numRows << " " << this->numColumns << "\n";

    int max = 0;

    for (unsigned int i = 0; i < this->numRows; i++)
    {
        for (unsigned int j = 0; j < this->numColumns; j++)
        {
            if (this->m[i][j] < 0)
                this->m[i][j] = 0;
            if (this->m[i][j] > 65535)
                this->m[i][j] = 65535;
            if (this->m[i][j] > max)
                max = this->m[i][j];
        }
    }

    os << max << "\n";
    for (unsigned int i = 0; i < this->numRows; i++)
    {
        for (unsigned int j = 0; j < this->numColumns; j++)
        {
            if (j + 1 == this->numColumns)
                os << this->m[i][j] << "\n";
            else
                os << this->m[i][j] << " ";
        }
    }
}