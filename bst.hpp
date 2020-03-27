#ifndef BST_HPP
#define BST_HPP

#include <iostream>

class AccessViolationException: public std::exception {
    virtual const char* what() const throw() {
        return "BST_301: E' stato effettuato un accesso illegale";
    }
};

class DuplicateDataException: public std::exception {
    virtual const char* what() const throw() {
        return "BST_201: E' stato inserito un dato duplicato.";
    }
};

class VoidContentException: public std::exception {
    virtual const char* what() const throw() {
        return "BST_202: E' stato inserito un dato nullo.";
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

        Node* parent;
        Node* left;
        Node* right;
        T data;

        /**
         * @brief Costruisce un nodo dato il contenuto e imposta il genitore al
         * @brief puntatore nullo
         *
         * @param data Il contenuto del nodo
         */
        Node(Node* parent, const T &data) {
            this->parent = parent;
            this->left = nullptr;
            this->right = nullptr;
            this->data = data;
        }

        /**
         * @brief Costruisce un nodo dato il contenuto e imposta il genitore al
         * @brief puntatore nullo
         *
         * @param data Il contenuto del nodo
         * 
         */
        Node(const T &data) {
            this->parent = nullptr; // Parent vuoto
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
            this->parent = nullptr;
        }

    }; // endstruct

    enum direction {
        left,
        right
    };

    Node* root;
    unsigned int size;

    Node* nextPlace(Node* curNode, T data, direction* lastBranch) {
        //std::raise(SIGINT);
        if(curNode == nullptr) {
            throw AccessViolationException{};
        }
        if(curNode->data > data) {
            *lastBranch = direction::left;
            printf("l,");
            return(curNode->left);
        } else if(curNode->data < data) {
            *lastBranch = direction::right;
            printf("r,");
            return(curNode->right);
        } else {
            throw DuplicateDataException{};
        }
    }

    void debugPrintNodeInfo(Node* curNode) {
        printf("\nCurrent Node:\n");
        printf("Addr:\t%i\n", curNode);
        printf("Data:\t%d\n", curNode->data);
        printf("Left:\t%i\n", curNode->left);
        printf("Rite:\t%i\n", curNode->right);
    }

    void r_destroyNode(Node *curNode) {
        if(curNode != nullptr) {
            r_destroyNode(curNode->left);
            r_destroyNode(curNode->right);
            delete curNode;
            curNode = nullptr;
        }
    }

public:

    BinarySearchTree(T data) {
        this->root = new Node(data);
    };

    ~BinarySearchTree() {
        r_destroyNode(this->root);
        this->root = nullptr;
    };

    void add(T data) {
        printf("\nadd()::data:%i\n\nSteps: ", data);
        Node* curNode = this->root;
        Node* tmpNodePtr;
        direction lastBranch;
        while((tmpNodePtr = nextPlace(curNode, data, &lastBranch)) != nullptr) {
            curNode = tmpNodePtr;
        }
        printf("\n");
        if(lastBranch == direction::left) {
            curNode->left = new Node(curNode, data);
            //debugPrintNodeInfo(curNode->left);
        } else {
            curNode->right = new Node(curNode, data);
            //debugPrintNodeInfo(curNode->right);
        }
    }

    void print() {
        
    }

}; // endclass

#endif