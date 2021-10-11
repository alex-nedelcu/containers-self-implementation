#include "ShortTest.h"
#include <cassert>
#include "Map.h"
#include "MapIterator.h"
#include <iostream>

using namespace std;

void testAll() { //call each function to see if it is implemented
    Map m;
    assert(m.isEmpty() == true);
    assert(m.size() == 0); // add elements
    assert(m.add(5, 5) == NULL_TVALUE);
    assert(m.add(1, 111) == NULL_TVALUE);
    assert(m.add(10, 110) == NULL_TVALUE);
    assert(m.add(7, 7) == NULL_TVALUE);
    assert(m.add(1, 1) == 111);
    assert(m.add(10, 10) == 110);
    assert(m.add(-3, -3) == NULL_TVALUE);
    assert(m.size() == 5);
    assert(m.search(10) == 10);
    assert(m.search(16) == NULL_TVALUE);
    assert(m.remove(1) == 1);
    assert(m.remove(6) == NULL_TVALUE);
    assert(m.size() == 4);


    TElem e;
    MapIterator id = m.iterator();
    id.first();
    int s1 = 0, s2 = 0;
    while (id.valid()) {
        e = id.getCurrent();
        s1 += e.first;
        s2 += e.second;
        id.next();
    }
    assert(s1 == 19);
    assert(s2 == 19);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Map mTest;
    mTest.add(100, 5);
    mTest.add(101, 4);
    mTest.add(102, 3);

    MapIterator itx = mTest.iterator();
    itx.first();
    assert(itx.valid());
    assert(mTest.size() == 3);

    while (itx.valid()) {
        TElem removedElement;
        removedElement = itx.removeCurrent();
        assert (removedElement.first + removedElement.second == 105);
    }

    assert(mTest.size() == 0);
    assert(!itx.valid());

    try {
        itx.removeCurrent();
        assert(false);
    } catch (...) {
        assert(true);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Map m2;
    m2.add(30, 70);
    m2.add(20, 80);
    m2.add(75, 25);
    m2.add(1, 2);
    m2.add(90, 10);
    MapIterator it2 = m2.iterator();
    it2.first();

    TElem removedElement;
    assert(m2.size() == 5);
    while (it2.valid()) {
        TElem element;
        element = it2.getCurrent();
        if (element.first + element.second != 100)
            removedElement = it2.removeCurrent();
        else
            it2.next();
    }
    assert(removedElement.first == 1);
    assert(removedElement.second == 2);
    assert(m2.size() == 4);

    cout << "Short tests successfully finished" << endl;
}


