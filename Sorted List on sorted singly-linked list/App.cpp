#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"


int main() {
    std::cout << "[[[ STARTED TESTS ]]]\n" << std::endl;
    testAll();
    testAllExtended();
    std::cout << "\n[[[ SUCCESSFULLY FINISHED TESTS ]]]" << std::endl;
    return 0;
}