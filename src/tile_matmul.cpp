/**
 * 2D Matrix Tiling Multiplication
 * 
 * This program performs matrix multiplication using a tiling optimization 
 * technique to improve cache utilization. Tiling breaks down larger matrices 
 * into smaller submatrices or tiles, allowing for efficient multiplication.
 *
 * Author: [F.C. Akhi]
 * Date: [7 Oct, 2023]
 */



#include <iostream>
#include <stdio.h>
#include <vector>


/**
 * Performs matrix multiplication using tiling optimization.
 * 
 * 
 * @param mat_a_vec: First input matrix of dimensions (a_mat_rows x a_mat_cols)
 * @param mat_b_vec: Second input matrix, should have dimensions compatible for multiplication with mat_a_vec
 * @param mat_res_vec: Resultant matrix to store multiplication results
 * @param tile_size: Size of the tile (submatrix) used in tiling optimization
 * @param a_mat_rows: Number of rows in the first matrix
 * @param a_mat_cols: Number of columns in the first matrix
 * @param b_mat_cols: Number of columns in the second matrix
 * @return: true if multiplication succeeds, false otherwise
 */
bool tiled_matrix_mult(const std::vector<std::vector<float>>& mat_a_vec, 
                       const std::vector<std::vector<float>>& mat_b_vec, 
                       std::vector<std::vector<float>>& mat_res_vec, 
                       unsigned int tile_size, 
                       unsigned int a_mat_rows, 
                       unsigned int a_mat_cols, 
                       unsigned int b_mat_cols) {

    // Ensure the inner dimensions of matrices are compatible for multiplication.
    if (a_mat_cols != mat_b_vec.size()) {
        printf("Matrix dimensions do not match for multiplication. Exiting.\n");
        return false;
    }

    // Loop through the tiles of the matrices
    for (unsigned int i = 0; i < a_mat_rows; i += tile_size){
        for (unsigned int j = 0; j < b_mat_cols; j += tile_size) {
            for (unsigned int k = 0; k < a_mat_cols; k += tile_size) {

                // Multiply the current tile of mat_a_vec with the current tile of mat_b_vec
                for (unsigned int x = i; x < std::min(i + tile_size, a_mat_rows); ++x) {
                    for (unsigned int y = j; y < std::min(j + tile_size, b_mat_cols); ++y) {
                        for (unsigned int z = k; z < std::min(k + tile_size, a_mat_cols); ++z) {
                            mat_res_vec[x][y] += mat_a_vec[x][z] * mat_b_vec[z][y];
                        }
                    }
                }
            }
        }
    }

    return true;  // Matrix multiplication completed successfully
}




/**
 * Performs standard (non-tiled) matrix multiplication for two 2D matrices.
 * Computes the product: mat_a_vec(m x a_mat_cols) * mat_b_vec(a_mat_cols x b_mat_cols) = mat_c_vec(m x b_mat_cols).
 * 
 * @param mat_a_vec: First input matrix of dimensions (a_mat_rows x a_mat_cols)
 * @param mat_b_vec: Second input matrix, should have dimensions compatible for multiplication with mat_a_vec
 * @param mat_c_vec: Resultant matrix to store multiplication results
 * @param a_mat_rows: Number of rows in the first matrix
 * @param a_mat_cols: Number of columns in the first matrix
 * @param b_mat_cols: Number of columns in the second matrix
 * @return: true if multiplication succeeds, false otherwise
 */
bool cpu_2d_matrix_mult_baseline(const std::vector<std::vector<float>>& mat_a_vec, 
                                 const std::vector<std::vector<float>>& mat_b_vec, 
                                 std::vector<std::vector<float>>& mat_c_vec, 
                                 unsigned int a_mat_rows, 
                                 unsigned int a_mat_cols, 
                                 unsigned int b_mat_cols) {   

    // Ensure the inner dimensions of matrices are compatible for multiplication.
    if (a_mat_cols != mat_b_vec.size()) {
        printf("Matrix dimensions do not match for multiplication. Exiting.\n");
        return false;  // Incompatible matrix dimensions
    }

    // Standard triple nested loop to compute 2D matrix multiplication
    for (unsigned int i = 0; i < a_mat_rows; i++) {
        for (unsigned int j = 0; j < b_mat_cols; j++) {
            for (unsigned int k = 0; k < a_mat_cols; k++) {
                mat_c_vec[i][j] += mat_a_vec[i][k] * mat_b_vec[k][j];
            }
        }
    }

    return true;  // Matrix multiplication completed successfully
}




/**
 * Compares the results of tiled matrix multiplication with the baseline matrix multiplication
 * to verify correctness. Differences beyond a small epsilon are reported.
 * 
 * @param mat_a_vec: First input matrix of dimensions (a_mat_rows x a_mat_cols)
 * @param mat_b_vec: Second input matrix, should have dimensions compatible for multiplication with mat_a_vec
 * @param mat_res_vec: Resultant matrix from tiled matrix multiplication
 * @param a_mat_rows: Number of rows in the first matrix
 * @param a_mat_cols: Number of columns in the first matrix
 * @param b_mat_cols: Number of columns in the second matrix
 */
void unit_testing(const std::vector<std::vector<float>>& mat_a_vec, 
                  const std::vector<std::vector<float>>& mat_b_vec, 
                  const std::vector<std::vector<float>>& mat_res_vec, 
                  unsigned int a_mat_rows, 
                  unsigned int a_mat_cols, 
                  unsigned int b_mat_cols) {

    // Tolerance level for floating-point comparison
    const float epsilon = 1e-6f;
    
    // Create a matrix to store results from the baseline multiplication
    std::vector<std::vector<float>> mat_c_vec(a_mat_rows, std::vector<float>(b_mat_cols, 0.0f));

    // Perform baseline matrix multiplication
    if (!cpu_2d_matrix_mult_baseline(mat_a_vec, mat_b_vec, mat_c_vec, a_mat_rows, a_mat_cols, b_mat_cols)) {
        printf("Error during baseline matrix multiplication in unit testing.\n");
        return;
    }

    // Compare results from tiled multiplication with baseline
    // Report any discrepancies beyond the tolerance level
    for (unsigned int i = 0; i < a_mat_rows; i++) {
        for (unsigned int j = 0; j < b_mat_cols; j++) {
            if (std::abs(mat_res_vec[i][j] - mat_c_vec[i][j]) > epsilon) {
                printf("Mismatch at i: %d, j: %d\n", i, j);
            }
        }
    }
}




/**
 * Displays the elements of the provided matrix in a formatted manner.
 * Each element is printed with one decimal point precision, followed by two spaces.
 * 
 * @param mat_res_vec: The matrix whose elements are to be printed.
 * @param a_mat_rows: Number of rows in the matrix.
 * @param b_mat_cols: Number of columns in the matrix.
 */
void result_print(const std::vector<std::vector<float>>& mat_res_vec, 
                  unsigned int a_mat_rows, 
                  unsigned int b_mat_cols) {

    // Loop over each element in the matrix and print it
    for (unsigned int i = 0; i < a_mat_rows; i++) {
        for (unsigned int j = 0; j < b_mat_cols; j++) {
            printf("%0.1f  ", mat_res_vec[i][j]);
        }
        printf("\n");  // Move to the next line after printing a row
    }
}




int main() {


    // =========Get matrix dimensions from user=========
    printf("Enter dimensions for matrix A (rows cols): ");
    unsigned int a_mat_rows, a_mat_cols;
    std::cin >> a_mat_rows >> a_mat_cols;

    printf("Enter dimensions for matrix B (rows cols): ");
    unsigned int b_mat_rows, b_mat_cols;
    std::cin >> b_mat_rows >> b_mat_cols;

    // =========Check for compatible matrix dimensions=========
    if (a_mat_cols != b_mat_rows) {
        printf("Matrix dimensions do not match for multiplication. Exiting.\n");
        return 1;
    }

    // =========Get tile size=========
    printf("Enter the tile size: ");
    unsigned int tile_size;
    std::cin >> tile_size;




    // =========Initialize matrices=========
    std::vector<std::vector<float>> mat_a_vec(a_mat_rows, std::vector<float>(a_mat_cols));
    std::vector<std::vector<float>> mat_b_vec(b_mat_rows, std::vector<float>(b_mat_cols));
    std::vector<std::vector<float>> mat_res_vec(a_mat_rows, std::vector<float>(b_mat_cols, 0.0f));

    // =========Get matrix values=========
    printf("Enter values for matrix A:\n");
    for (unsigned int i = 0; i < a_mat_rows; i++)
        for (unsigned int j = 0; j < a_mat_cols; j++)
            std::cin >> mat_a_vec[i][j];

    printf("Enter values for matrix B:\n");
    for (unsigned int i = 0; i < b_mat_rows; i++)
        for (unsigned int j = 0; j < b_mat_cols; j++)
            std::cin >> mat_b_vec[i][j];




    // =========Perform tiled multiplication=========
    if (!tiled_matrix_mult(mat_a_vec, mat_b_vec, mat_res_vec, tile_size, a_mat_rows, a_mat_cols, b_mat_cols)) {
        return 1;
    }

    // =========Verify results against baseline=========
    unit_testing(mat_a_vec, mat_b_vec, mat_res_vec, a_mat_rows, a_mat_cols, b_mat_cols);

    // =========Display results=========
    result_print(mat_res_vec, a_mat_rows, b_mat_cols);
    return 0;
}

