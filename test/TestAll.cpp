#include <iostream>

#include "types/TestTypes.h"
#include "utils/TestUtils.h"
#include "core/TestCore.h"

using namespace std;

int main() {
    TestTypes testTypes;
    testTypes.test();

    TestUtils testUtils;
    testUtils.test();

    TestCore testCore;
    testCore.test();
}
