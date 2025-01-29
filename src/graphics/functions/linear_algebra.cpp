#include "linear_algebra.hpp"

#include "cmath"

namespace gfx{
    std::vector<double> getSubmatrix(const std::vector<double>& matrix_values,
                                    size_t row_to_remove,
                                    size_t col_to_remove)
    {
        const size_t matrix_dimension{ static_cast<size_t>(std::sqrt(matrix_values.size())) };
        const size_t submatrix_dimension{ matrix_dimension - 1 };
        std::vector<double> submatrix_values(submatrix_dimension * submatrix_dimension);

        for (int row = 0; row < submatrix_dimension; ++row)
            for (int col = 0; col < submatrix_dimension; ++col) {
                submatrix_values[row * submatrix_dimension + col] =
                        matrix_values[(row + (row >= row_to_remove ? 1 : 0)) * matrix_dimension +
                        (col + (col >= col_to_remove ? 1 : 0))];
            }

        return submatrix_values;
    }

    double calculateDeterminant(const std::vector<double>& matrix_values)
    {
        const size_t matrix_dimension{ static_cast<size_t>(std::sqrt(matrix_values.size())) };

        // Base Case: 2x2 Matrix
        if (matrix_dimension == 2) {
            return matrix_values[0] * matrix_values[3] - matrix_values[1] * matrix_values[2];
        }

        // Recursive Case: Calculate the determinant of the submatrix
        else {
            double determinant = 0;
            for (int col = 0; col < matrix_dimension; ++col) {
                const double minor = calculateDeterminant(getSubmatrix(matrix_values, 0, col));
                determinant += matrix_values[col] * (0 + col % 2 == 0 ? minor : -minor);
            }
            return determinant;
        }
    }
}