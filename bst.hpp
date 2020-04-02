#ifndef BST_HPP
#define BST_HPP

#include <iostream>
#include "bstexcept.hpp"

/**
 * @brief Rappresenta un albero binario di ricerca
 *
 * @tparam T Tipo di dato contenuto dall'albero
 */
template <typename T> class BST {

private:

    /**
     * @brief Rappresenta un nodo del BST
     */
    struct Node {

        Node* left;
        Node* right;
        Node* parent;
        T data;

        /**
         * @brief Costruisce un nodo dato il contenuto
         *
         * @param data Il contenuto del nodo
         */
        Node(const T &data, Node* parent) {
            this->left = nullptr;
            this->right = nullptr;
            this->parent = parent;
            this->data = data;
        }

        /**
         * @brief Distrugge il nodo
         */
        ~Node() {
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }

        /**
         * @brief Overload dell'operatore << per la stampa di un nodo
         * 
         * @param output Lo stream di output
         * @param node Il nodo da stampare
         */
        friend std::ostream &operator<<(std::ostream &output, const Node& node) {
            output << node.data;
            return output;
        }

    }; // endstruct Node

    /**
     * @brief direzione del ramo
     */
    enum direction {
        left,
        right
    };

    Node* root;
    uint size;

    /**
     * @brief Crea un nuovo nodo
     * 
     * @param data Il dato contenuto nel nodo
     * @param parent Il genitore del nodo
     * @return Node* Un puntatore al nodo creato
     * 
     * @throw node_creation_error{} Nel caso non sia possibile creare il nodo
     */
    Node* createNode(T data, Node* parent = nullptr) {
        try {
            return new Node(data, parent);
        } catch(...) {
            r_destroyTree(this->root);
            throw node_creation_error{};
        }
    }

    /**
     * @brief Trova la direzione corretta dato un nodo e un dato da inserire
     *
     * @param curNode Il nodo di partenza
     * @param data Il dato da inserire
     * @param lastBranch Annotazione riguardo all'ultima direzione presa
     *
     * @return Node* il puntatore in cui inserire il nodo
     *
     * @throw duplicate_data{} nel caso di dato duplicato
     */
    Node* nextBranch(Node* curNode, T data, direction* curBranch) {
        if(curNode->data > data) {
            *curBranch = direction::left;
            return(curNode->left);
        } else if(curNode->data < data) {
            *curBranch = direction::right;
            return(curNode->right);
        } else {
            r_destroyTree(this->root);
            throw duplicate_data{};
        }
    }

    /**
     * @brief Stampa il BST su uno stream a partire dalla radice
     * 
     * @param output Lo stream su cui stampare
     */
    void printTree(std::ostream &output) const {
        if(this->root == nullptr) return; // sanity check
        r_printTree(output, this->root->left, this->root, direction::left);
        r_printTree(output, this->root->right, this->root, direction::right);
    }

    /**
     * @brief Scorre ricorsivamente il BST per stampare tutti i nodi
     * 
     * @param output Lo stream su cui stampare
     * @param curNode Il nodo corrente
     * @param parentNode Il nodo genitore
     * @param lastBranch L'ultimo ramo preso
     */
    void r_printTree(std::ostream &output, Node* curNode, Node* parentNode, direction lastBranch) const {
        if(curNode == nullptr) return;
        if(lastBranch == direction::left) {
            output << *parentNode << " -- l --> " << *curNode << "; ";
        } else if(lastBranch == direction::right) {
            output << *parentNode << " -- r --> " << *curNode << "; ";
        }
        r_printTree(output, curNode->left, curNode, direction::left);
        r_printTree(output, curNode->right, curNode, direction::right);
    }

    /**
     * @brief Scorre ricorsivamente il BST per cercare un nodo
     * 
     * @param curNode Il nodo corrente
     * @param data Il dato da cercare
     * @return true Se il nodo esiste
     * @return false Se il nodo non esiste
     */
    bool r_findNode(Node* curNode, T data) const {
        if(curNode != nullptr) {
            if(curNode->data == data) {
                return true;
            } else if(curNode->data > data) {
                return r_findNode(curNode->left, data);
            } else if(curNode->data < data) {
                return r_findNode(curNode->right, data);
            }
        }
        return false;
    }


    /**
     * @brief Scorre ricorsivamente il BST per distruggerne i nodi
     * 
     * @param curNode Il nodo corrente
     */
    void r_destroyTree(Node* curNode) {
        if(curNode != nullptr) {
            r_destroyTree(curNode->left);
            r_destroyTree(curNode->right);
            delete curNode;
            curNode = nullptr;
        }
    }

public:

    /**
     * @brief Costruttore per il BST
     * 
     * @param data Il dato da inserire nel nodo radice
     */
    explicit BST(T data) {
        this->root = createNode(data);
        this->size = 0;
    };

    /**
     * @brief Distruttore per il BST
     */
    ~BST() {
        this->destroy();
    };

    /**
     * @brief Aggiunge un nodo al BST
     * 
     * @param data Il dato da inserire nel nuovo nodo
     */
    void add(T data) {
        Node* curNode = this->root;
        Node* tmpNodePtr;
        direction lastBranch;
        while((tmpNodePtr = nextBranch(curNode, data, &lastBranch)) != nullptr) {
            curNode = tmpNodePtr;
        }
        switch(lastBranch) {
            case direction::left:
                curNode->left = createNode(data, curNode);
                break;
            case direction::right:
                curNode->right = createNode(data, curNode);
                break;
            default:
                r_destroyTree(this->root);
                throw std::logic_error("add(): valore logico non consentito");
                break;
        }
        this->size++;
    }

    /**
     * @brief Restituisce la dimensione del BST
     */
    uint getSize() const {
        return this->size;
    }

    /**
     * @brief Trova un nodo nel BST
     * 
     * @param data Il dato da cercare
     * @return true Se il nodo esiste
     * @return false Se il nodo non esiste
     */
    bool exists(T data) const {
        return r_findNode(this->root, data);
    }

    /**
     * @brief Stampa l'albero (sintassi compatibile con Mermaidhttps://mermaid-js.github.io/mermaid/#/?id=flowchart
     */
    void print() const {
        std::cout << *this << std::endl;   
    }

    /**
     * @brief Overload dell'operatore << per la stampa su uno stream
     * 
     * @param output Lo stream di output
     * @param bst L'albero da stampare
     */
    friend std::ostream& operator<<(std::ostream& output, const BST& bst) {
        output << "graph TD; ";
        bst.printTree(output);
        return output;
    }

    /**
     * @brief Distrugge il BST a partire dalla radice
     */
    void destroy() {
        if(this->root != nullptr) {
            r_destroyTree(this->root);
            this->root = nullptr; // se non lo metto, succedono casini
        }
    }

}; // endclass BST

#endif