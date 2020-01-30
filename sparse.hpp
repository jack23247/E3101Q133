/**
 * \file SparseMatrix.hpp
 * Una classe template che implementa una matrice sparsa.
 */

#include <limits> // Definisce UINT_MAX
#include <iostream>

/** \def EXC_INDEX_BOUND
 * Eccezione generata in lettura/scrittura fuori dai limiti.
 */
#define EXC_INDEX_BOUNDS 0x01

/** \typedef uint_t
 * Shortcut per unsigned int.
 */
typedef unsigned int uint_t;

/** \class SparseMatrix
 * Classe template che implementa una matrice sparsa.
 */
template <class T> class SparseMatrix {

private:

    /** \class SMNode
     * Nodo della lista tramite cui la matrice è implementata.
     */
    class SMNode {

    public:
        uint_t x, y;
        SMNode* next;
        T data;

        SMNode(T data, uint_t x, uint_t y) {
            this->x = x;
            this->y = y;
            this->data = data;
            this->next = nullptr;
        }
        inline bool hasNext() { return(this->next != nullptr); }
    };

    // Dimensioni della matrice
    uint_t maxX;
    uint_t maxY; // Linear size x*y

    // Testa della lista linkata sottostante
    SMNode* head;

public:

    // Costruttore
    SparseMatrix(uint_t maxX, uint_t maxY) {
        this->head = nullptr;
        this->maxX = maxX;
        this->maxY = maxY;
    }

    /*
    * Metodi
    */

    // add(elem, i, j)
    // Aggiunge un elemento elem in posizione i,j
    // Sovrascrive se già presente
    void add(T elem, uint_t i, uint_t j) {
        // oob check
        if(i > this->maxX || j > this->maxY) {
            throw EXC_INDEX_BOUNDS; // TODO gestione eccezioni
        }
        SMNode newNode(elem, i, j);
        // emptycheck
        if(this->head == nullptr) {
            this->head = &newNode;
        }
        SMNode* curNodePtr = this->head;
        // row select
        while(curNodePtr->hasNext() && curNodePtr->next->x < i) {
                curNodePtr = curNodePtr->next;
        }
        // col select
        while(
            curNodePtr->hasNext() &&
            curNodePtr->next->x == i &&
            curNodePtr->next->y < j
            ) {
                curNodePtr = curNodePtr->next;
        }
        // Debug outcome check
        std::cout << "Aggiungo: <" << i << "," << j << "> in posizione <" << curNodePtr->x << "," << curNodePtr->y << ">" << std::endl;

    }

};