#pragma once

#include <vector>

namespace gfx {
    /* Flattened Matrix Operations */

    // Returns a flattened square matrix of dimension n-1 calculated from a matrix with dimension n
    // with the specified row and column removed
    [[nodiscard]] std::vector<float> getSubmatrix(const std::vector<float>& matrix_values,
                                                  size_t row_to_remove,
                                                  size_t col_to_remove);
}