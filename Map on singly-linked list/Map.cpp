#include "Map.h"
#include "MapIterator.h"


Map::Map() {
    m_SLLA = new SLLA;
    m_SLLA->capacity = 10;
    m_SLLA->size = 0;
    m_SLLA->head = -1;
    m_SLLA->firstEmpty = 0;

    m_collection = new TElem[m_SLLA->capacity];
    m_next = new int[m_SLLA->capacity];

    for (int i = 0; i < m_SLLA->capacity - 1; i++) {
        m_collection[i] = NULL_TELEM;
        m_next[i] = i + 1;
    }

    m_collection[m_SLLA->capacity - 1] = NULL_TELEM;
    m_next[m_SLLA->capacity - 1] = -1;
} // theta(initial capacity)

TValue Map::add(TKey key, TValue value) {
    // resize case
    if (m_SLLA->firstEmpty == -1) {
        m_SLLA->capacity *= 2;
        TElem* resizedCollection = new TElem[m_SLLA->capacity];
        int* resizedNext = new int[m_SLLA->capacity];

        for (int i = 0; i < m_SLLA->size; i++) {
            resizedCollection[i] = m_collection[i];
            resizedNext[i] = m_next[i];
        }

        for (int i = m_SLLA->size; i < m_SLLA->capacity; i++)
            resizedCollection[i] = NULL_TELEM;
        for (int i = m_SLLA->size; i < m_SLLA->capacity - 1; i++)
            resizedNext[i] = i + 1;

        m_SLLA->firstEmpty = m_SLLA->size;
        resizedNext[m_SLLA->capacity - 1] = -1;

        delete[] m_collection;
        delete[] m_next;
        m_collection = resizedCollection;
        m_next = resizedNext;
    }

    int currentPosition = m_SLLA->head;
    while (m_collection[currentPosition].first != key && currentPosition != -1)
        currentPosition = m_next[currentPosition];

    if (currentPosition == -1) {
        // the key of the new element does not exist in the map
        TElem newElement;
        newElement.first = key;
        newElement.second = value;

        int targetPosition = m_SLLA->firstEmpty;
        m_collection[targetPosition] = newElement;
        m_SLLA->firstEmpty = m_next[m_SLLA->firstEmpty];
        m_next[targetPosition] = m_SLLA->head;
        m_SLLA->head = targetPosition;
        m_SLLA->size += 1;

        return NULL_TVALUE;
    } else {
        // the key of the new element exists in the map, so its value must be replaced and returned
        int targetPosition = currentPosition;
        TValue replacedValue = m_collection[targetPosition].second;
        m_collection[targetPosition].second = value;

        return replacedValue;
    }
}
// BC: theta(1) - when resize is not needed and the key of the new element is the same with the key of the first element
// WC: theta(n) - when resize is needed and the key of the new element is not in the map
// AC: theta(n)
// Total complexity: O(n)

TValue Map::search(TKey key) const {
    int currentPosition = m_SLLA->head;
    while (m_collection[currentPosition].first != key && currentPosition != -1)
        currentPosition = m_next[currentPosition];

    if (currentPosition == -1)
        return NULL_TVALUE;
    else
        return m_collection[currentPosition].second;
}
// BC: theta(1) - when the given key corresponds to the head of the list
// WC: theta(n) - when the given key does not correspond to any element of the list
// AC: theta(n)
// Total complexity: O(n)

TValue Map::remove(TKey key) {
    int currentPosition = m_SLLA->head;
    int previousPosition = -1;

    while (m_collection[currentPosition].first != key && currentPosition != -1) {
        previousPosition = currentPosition;
        currentPosition = m_next[currentPosition];
    }

    if (currentPosition == -1) {
        // the given key does not exist in the map
        return NULL_TVALUE;
    } else {
        // the key exists in the map
        TValue removedValue = m_collection[currentPosition].second;

        if (currentPosition == m_SLLA->head) {
            // we must remove the head
            m_SLLA->head = m_next[m_SLLA->head];
        } else {
            // we must remove an element which is not the head
            m_collection[currentPosition] = NULL_TELEM;
            m_next[previousPosition] = m_next[currentPosition];
        }
        // common part both for removing the head and for removing other element
        m_next[currentPosition] = m_SLLA->firstEmpty;
        m_SLLA->firstEmpty = currentPosition;

        m_SLLA->size -= 1;
        return removedValue;
    }
}
// BC: theta(1) - when the given key corresponds to the first element of the map
// WC: theta(n) - when the given key does not correspond to any element of the map
// AC: theta(n)
// Total complexity: O(n)

int Map::size() const {
    return m_SLLA->size;
} // theta(1)

bool Map::isEmpty() const {
    return m_SLLA->size == 0;
} // theta(1)

MapIterator Map::iterator() const {
    MapIterator iterator = MapIterator(*this);
    iterator.first();
    return iterator;
} // theta(1)

Map::~Map() {
    delete[] m_collection;
    delete[] m_next;
    delete m_SLLA;
} // theta(1)

