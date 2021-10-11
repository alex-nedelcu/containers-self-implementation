
#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"

using namespace std;


int main() {
    cout << "Executing short test...\n";
    testAll();
    cout << "Short test finished successfully\n\n";
    cout << "Executing extended test...\n";
    testAllExtended();
    cout << "Extended test finished successfully\n";
}