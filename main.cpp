#include <limits>
#include "sparse.hpp"

int main() {

	SparseMatrix<int> sparseMatrixA (5, 5, 40);
	sparseMatrixA.add(5, 1, 3);
	sparseMatrixA.add(3, 1, 4);
	sparseMatrixA.add(2, 1, 3);
	std::cout << sparseMatrixA.getByPosition(1, 3) << std::endl;
	return 0;

}

