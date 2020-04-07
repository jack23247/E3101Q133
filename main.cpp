// main.cpp
// Programma dimostrativo per il progetto "btree"
// Esame di Programmazione C++ 20/04/20
// (c) 2020 - Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
// Rilasciato sotto licenza MIT - Released under the MIT license

#include <cassert>
#include <ostream>
#include <csignal>

#include "btree.hpp"

// #define TEST_FAIL

struct equal_int {
  bool operator()(int a, int b) const { return a == b; }
};

struct compare_int {
  bool operator()(int a, int b) const { return a < b; }
};

int main() {

  // test costruttore base btree(T data)
  btree<int, compare_int, equal_int> bst_a(6);

  // test add()
  bst_a.add(3);
  bst_a.add(2);
  bst_a.add(4);
  bst_a.add(5);
  bst_a.add(9);
  bst_a.add(7);
  bst_a.add(8);
  bst_a.add(10);

#ifdef TEST_FAIL
  bst_a.add(10);
#endif

  bst_a.add(11);
  bst_a.add(12);

  // test print()
  std::cout << "L'albero \"bst_a\" e': " << std::flush;
  bst_a.print();

  // test exist()
  assert(bst_a.exists(7));
  assert(!bst_a.exists(13));

  // test get_size()
  assert(bst_a.get_size() == 10);

  // test costruttore copia btree(btree src)
  btree<int, compare_int, equal_int> bst_b(bst_a);

  // test operator<<()
  std::cout << "L'albero \"bst_b\" e': " << bst_b << std::endl;

  // test operator=()
  btree<int, compare_int, equal_int> bst_c = bst_b;
  std::cout << "L'albero \"bst_c\" e': " << bst_c << std::endl;

  // test subtree() e operator=()
  btree<int, compare_int, equal_int> bst_sub = bst_a.subtree(3);
  std::cout << "Il sotto-albero \"bst_sub\" di \"bst_a\" e': " << bst_sub << std::endl;

  return 0;
}