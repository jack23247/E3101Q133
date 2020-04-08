// main.cpp
// Programma dimostrativo per il progetto "btree"
// Esame di Programmazione C++ 20/04/20
// (c) 2020 - Jacopo Maltagliati <j.maltagliati@campus.unimib.it>

#include <cassert>
#include <csignal>
#include <ostream>
#include <string>

#include "btree.hpp"

// #define FAIL_INT_TEST
// #define FAIL_LI_TEST

/**
 * @brief Tipo del funtore di uguaglianza per gli interi
 */
struct equal_int {
  /**
   * @brief Funtore di uguaglianza per gli interi
   * @param a un intero
   * @param b un intero
   * @return true se a e b sono uguali
   * @return false se a e b sono diversi
   */
  bool operator()(int a, int b) const { return b == a; }
};

/**
 * @brief Tipo del funtore di comparazione per gli interi
 */
struct compare_int {
  /**
   * @brief Funtore di comparazione per gli interi
   *
   * @param a un intero
   * @param b un intero
   *
   * @return true se b e' maggiore di a
   * @return false se b e' minore di a
   */
  bool operator()(int a, int b) const { return b > a; }
};

/**
 * @brief Tipo del funtore di test della condizione "pari" per gli interi
 */
struct even_int {
  /**
   * @brief Funtore di test della condizione "pari" per gli interi
   *
   * @param a un intero
   *
   * @return true se a e' pari
   * @return false se a e' dispari
   */
  bool operator()(int a) const { return (a % 2) == 0; }
};

/**
 * @brief Tipo custom: indice etichettato
 */
class labeled_idx {
 private:
  const uint _index;
  const std::string _label;

 public:
  labeled_idx(const uint index, const std::string& content)
      : _index(index), _label(content) {}

  uint get_index() { return this->_index; }

  friend std::ostream& operator<<(std::ostream& output, const labeled_idx& li) {
    output << li._index << ":" << li._label;
    return output;
  }
};

/**
 * @brief Tipo del funtore di uguaglianza per gli indici etichettati
 */
struct equal_labeled_idx {
  /**
   * @brief Funtore di uguaglianza per gli indici etichettati
   * @param a un indice etichettato
   * @param b un indice etichettato
   * @return true se a e b sono uguali
   * @return false se a e b sono diversi
   */
  bool operator()(labeled_idx a, labeled_idx b) const {
    return b.get_index() == a.get_index();
  }
};

/**
 * @brief Tipo del funtore di comparazione per gli indici etichettati
 *
 */
struct compare_labeled_idx {
  /**
   * @brief Funtore di comparazione per gli indici etichettati
   *
   * @param a un indice etichettato
   * @param b un indice etichettato
   *
   * @return true se b e' maggiore di a
   * @return false se b e' minore di a
   */
  bool operator()(labeled_idx a, labeled_idx b) const {
    return b.get_index() > a.get_index();
  }
};

/**
 * @brief Tipo del funtore di test della condizione "pari" per gli indici
 * etichettati
 */
struct even_labeled_idx {
  /**
   * @brief Funtore di test della condizione "pari" per gli indici etichettati
   *
   * @param a un indice etichettato
   *
   * @return true se a e' pari
   * @return false se a e' dispari
   */
  bool operator()(labeled_idx a) const { return (a.get_index() % 2) == 0; }
};

/**
 * @brief Entry point
 *
 * @return int sempre zero
 */
int main() {
  std::cout << "Progetto \"btree\" - programma dimostrativo." << std::endl;

  {  // block int_test
    std::cout << "Test sugli interi in corso...\n\n" << std::endl;

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
    assert(bst_a.get_size() == 11);

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

    std::cout << "\n\nTest sugli interi completato." << std::endl;
  }  // endblock int_test

  {  // block indexed_lbl_test
    std::cout << "Test sugli indici etichettati in corso...\n\n" << std::endl;

    labeled_idx lm_91_pos1(1, "Mazda_787B");
    labeled_idx lm_91_pos2(2, "Jaguar_XJR-12");
    labeled_idx lm_91_pos3(3, "Jaguar_XJR-12");
    labeled_idx lm_91_pos4(4, "Jaguar_XJR-12");
    labeled_idx lm_91_pos5(5, "Mercedes-Benz_C11");
    labeled_idx lm_91_pos6(6, "Mazda_787B");
    labeled_idx lm_91_pos7(7, "Porsche_962C");
    labeled_idx lm_91_pos8(8, "Mazda_787");
    labeled_idx lm_91_pos9(9, "Porsche_962CK6");

    labeled_idx lm_91_pos15(15, "Lancia_LC2");

    // test costruttore base btree(T data)
    btree<labeled_idx, compare_labeled_idx, equal_labeled_idx> bst_a(
        lm_91_pos1);

    // test add()
    bst_a.add(lm_91_pos3);
    bst_a.add(lm_91_pos4);
    bst_a.add(lm_91_pos5);
    bst_a.add(lm_91_pos6);
    bst_a.add(lm_91_pos7);


#ifdef FAIL_LI_TEST
    bst_a.add(lm_91_pos7);
#endif

    bst_a.add(lm_91_pos8);
    bst_a.add(lm_91_pos9);

    bst_a.add(lm_91_pos2);

    // test print()
    std::cout
        << "I primi dieci classificati della 24 ore di Le Mans del 1991 sono: "
        << std::flush;
    bst_a.print();

    // test exist()
    assert(bst_a.exists(lm_91_pos9));
    assert(!bst_a.exists(lm_91_pos15));

    // test get_size()
    assert(bst_a.get_size() == 9);

    // test costruttore copia btree(btree src)
    btree<labeled_idx, compare_labeled_idx, equal_labeled_idx> bst_b(bst_a);

    // test operator<<()
    std::cout << "I primi dieci classificati (copia 1) sono: " << bst_b
              << std::endl;

    // test operator=()
    btree<labeled_idx, compare_labeled_idx, equal_labeled_idx> bst_c = bst_b;
    std::cout << "I primi dieci classificati (copia 2) sono: " << bst_c
              << std::endl;

    // test subtree() e operator=()
    btree<labeled_idx, compare_labeled_idx, equal_labeled_idx> bst_sub =
        bst_a.subtree(lm_91_pos4);
    std::cout << "Coloro che non sono saliti sul podio sono: " << bst_sub
              << std::endl;

    // test iteratori
    btree<labeled_idx, compare_labeled_idx, equal_labeled_idx>::const_iterator
        i,
        i_e;
    std::cout << "I dati dei nodi in ordine di inserimento sono: "
              << std::flush;
    for (i = bst_a.begin(), i_e = bst_a.end(); i != i_e; ++i) {
      std::cout << *i << " " << std::flush;
    }
    std::cout << std::endl;

    // test printIF()
    even_labeled_idx pred_even;
    std::cout << "I valori pari contenuti nei nodi sono: " << std::flush;
    printIF<labeled_idx, compare_labeled_idx, equal_labeled_idx,
            even_labeled_idx>(bst_a, pred_even);

    std::cout << "\n\nTest sugli indici etichettati completato." << std::endl;
  }  // endblock

  std::cout << "Tutti i test sono stati completati." << std::endl;
  return 0;
}
