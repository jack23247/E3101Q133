#include "bst.hpp"
#include <cassert>
#include <ostream>

// #define TEST_FAIL

int main() {

    BST<int> myBst(6);

    myBst.add(3);
    myBst.add(2);
    myBst.add(4);
    myBst.add(5);
    myBst.add(9);
    myBst.add(7);
    myBst.add(8);
    myBst.add(10);

    #ifdef TEST_FAIL
    myBst.add(10);
    #endif

    myBst.add(11);
    myBst.add(12);

    myBst.print();

    assert(myBst.exists(7));
    assert(myBst.exists(12));
    assert(!myBst.exists(128));
    assert(myBst.getSize() == 10);
    
    std::cout << myBst << std::endl;

    myBst.destroy();

    return 0;
}