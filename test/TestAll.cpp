#include <iostream>

#include "types/TestTypes.h"
#include "utils/TestUtils.h"

using namespace std;

int main() {
    TestTypes testTypes;
    testTypes.test();

    TestUtils testUtils;
    testUtils.test();
}
