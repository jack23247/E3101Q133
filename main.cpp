#include <limits>
#include "sparse.hpp"

int main() {

    SparseMatrix<char> sparseMatrixA (5, 5);
    sparseMatrixA.add('a', 1, 7);
	return 0;
}

