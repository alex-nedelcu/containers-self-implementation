#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cassert>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
    return e1 <= e2;
}

bool relationX(TComp e1, TComp e2) {
    return e1 >= e2;
}

void testAll() {
    SortedBag sb(relation1);
    sb.add(5);
    sb.add(6);
    sb.add(5);
    sb.add(5);
    sb.add(5);
    sb.add(0);
    sb.add(10);
    sb.add(8);
    sb.add(5);
    sb.add(2);
    sb.add(8);
    sb.add(2);
    sb.add(111);

    assert(sb.size() == 13);
    assert(sb.nrOccurrences(5) == 5);

    assert(sb.remove(5) == true);
    assert(sb.nrOccurrences(5) == 4);
    assert(sb.size() == 12);

    assert(sb.search(6) == true);
    assert(sb.isEmpty() == false);

    assert(sb.search(111) == true);
    assert(sb.nrOccurrences(111) == 1);
    assert(sb.remove(111) == true);
    assert(sb.nrOccurrences(111) == 0);
    assert(sb.search(111) == false);
    assert(sb.size() == 11);

    assert(sb.nrOccurrences(5) == 4);
    assert(sb.remove(5) == true);
    assert(sb.remove(5) == true);
    assert(sb.remove(5) == true);
    assert(sb.remove(5) == true);
    assert(sb.nrOccurrences(5) == 0);

    assert(sb.size() == 7);
    sb.add(100);
    sb.add(101);
    assert(sb.size() == 9);
    assert(sb.remove(100) == true);
    assert(sb.size() == 8);
    assert(sb.remove(100) == false);
    assert(sb.size() == 8);

    SortedBagIterator it = sb.iterator();
    assert(it.valid() == true);

    while (it.valid()) {
        it.getCurrent();
        it.next();
    }

    assert(it.valid() == false);
    it.first();
    assert(it.valid() == true);

    ////////////////////////////////////////////////////////////////////////////////////////

    SortedBag sortedBag(relation1);
    sortedBag.add(5);
    sortedBag.add(2);
    sortedBag.add(-1); // min
    sortedBag.add(13);
    sortedBag.add(29);
    sortedBag.add(81); // max
    sortedBag.add(12);
    assert(sortedBag.getRange() == 82);


    SortedBag sortedBag1(relationX);
    assert(sortedBag1.getRange() == -1);

    sortedBag1.add(-3);
    assert(sortedBag1.getRange() == 0);

    sortedBag1.add(-1); // max
    sortedBag1.add(-2);
    sortedBag1.add(-3);
    sortedBag1.add(-4);
    sortedBag1.add(-5);
    sortedBag1.add(-6);
    sortedBag1.add(-7);
    sortedBag1.add(-8); // min
    assert(sortedBag1.getRange() == 7);
}

