#include "linear_algebra.hpp"

#include "cmath"

namespace gfx{
    std::vector<float> getSubmatrix(const std::vector<float>& matrix_values,
                                    size_t row_to_remove,
                                    size_t col_to_remove)
    {
        const size_t matrix_dimension{ static_cast<size_t>(std::sqrt(matrix_values.size())) };
        const size_t submatrix_dimension{ matrix_dimension - 1 };
        std::vector<float> submatrix_values(submatrix_dimension * submatrix_dimension);

        for (int row = 0; row < submatrix_dimension; ++row)
            for (int col = 0; col < submatrix_dimension; ++col) {
                submatrix_values[row * submatrix_dimension + col] =
                        matrix_values[(row + (row >= row_to_remove ? 1 : 0)) * matrix_dimension +
                        (col + (col >= col_to_remove ? 1 : 0))];
            }

        return submatrix_values;
    }
}