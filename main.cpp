// main.cpp
// Programma dimostrativo per il progetto "btree"
// Esame di Programmazione C++ 20/04/20
// (c) 2020 - Jacopo Maltagliati <j.maltagliati@campus.unimib.it>
// Rilasciato sotto licenza MIT - Released under the MIT license

#include <cassert>
#include <csignal>
#include <ostream>
#include <string>

#include "btree.hpp"

#define FAIL_INT_TEST
// #define FAIL_CUSTOM_TYPE_TEST

/**
 * @brief Funtore di uguaglianza per gli int
 * @return true se i valori sono uguali
 * @return false se i valori sono diversi
 */
struct equal_int {
  bool operator()(int a, int b) const { return a == b; }
};

/**
 * @brief Funtore di uguaglianza per gli int
 * @return true se i valori sono uguali
 * @return false se i valori sono diversi
 */
struct compare_int {
  bool operator()(int a, int b) const { return a < b; }
};

/**
 * @brief Funtore di uguaglianza per gli int
 * @return true se i valori sono uguali
 * @return false se i valori sono diversi
 */
struct even_int {
  bool operator()(int a) const { return (a %= 2) == 0; }
};

int test_int() {
  try {
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

#ifdef FAIL_INT_TEST
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
    std::cout
        << "Il sotto-albero \"bst_sub\" di \"bst_a\" a partire dal nodo 3 e': "
        << bst_sub << std::endl;

    // test iteratori
    btree<int, compare_int, equal_int>::const_iterator i, i_e;
    std::cout << "I dati dei nodi in ordine di inserimento sono: "
              << std::flush;
    for (i = bst_a.begin(), i_e = bst_a.end(); i != i_e; ++i) {
      std::cout << *i << " " << std::flush;
    }
    std::cout << std::endl;

    // test printIF()
    even_int pred_even;
    std::cout << "I valori pari contenuti nei nodi sono: " << std::flush;
    printIF<int, compare_int, equal_int, even_int>(bst_a, pred_even);
  } catch (...) {
    return 1;
  }
  return 0;
}

// TODO //
int test_custom_type() { return 0; }

int main() {
  uint failed = 0;
  std::cout << "Progetto \"btree\" - programma dimostrativo." << std::endl;

  std::cout << "Esecuzione del test \"test_int()\"\n" << std::endl;
  if (test_int()) {
    std::cout << "\nIl test \"test_int()\" e' fallito." << std::endl;
    failed++;
  } else {
    std::cout << "\nIl test \"test_int()\" e' stato superato." << std::endl;
  }

  std::cout << "\nEsecuzione del test \"test_custom_type()\"\n" << std::endl;
  if (test_custom_type()) {
    std::cout << "Il test sui tipi custom e' fallito." << std::endl;
    failed++;
  } else {
    std::cout << "Il test \"test_custom_type()\" e' stato superato."
              << std::endl;
  }

  std::cout << "\nRisultati dei test per il progetto \"btree\":" << std::endl;
  std::cout << failed << " e' il numero di test che non sono stati superati."
            << std::endl;
  return failed;
}