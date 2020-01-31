#ifdef _WIN32
// #pragma once // Non posso usare sia pragma once che define SPARSE_HPP sadly
#define VC_EXTRALEAN
#endif

#ifndef SPARSE_HPP
#define SPARSE_HPP

<<<<<<< HEAD
#include <limits> // Definisce UINT_MAX
=======

#include <limits> ///< Definisce UINT_MAX
>>>>>>> 388031aa18faa0b34fe9a3e001d3caed27ae15fd
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
 *
 * @brief Matrice Sparsa
 *
 * @param T tipo del dato
 */
template <class T> class SparseMatrix {

private:

<<<<<<< HEAD
    /** \struct SMNode
     * Nodo della lista tramite cui la matrice è implementata.
     */
    struct SMNode {
        uint_t x, y;
        SMNode* next;
        T data;

        SMNode(T data, uint_t x, uint_t y) {
            this->x = x;
            this->y = y;
            this->data = data;
            this->next = nullptr;
        }

        ~SMNode(void) {
            /** TODO: T potrebbe essere una classe, chiamare il distruttore di T se esiste */
            this->next = nullptr;
        }

        inline bool hasNext() { return(this->next != nullptr); }

        /** TODO: implementare una struct della forma struct element{
        *           posx;
        *           posy;
        *           value;
        *       };
        * @jack23247 IMHO annidiamo troppo
=======
	/** \struct SMNode
	 * Nodo della lista tramite cui la matrice è implementata.
	 */
	struct SMNode {
		uint_t x, y;
		SMNode* next;
		T data;

		SMNode(T data, uint_t x, uint_t y) {
			this->x = x;
			this->y = y;
			this->data = data;
			this->next = nullptr;
		}

		~SMNode(void) {
			this->next = nullptr;
		}

		inline bool hasNext() { return(this->next != nullptr); }

		/** TODO: implementare una struct della forma struct element{
		*           posx;
		*           posy;
		*           value;
		*       };
		* @jack23247 IMHO annidiamo troppo
>>>>>>> 8218d65e162b5c261dee86cb9089008fe0e9ff78
		* @sgro Allora dobbiamo generarla nel return? oppure creiamo una classe
		* esterna?
		*/
	};

<<<<<<< HEAD
    // Spazio utilizzato
    uint_t size; /** TODO: Refactoring, nome migliore? */

    // Dimensioni della matrice
    uint_t maxX;
    uint_t maxY;
=======
	// Dimensioni della matrice
	uint_t maxX;
	uint_t maxY;
>>>>>>> 8218d65e162b5c261dee86cb9089008fe0e9ff78
	uint_t size;
	T def_elem;
	// Testa della lista linkata sottostante
	SMNode* head;

public:
	/** Costruttore per una matrice X*Y senza elementi
	 *
	 * @param maxX X della matrice
	 * @param maxY Y della matrice
	*/
	SparseMatrix(uint_t maxX, uint_t maxY, const T &def_elem) {
		this->head = nullptr;
		this->size = 0;
		this->maxX = maxX;
		this->maxY = maxY;
		this->def_elem = def_elem;
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
			throw EXC_INDEX_BOUNDS; /** TODO: gestione eccezioni */
		}
		SMNode newNode(elem, i, j);
		// emptycheck
		if(this->head == nullptr) {
			this->head = &newNode;
			this->size +=1;
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
<<<<<<< HEAD
		std::cout << "Aggiungo: <" << i << "," << j << "> in posizione <" << curNodePtr->x << "," << curNodePtr->y << ">" << std::endl;
        /** TODO: inserimento */
=======
		std::cout << "Aggiungo: <" << i << "," << j << "> : " << elem << " in posizione <" << curNodePtr->x << "," << curNodePtr->y << ">" << std::endl;
>>>>>>> 388031aa18faa0b34fe9a3e001d3caed27ae15fd
	}


	T getByPosition(uint_t i, uint_t j) {
		// iteratore che scorre la sparse matrix fino all'indice ij, una volta trovato, returna una struct con l'elemento cercato e le coordinate.
		// in caso l'iteratore arrivi a fine matrice, returna una struct senza indici (o indici -1 -1 ) con l'elemento di default
		return this->def_elem;
	}

	void printSM(SparseMatrix<T> sm);
	// printa su STD::COUT la matrice in ordine, scorrendo per righe.
};

#endif