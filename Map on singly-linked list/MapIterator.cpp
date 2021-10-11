#include "MapIterator.h"
#include <exception>

using namespace std;

MapIterator::MapIterator(const Map& map) : m_map{map} {
    m_currentPosition = m_map.m_SLLA->head;
    m_previousPosition = -1;
} // theta(1)


void MapIterator::first() {
    m_currentPosition = m_map.m_SLLA->head;
    m_previousPosition = -1;
} // theta(1)


void MapIterator::next() {
    if (m_currentPosition == -1)
        throw exception();
    m_previousPosition = m_currentPosition;
    m_currentPosition = m_map.m_next[m_currentPosition];
} // theta(1)


TElem MapIterator::getCurrent() {
    if (m_currentPosition == -1)
        throw exception();
    return m_map.m_collection[m_currentPosition];
} // theta(1)


bool MapIterator::valid() const {
    return m_currentPosition != -1;
} // theta(1)

TElem MapIterator::removeCurrent() {
    if (m_currentPosition == -1)
        throw exception();

    TElem returnedPair = m_map.m_collection[m_currentPosition];

    if (m_currentPosition == m_map.m_SLLA->head) {
        // we have to remove the head
        m_map.m_SLLA->head = m_map.m_next[m_map.m_SLLA->head]; // reset the head
        m_map.m_collection[m_currentPosition] = NULL_TELEM; // optional
    } else {
        // we must remove an element which is not the head
        m_map.m_next[m_previousPosition] = m_map.m_next[m_currentPosition]; // we link the previous "node" with the next one
        m_map.m_collection[m_currentPosition] = NULL_TELEM; // optional
    }
    // common part both for removing the head and for removing other element
    int nextPosition = m_map.m_next[m_currentPosition]; // needed in order to move the iterator on the next position
    m_map.m_next[m_currentPosition] = m_map.m_SLLA->firstEmpty; // link the current position with the list of emtpy positions
    m_map.m_SLLA->firstEmpty = m_currentPosition; // add the current position in the list of empty positions
    m_currentPosition = nextPosition; // the actual current position of the iterator is updated
    m_map.m_SLLA->size--;

    return returnedPair;
} // theta(1)




