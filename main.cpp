#include "matrix_lib.h"

#include <iostream>

using namespace std;

int main() {
	Matrix<size_t, 0> matrix;

	for (size_t i = 0; i < 10; ++i) {
		matrix[i][i] = i;
		matrix[i][9 - i] = 9 - i;
	}

	for (size_t i = 1; i < 9; ++i) {
		cout << matrix[i][1];
		for (size_t j = 2; j < 9; ++j) {
			cout << " " << matrix[i][j];
		}
		cout << endl;
	}

	cout << matrix.size() << endl;

	for (const auto& m : matrix) {
		int x;
		int y;
		int v;
		std::tie(x, y, v) = m;
		std::cout << x << y << v << std::endl;
	}

	return 0;
}
