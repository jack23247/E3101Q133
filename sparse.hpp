#define EXC_INDEX_BOUND 0x01

typedef unsigned int T_UInt;

template <class T> class SparseMatrix {

    /*
     * Parametri
     */
private:
    struct T_SM_Node {
        T_UInt x, y;
        T_SM_Node* next;
        T data;
    };
    T_UInt maxX, maxY;
    T_SM_Node* head;

    /*
     * Costruttore
     */
public:
    SparseMatrix(T_UInt maxX, T_UInt maxY) {
        this.head = T_SM_Node;
    }

    void add(T elem, T_UInt i, T_UInt j) {
        T_SM_Node curPtr = head;
        // oob check
        if(i > maxX || j > maxY) {
            throw EX_INDEX_OUT_OF_RANGE
        }
        // row check
        do {
            if(head->next->x < i || head->next->y < j) {
                if(head->x == i) {

                }
            }
        } while(T.next != nullptr);

    }

private:
    T_SM_Node seek(unsigned in) {

    }

    T_SM_Node* getPrevElemPtr(T_UInt i, T_UInt j) {
        T_UInt rowIndex, colIndex = 0;
        T_SM_Node* curNodePtr = this.head;
        T_SM_Node* retNodePtr = nullptr;
        do {
            if(curNodePtr->next == nullptr || curNodePtr->next->x < i) break;
        } while(curNodePtr = curNodePtr->next);
        do {
            if(curNodePtr->next == nullptr) return rowIndex;
            if(curNodePtr->next->x < i) return rowIndex;
        } while(curNodePtr = curNodePtr->next);
    }


};