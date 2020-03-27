#ifndef BST_HPP
#define BST_HPP

#define BST_ROOT_NODE nullptr
#include <iostream>
#include <csignal>

class DuplicateDataException: public std::exception {
    virtual const char* what() const throw() {
        return "Inserimento duplicato";
    }
};

class AccessViolationException: public std::exception {
    virtual const char* what() const throw() {
        return "Violazione di accesso";
    }
};

template <typename T> class BinarySearchTree {

private:

    struct Node {

        Node* parent;
        Node* left;
        Node* right;
        T data;

        Node(Node* parent, const T &data) {
            this->parent = parent;
            this->left = nullptr;
            this->right = nullptr;
            this->data = data;
        }

        Node(const T &data) {
            this->parent = BST_ROOT_NODE;
            this->left = nullptr;
            this->right = nullptr;
            this->data = data;
        }

        ~Node() {
            this->parent = nullptr;
            this->left = nullptr;
            this->right = nullptr;
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

public:

    BinarySearchTree(T data) {
        this->root = new Node(data);
    };

    ~BinarySearchTree() {
        // TODO: implement
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