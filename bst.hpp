#ifndef BST_HPP
#define BST_HPP

#include <iostream>

#ifdef DEBUG
#include <cassert>
#endif

/**
 * @brief Accesso illegale impedito.
 *
 */
class Trap_Mem01: public std::exception {
    virtual const char* what() const throw() {
        return "Trap_Mem01 !! Accesso illegale impedito.";
    }
};

/**
 * @brief Eccezione generata durante la creazione di un nodo.
 *
 */
class Trap_Mem02: public std::exception {
    virtual const char* what() const throw() {
        return "Trap_Mem02 !! Eccezione generata durante la creazione di un nodo.";
    }
};

/**
 * @brief Inserimento di un dato duplicato impedito.
 *
 */
class Trap_Log01: public std::exception {
    virtual const char* what() const throw() {
        return "Trap_Log01 !! Inserimento di un dato duplicato impedito.";
    }
};

/**
 * @brief Inserimento di un dato nullo.
 *
 */
class Trap_Log02: public std::exception {
    virtual const char* what() const throw() {
        return "Trap_Log02 !! Inserimento di un dato nullo impedito.";
    }
};

/**
 * @brief Errore generale.
 *
 */
class Trap_Gen99: public std::exception {
    virtual const char* what() const throw() {
        return "Trap_Gen99 !! Errore generale.";
    }
};

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
    //unsigned int size;

    Node* createNode(T data) {
        Node* ret;
        try {
            ret = new Node(data);
        } catch(...) {
            r_destroyTree(this->root);
            throw Trap_Mem02{};
        }
        return ret;
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
     * @throw Trap_Mem01{}
     * @throw Trap_Log01{}
     */
    Node* nextPlace(Node* curNode, T data, direction* lastBranch) {
        if(curNode == nullptr) {
            r_destroyTree(this->root);
            throw Trap_Mem01{};
        }
        if(curNode->data > data) {
            *lastBranch = direction::left;
            std::cout << "nextPlace(): " << curNode->data << " is curNode->data. We are going LEFT!" << std::endl;
            return(curNode->left);
        } else if(curNode->data < data) {
            *lastBranch = direction::right;
            std::cout << "nextPlace(): " << curNode->data << " is curNode->data. We are going RIGHT!" << std::endl;
            return(curNode->right);
        } else {
            r_destroyTree(this->root);
            throw Trap_Log01{};
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
        } else {
            std::cout << "r_destroyTree(): node is NULL! Exiting." << std::endl;
        }
    }

    void r_printTree(Node* curNode, Node* parentNode = nullptr, direction lastBranch = direction::none) {
        if(curNode == nullptr) return;
        if(lastBranch != direction::none && parentNode == nullptr) {
            r_destroyTree(this->root);
            throw Trap_Mem01{};
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
                throw Trap_Gen99{};
                break;
        }
        r_printTree(curNode->left, curNode, direction::left);
        r_printTree(curNode->right, curNode, direction::right);
    }

public:

    BinarySearchTree(T data) {
        this->root = createNode(data);
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
                throw Trap_Gen99{};
                break;
        }
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