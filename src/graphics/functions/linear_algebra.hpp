#pragma once

#include <vector>

namespace gfx {
    /* Flattened Matrix Operations */

    // Returns a flattened square matrix of dimension n-1 calculated from a matrix with dimension n
    // with the specified row and column removed
    [[nodiscard]] std::vector<double> getSubmatrix(const std::vector<double>& matrix_values,
                                                  size_t row_to_remove,
                                                  size_t col_to_remove);

    // Recursively calculates the determinant of any square matrix from a vector representing
    // their values stored in flattened, row-major order
    [[nodiscard]] double calculateDeterminant(const std::vector<double>& matrix_values);
}