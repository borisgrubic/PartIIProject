#include <iostream>

#include "types/TestTypes.h"
#include "utils/TestUtils.h"
#include "core/TestCore.h"

using namespace std;

int main() {
    string msg = "------------ Running unit tests ------------";
    cout << msg << endl;
    cout << endl;

    TestTypes testTypes;
    testTypes.test();

    TestUtils testUtils;
    testUtils.test();

    TestCore testCore;
    testCore.test();

    cout << endl;
    msg = "---- All unit tests passed successfully ----";
    cout << msg << endl;
}
