#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

SortedBagIterator::SortedBagIterator(const SortedBag& bag) : m_bag{bag} {
    m_currentNodePosition = m_bag.m_BST->root;

    /// from the root we go left as much as we can
    if (m_currentNodePosition != -1)
        while (m_bag.m_leftArray[m_currentNodePosition] != -1)
            m_currentNodePosition = m_bag.m_leftArray[m_currentNodePosition];
} // O(height of the tree)

void SortedBagIterator::first() {
    m_currentNodePosition = m_bag.m_BST->root;

    /// from the root we go left as much as we can
    if (m_currentNodePosition != -1)
        while (m_bag.m_leftArray[m_currentNodePosition] != -1)
            m_currentNodePosition = m_bag.m_leftArray[m_currentNodePosition];
} // O(height of the tree)

TComp SortedBagIterator::getCurrent() {
    if (m_currentNodePosition == -1)
        throw std::exception();

    return m_bag.m_infoArray[m_currentNodePosition];
} // theta(1)


void SortedBagIterator::next() {
    if (m_currentNodePosition == -1)
        throw std::exception();

    m_currentNodePosition = m_bag.findSuccessorPosition(m_currentNodePosition);
} // O(height of the tree)

bool SortedBagIterator::valid() const {
    return m_currentNodePosition != -1;
} // theta(1)