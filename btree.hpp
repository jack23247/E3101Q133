// btree.hpp
// Classe templata per il progetto "btree"
// Esame di Programmazione C++ 20/04/20
// Copyright (c) 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>

#ifndef BTREE_HPP
#define BTREE_HPP

#include <cstddef>
#include <iostream>
#include <iterator>

#include "btexcept.hpp"

/**
 * @brief Rappresenta un albero binario di ricerca
 *
 * @tparam T Tipo di dato contenuto dall'albero
 * @tparam C Il funtore di comparazione
 * @tparam E Il funtore di uguaglianza
 */
template <typename T, typename C, typename E>
class btree {
 private:
  /**
   * @brief Rappresenta un nodo del btree
   */
  struct node {
    node* _left;
    node* _right;
    node* _parent;
    node* _qnext;
    const T _data;
    /**
     * @brief Costruisce un nodo dato il contenuto
     *
     * @param data Il contenuto del nodo
     * @param parent Il genitore del nodo
     */
    node(const T& data, node* parent)
        : _left(nullptr),
          _right(nullptr),
          _parent(parent),
          _qnext(nullptr),
          _data(data) {}

    /**
     * @brief Distrugge il nodo
     */
    ~node() {
      this->_left = nullptr;
      this->_right = nullptr;
      this->_parent = nullptr;
      this->_qnext = nullptr;
    }

    /**
     * @brief Overload dell'operatore << per la stampa di un nodo
     *
     * @param output Lo stream di output
     * @param node Il nodo da stampare
     */
    friend std::ostream& operator<<(std::ostream& output, const node& node) {
      output << node._data;
      return output;
    }

  };  // endstruct node

  /**
   * @brief direzione del ramo
   */
  enum direction { left, right };

  uint _size;
  node* _root;
  C _compare_strategy;
  E _equals_strategy;
  node* _qlast;

  /**
   * @brief Crea un nuovo nodo
   *
   * @param data Il dato contenuto nel nodo
   * @param parent Il genitore del nodo
   * @return node* Un puntatore al nodo creato
   *
   * @throw node_creation_error{} Nel caso non sia possibile creare il nodo
   */
  node* create_node(const T& data, node* parent = nullptr) {
    try {
      this->_size++;
      return new node(data, parent);
    } catch (...) {
      r_destroy(this->_root);
      throw node_creation_error{};
    }
  }

  /**
   * @brief Trova la direzione corretta dato un nodo e un dato da inserire
   *
   * @param cur_node Il nodo di partenza
   * @param data Il dato da inserire
   * @param cur_branch Annotazione riguardo all'ultima direzione presa
   *
   * @return node* il puntatore in cui inserire il nodo
   *
   * @throw duplicate_data{} nel caso di dato duplicato
   */
  node* next_branch(const node* cur_node, const T data, direction* cur_branch) {
    if (this->_equals_strategy(cur_node->_data, data)) {
      r_destroy(this->_root);
      throw duplicate_data{};
    }
    if (this->_compare_strategy(cur_node->_data, data)) {
      *cur_branch = direction::right;
      return (cur_node->_right);
    } else {
      *cur_branch = direction::left;
      return (cur_node->_left);
    }
  }

  /**
   * @brief Stampa il btree su uno stream a partire dalla radice
   *
   * @param output Lo stream su cui stampare
   */
  void stream_print(std::ostream& output) const {
    if (this->_root == nullptr) return;  // sanity check
    output << *this->_root << "; ";
    r_stream_print(output, this->_root->_left, this->_root, direction::left);
    r_stream_print(output, this->_root->_right, this->_root, direction::right);
  }

  /**
   * @brief Scorre ricorsivamente il btree per stampare tutti i nodi
   *
   * @param output Lo stream su cui stampare
   * @param cur_node Il nodo corrente
   * @param parent_node Il nodo genitore
   * @param cur_branch L'ultimo ramo preso
   */
  void r_stream_print(std::ostream& output, const node* cur_node,
                      const node* parent_node, direction cur_branch) const {
    if (cur_node == nullptr) return;
    if (cur_branch == direction::left) {
      output << *parent_node << " -- l --> " << *cur_node << "; ";
    } else if (cur_branch == direction::right) {
      output << *parent_node << " -- r --> " << *cur_node << "; ";
    }
    r_stream_print(output, cur_node->_left, cur_node, direction::left);
    r_stream_print(output, cur_node->_right, cur_node, direction::right);
  }

  /**
   * @brief Scorre ricorsivamente il btree per cercare un nodo
   *
   * @param cur_node Il nodo corrente
   * @param data Il dato da cercare
   * @return true Se il nodo esiste
   * @return false Se il nodo non esiste
   */
  node* r_find_node(node* cur_node, const T data) const {
    if (cur_node != nullptr) {
      if (this->_equals_strategy(cur_node->_data, data)) {
        return cur_node;
      }
      if (this->_compare_strategy(cur_node->_data, data)) {
        return r_find_node(cur_node->_right, data);
      } else {
        return r_find_node(cur_node->_left, data);
      }
    }
    return nullptr;
  }

  /**
   * @brief Distrugge il btree a partire dalla radice
   */
  void destroy() {
    if (this->_root != nullptr) {
      r_destroy(this->_root);
      this->_root = nullptr;  // se non lo metto, succedono casini
    }
  }

  /**
   * @brief Scorre ricorsivamente il btree per distruggerne i nodi
   *
   * @param cur_node Il nodo corrente
   */
  void r_destroy(node* cur_node) {
    if (cur_node != nullptr) {
      r_destroy(cur_node->_left);
      r_destroy(cur_node->_right);
      delete cur_node;
      // cur_node = nullptr;
    }
  }

  /**
   * @brief Copia una porzione dell'albero, usato solo da subtree
   *
   * @param dest_tree L'albero di destinazione
   * @param cur_node Il nodo corrente
   */
  void sub_copy(btree& dest_tree, const node* cur_node) const {
    if (cur_node == nullptr) {
      return;
    }  // sanity check
    // salto il primo nodo poiche' e' la radice di dest_tree
    r_copy(dest_tree, cur_node->_left);
    r_copy(dest_tree, cur_node->_right);
  }

  /**
   * @brief Copia ricorsivamente una porzione dell'albero
   *
   * @param dest_tree L'albero di destinazione
   * @param cur_node Il nodo corrente
   */
  void r_copy(btree& dest_tree, const node* cur_node) const {
    if (cur_node == nullptr) {
      return;
    }
    dest_tree.add(cur_node->_data);
    r_copy(dest_tree, cur_node->_left);
    r_copy(dest_tree, cur_node->_right);
  }

  /**
   * @brief Copia ricorsivamente i dati da un altro albero
   *
   * @param src_tree L'albero sorgente
   * @param cur_src_node Il nodo corrente nell'albero sorgente
   */
  void r_copy_from(const btree& src_tree, const node* cur_src_node) {
    if (cur_src_node == nullptr) {
      return;
    }
    if (cur_src_node->_parent !=
        nullptr) {  // aggiungo il nodo solo se non è root
      this->add(cur_src_node->_data);
    }
    r_copy_from(src_tree, cur_src_node->_left);
    r_copy_from(src_tree, cur_src_node->_right);
  }

 public:
  /**
   * @brief Iteratore di sola lettura forward per la lettura della coda
   * associata all'albero binario
   *
   */
  class const_iterator {
    const node* _cur_node;

   public:
    /**
     * @brief Costruttore di default per l'iteratore
     */
    const_iterator() : _cur_node(nullptr) {}

    /**
     * @brief Costruttore di copia per l'iteratore
     *
     * @param src L'iteratore sorgente
     */
    const_iterator(const const_iterator& src) : _cur_node(src._cur_node) {}

    /**
     * @brief Overload dell'operatore di assegnamento per l'iteratore
     *
     * @param src L'iteratore sorgente
     */
    const_iterator& operator=(const const_iterator& src) {
      this->_cur_node = src._cur_node;
      return *this;
    }

    /**
     * @brief Distruttore per l'iteratore
     */
    ~const_iterator() {}

    /**
     * @brief Overload dell'operatore di dereference per l'iteratore
     */
    const T& operator*() const { return this->_cur_node->_data; }

    /**
     * @brief Overload dell'operatore di accesso per l'iteratore
     */
    const T* operator->() const { return &(this->_cur_node->_data); }


    /**
     * @brief Overload dell'operatore di pre-incremento per l'iteratore
     */
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      this->_cur_node = this->_cur_node->_qnext;
      return tmp;
    }

    /**
     * @brief Overload dell'operatore di post-incremento per l'iteratore
     */
    const_iterator& operator++() {
      this->_cur_node = this->_cur_node->_qnext;
      return *this;
    }

    /**
     * @brief Overload dell'operatore di uguaglianza per l'iteratore
     */
    bool operator==(const const_iterator& cmp) const {
      return (this->_cur_node == cmp._cur_node);
    }

    /**
     * @brief Overload dell'operatore di disuguaglianza per l'iteratore
     */
    bool operator!=(const const_iterator& cmp) const {
      return (this->_cur_node != cmp._cur_node);
    }

   private:
    friend class btree;

    /**
     * @brief Overload del costruttore a partire da un nodo per l'iteratore
     */
    explicit const_iterator(const node* cur_node) : _cur_node(cur_node) {}

  };  // endclass const_iterator

  /**
   * @brief Costruttore a partire da un dato per il btree
   *
   * @param data Il dato da inserire nel nodo radice
   */
  explicit btree(const T data) : _size(0) {
    this->_root = this->create_node(data);
    this->_qlast = this->_root;
  }

  /**
   * @brief Costruttore di copia per il btree
   *
   * @param src L'albero sorgente
   */
  btree(const btree& src) : _size(0) {
    this->_root = this->create_node(src._root->_data);
    this->_qlast = this->_root;
    this->r_copy_from(src, src._root);
    // l'eccezione è lanciata da add dentro r_copy_from
  }

  /**
   * @brief Overload dell'operatore di assegnamento
   *
   * @param src L'albero sorgente
   * @return btree& Un puntatore all'albero
   */
  btree& operator=(const btree& src) {
    if (this != &src) {
      btree tmp(src);
      std::swap(this->_root, tmp._root);
      std::swap(this->_size, tmp._size);
    }
    return *this;
  }

  /**
   * @brief Distruttore per il btree
   */
  ~btree() { this->destroy(); }

  /**
   * @brief Aggiunge un nodo al btree e ne incrementa la dimensione
   *
   * @param data Il dato da inserire nel nuovo nodo
   */
  void add(T data) {
    node* cur_node = this->_root;
    node* tmp_node;
    direction last_branch;
    while ((tmp_node = next_branch(cur_node, data, &last_branch)) != nullptr) {
      cur_node = tmp_node;
    }
    if (last_branch == direction::left) {
      cur_node->_left = create_node(data, cur_node);
      tmp_node = cur_node->_left;
    } else {
      cur_node->_right = create_node(data, cur_node);
      tmp_node = cur_node->_right;
    }
    this->_qlast->_qnext = tmp_node;
    this->_qlast = tmp_node;
  }

  /**
   * @brief Restituisce la dimensione del btree
   */
  uint get_size() const { return this->_size; }

  /**
   * @brief Trova un nodo nel btree
   *
   * @param data Il dato da cercare
   * @return true Se il nodo esiste
   * @return false Se il nodo non esiste
   */
  bool exists(T data) const {
    return (r_find_node(this->_root, data) != nullptr);
  }

  /**
   * @brief Stampa l'albero (sintassi compatibile con Mermaid
   * https://mermaid-js.github.io/mermaid/#/?id=flowchart)
   */
  void print() const { std::cout << *this << std::endl; }

  /**
   * @brief Crea un sotto-albero a partire da un nodo di contenuto dato
   *
   * @param data Il contenuto del nodo da cui dobbiamo partire
   * @return btree Il sotto-albero
   */
  btree subtree(const T data) const {
    node* sub_root = this->r_find_node(this->_root, data);
    if (sub_root == nullptr) {
      throw no_such_node{};
    }
    btree ret(data);
    sub_copy(ret, sub_root);
    return ret;
  }

  /**
   * @brief Overload dell'operatore << per la stampa su uno stream
   *
   * @param output Lo stream di output
   * @param bst L'albero da stampare
   */
  friend std::ostream& operator<<(std::ostream& output, const btree& bst) {
    output << "graph TD; ";
    bst.stream_print(output);
    return output;
  }

  /**
   * @brief Restituisce l'iteratore alla radice dell'albero
   *
   * @return const_iterator L'iteratore all'inizio della coda
   */
  const_iterator begin() const { return const_iterator(this->_root); }

  /**
   * @brief Restituisce l'iteratore alla fine della struttura dati appiattita
   *
   * @return const_iterator L'iteratore alla fine della coda
   */
  const_iterator end() const { return const_iterator(nullptr); }

};  // endclass btree

/**
 * @brief Stampa il valore dei nodi dell'albero che soddisfano un predicato
 *
 * @tparam T Il tipo di dato contenuto nell'albero
 * @tparam C Il funtore di comparazione
 * @tparam E Il funtore di uguaglianza
 * @tparam P Il predicato tramite cui effettuare il controllo
 * @param bt L'albero binario su cui effettuare il controllo e la stampa
 */
template <typename T, typename C, typename E, typename P>
void printIF(const btree<T, C, E>& bt, P pred) {
  typename btree<T, C, E>::const_iterator i, i_e;

  for (i = bt.begin(), i_e = bt.end(); i != i_e; ++i) {
    if (pred(*i)) {
      std::cout << *i << " " << std::flush;
    }
  }
  std::cout << std::endl;
}

#endif
