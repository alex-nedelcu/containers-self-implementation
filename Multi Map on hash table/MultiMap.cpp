#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>

MultiMap::MultiMap() {
    m_hashTable = new HashTable;
    m_hashTable->m_positions = findNextPrime(10);
    m_hashTable->m_array = new Node* [m_hashTable->m_positions];
    m_hashTable->m_loadFactor = 0;
    m_hashTable->m_firstNonEmptyPosition = -1;
    m_hashTable->m_numberOfNodes = 0; // number of nodes of the hash table
    m_numberOfElements = 0; // number of elements of the map

    for (int i = 0; i < m_hashTable->m_positions; i++)
        m_hashTable->m_array[i] = NULL;
} // theta(number of positions of the hash table)

MultiMap::~MultiMap() {
    Node* currentNode;
    Node* previousNode;
    for (int i = 0; i < m_hashTable->m_positions; i++) {
        currentNode = m_hashTable->m_array[i];
        previousNode = NULL;

        while (currentNode != NULL) {
            delete[] currentNode->data.values;
            previousNode = currentNode;
            currentNode = currentNode->next;
            delete previousNode;
        }
    }

    delete[] m_hashTable->m_array;
    delete m_hashTable;
} // theta(total number of nodes)

void MultiMap::add(TKey key, TValue value) {
    if (m_hashTable->m_loadFactor - 0.7 > 0.1) {
        rehash();
    }

    int targetPosition = hash(key);
    if (m_hashTable->m_firstNonEmptyPosition == -1)
        m_hashTable->m_firstNonEmptyPosition = targetPosition;
    else if (targetPosition < m_hashTable->m_firstNonEmptyPosition)
        m_hashTable->m_firstNonEmptyPosition = targetPosition;

    if (m_hashTable->m_array[targetPosition] == NULL) {
        // the target position does not contain any node
        Node* newNode = new Node;
        m_hashTable->m_numberOfNodes += 1;
        m_hashTable->m_array[targetPosition] = newNode;
        newNode->next = NULL;

        newNode->data.key = key;
        newNode->data.capacity = 10;
        newNode->data.size = 0;
        newNode->data.values = new TValue[newNode->data.capacity];

        newNode->data.values[newNode->data.size] = value;
        newNode->data.size += 1;
    } else {
        // the SLL from the target position contains at least one node
        // we must now decide whether the new <key,value> pair must be added to an existing node or as a separate node
        Node* head = m_hashTable->m_array[targetPosition];
        Node* currentNode = head;

        while (currentNode != NULL) {
            if (currentNode->data.key == key) {
                // we must add the new TElem as part of the current node
                if (currentNode->data.size == currentNode->data.capacity) {
                    // resize for the dynamic array associated to the key
                    currentNode->data.capacity *= 2;
                    TValue* resizedArray = new TValue[currentNode->data.capacity];

                    for (int i = 0; i < currentNode->data.size; i++)
                        resizedArray[i] = currentNode->data.values[i];

                    delete[] currentNode->data.values;
                    currentNode->data.values = resizedArray;
                }
                currentNode->data.values[currentNode->data.size] = value;
                currentNode->data.size += 1;
                break;
            }
            currentNode = currentNode->next;
        }

        if (currentNode == NULL) {
            // we must add the new element as a separate node
            Node* newNode = new Node;
            m_hashTable->m_numberOfNodes += 1;
            m_hashTable->m_array[targetPosition] = newNode;
            newNode->next = head;

            newNode->data.key = key;
            newNode->data.capacity = 10;
            newNode->data.size = 0;
            newNode->data.values = new TValue[newNode->data.capacity];

            newNode->data.values[newNode->data.size] = value;
            newNode->data.size += 1;
        }
    }

    m_numberOfElements += 1;
    m_hashTable->m_loadFactor = ((double)m_hashTable->m_numberOfNodes / m_hashTable->m_positions);
}
// BC: theta(1) - when the slot from the table where the key should be placed is NULL
// WC: theta(1 + load factor + number of elements associated with the received key) - when the key of the element
//     which needs to be added corresponds to the last node of a chain and the dynamic array containing the other
//     values needs a resize
// AC: theta(1 + load factor)
// Total complexity: O(load factor)

bool MultiMap::remove(TKey key, TValue value) {
    int targetPosition = hash(key);
    Node* currentNode = m_hashTable->m_array[targetPosition];
    Node* previousNode = NULL;

    while (currentNode != NULL) {
        if (currentNode->data.key == key) {
            // the current node might contain the searched value
            for (int i = 0; i < currentNode->data.size; i++)
                if (currentNode->data.values[i] == value) {
                    // we found the searched value, so we need to remove it
                    for (int j = i + 1; j < currentNode->data.size; j++)
                        currentNode->data.values[j - 1] = currentNode->data.values[j];
                    currentNode->data.size -= 1;

                    if (currentNode->data.size == 0) {
                        // we must delete the entire node
                        delete[] currentNode->data.values;

                        if (previousNode == NULL)
                            m_hashTable->m_array[targetPosition] = currentNode->next;
                        else
                            previousNode->next = currentNode->next;

                        delete currentNode;
                    }
                    m_numberOfElements -= 1;
                    m_hashTable->m_loadFactor = ((double)m_hashTable->m_numberOfNodes / m_hashTable->m_positions);

                    if (m_hashTable->m_array[m_hashTable->m_firstNonEmptyPosition] == NULL)
                        for (int k = m_hashTable->m_firstNonEmptyPosition + 1; k < m_hashTable->m_positions; k++)
                            if (m_hashTable->m_array[k] != NULL) {
                                m_hashTable->m_firstNonEmptyPosition = k;
                                break;
                            }
                    return true;
                }
            // if we exited the for loop without finding the searched value, we must return false
            return false;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    // if we exited the while loop without returning true, it means that the searched value is not in the table
    return false;
}
// BC: theta(1) - when the slot from the table where the key should be found is NULL
// WC: theta(1 + load factor + number of values associated with the received key) - when the key of the element
//     which needs to be removed corresponds to the last node of a chain
// AC: theta(1 + load factor + number of values associated with the received key)
// Total complexity: O(load factor + number of values associated with the received key)

std::vector<TValue> MultiMap::search(TKey key) const {
    std::vector<TValue> values;
    int targetPosition = hash(key);
    Node* currentNode = m_hashTable->m_array[targetPosition];

    while (currentNode != NULL) {
        if (currentNode->data.key == key) {
            for (int i = 0; i < currentNode->data.size; i++)
                values.push_back(currentNode->data.values[i]);
            return values;
        }
        currentNode = currentNode->next;
    }
    return values;
}
// BC: theta(1) - when the slot from the table where the key should be found is NULL
// WC: theta(1 + load factor) - when the searched key corresponds to the last node of a chain
// AC: theta(1 + load factor)
// Total complexity: O(load factor)

int MultiMap::size() const {
    return m_numberOfElements;
} // theta(1)

bool MultiMap::isEmpty() const {
    return m_numberOfElements == 0;
} // theta(1)

MultiMapIterator MultiMap::iterator() const {
    return MultiMapIterator(*this);
} // theta(1)

int MultiMap::hash(TKey key) const {
    return fabs(key % m_hashTable->m_positions);
} // theta(1)

int MultiMap::findNewCapacity() {
    return findNextPrime(m_hashTable->m_positions * 7);
} // theta(1)

void MultiMap::rehash() {
    int newCapacity = findNewCapacity(); // the load factor will become approximately = 0.1 after the rehash
    Node** resizedTable = new Node* [newCapacity];
    std::vector<TElem> elements;
    TKey key;
    TValue value;
    TElem element;

    // initialize the new hash table
    for (int i = 0; i < newCapacity; i++)
        resizedTable[i] = NULL; // theta(2 * initial capacity)

    // store the elements of the old hash table
    for (int i = 0; i < m_hashTable->m_positions; i++) {
        Node* currentNode = m_hashTable->m_array[i];
        while (currentNode != NULL) {
            key = currentNode->data.key;
            for (int j = 0; j < currentNode->data.size; j++) {
                value = currentNode->data.values[j];
                element.first = key;
                element.second = value;
                elements.push_back(element);
            }
            currentNode = currentNode->next;
        }
    } // theta(number of elements of the map + number of positions of the hash table)

    // deallocate the old hash table
    for (int i = 0; i < m_hashTable->m_positions; i++) {
        Node* currentNode = m_hashTable->m_array[i];
        Node* previousNode;
        while (currentNode != NULL) {
            delete[] currentNode->data.values;
            previousNode = currentNode;
            currentNode = currentNode->next;
            delete previousNode;
        }
    } // theta(number of nodes of the hash table)
    delete[] m_hashTable->m_array;

    m_hashTable->m_positions = newCapacity;
    m_hashTable->m_array = resizedTable;
    m_hashTable->m_loadFactor = 0;
    m_hashTable->m_firstNonEmptyPosition = -1;
    m_numberOfElements = 0;

    for (const TElem& x: elements)
        add(x.first, x.second); // theta(number of elements of the map * load factor)
} // theta(number of elements of the map + number of positions of the hash table)

