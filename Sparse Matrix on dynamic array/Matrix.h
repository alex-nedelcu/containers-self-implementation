#pragma once

#include <tuple>

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int line;
typedef int column;
typedef std::tuple<line, column, TElem> triple;
#define NULL_TELEM 0

class Matrix {

private:
    int linesNumber, columnsNumber, nonZeroElemsNumber, capacity;
    triple* collection;

public:
    // constructor
    Matrix(int nrLines, int nrCols);

    // destructor
    ~Matrix();

    // returns the number of lines
    int nrLines() const;

    // returns the number of columns
    int nrColumns() const;

    // returns the number of non-zero elements from the dynamic array
    int totalNumberOfNonZeroElems() const;

    // returns the number of non-zero elements from a given line
    // throws an exception if line is not valid
    int numberOfNonZeroElemsOnLine(int line) const;


    // returns the element from line i and column j (indexing starts from 0)
    // throws exception if (i,j) is not a valid position in the Matrix
    TElem getElement(int i, int j) const;

    // modifies the value from line i and column j
    // returns the previous value from the position
    // throws exception if (i,j) is not a valid position in the Matrix
    TElem modify(int i, int j, TElem e);
};
