#include "bst.hpp"

int main(int argc, char** argv) {

    BinarySearchTree<int> myBst(6);

    myBst.add(3);
    myBst.add(2);
    myBst.add(4);
    myBst.add(5);
    myBst.add(9);
    myBst.add(7);
    myBst.add(8);
    myBst.add(10);
    myBst.add(11);
    myBst.add(12);

    //myBst.print();

    //delete &myBst;

    return 0;
}