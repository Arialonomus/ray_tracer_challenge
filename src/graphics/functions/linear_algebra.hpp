#pragma once

#include <vector>
#include <span>

namespace gfx {
    /* Flattened Matrix Operations */

    // Returns a flattened square matrix of dimension n-1 calculated from a span representing a
    // matrix with dimension n with the specified row and column removed
    [[nodiscard]] std::vector<double> getSubmatrix(std::span<const double> matrix_values,
                                                   size_t row_to_remove,
                                                   size_t col_to_remove);

    // Recursively calculates the determinant of any square matrix from a span representing
    // their values stored in flattened, row-major order
    [[nodiscard]] double calculateDeterminant(std::span<const double> matrix_values);

    // Recursively calculates the inverse of any square matrix from a span representing
    // their values stored in flattened, row-major order
    [[nodiscard]] std::vector<double> calculateInverse(std::span<const double> matrix_values, double determinant);
}