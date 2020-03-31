#ifndef BST_HPP
#define BST_HPP

#include <stdexcept>
#include <ostream>

#ifdef DEBUG
#include <iostream>
#include <cassert>
#endif

/**
 * @brief Rappresenta un albero binario di ricerca
 *
 * @tparam T Tipo di dato contenuto dall'albero
 *
 */
template <typename T> class BinarySearchTree {

private:

    /**
     * @brief Rappresenta un nodo dell'albero binario
     *
     */
    struct Node {

        Node* left;
        Node* right;
        T data;

        /**
         * @brief Costruisce un nodo dato il contenuto
         *
         * @param data Il contenuto del nodo
         */
        Node(const T &data) {
            this->left = nullptr;
            this->right = nullptr;
            this->data = data;
        }

        /**
         * @brief Distrugge il nodo
         *
         */
        ~Node() {
            this->left = nullptr;
            this->right = nullptr;
        }

    }; // endstruct Node

    /**
     * @brief direzione del ramo
     *
     */
    enum direction {
        none = -1,
        left,
        right
    };

    Node* root;
    uint size;

    Node* createNode(T data) {
        try {
            return new Node(data);
        } catch(...) {
            r_destroyTree(this->root);
            throw std::runtime_error("createNode(): impossibile creare un nodo");
        }
    }

    /**
     * @brief trova il prossimo puntatore dato un nodo
     *
     * @param curNode il nodo di partenza
     * @param data il dato da inserire
     * @param lastBranch annotazione riguardo all'ultima direzione presa
     *
     * @return Node* il puntatore in cui inserire il nodo
     *
     * @throw std::out_of_range{} nel caso di accesso ad una foglia vuota
     * @throw std::invalid_argument{} nel caso di dato duplicato
     */
    Node* nextPlace(Node* curNode, T data, direction* lastBranch) {
        if(curNode == nullptr) {
            r_destroyTree(this->root);
            throw std::out_of_range("nextPlace(): accesso ad un nodo nullo: possibile albero non inizializzato");
        }
        if(curNode->data > data) {
            *lastBranch = direction::left;
            #ifdef DEBUG
            std::cout << "nextPlace(): " << curNode->data << " is curNode->data. We are going LEFT!" << std::endl;
            #endif
            return(curNode->left);
        } else if(curNode->data < data) {
            *lastBranch = direction::right;
            #ifdef DEBUG
            std::cout << "nextPlace(): " << curNode->data << " is curNode->data. We are going RIGHT!" << std::endl;
            #endif
            return(curNode->right);
        } else {
            r_destroyTree(this->root);
            throw std::invalid_argument("nextPlace(): tentativo di inserimento di un dato duplicato");
        }
    }

    /* WALK-TREE DF proto
    void r_walkTree(Node *curNode) {
        if(curNode != nullptr) {
            r_walkTree(curNode->left);
            r_walkTree(curNode->right);
        }
    }
    */

    void r_destroyTree(Node* curNode) {
        if(curNode != nullptr) {
            std::cout << "r_destroyTree(): destroying node " << curNode->data << "." << std::endl;
            r_destroyTree(curNode->left);
            r_destroyTree(curNode->right);
            delete curNode;
            curNode = nullptr;
        }
        #ifdef DEBUG
        else {
            std::cout << "r_destroyTree(): node is NULL! Exiting." << std::endl;
        }
        #endif
    }

    void r_printTree(Node* curNode, Node* parentNode = nullptr, direction lastBranch = direction::none) {
        if(curNode == nullptr) return;
        if(lastBranch != direction::none && parentNode == nullptr) {
            r_destroyTree(this->root);
            throw std::out_of_range("r_printTree(): accesso ad un nodo nullo con direzione nulla: possibile albero non inizializzato");
        }
        switch(lastBranch) {
            case direction::none:
                break;
            case direction::left:
                std::cout << parentNode->data << " -- l --> " << curNode->data << ";" << std::endl;
                break;
            case direction::right:
                std::cout << parentNode->data << " -- r --> " << curNode->data << ";" << std::endl;
                break;
            default:
                r_destroyTree(this->root);
                throw std::logic_error("r_printTree(): valore logico non consentito");
                break;
        }
        r_printTree(curNode->left, curNode, direction::left);
        r_printTree(curNode->right, curNode, direction::right);
    }

    bool r_findNode(Node* curNode, T data) {
        if(curNode != nullptr) {
            if(curNode->data == data) {
                return true;
            } else if(curNode->data > data) {
                return r_findNode(curNode->left, data);
            } else if(curNode->data < data) {
                return r_findNode(curNode->right, data);
            } else {
                r_destroyTree(this->root);
                std::logic_error("r_findNode(): valore logico non consentito");
            }
        }
        return false;
    }

public:

    BinarySearchTree(T data) {
        this->root = createNode(data);
        this->size = 0;
    };

    ~BinarySearchTree() {
        this->destroy();
    };

    void add(T data) {
        Node* curNode = this->root;
        Node* tmpNodePtr;
        direction lastBranch;
        while((tmpNodePtr = nextPlace(curNode, data, &lastBranch)) != nullptr) {
            curNode = tmpNodePtr;
        }
        switch(lastBranch) {
            case direction::left:
                curNode->left = createNode(data);
                break;
            case direction::right:
                curNode->right = createNode(data);
                break;
            default:
                r_destroyTree(this->root);
                throw std::logic_error("add(): valore logico non consentito");
                break;
        }
        this->size++;
    }

    uint getSize() {
        return this->size;
    }

    bool exists(T data) {
        return r_findNode(this->root, data);
    }

    /**
     * @brief stampa l'albero (sintassi compatibile con Mermaid)
     * @brief https://mermaid-js.github.io/mermaid/#/?id=flowchart
     *
     */
    void print() {
        std::cout << "graph TD;" << std::endl;
        r_printTree(this->root);
    }

    void destroy() {
        if(this->root != nullptr) {
            r_destroyTree(this->root);
            #ifdef DEBUG
            std::cout << "~BST(): destroying node ROOT." << std::endl;
            #endif
            this->root = nullptr; // se non lo metto, succedono casini
        }
    }

}; // endclass

#endif