#include <assert.h>
#include "Matrix.h"

using namespace std;

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    assert(m.totalNumberOfNonZeroElems() == 0);
    m.modify(1, 1, 5);
    m.modify(0, 3, 3);
    m.modify(0, 1, 7);
    m.modify(1, 3, 9);

    assert(m.numberOfNonZeroElemsOnLine(1) == 2);
    assert(m.numberOfNonZeroElemsOnLine(0) == 2);
    assert(m.numberOfNonZeroElemsOnLine(2) == 0);
    assert(m.numberOfNonZeroElemsOnLine(3) == 0);

    m.modify(1, 0, 10);
    assert(m.numberOfNonZeroElemsOnLine(1) == 3);

    m.modify(3, 1, 15);
    assert(m.numberOfNonZeroElemsOnLine(3) == 1);

    try {
        m.numberOfNonZeroElemsOnLine(7);
        assert(false);
    }
    catch (exception& ex) {
        assert(true);
    }

    assert(m.totalNumberOfNonZeroElems() == 6);
    assert(m.getElement(1, 1) == 5);
    TElem old = m.modify(1, 1, 6);
    assert(m.getElement(1, 2) == NULL_TELEM);
    assert(old == 5);
}