#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#include "bstexcept.hpp"

/**
 * @brief Rappresenta un albero binario di ricerca
 *
 * @tparam T Tipo di dato contenuto dall'albero
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
    T _data;

    /**
     * @brief Costruisce un nodo dato il contenuto
     *
     * @param data Il contenuto del nodo
     * @param parent Il genitore del nodo
     */
    explicit node(const T& data, node* parent)
        : _left(nullptr), _right(nullptr), _parent(parent), _data(data) {}

    /**
     * @brief Distrugge il nodo
     */
    ~node() {
      this->_left = nullptr;
      this->_right = nullptr;
      this->_parent = nullptr;
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

  node* _root;
  uint _size;
  C _compare_node;
  E _equals_node;

  /**
   * @brief Crea un nuovo nodo
   *
   * @param data Il dato contenuto nel nodo
   * @param parent Il genitore del nodo
   * @return node* Un puntatore al nodo creato
   *
   * @throw node_creation_error{} Nel caso non sia possibile creare il nodo
   */
  node* create_node(const T data, node* parent = nullptr) {
    try {
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
   * @param lastBranch Annotazione riguardo all'ultima direzione presa
   *
   * @return node* il puntatore in cui inserire il nodo
   *
   * @throw duplicate_data{} nel caso di dato duplicato
   */
  node* next_branch(const node* cur_node, const T data, direction* cur_branch) {
    if (this->_equals_node(cur_node->_data, data)) {
      r_destroy(this->_root);
      throw duplicate_data{};
    }
    if (this->_compare_node(cur_node->_data, data)) {
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
    r_stream_print(output, this->_root->_left, this->_root, direction::left);
    r_stream_print(output, this->_root->_right, this->_root, direction::right);
  }

  /**
   * @brief Scorre ricorsivamente il btree per stampare tutti i nodi
   *
   * @param output Lo stream su cui stampare
   * @param cur_node Il nodo corrente
   * @param parentNode Il nodo genitore
   * @param lastBranch L'ultimo ramo preso
   */
  void r_stream_print(std::ostream& output, const node* cur_node, const node* parentNode,
                      direction lastBranch) const {
    if (cur_node == nullptr) return;
    if (lastBranch == direction::left) {
      output << *parentNode << " -- l --> " << *cur_node << "; ";
    } else if (lastBranch == direction::right) {
      output << *parentNode << " -- r --> " << *cur_node << "; ";
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
      if (cur_node->_data == data) {
        return cur_node;
      } else if (cur_node->_data > data) {
        return r_find_node(cur_node->_left, data);
      } else if (cur_node->_data < data) {
        return r_find_node(cur_node->_right, data);
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
      cur_node = nullptr;
    }
  }

  void sub_copy(btree& dest_tree, const node* cur_node) const {
    if (cur_node == nullptr) { return; } // salto il primo nodo
    r_copy(dest_tree, cur_node->_left);
    r_copy(dest_tree, cur_node->_right);
  }

  void r_copy(btree& dest_tree, const node* cur_node) const {
    if (cur_node == nullptr) { return; }
    dest_tree.add(cur_node->_data);
    r_copy(dest_tree, cur_node->_left);
    r_copy(dest_tree, cur_node->_right);
  }

  void r_copy_from(const btree& src_tree, const node* cur_src_node) {
    if (cur_src_node == nullptr) { return; }
    if(cur_src_node->_parent != nullptr) { // aggiungo il nodo solo se non è root
      this->add(cur_src_node->_data);
    }
    r_copy_from(src_tree, cur_src_node->_left);
    r_copy_from(src_tree, cur_src_node->_right);
  }

 public:
  /**
   * @brief Costruttore per il btree
   *
   * @param data Il dato da inserire nel nodo radice
   */
  btree(const T data) {
    this->_root = this->create_node(data);
    this->_size = 0;
  };

  btree(const btree& src) {
    this->_root = this->create_node(src._root->_data);
    this->_size = 0;
    this->r_copy_from(src, src._root);
    // l'eccezione è lanciata da add dentro r_copy
  }

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
  ~btree() { this->destroy(); };

  /**
   * @brief Aggiunge un nodo al btree e ne incrementa la dimensione
   *
   * @param data Il dato da inserire nel nuovo nodo
   */
  void add(T data) {
    node* cur_node = this->_root;
    node* tmpNodePtr;
    direction lastBranch;
    while ((tmpNodePtr = next_branch(cur_node, data, &lastBranch)) != nullptr) {
      cur_node = tmpNodePtr;
    }
    if (lastBranch == direction::left) {
      cur_node->_left = create_node(data, cur_node);
    } else {
      cur_node->_right = create_node(data, cur_node);
    }
    this->_size++;
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

  btree<T,C,E> subtree(const T data) const {
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

};  // endclass btree

/*
template <typename T, typename C, typename E, typename P>
void printIF(const btree<T,C,E> &btr, P pred) {

        typename ordered_list<T,C,E>::const_iterator i,ie;

        i = ol.begin();
        ie = ol.end();

        while(i!=ie) {
                if(pred(*i)) {
                        std::cout << *i << std::endl;
                }
                ++i;
        }
}
*/

#endif