#include <stdexcept>

class duplicate_data: public std::invalid_argument {

    virtual const char* what() const throw() {
        return "nextPlace(): tentativo di inserimento di un dato duplicato";
    }

};

class node_creation_error: public std::runtime_error {

    virtual const char* what() const throw() {
        return "createNode(): impossibile creare un nodo";
    }
    
};