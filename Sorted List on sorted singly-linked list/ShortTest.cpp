#include <assert.h>

#include "SortedIteratedList.h"
#include "ListIterator.h"

#include <exception>

using namespace std;

bool relation1(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    } else {
        return false;
    }
}

bool parityCondition(TComp e) {
    if (e % 2 == 0) {
        return true;
    } else {
        return false;
    }
}

void testAll() {
    SortedIteratedList list = SortedIteratedList(relation1);
    assert(list.size() == 0);
    assert(list.isEmpty());

    list.add(1);
    list.add(2);
    list.add(3);
    assert(list.size() == 3);
    assert(!list.isEmpty());

    ListIterator it = list.search(1);
    assert(it.valid());
    assert(it.getCurrent() == 1);

    it.next();
    assert(it.valid());
    assert(it.getCurrent() == 2);

    it.next();
    assert(it.valid());
    assert(it.getCurrent() == 3);

    it.next();
    assert(!it.valid());

    it.first();
    assert(it.valid());
    assert(it.getCurrent() == 1);
    assert(it.getCurrent() != 2 && it.getCurrent() != 3);

    ListIterator itFirst = list.first();
    assert(itFirst.valid());
    assert(itFirst.getCurrent() == 1);
    assert(list.remove(itFirst) == 1);
    assert(list.size() == 2);
    assert(!list.isEmpty());
    assert(!list.search(1).valid()); // the TComp 1 is not found in the list, so the search function returns an invalid iterator
    assert(list.remove(itFirst) == 2);
    assert(list.remove(itFirst) == 3);
    assert(!itFirst.valid());

    SortedIteratedList list2 = SortedIteratedList(relation1);
    list2.add(5);
    list2.add(2);
    list2.add(10);
    list2.add(4);
    // the order must be 2, 4, 5, 10
    ListIterator it2 = list2.first();
    assert(it2.getCurrent() == 2);
    it2.next();
    assert(it2.getCurrent() == 4);
    it2.next();
    assert(it2.getCurrent() == 5);
    it2.next();
    assert(it2.getCurrent() == 10);
    it2.next();
    assert(!it2.valid());

    SortedIteratedList list3 = SortedIteratedList(relation1);
    ListIterator it3 = list3.first();

    list3.add(1);
    list3.add(2);
    list3.add(3);
    list3.add(4);
    list3.add(5);
    list3.add(6);
    list3.add(7);

    assert(list3.size() == 7);
    list3.filter(parityCondition);
    assert(list3.size() == 3);

    it3.first();
    assert(it3.getCurrent() == 2);
    it3.next();
    assert(it3.getCurrent() == 4);
    it3.next();
    assert(it3.getCurrent() == 6);
    it3.next();
    assert(!it3.valid());
}

