#include "Utils.h"

bool isPrime(int primeCandidate) {
    if (primeCandidate <= 1)
        return false;

    for (int i = 2; i <= primeCandidate / 2; i++)
        if (primeCandidate % i == 0)
            return false;

    return true;
}

int findNextPrime(int lowerBound) {
    if (lowerBound <= 1)
        return 2;

    int searchedPrime = lowerBound;
    bool found = false;

    while (!found) {
        searchedPrime++;
        if (isPrime(searchedPrime))
            found = true;
    }

    return searchedPrime;
}
