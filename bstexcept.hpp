#ifndef BSTEXCEPT_HPP
#define BSTEXCEPT_HPP

#include <stdexcept>

class duplicate_data : public std::exception {
  virtual const char* what() const throw() {
    return "nextPlace(): tentativo di inserimento di un dato duplicato";
  }
};

class no_such_node : public std::exception {
  virtual const char* what() const throw() {
    return "subtree(): tentativo di creazione di un sotto-albero a partire da "
           "un nodo inesistente";
  }
};

class node_creation_error : public std::exception {
  virtual const char* what() const throw() {
    return "createNode(): creazione di un nuovo nodo fallita";
  }
};

#endif