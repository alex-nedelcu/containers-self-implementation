#include "ShortTest.h"
#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <assert.h>
#include <vector>
#include<iostream>

using namespace std;

void testAll() {
    cout << "Start short tests" << endl;
    MultiMap m;
    m.add(1, 100);
    m.add(2, 200);
    m.add(3, 300);
    m.add(1, 500);
    m.add(2, 600);
    m.add(4, 800);

    assert(m.size() == 6);

    assert(m.remove(5, 600) == false);
    assert(m.remove(1, 500) == true);

    assert(m.size() == 5);

    vector<TValue> v;
    v = m.search(6);
    assert(v.size() == 0);

    v = m.search(1);
    assert(v.size() == 1);

    assert(m.isEmpty() == false);

    MultiMapIterator im = m.iterator();
    assert(im.valid() == true);

    while (im.valid()) {
        im.getCurrent();
        im.next();
    }
    assert(im.valid() == false);
    im.first();
    assert(im.valid() == true);

    ////////////////////////////////////////////////////////////////////////////////////////////////

    MultiMap myMap;
    myMap.add(1, 543);
    myMap.add(2, 765);
    myMap.add(4, 120);
    myMap.add(1, 423);
    myMap.add(3, 869);
    myMap.add(2, 698);
    MultiMapIterator myIterator = myMap.iterator();

    // the order in which the iterator must iterate is: <1,543>, <1,423>, <2,765>, <2,698>, <3,869>, <4,120>

    myIterator.first();
    myIterator.next();
    myIterator.next();
    myIterator.next();
    myIterator.next();
    myIterator.next(); // the iterator is placed on the last element

    int key1 = 0, key2 = 0, key3 = 0, key4 = 0, mustBeNull = 0;
    while (myIterator.valid()) {
//        cout << myIterator.getCurrent().first << "-" << myIterator.getCurrent().second << endl;
        if (myIterator.getCurrent().first == 1) key1++;
        else if (myIterator.getCurrent().first == 2) key2++;
        else if (myIterator.getCurrent().first == 3) key3++;
        else if (myIterator.getCurrent().first == 4) key4++;
        else mustBeNull++;
        myIterator.previous();
    }
    assert(key1 == 2);
    assert(key2 == 2);
    assert(key3 == 1);
    assert(key4 == 1);
    assert(mustBeNull == 0);

    try {
        myIterator.previous();
        assert(false);
    } catch (...) {
        assert(true);
    }

    MultiMap emptyMap;
    MultiMapIterator w = emptyMap.iterator();
    assert(!w.valid());

    try {
        w.previous();
        assert(false);
    } catch (...) {
        assert(true);
    }

    emptyMap.add(1, 1);
    emptyMap.add(2, 2);
    w.first();
    assert(w.valid());

    assert(w.getCurrent().first == 1);
    assert(w.getCurrent().second == 1);
    w.next();
    assert(w.getCurrent().first == 2);
    assert(w.getCurrent().second == 2);

    w.previous();
    assert(w.getCurrent().first == 1);
    assert(w.getCurrent().second == 1);
    w.previous();
    assert(!w.valid());

    try {
        w.previous();
        assert(false);
    } catch (...) {
        assert(true);
    }

    cout << "Finish short tests" << endl;
}
