#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>
#include <iostream>
#include <cmath>

SortedBag::SortedBag(TRelation relation) : m_relation{relation} {
    m_BST = new BinarySearchTree{};
    m_BST->root = -1;
    m_capacity = 16;
    m_size = 0;
    m_infoArray = new int[m_capacity];
    m_leftArray = new int[m_capacity];
    m_rightArray = new int[m_capacity];
    m_nextEmptyArray = new int[m_capacity];
    m_firstEmpty = 0;

    /// initialize the content of the Binary Search Tree (actually the 4 arrays)
    for (int i = 0; i < m_capacity; i++) {
        m_infoArray[i] = -1;
        m_leftArray[i] = -1;
        m_rightArray[i] = -1;

        /// set the links between the empty positions
        if (i < m_capacity - 1)
            m_nextEmptyArray[i] = i + 1;
        else
            m_nextEmptyArray[i] = -1;
    }
} // theta(capacity)

void SortedBag::add(TComp element) {
    if (m_firstEmpty == -1) {
        /// resize
        int oldCapacity = m_capacity;
        m_capacity *= 2;
        int* newInfoArray = new int[m_capacity];
        int* newLeftArray = new int[m_capacity];
        int* newRightArray = new int[m_capacity];
        int* newNextEmptyArray = new int[m_capacity];

        for (int i = 0; i < oldCapacity; i++) {
            newInfoArray[i] = m_infoArray[i];
            newLeftArray[i] = m_leftArray[i];
            newRightArray[i] = m_rightArray[i];
            newNextEmptyArray[i] = m_nextEmptyArray[i];
        }

        for (int i = oldCapacity; i < m_capacity; i++) {
            newInfoArray[i] = -1;
            newLeftArray[i] = -1;
            newRightArray[i] = -1;

            if (i < m_capacity - 1)
                newNextEmptyArray[i] = i + 1;
            else
                newNextEmptyArray[i] = -1;
        }

        m_firstEmpty = oldCapacity;
        delete[] m_infoArray;
        delete[] m_leftArray;
        delete[] m_rightArray;
        delete[] m_nextEmptyArray;

        m_infoArray = newInfoArray;
        m_leftArray = newLeftArray;
        m_rightArray = newRightArray;
        m_nextEmptyArray = newNextEmptyArray;
    }

    int targetPositionInArray = m_firstEmpty;
    m_firstEmpty = m_nextEmptyArray[m_firstEmpty];
    m_nextEmptyArray[targetPositionInArray] = -1;

    if (m_size == 0) {
        /// the new node must be added as the root of the BST
        m_BST->root = targetPositionInArray;
        m_infoArray[m_BST->root] = element;
        m_leftArray[m_BST->root] = -1;
        m_rightArray[m_BST->root] = -1;
    } else {
        /// the new node must be added inside the BST
        int currentNodePosition = m_BST->root;
        int parentNodePosition = -1;

        while (currentNodePosition != -1)
            if (m_relation(m_infoArray[currentNodePosition], element)) {
                parentNodePosition = currentNodePosition;
                currentNodePosition = m_rightArray[currentNodePosition];
            } else {
                parentNodePosition = currentNodePosition;
                currentNodePosition = m_leftArray[currentNodePosition];
            }

        if (m_relation(m_infoArray[parentNodePosition], element))
            m_rightArray[parentNodePosition] = targetPositionInArray;
        else
            m_leftArray[parentNodePosition] = targetPositionInArray;

        m_infoArray[targetPositionInArray] = element;
        m_leftArray[targetPositionInArray] = -1;
        m_rightArray[targetPositionInArray] = -1;
    }

    m_size += 1;
}
// BC: theta(1) - the BST is empty
// WC: theta(2*capacity + height of the tree) - when resize is needed
// AC: theta(height of the tree)
// Total complexity: O(total height of the tree)

bool SortedBag::remove(TComp element) {
    /// when removing a node, there are 3 options:
    /// a. it is a leaf, so it has no successors
    ///     - we simply remove the node from the BST
    /// b. it has only 1 successor
    ///     - we link the sub-binary tree which starts from the node with the node's parent
    /// c. it has 2 successors
    ///     - we replace the node with its predecessor/successor and the remove the precessor/successor which is a
    ///       node with no successors
    int currentNodePosition = m_BST->root;
    int currentNodeInfo;
    int parentNodePosition = -1;
    bool found = false;

    while (currentNodePosition != -1 && !found) {
        currentNodeInfo = m_infoArray[currentNodePosition];
        if (currentNodeInfo == element)
            found = true;
        else {
            if (m_relation(currentNodeInfo, element)) {
                parentNodePosition = currentNodePosition;
                currentNodePosition = m_rightArray[currentNodePosition];
            } else {
                parentNodePosition = currentNodePosition;
                currentNodePosition = m_leftArray[currentNodePosition];
            }
        }
    }

    if (!found)
        return false;
    else {
        /// the searched element was found
        /// its parent position is parentNodePosition
        /// its position is currentNodePosition
        /// its info is currentNodeInfo

        if (m_leftArray[currentNodePosition] == -1 && m_rightArray[currentNodePosition] == -1) {
            /// 1st case - no children
            if (parentNodePosition == -1)
                m_BST->root = -1;
            else if (m_relation(m_infoArray[parentNodePosition], currentNodeInfo))
                m_rightArray[parentNodePosition] = -1;
            else
                m_leftArray[parentNodePosition] = -1;

            m_infoArray[currentNodePosition] = -1;
            m_leftArray[currentNodePosition] = -1;
            m_rightArray[currentNodePosition] = -1;
            int previousFirstEmpty = m_firstEmpty;
            m_firstEmpty = currentNodePosition;
            m_nextEmptyArray[m_firstEmpty] = previousFirstEmpty;
        } else if ((m_leftArray[currentNodePosition] == -1 && m_rightArray[currentNodePosition] != -1) ||
                   (m_leftArray[currentNodePosition] != -1 && m_rightArray[currentNodePosition] == -1)) {
            /// 2nd case - 1 child
            int descendantPosition;
            if (m_leftArray[currentNodePosition] != -1)
                descendantPosition = m_leftArray[currentNodePosition];
            else
                descendantPosition = m_rightArray[currentNodePosition];

            if (parentNodePosition == -1)
                m_BST->root = descendantPosition;
            else if (m_relation(currentNodeInfo, m_infoArray[parentNodePosition]))
                m_leftArray[parentNodePosition] = descendantPosition;
            else
                m_rightArray[parentNodePosition] = descendantPosition;

            m_infoArray[currentNodePosition] = -1;
            m_leftArray[currentNodePosition] = -1;
            m_rightArray[currentNodePosition] = -1;
            int previousFirstEmpty = m_firstEmpty;
            m_firstEmpty = currentNodePosition;
            m_nextEmptyArray[m_firstEmpty] = previousFirstEmpty;
        } else {
            /// 3rd case - 2 children
            /// first we find the successor of the node to be removed
            /// successor = minimum node from the right sub-tree of the current node
            int successorPosition = findSuccessorPosition(currentNodePosition);
            int parentOfSuccessor = findParentPosition(successorPosition);

            m_leftArray[parentOfSuccessor] = m_rightArray[successorPosition];
            m_infoArray[currentNodePosition] = m_infoArray[successorPosition];

            /// now we remove the successor
            if (m_rightArray[successorPosition] == -1) {
                /// the successor has no children
                if (m_infoArray[m_leftArray[parentOfSuccessor]] == m_infoArray[successorPosition]) {
                    /// the successor is a left child of its parent
                    m_leftArray[parentOfSuccessor] = -1;
                } else {
                    /// the successor is a right child of its parent
                    m_rightArray[parentOfSuccessor] = -1;
                }
            } else {
                /// the successor has a right child
                if (m_infoArray[m_leftArray[parentOfSuccessor]] == m_infoArray[successorPosition]) {
                    /// the successor is a left child of its parent
                    m_leftArray[parentOfSuccessor] = m_rightArray[successorPosition];
                } else {
                    /// the successor is a right child of its parent
                    m_rightArray[parentOfSuccessor] = m_rightArray[successorPosition];
                }
            }

            m_infoArray[successorPosition] = -1;
            m_leftArray[successorPosition] = -1;
            m_rightArray[successorPosition] = -1;
            int previousFirstEmpty = m_firstEmpty;
            m_firstEmpty = successorPosition;
            m_nextEmptyArray[m_firstEmpty] = previousFirstEmpty;
        }
        m_size -= 1;
        return true;
    }
} // O(height of the tree)

bool SortedBag::search(TComp element) const {
    int currentNodePosition = m_BST->root;
    int currentNodeInfo;
    bool found = false;

    while (currentNodePosition != -1 && !found) {
        currentNodeInfo = m_infoArray[currentNodePosition];
        if (currentNodeInfo == element)
            found = true;
        else {
            if (m_relation(currentNodeInfo, element)) {
                /// we must search in the right side of the current node, because currentNodeInfo "<" element
                currentNodePosition = m_rightArray[currentNodePosition];
            } else {
                /// we must search in the left side of the current node, because currentNodeInfo ">" element
                currentNodePosition = m_leftArray[currentNodePosition];
            }
        }
    }

    return found;
}
// BC: theta(1)
// WC: theta(height of the tree)
// AC: theta(height of the tree)
// Total complexity: O(height of the tree)

int SortedBag::nrOccurrences(TComp element) const {
    int currentNodePosition = m_BST->root;
    int currentNodeInfo;
    int count = 0;

    while (currentNodePosition != -1) {
        currentNodeInfo = m_infoArray[currentNodePosition];
        if (currentNodeInfo == element)
            count += 1;
        if (m_relation(currentNodeInfo, element))
            currentNodePosition = m_rightArray[currentNodePosition];
        else
            currentNodePosition = m_leftArray[currentNodePosition];
    }

    return count;
} // theta(height of the tree)

int SortedBag::size() const {
    return m_size;
} // theta(1)

bool SortedBag::isEmpty() const {
    return m_size == 0;
} // theta(1)

SortedBagIterator SortedBag::iterator() const {
    SortedBagIterator it{*this};
    it.first();
    return it;
} // O(height of the tree)

SortedBag::~SortedBag() {
    delete m_BST;
    delete[] m_infoArray;
    delete[] m_leftArray;
    delete[] m_rightArray;
    delete[] m_nextEmptyArray;
} // theta(1)

int SortedBag::findParentPosition(int nodePosition) const {
    if (nodePosition < 0 || nodePosition >= m_capacity)
        throw std::exception();

    if (nodePosition == m_BST->root)
        return -1;

    int currentNodePosition = m_BST->root;
    while (currentNodePosition != -1 &&
           m_leftArray[currentNodePosition] != nodePosition && m_rightArray[currentNodePosition] != nodePosition)
        if (m_relation(m_infoArray[currentNodePosition], m_infoArray[nodePosition]))
            currentNodePosition = m_rightArray[currentNodePosition];
        else
            currentNodePosition = m_leftArray[currentNodePosition];

    return currentNodePosition;
} // O(height of the tree)

int SortedBag::findSuccessorPosition(int nodePosition) const {
    int currentNodePosition;

    if (m_rightArray[nodePosition] != -1) {
        currentNodePosition = m_rightArray[nodePosition];
        while (m_leftArray[currentNodePosition] != -1)
            currentNodePosition = m_leftArray[currentNodePosition];
        return currentNodePosition;
    } else {
        int parentNodePosition = findParentPosition(nodePosition);
        while (parentNodePosition != -1 && m_relation(m_infoArray[parentNodePosition], m_infoArray[nodePosition]))
            parentNodePosition = findParentPosition(parentNodePosition);
        return parentNodePosition;
    }
} // O(height of the tree)

int SortedBag::getRange() const {
    if (m_size == 0)
        return -1;

    if (m_size == 1)
        return 0;

    /// find the minimum element, i.e. the leftmost element in the tree
    int minimum = m_BST->root;
    while (m_leftArray[minimum] != -1)
        minimum = m_leftArray[minimum];

    /// find the maximum element, i.e. the rightmost element in the tree
    int maximum = m_BST->root;
    while (m_rightArray[maximum] != -1)
        maximum = m_rightArray[maximum];

    return fabs(m_infoArray[maximum] - m_infoArray[minimum]);
}
// BC: theta(1) - when the left child of the root is the minimum from the left sub-tree and
//                the right child of the root is maximum from the right sub-tree => they themselves do not have
//                a left and a right sub-tree, so the iteration stops after 2 steps
// WC: theta(height of the tree)
// AC: theta(height of the tree)
// Total complexity: O(height of the tree)

