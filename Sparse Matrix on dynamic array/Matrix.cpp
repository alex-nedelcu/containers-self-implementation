#include "Matrix.h"
#include <exception>

using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
    this->linesNumber = nrLines;
    this->columnsNumber = nrCols;
    this->nonZeroElemsNumber = 0;
    this->capacity = 5;
    this->collection = new triple[capacity];
} // theta(1)


Matrix::~Matrix() {
    delete[] this->collection;
} // theta(1)


int Matrix::nrLines() const {
    return this->linesNumber;
} // theta(1)


int Matrix::nrColumns() const {
    return this->columnsNumber;
} // theta(1)


int Matrix::totalNumberOfNonZeroElems() const {
    return this->nonZeroElemsNumber;
} // theta(1)


TElem Matrix::getElement(int i, int j) const {
    if (i < 0 || j < 0 || i >= this->linesNumber || j >= this->columnsNumber) {
        throw exception();
    }

    int index = 0;
    triple currentTriple;
    bool possible = true;

    while (possible == true && index < this->nonZeroElemsNumber) {
        currentTriple = this->collection[index];

        if (i == std::get<0>(currentTriple) && j == std::get<1>(currentTriple))
            return std::get<2>(currentTriple);
        else
            index++;

        if (index < this->nonZeroElemsNumber && i < std::get<0>(this->collection[index]) ||
            (i == std::get<0>(this->collection[index]) && j < std::get<1>(this->collection[index])))
            possible = false;
    }
    return NULL_TELEM;
}
// n = number of elements in the dynamic array
// BC: theta(1) - the searched element is placed on the first position
// WC: theta(n) - the searched element is not in the array and its position is "greater" than the positions of the
//              - elements in the array, when ordered lexicographically
// AC: theta(n) - SUM [P(I) * E(I)]
//              - P(I) = input I probability -> we consider that the searched element can have any indices (i,j) and
//                its value can be either 0 or non-0 -> P(I) = 1/(linesNumber*columnsNumber*2)
//              - E(I) = number of steps executed for input I
// Total complexity: O(n)


TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i >= this->linesNumber || j >= this->columnsNumber) {
        throw exception();
    }

    TElem previousValue = this->getElement(i, j);
    TElem newValue = e;

    if (previousValue == NULL_TELEM) {
        if (newValue == NULL_TELEM)
            return NULL_TELEM;
        else {
            // the triple <i,j,e> must be added to the array
            if (this->nonZeroElemsNumber == this->capacity) {
                // resize is needed firstly
                this->capacity *= 2;
                triple* resizedCollection = new triple[this->capacity];
                for (int k = 0; k < this->nonZeroElemsNumber; k++)
                    resizedCollection[k] = this->collection[k];
                delete[] this->collection;
                this->collection = resizedCollection;
            }

            int targetPosition, index = 0;
            bool stop = false;

            while (stop == false && index < this->nonZeroElemsNumber)
                if (i < std::get<0>(this->collection[index]) ||
                    (i == std::get<0>(this->collection[index]) && j < std::get<1>(this->collection[index]))) {
                    targetPosition = index;
                    stop = true;
                } else index++;

            if (stop == false) targetPosition = this->nonZeroElemsNumber;

            // we must insert the new triple on targetPosition
            for (int k = this->nonZeroElemsNumber - 1; k >= targetPosition; k--)
                this->collection[k + 1] = this->collection[k];

            std::get<0>(this->collection[targetPosition]) = i;
            std::get<1>(this->collection[targetPosition]) = j;
            std::get<2>(this->collection[targetPosition]) = e;
            this->nonZeroElemsNumber++;
        }
    } else {
        if (newValue == NULL_TELEM) {
            int removePosition, index = 0;
            bool found = false;

            while (found == false && index < this->nonZeroElemsNumber)
                if (i == std::get<0>(this->collection[index]) && j == std::get<1>(this->collection[index])) {
                    found = true;
                    removePosition = index;
                } else index++;

            // we must remove the triple from removePosition
            for (int k = removePosition + 1; k < this->nonZeroElemsNumber; k++)
                this->collection[k - 1] = this->collection[k];
            this->nonZeroElemsNumber--;
        } else {
            // we must simply replace the old value with the new one
            int index = 0;
            bool found = false;
            while (found == false && index < this->nonZeroElemsNumber)
                if (i == std::get<0>(this->collection[index]) && j == std::get<1>(this->collection[index])) {
                    found = true;
                    std::get<2>(this->collection[index]) = e;
                } else index++;
        }
    }
    return previousValue;
}
// n = number of elements in the dynamic array
// BC: theta(1) - when both the previous and the new value are 0
// WC: theta(n) - when the previous value was 0 and the new value is non-0, and a resize in needed
// AC: theta(n) - SUM [P(I) * E(I)]
//              - P(I) = input I probability
//              - E(I) = number of steps executed for input I
// Total complexity: O(n)

int Matrix::numberOfNonZeroElemsOnLine(int line) const {
    if (line < 0 || line >= this->linesNumber) {
        throw exception();
    }

    bool stop = false;
    int searchedNumber = 0;
    for (int index = 0; index < this->nonZeroElemsNumber && !stop; index++) {
        if (std::get<0>(this->collection[index]) == line)
            searchedNumber++;
        if (std::get<0>(this->collection[index]) > line)
            stop = true;
    }

    return searchedNumber;
}
// n = number of elements in the dynamic array
// if line == k, then there are executed NUMBER OF NON-ZERO ELEMENTS ON LINES 0 TO K steps
// BC: theta(1) - when the received line is smaller than the first line which contains non-zero elements
// WC: theta(n) - when the received line is greater or equal with the last line which contains non-zero elements
// AC: theta(n) - SUM [P(I) * E(I)]
// Total complexity: O(n)
