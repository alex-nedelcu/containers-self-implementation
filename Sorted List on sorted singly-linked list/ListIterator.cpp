#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : m_list(list) {
    m_currentElement = m_list.m_SSLL->head;
} // theta(1)

void ListIterator::first() {
    m_currentElement = m_list.m_SSLL->head;
} // theta(1)

void ListIterator::next() {
    if (m_currentElement == NULL)
        throw std::exception();

    m_currentElement = m_currentElement->next;
} // theta(1)

bool ListIterator::valid() const {
    if (m_currentElement != NULL)
        return true;
    else
        return false;
} // theta(1)

TComp ListIterator::getCurrent() const {
    if (m_currentElement == NULL)
        throw std::exception();

    return m_currentElement->data;
} // theta(1)

void ListIterator::invalidate() {
    m_currentElement = NULL;
} // theta(1)


