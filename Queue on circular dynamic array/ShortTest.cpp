#include "ShortTest.h"
#include "Queue.h"
#include <assert.h>

void testAll() {
    Queue q;
    assert(q.isEmpty() == true);
    q.push(5);
    q.push(1);
    q.push(10);
    q.push(123);
    q.push(465);
    q.push(1534);
    assert(q.isEmpty() == false);
    assert(q.top() == 5);
    assert(q.pop() == 5);
    assert(q.top() == 1);
    assert(q.pop() == 1);
    assert(q.top() == 10);
    assert(q.pop() == 10);
    assert(q.isEmpty() == false);
    assert(q.top() == 123);
    assert(q.pop() == 123);
    assert(q.top() == 465);
    assert(q.pop() == 465);
    assert(q.top() == 1534);
    assert(q.pop() == 1534);
    assert(q.isEmpty() == true);
}