// btexcept.hpp
// Eccezioni custom per il progetto "btree"
// Esame di Programmazione C++ 20/04/20
// Copyright (c) 2020 Jacopo Maltagliati <j.maltagliati@campus.unimib.it>

#ifndef BTEXCEPT_HPP
#define BTEXCEPT_HPP

#include <stdexcept>

/**
 * @brief Eccezione personalizzata utilizzata nel caso in cui venga tentato
 * l'inserimento di un dato duplicato all'interno dell'albero binario
 */
class duplicate_data : public std::exception {
  virtual const char* what() const throw() {
    return "nextPlace(): tentativo di inserimento di un dato duplicato";
  }
};

/**
 * @brief Eccezione personalizzata utilizzata nel caso in cui venga tentato
 * l'accesso ad un nodo inesistente
 */
class no_such_node : public std::exception {
  virtual const char* what() const throw() {
    return "subtree(): tentativo di creazione di un sotto-albero a partire da "
           "un nodo inesistente";
  }
};

/**
 * @brief Eccezione personalizzata utilizzata nel caso in cui si verifichi un
 * errore di allocazione durante la creazione di un nuovo nodo
 */
class node_creation_error : public std::exception {
  virtual const char* what() const throw() {
    return "createNode(): creazione di un nuovo nodo fallita";
  }
};

#endif
